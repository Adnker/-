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
	class Input* GetInput() { return &input; }
private:
	//�˳���־
	bool isRuning;
	//��Ϸʱ��������
	Uint32 mTickCout;
	//��������
	class Main_Window main_window;
	//������
	class Input input;
	//�����
	class Player red_player;
	class Player blue_player;
	//��ͼ��
	class Map map;
};
#pragma message ("Game is loaded")