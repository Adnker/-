#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "Input.h"

/*���ڱ��水ť��Ϣ
* const wchar_t* text ���水ť��ʾ������
* TTF_Font* font ��������
* SDL_Texture* tex ���水ť�ı���ͼƬ
* SDL_Rect* rect1 ���水ť��ʾͼƬ�Ŀ�ͼλ��
* SDL_Rect* rectxy ���水ť��ʾ
* ��ӦSDL_RenderCopy������rect1 �� rect2
* һ�����rect1����ΪNULL
* int Left_state ���水ť��һ֡��������״̬
* int Right_state ���水ť��һ֡����Ҽ���״̬
const int Key_Up = 0;
const int Key_Down = 1;
const int Key_Keep = 2;
const int Key_None = 3;
const int Key_Move = 4;
*int flag ���ڶ����������ʶ
*/
struct BUTTON {
	BUTTON(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect* rectxy_, SDL_Rect* recttext_, TTF_Font* font_, SDL_Color* color_) {
		text = text_;
		font = font_;
		color = color_;
		tex = tex_;
		if (rect1_ == NULL) {
			rect1 = NULL;
		}
		else {
			rect1 = new SDL_Rect(*rect1_);
		}
		if (rectxy_ == NULL) {
			rectxy = NULL;//�����Ʋ�����
		}
		else {
			rectxy = new SDL_Rect(*rectxy_);
		}
		if (recttext_ == NULL) {
			recttext = NULL;
		}
		else {
			recttext = new SDL_Rect(*recttext_);
		}
	}
	BUTTON(BUTTON* button_) {
		text = button_->text;
		font = button_->font;
		color = button_->color;
		tex = button_->tex;
		rect1 = button_->rect1;
		rectxy = button_->rectxy;
		recttext = button_->recttext;
	}
	const wchar_t* text;
	TTF_Font* font;
	SDL_Color* color;
	SDL_Texture* tex;
	SDL_Rect* rect1;
	SDL_Rect* recttext;
	SDL_Rect* rectxy;
	int Left_state = -1;
	int Right_state = -1;
	int flag = 0;
	int drawFlag = true;
};

/*�ö�Ӧ��ť�������е�������Ϊ��ť�ı�ʶ*/
typedef int BUTTONER;

class Button
{
public:
	int Updata(class Input* input_);//����ÿ����ť״̬
	int DrawButton(SDL_Renderer* renderer_);//������һ֡
	int GetButtonLeftState(BUTTONER index_);//��ȡ��ť���״̬
	int GetButtonRightState(BUTTONER index_);//��ȡ��ť�Ҽ�״̬
	BUTTON* GetButton(BUTTONER index_);//��ȡ��ť��Ϣ
	int Clear();//��հ�ť

	//��������
	void DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect, SDL_Renderer* renderer, TTF_Font* font);

	BUTTONER AddButton(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect* rectxy_, SDL_Rect* recttext, TTF_Font* font, SDL_Color* color_);//��Ӱ�ť
	BUTTONER AddButton(BUTTON* button_);//��Ӱ�ť
	BUTTONER AddButton(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect rectxy_, SDL_Rect recttext, TTF_Font* font, SDL_Color* color_);//��Ӱ�ť
protected:
	bool InButtonRect(Point* now_point,int i);
private:
	std::vector<BUTTON*> button;
};

#endif