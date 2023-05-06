#include <Windows.h>

#pragma comment (lib, "urlmon.lib") // for URLDownloadToFile
#pragma comment(lib, "Winmm.lib") // for PlaySound

int downloadSound() {
    HRESULT hResult = URLDownloadToFileW(NULL, L"https://github.com/Lucky0nee/music/raw/main/TetrisTheme.wav", L"C:\\Windows\\Temp\\TetrisTheme.wav", 0, 0);
    
    // If the file has not been downloaded
    if (hResult != S_OK) {
        return 1;
    }

    return 0;
}

void playSound(bool& gameOver) {
    PlaySoundW(L"C:\\Windows\\Temp\\TetrisTheme.wav", NULL, SND_LOOP | SND_ASYNC);
    while (true) {
        if (gameOver) {
            ExitThread(EXIT_SUCCESS);
        }
    }
}