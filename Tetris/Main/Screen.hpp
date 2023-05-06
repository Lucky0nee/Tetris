#pragma once

#include <iostream>

#include "constants.hpp"

class Screen {
public:
	Screen();

	void printField(const int score, const int scoreLine, const int timer, const int timerLine);
	void updateField();
	void clearField();
	void moveField(int lineIndex);

	void hideCursor(const bool hide);

	std::vector<std::vector<wchar_t>> mainField;
	std::vector<std::vector<unsigned int>> fieldColors;
};

Screen::Screen() {
	std::vector<wchar_t> tempfield;
	std::vector<unsigned int> tempColors;

	// field
	for (int i = 0; i < constants::height + 1; i++) {
		mainField.push_back(tempfield);

		// border
		mainField[i].push_back(constants::border_symbol);
		mainField[i].push_back(constants::border_symbol);

		for (int j = 0; j < constants::width; j++) {
			mainField[i].push_back(constants::field_symbol);
		}

		// border
		mainField[i].push_back(constants::border_symbol);
		mainField[i].push_back(constants::border_symbol);
	}

	// border
	for (int i = 2; i < constants::width + 2; i++) {
		mainField[constants::height][i] = constants::border_symbol2;
	}

	// colors
	for (int i = 0; i < constants::height + 1; i++) {
		fieldColors.push_back(tempColors);
		for (int j = 0; j < constants::width + 4; j++) {
			fieldColors[i].push_back(WHITE);
		}
	}

	hideCursor(true);
}

void Screen::printField(const int score, const int scoreLine, const int timer, const int timerLine) {
	// alternative to system(cls);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

	for (int i = 0; i < constants::height + 1; i++) {
		for (int j = 0; j < constants::width + 4; j++) {
			// Change the color of the following characters
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fieldColors[i][j]);
			std::wcout << mainField[i][j];
		}

		// score
		if (i == scoreLine - 1) {
			std::wcout << L"\t┏━━━━━━━━━┓";
		}
		else if (i == scoreLine) {
			std::wcout << L"\t┃" << "Score " << (score > 100 ? L"" : L"0") << ((score > 10) ? L"" : L"0") << score << L"┃";
		}
		else if (i == scoreLine + 1) {
			std::wcout << L"\t┗━━━━━━━━━┛";
		}

		// timer
		if (i == timerLine - 1) {
			std::wcout << L"\t┏━━━━━━━━━┓";
		}
		else if (i == timerLine) {
			std::wcout << L"\t┃" << "Timer " << (timer >= 100 ? L"" : L"0") << ((timer >= 10) ? L"" : L"0") << timer << L"┃";
		}
		else if (i == timerLine + 1) {
			std::wcout << L"\t┗━━━━━━━━━┛";
		}

		std::wcout << L"\n";
	}
}
void Screen::updateField() {
	for (int i = 0; i < constants::height; i++) {
		for (int j = 2; j < constants::width + 2; j++) {
			if (mainField[i][j] == constants::shape_symbol) {
				mainField[i][j] = constants::shape_symbol2;
				fieldColors[i][j] = fieldColors[i][j];
			}
		}
	}
}
void Screen::clearField() {
	for (int i = 0; i < constants::height; i++) {
		for (int j = 2; j < constants::width + 2; j++) {
			if (mainField[i][j] == constants::shape_symbol) {
				mainField[i][j] = constants::field_symbol;
				fieldColors[i][j] = WHITE;
			}
		}
	}
}
void Screen::moveField(int lineIndex) {
	const int constlineIndex = lineIndex + 1;

	for (int i = 1; i < (constlineIndex + constlineIndex) - constants::height; i++) {
		mainField[lineIndex] = mainField[lineIndex - 1];
		fieldColors[lineIndex] = fieldColors[lineIndex - 1];

		lineIndex--;
	}
}

void Screen::hideCursor(const bool hide) {
	CONSOLE_CURSOR_INFO ConsoleCursorInfo = { NULL };
	ConsoleCursorInfo.bVisible = !hide; // true => false
	ConsoleCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursorInfo);
}