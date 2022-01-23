#pragma once
#ifndef Main_Window_H
#define Main_Window_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Mouse_Window.h"


const int All_true = 0;
const int Window_error = 1;
const int Renderer_error = 2;
const int Init_error = 3;
const int TTF_Init_error = 4;
const int TTF_Open_error = 5;

//���ڱ�־
//����ȷ�����ڴ���״̬
const int MainWindow = 0;
const int FrightWindow = 1;
const int GameoverWindow = 2;

//���ص�����
static const char* fontText = "simkai.TTF";
const int fontSize = 25;

//���ڱ��洰����ʾ����Ϣ
struct Window_Msg {
	const wchar_t* text;
	SDL_Rect rect;
	int liveTime;
};

#pragma message ("Loading Main_Window...")
class Main_Window {
public:
	//��ʼ��
	int CreatWindow(class Game* game_, class Player* player_red,
		Player* player_blue);
	//����
	int Updata();
	//�ر�
	int Shutdown();

	//�����ʾ����
	int Player_Window(const wchar_t* text_,SDL_Rect rect_);
	//��ȡ���ڱ�־
	int GetFlag() { return flagWindow; };
	//��Ϸ����
	int GameIsEnd(int flag_Player);

	//������
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color);
	//���ƾ���
	void DrawRect(int x, int y, int w, int h, SDL_Color* color);
	//����������
	void FillRect(int x, int y, int w, int h, SDL_Color* color);
	//��������
	void DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect);
private:
	//�����µĴ���
	int CreatNewWindow(const char* title, int x, int y, int w, int h);
	//����ս���Ľ���
	int Draw_FrightWindow();
	//����������
	int Draw_MainWindow();
	//������Ϸ�����Ľ���
	int Draw_GameOverWindow();
	//������ʾ
	std::vector<Window_Msg*> window_msg;
	//������
	class Game* game;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	//������
	class Mouse_Window* mouse_window;
	//����
	SDL_Window* window;
	//��ɫ��
	SDL_Renderer* renderer;
	//����
	SDL_Rect rect;
	//����
	TTF_Font* font;
	//���ں�����ͼ��
	SDL_Surface* windowSurface;
	//���ڱ�־
	//MainWindow = 0 FrightWindow = 1 GameoverWindow = 2
	int flagWindow;
	//������ʾ˭���ʤ��
	int flag_Player;
};
#pragma message ("Main_Window is loaded")
#endif // !Main_Window_H