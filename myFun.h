#pragma once
#include <iostream>
#include <random>
#include <Windows.h>

class Rander {
public:
	Rander();
	int GetARand(int max,int min = 0 );
private:
	std::default_random_engine e;
	int seek;
};

//������֮��ľ���
double distance(double x1, double y1, double x2, double y2);

//���ô���͸��
bool SetWindowA(HWND hwnd, int w, int h);