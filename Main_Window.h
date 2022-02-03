#pragma once
#ifndef Main_Window_H
#define Main_Window_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Mouse_Window.h"
#include "myMath.h"
#include "Player.h"


//����ֵ
const int All_true = 0;
const int Window_error = 1;
const int Renderer_error = 2;
const int Init_error = 3;
const int TTF_Init_error = 4;
const int TTF_Open_error = 5;

//���ڱ�־
//����ȷ�����ڴ���״̬
//������
const int MainWindow = 0;
//ս������
const int FrightWindow = 1;
//��Ϸ��������
const int GameoverWindow = 2;
//����ѡ�񴰿�
const int SkillWindow = 4;
//ģʽѡ�񴰿�
const int ModelWindow = 5;

//��ͨģʽ
const int BaseModel = 1;
//����ģʽ
const int SkillModel = 2;
//����ģʽ
const int FrightModel = 3;

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
	class Rander* rander;
	//��ʼ��
	int CreatWindow(class Game* game_);
	//����
	int Updata(class Player* red_player_,class Player* blue_player);
	//�ر�
	int Shutdown();

	//��������ʾ����
	//window_time = 0
	int Player_Window(const wchar_t* text_,SDL_Rect rect_,int& flag_window_);
	//��ȡ���ڱ�־
	int GetFlag();
	//��Ϸ����
	int GameIsEnd(int flag_Player);
	//��ȡ��Ϸģʽ
	int GetGameModel();

	//������
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color);
	//���Ʊ߿����
	void DrawRect(int x, int y, int w, int h, SDL_Color* color);
	//����������
	void FillRect(int x, int y, int w, int h, SDL_Color* color);
	//��������
	void DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect);
private:
	//�����µĴ��� �Զ����ٵ�ǰ����
	int CreatNewWindow(const char* title, int x, int y, int w, int h);
	//����ս���Ľ���
	int Draw_FrightWindow();
	//����������
	int Draw_MainWindow();
	//������Ϸ�����Ľ���
	int Draw_GameOverWindow();
	//���Ƽ���ѡ�񴰿�
	int Draw_SkillWindow();
	//����ģʽѡ�����
	int Draw_ModelWindow();
	//��������ж�
	int DrawMove(const vector<struct Move_point*>* move_point,SDL_Color* color_);
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
	//MainWindow = 0 FrightWindow = 1 GameoverWindow = 2 SkillWinodw = 3
	int flagWindow;
	//������ʾ˭���ʤ��
	int flag_Player;
	//���ڼ���ѡ������ҳ������
	int index = 1;
	//����ģʽѡ��
	int model = BaseModel;
};
#pragma message ("Main_Window is loaded")
#endif // !Main_Window_H