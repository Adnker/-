#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Main_Window.h"
#include "Input.h"
using namespace std;

const int Red_Player = 0;
const int Blue_Player = 1;

class Player {
public:
	int CreatePlayer(class Main_Window* main_window,
		class Input* input_,class Map* map_,int flag_);
	int Updata();
	//��ȡԤѡλ�õ�����
	struct Point Getyuxuan_point();
	struct Point Getjidi_point();
	//��ȡ�������·��
	vector<Point*> Getmove_point() { return move_point; }
private:
	//ת��Ϊ��ͼ���ľ�������
	Point* ToMapPoint(Point* point_);
	//�ж�������ߵ�λ�Ƿ���ȷ
	bool MoveIsRight();
	//���������ڵļ���������������
	vector<int> skill_num;//����
	vector<int> skill_sum;//����
	//ѵ��Ӫģʽ��ʹ�õ�������
	int skill;
	//����������·��
	vector<Point*> move_point;//�Ѿ���ת��Ϊ��ͼ��λ
	//�����һ���
	struct Point jidi_point;
	//��ұ�־
	int flag;
	//��ʾ��־
	int flag_window;
	//���Ԥѡλ��
	struct Point yuxuan_point;
	//Input
	class Input* input;
	//Main_Window
	class Main_Window* main_window;
	//Map
	class Map* map;
};

#endif // !PLAYER_H
