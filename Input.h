#pragma once
#ifndef Input_H
#define Input_H

#include <SDL.h>
#include <iostream>

struct Point {
	Point() { x = 0; y = 0; }
	Point(int x_, int y_) {
		x = x_;
		y = y_;
	}
	int x;
	int y;
};

const int Key_Up = 0;
const int Key_Down = 1;
const int Key_Keep = 2;
const int Key_None = 3;

#pragma message ("Loading Input...")
class Input {
public:
	//��ʼ��
	int CreateInput();
	//����
	int Updata();

	//����״̬
	int GetKeyState(SDL_Scancode key);
	//���״̬
	int GetMouseState(int button);
	bool GetMouseMove();
	struct Point* GetNowPoint() { return &nowPoint; };
	struct Point* GetbeforePoint() { return &beforePoint; };
private:
	//���ڵļ���״̬
	Uint8 nowKeyState[SDL_NUM_SCANCODES];
	//��һ֡����״̬
	Uint8 beforeKeyState[SDL_NUM_SCANCODES];
	//�������״̬
	struct Point nowPoint;
	Uint32 nowMouseState;
	//��һ֡���״̬
	struct Point beforePoint;
	Uint32 beforeMouseState;
};
#pragma message ("Input is loaded")
#endif