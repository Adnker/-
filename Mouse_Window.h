#pragma once
#ifndef MOUSE_WINDOW
#define MOUSE_WINDOW

#include <vector>
#include "Input.h"
#include "Main_Window.h"
using std::vector;

class Mouse_Window {
public:
	Mouse_Window(Input* input_, class Main_Window* main_window);
	//����С��
	int DrawSnake();
private:
	//����Ƶ��
	int flag_mouse_time;
	//ɾ���ٶ�
	int erase_time;
	//������
	vector<Point*> point_sum;

	//class
	class Input* input;
	class Main_Window* main_window;
};
#endif