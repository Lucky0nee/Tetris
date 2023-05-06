#pragma once 

#include <wtypes.h>
#include <vector>

#define _O_U16TEXT     0x20000 // file mode UTF-16

namespace constants {
	const int width = 28;
	const int height = 28;

	const int shape_width = 4;
	const int shape_height = 4;

	const wchar_t shape_symbol = L'█';
	const wchar_t shape_symbol2 = L'▓';

	const wchar_t border_symbol = L'|';
	const wchar_t border_symbol2 = L'═';

	const wchar_t field_symbol = L'.';

	const size_t shape_types_count = 7;
	const size_t colors_types_count = 6;

	const HWND hWnd = GetConsoleWindow();

	const std::vector<const wchar_t*> shape_types = { // "T", "Q", "I", "Z", "S", "J", "L".
		L"    "
		L" ███"
		L"  █ "
		L"    ",

		L"    "
		L" ██ "
		L" ██ "
		L"    ",

		L"   █"
		L"   █"
		L"   █"
		L"   █",

		L"    "
		L"    "
		L" ██ "
		L"  ██",

		L"    "
		L"    "
		L" ██ "
		L"██  ",

		L"   █"
		L"   █"
		L"   █"
		L"  ██",

		L"█   "
		L"█   "
		L"█   "
		L"██  ",
	};
}

enum colors {
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_BLUE,
	YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	// don't count
	WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

struct COORDS {
	int x;
	int y;
};