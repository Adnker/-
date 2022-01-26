#pragma once
#include <iostream>
#include <SDL.h>
#include "Input.h"
#include "Main_Window.h"
#include "Player.h"
#include "Map.h"


#pragma message ("Loading Game...")
class Game {
public:
	int OpenGame();
	int Updata();
	int Shutdown();

	//��Ϸ�Ƿ����
	bool gameIsRun;

	//Ϊ��ҷ����ڴ�
	int CreatePlay();
	int DestroyPlay();
	class Input* GetInput() { return input; }

	//��ȡȫ��������
	const wchar_t* Getskill_name(int index);
	//ת��Ϊ���ܴ�����const wchar_t* ��ʽ
	const wchar_t* Getskill_flag_sum(int sum);
	//��ȡ��������
	int Getskill_sum();
private:
	//�˳���־
	bool isRuning;
	//��Ϸʱ��������
	Uint32 mTickCout;
	//��������
	class Main_Window* main_window;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	class Map* map;
	class Skiller* skiller;
};
#pragma message ("Game is loaded")