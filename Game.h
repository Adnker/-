#pragma once
#include <iostream>
#include <SDL.h>
#include "Input.h"
#include "Main_Window.h"
#include "Player.h"
#include "Map.h"

class Game {
public:
	int OpenGame();
	int Updata();
	int Shutdown();
	class Input* GetInput() { return input; }
	bool gameIsRun;//��Ϸ�Ƿ����
	int CreatePlay();//Ϊ��ҷ����ڴ�
	int DestroyPlay();//��������ڴ�
	const wchar_t* Getskill_name(int index);//��ȡȫ��������
	const wchar_t* Getskill_flag_sum(int sum);//ת��Ϊ���ܴ�����const wchar_t* ��ʽ
	int Getskill_sum();//��ȡ��������
	const wchar_t* Getskill_jieshao(int index);//��ȡ���ܽ���
private:
	bool isRuning;//�˳���־
	Uint32 mTickCout;//��Ϸʱ��������

	//class
	class Main_Window* main_window;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	class Map* map;
	class Skiller* skiller;
};