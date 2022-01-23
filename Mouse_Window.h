#pragma once
#ifndef MOUSE_WINDOW
#define MOUSE_WINDOW

#include <vector>
#include "Input.h"
using std::vector;

class Mouse_Window {
public:
	Mouse_Window(Input* input_);
	int Updata();

	vector<Point*> Getpoint();
private:
	//����Ƶ��
	int flag_mouse_time;
	//������
	vector<Point*> point_sum;

	//class
	class Input* input;
};
#endif