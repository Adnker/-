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
#include "Texture.h"

static SDL_Color WHITE = { 255,255,255,255 };//��ɫ
static SDL_Color BLACK = { 0,0,0,255 };//��ɫ
static SDL_Color RED = { 255,0,0,255 };//��ɫ
static SDL_Color BLUE = { 0,0,255,255 };//��ɫ
static SDL_Color LITTLE_BLACK = { 200,200,200,255 };//��ɫ

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
	int Updata(class Player* red_player_, class Player* blue_player);
	//�ر�
	int Shutdown();

	//��������ʾ����
	//window_time = 0
	int Player_Window(const wchar_t* text_, SDL_Rect rect_, int& flag_window_);
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
	//����ͼƬ
	void DrawPicture(const std::string fileName, SDL_Rect* rect1, SDL_Rect rect2);
	//���Ƽ���ͼƬ
	void DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect rect2, int flag_ = true);
private:
	//�����µĴ��� �Զ����ٵ�ǰ����
	int CreatNewWindow(const char* title, SDL_Rect* rect);
	//����������
	int Draw_MainWindow();
	//����ս���Ľ���
	int Draw_FrightWindow();
	//������Ϸ�����Ľ���
	int Draw_GameOverWindow();
	//���Ƽ���ѡ�񴰿�
	int Draw_SkillWindow();
	//����ģʽѡ�����
	int Draw_ModelWindow();
	//��������ж�
	int DrawMove(const vector<struct Move_point*>* move_point, SDL_Color* color_);
	//������ʾ
	std::vector<Window_Msg*> window_msg;
	//������
	class Game* game;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	class Texture* texture;
	//������
	class Mouse_Window* mouse_window;
	//����
	SDL_Window* window;
	//��ɫ��
	SDL_Renderer* renderer;
	//����
	SDL_Rect rect;
	SDL_Rect rect_Main_Window = { 100,100,500,500 };
	SDL_Rect rect_Fright_Window = { 200, 40, 700, 800 };
	SDL_Rect rect_Skill_Window = { 100, 100, 300, 300 };
	SDL_Rect rect_Over_Window = { 300, 300, 200, 200 };
	SDL_Rect rect_Model_Window = { 100,100,500,500 };
	//����
	TTF_Font* font;
	//������ͼ��
	SDL_Surface* surface;
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