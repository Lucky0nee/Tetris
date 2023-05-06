#include <io.h>

#include "Tetris.hpp"

void changeWindowStyle(HWND hWnd, LONG_PTR style) {
	SetWindowLongW(constants::hWnd, GWL_STYLE, style);
	ShowWindow(constants::hWnd, SW_SHOW);
}

int main() {
	// hiding window
	ShowWindow(constants::hWnd, SW_HIDE);

	// Downloading music
	if (downloadSound() != NULL) {
		MessageBoxW(
			NULL,
			L"Music didn't download, please restart the application\n",
			L"Error",
			MB_OK
		);
		return GetLastError();
	}

	// change encoding to UTF-16
	if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
		MessageBoxW(
			NULL,
			L"Something went wrong, please restart the application\n",
			L"Error",
			MB_OK
		);
		return GetLastError();
	}

	// console resizing
	system("mode con cols=54 lines=32");

	// changing tytle
	SetConsoleTitleW(L"Tetris");

	// changing style && showing window
	changeWindowStyle(constants::hWnd, WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_OVERLAPPED);

	// random shapes && random colors
	srand(time(NULL));

	bool startGame = true;
	int choise;

	while (true) {
		std::wcout << "1.Start the game" << "\n";
		std::wcout << "2.Control" << "\n";
		std::wcout << "3.Info" << "\n";

		std::wcout << "->";
		std::cin >> choise;

	playAgain:
		SetForegroundWindow(constants::hWnd);
		switch (choise) {
		case 1: {
			// start game
			TetrisGame Tetris(startGame);

			// after the end of the game, we offer to play again
			int messageBox = MessageBoxW(
				NULL,
				L"Would you like to play again?",
				L"Tetris",
				MB_YESNO
			);

			// showing the window to see the message box
			ShowWindow(constants::hWnd, SW_SHOW);

			switch (messageBox) {

			case IDYES:
				goto playAgain;

			case IDNO:
				return 0;
			}

			break;
		}
		case 2: {
			MessageBoxW(
				NULL,
				L"A - left\n"
				L"S - down\n"
				L"D - right\n"
				L"F - rotate\n",
				L"Control",
				MB_OK
			);
			break;
		}
		case 3: {
			MessageBoxW(
				NULL,
				L"Creator - Dmitriy\n"
				L"Last update - 03.05.2023\n",
				L"Info",
				MB_OK
			);
			break;
		}
		default:
			std::cin.clear();
			std::cin.ignore();
			system("cls");
			break;
		}

		system("cls");
	}

	return 0;
}