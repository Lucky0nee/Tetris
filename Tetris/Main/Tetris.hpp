#pragma once

#include <thread>

#include "constants.hpp"
#include "Screen.hpp"
#include "Shape.hpp"
#include "Music.hpp"

void timer(int& time, bool& gameOver) {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		if (time != 999) {
			time++;
		}

		if (gameOver) {
			ExitThread(EXIT_SUCCESS);
		}
	}
}

class TetrisGame {
public:
	TetrisGame(bool start = false);

	void moveShapeInXCoordinates();
	void moveShapeInYCoordinates();
	void rotateShape(const int TypeOfTheShape, int ColorOfTheShape);

	bool OneLineFilled(int& lineIndex);

	bool gameOver(bool& firstElement);
	void startGame();

private:
	Screen screen;
	Shape shape;

	COORDS coordinates;

	int score;
	int time;

	bool gameIsOver;
};

TetrisGame::TetrisGame(bool start) {
	shape.setShapeTypes(constants::shape_types);

	coordinates.x = constants::width / 4;
	coordinates.y = 0;

	score = 0;
	time = 0;

	gameIsOver = false;

	if (start) {
		system("cls");
		startGame();
	}
}

void TetrisGame::moveShapeInXCoordinates() {
	if (GetAsyncKeyState(0x41) && shape.canPlaceShape(screen, -1, 1)) { // A key - Move left
		coordinates.x--;
	}
	else if (GetAsyncKeyState(0x44) && shape.canPlaceShape(screen, 1, 1)) { // D key - Move right
		coordinates.x++;
	}
}
void TetrisGame::moveShapeInYCoordinates() {
	if (!GetAsyncKeyState(0x53)) { // S key - Move down
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	coordinates.y++;
}
void TetrisGame::rotateShape(const int TypeOfTheShape, int ColorOfTheShape) {
	if (GetAsyncKeyState(0x46)) { // F key - rotate
		shape.rotateShape(1, TypeOfTheShape, ColorOfTheShape);

		if (!shape.canPlaceShape(screen, 0, 0)) {
			shape.rotateShape(3, TypeOfTheShape, ColorOfTheShape);
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

bool TetrisGame::OneLineFilled(int& lineIndex) {
	for (int i = 0; i < constants::height; i++) {
		int counter = 0;
		for (int j = 2; j < constants::width + 2; j++) {
			if (screen.mainField[i][j] == constants::shape_symbol2) {
				counter++;
			}
		}
		if (counter >= constants::width) {
			lineIndex = i;
			return true;
		}
	}
	return false;
}

bool TetrisGame::gameOver(bool& firstElement) {
	if (!shape.canPlaceShape(screen, 0, 1) && firstElement == true) {
		return true;
	}

	firstElement = false;
	return false;
}
void TetrisGame::startGame() {
	std::thread th_timer(timer, std::ref(time), std::ref(gameIsOver));
	std::thread th_playSound(playSound, std::ref(gameIsOver));

	th_timer.detach();
	th_playSound.detach();

Shape—reation:
	const int TypeOfTheShape = rand() % constants::shape_types_count;
	const int ColorOfTheShape = rand() % constants::colors_types_count;

	bool firstElement = true;
	int lineIndex = NULL;

	while (true) {
		screen.clearField();
		moveShapeInXCoordinates();
		moveShapeInYCoordinates();
		shape.setXY(coordinates.x, coordinates.y);
		rotateShape(TypeOfTheShape, ColorOfTheShape);
		shape.setShape(TypeOfTheShape, ColorOfTheShape);
		shape.shapeToField(screen);
		screen.printField(score, 3, time, 6);

		if (gameOver(firstElement)) {
			WCHAR WCharScore = score + 48;

			ShowWindow(constants::hWnd, SW_HIDE);
			MessageBoxW(NULL, L" :c ", L"Game Over", MB_OK);
			MessageBoxW(NULL, &WCharScore, L"Score", MB_OK | MB_ICONINFORMATION);

			gameIsOver = true;
			return;
		}

		if (OneLineFilled(lineIndex)) {
			screen.moveField(lineIndex);

			if (score != 999) {
				score++;
			}
		}

		if (!shape.canPlaceShape(screen, 0, 1)) {
			screen.updateField();
			coordinates.x = constants::width / 5;
			coordinates.y = 0;

			goto Shape—reation;
		}
	}
}