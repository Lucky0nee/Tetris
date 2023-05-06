#pragma once

#include "constants.hpp"
#include "Screen.hpp"

class Shape {
public:
	Shape();

	void shapeToField(Screen& scr);
	bool canPlaceShape(Screen& scr, int aditiontXcord = 0, int aditiontYcord = 0);

	void rotateShape(const int countOfRotates, const int TypeOfTheShape, int ColorOfTheShape);

	void setXY(const int _x, const int _y);
	void setShape(const int TypeOfTheShape, int ColorOfTheShape);
	void setShapeTypes(std::vector<const wchar_t*> shapeTypes);

private:
	std::vector<std::vector<wchar_t>> shape;
	std::vector<std::vector<unsigned int>> shapeColor;

	std::vector<const wchar_t*> shape_types;

	COORDS coordinates;
	int rotate;
};

Shape::Shape() {
	std::vector<wchar_t> tempShape;
	for (int i = 0; i < constants::shape_height; i++) {
		shape.push_back(tempShape);

		for (int j = 0; j < constants::shape_width; j++) {
			shape[i].push_back(constants::field_symbol);
		}
	}

	rotate = 0;
	setXY(constants::width / 5, 0);

	std::vector<unsigned int> tempShapeColor;
	for (int i = 0; i < constants::shape_height; i++) {
		shapeColor.push_back(tempShapeColor);

		for (int j = 0; j < constants::shape_width; j++) {
			shapeColor[i].push_back(constants::field_symbol);
		}
	}
}

void Shape::shapeToField(Screen& scr) {
	for (int i = 0; i < constants::shape_height; i++) {
		for (int j = 0; j < constants::shape_width; j++) {
			if (shape[i][j] == constants::shape_symbol) {
				scr.mainField[coordinates.y + i][(coordinates.x + j) * 2] = constants::shape_symbol;
				scr.mainField[coordinates.y + i][(coordinates.x + j) * 2 + 1] = constants::shape_symbol;

				scr.fieldColors[coordinates.y + i][(coordinates.x + j) * 2] = shapeColor[i][j];
				scr.fieldColors[coordinates.y + i][(coordinates.x + j) * 2 + 1] = shapeColor[i][j];
			}
		}
	}
}
bool Shape::canPlaceShape(Screen& scr, int aditiontXcord, int aditiontYcord) {
	for (int i = 0; i < constants::shape_height; i++) {
		for (int j = 0; j < constants::shape_width; j++) {
			if (shape[i][j] == constants::shape_symbol) {
				if (scr.mainField[coordinates.y + i + aditiontYcord][(coordinates.x + j) * 2 + aditiontXcord] == constants::border_symbol ||
					scr.mainField[coordinates.y + i + aditiontYcord][(coordinates.x + j) * 2 + aditiontXcord] == constants::border_symbol2 ||
					scr.mainField[coordinates.y + i + aditiontYcord][(coordinates.x + j) * 2 + aditiontXcord] == constants::shape_symbol2 ||
					scr.mainField[coordinates.y + i + aditiontYcord][(coordinates.x + j) * 2 + 1 + aditiontXcord] == constants::border_symbol ||
					scr.mainField[coordinates.y + i + aditiontYcord][(coordinates.x + j) * 2 + 1 + aditiontXcord] == constants::border_symbol2 ||
					scr.mainField[coordinates.y + i + aditiontYcord][(coordinates.x + j) * 2 + 1 + aditiontXcord] == constants::shape_symbol2)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Shape::rotateShape(const int countOfRotates, const int TypeOfTheShape, int ColorOfTheShape) {
	for (int i = 0; i < countOfRotates; i++) {
		if (rotate == 3) {
			rotate = 0;
		}
		else {
			rotate++;
		}
	}
	setShape(TypeOfTheShape, ColorOfTheShape);
}

void Shape::setXY(const int _x, const int _y) {
	coordinates.x = _x;
	coordinates.y = _y;
}
void Shape::setShape(const int TypeOfTheShape, int ColorOfTheShape) {
	switch (ColorOfTheShape) {
	case 0:
		ColorOfTheShape = RED;
		break;
	case 1:
		ColorOfTheShape = GREEN;
		break;
	case 2:
		ColorOfTheShape = BLUE;
		break;
	case 3:
		ColorOfTheShape = YELLOW;
		break;
	case 4:
		ColorOfTheShape = MAGENTA;
		break;
	case 5:
		ColorOfTheShape = CYAN;
		break;
	}

	int couter = 0;
	for (int i = 0; i < constants::shape_height; i++) {
		for (int j = 0; j < constants::shape_width; j++) {
			switch (rotate) {
			case 0:
				shape[i][j] = shape_types[TypeOfTheShape][couter];
				shapeColor[i][j] = ColorOfTheShape;
				couter++;
				break;
			case 1:
				shape[constants::shape_width - j - 1][i] = shape_types[TypeOfTheShape][couter];
				shapeColor[constants::shape_width - j - 1][i] = ColorOfTheShape;
				couter++;
				break;
			case 2:
				shape[constants::shape_width - i - 1][constants::shape_width - j - 1] = shape_types[TypeOfTheShape][couter];
				shapeColor[constants::shape_width - i - 1][constants::shape_width - j - 1] = ColorOfTheShape;
				couter++;
				break;
			case 3:
				shape[j][constants::shape_width - i - 1] = shape_types[TypeOfTheShape][couter];
				shapeColor[j][constants::shape_width - i - 1] = ColorOfTheShape;
				couter++;
				break;
			}
		}
	}
}
void Shape::setShapeTypes(std::vector<const wchar_t*> shapeTypes) {
	shape_types = shapeTypes;
}