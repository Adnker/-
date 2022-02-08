#pragma once
#ifndef Main_Window_H
#define Main_Window_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Mouse_Window.h"
#include "myFun.h"
#include "Player.h"
#include "Texture.h"
#include "Button.h"


static SDL_Color WHITE = { 255,255,255,255 };//��ɫ
static SDL_Color BLACK = { 0,0,0,255 };//��ɫ
static SDL_Color RED = { 255,0,0,255 };//��ɫ
static SDL_Color BLUE = { 0,0,255,255 };//��ɫ
static SDL_Color LITTLE_BLACK = { 220,220,220,255 };//��ɫ


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

const int picture_jianju_x = 40;
const int picture_jianju_w = 80;


/*���ڱ��洰����ʾ����Ϣ
* const wchar_t* text ���ڱ�����ʾ������
* SDL_Rect rect ���ڱ�����ʾ������ʾ��λ�ã���ʾλ��x����ʾλ��y�����ڿ�w�����ڸ�h��
* int liveTime ���ڱ��洰���Ѿ���ʾ��ʱ��
* int flag ���ڱ���˭���õ���Ϣ
*/
struct Window_Msg {
	Window_Msg(const wchar_t* text_, SDL_Rect rect_, int flag_) {
		text = text_;
		rect = rect_;
		flag = flag_;
		liveTime = 0;
	}
	const wchar_t* text;
	SDL_Rect rect;
	int liveTime;
	int flag;
};
//������ʾ������ʱ�� ���ڴ�ʱ��Ĵ���Ҫ��������
const int DeadTime = 100;

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
	int Player_Window(const wchar_t* text_, SDL_Rect rect_, int& flag_window_, int flag_);
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
	//�޸���Ҽ���
	void ChangeSkill(int index_);
	//�����µĴ��� �Զ����ٵ�ǰ����
	int CreatNewWindow(SDL_Rect* rect);
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
	//������ʾ
	std::vector<Window_Msg*> window_msg;
	//������
	class Game* game;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	class Texture* texture;
	class Button* button;
	//������
	class Mouse_Window* mouse_window;
	//����
	SDL_Window* window;
	//��ɫ��
	SDL_Renderer* renderer;
	//����
	SDL_Rect rect;
	//�����ھ��� ����ʾλ��x����ʾλ��y����w����h��
	SDL_Rect rect_Main_Window = { 100,100,500,500 };
	//ս�����ھ��� ����ʾλ��x����ʾλ��y����w����h��
	SDL_Rect rect_Fright_Window = { 200, 40, 700, 700 };
	//����
	TTF_Font* font;
	//������ͼ��
	SDL_Surface* surface;
	//���ڱ�־
	//MainWindow = 0 FrightWindow = 1 GameoverWindow = 2 SkillWinodw = 3
	int flagWindow;
	int b_flagWindow;//��һ֡���ڱ�ʶ
	//������ʾ˭���ʤ��
	int flag_Player;
	//���ڼ���ѡ������ҳ������
	int index = 1;
	//����ģʽѡ��
	int model = BaseModel;
};
#endif // !Main_Window_H