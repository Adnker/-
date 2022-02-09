#include "Game.h"
#include <Windows.h>


//SDL2.lib
//SDL2main.lib
//SDL2_ttf.lib
#pragma comment (lib,"SDL2.lib")
#pragma comment (lib,"SDL2main.lib")
#pragma comment (lib,"SDL2_ttf.lib")
#pragma comment (lib,"SDL2_image.lib")

#undef main

int main(){

	//����cmd����
	HWND hwnd = GetForegroundWindow();
	ShowWindow(hwnd, SW_HIDE);

	HANDLE handle;
	handle = CreateMutex(NULL, FALSE, L"Snake");//Releaseģʽ�¼���һ��ʹ�ã�handle = CreateMutex(NULL, FALSE, L"Snake");
	if (GetLastError() != ERROR_ALREADY_EXISTS) {
		class Game game = Game();
		bool isRun = true;
		if (game.OpenGame() > 0) {
			isRun = false;
		}
		if (isRun) {
			game.Updata();
		}
		game.Shutdown();
		//int i; std::cin >> i;
	}
}