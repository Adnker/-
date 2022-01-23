#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Main_Window.h"
#include "Input.h"
using namespace std;

const int Red_Player = 0;
const int Blue_Player = 1;

const int DEAD = 0;
const int LIFE = 1;
#pragma message ("Loading Player...")
class Player {
public:
	int CreatePlayer(class Main_Window* main_window,
		class Input* input_,class Map* map_,int flag_);
	int Updata();
	//��ȡԤѡλ�õ����� ��ͼ����
	struct Point Getyuxuan_point();
	//��ȡ����λ�õ����� ��ͼ����
	struct Point Getjidi_point();
	//��ȡ�������·�� ��ͼ����
	vector<Point*> Getmove_point() { return move_point; }
private:
	//ת��Ϊ��ͼ���ľ�������
	//Ϊһ���µĵ�λ�����ڴ�
	//point_ = ��������
	Point* ToMapPoint(Point* point_);
	//�ж�������ߵ�λ�Ƿ���ȷ
	//flag_ = �����־
	//point_ = ʹ���ĸ�������ж�
	int MoveIsRight(bool flag_ = false, Point point_ = { 0,0 });
	//����ж�
	int Movetion();
	//�ж�����Ƿ�����
	int IsLife();
	//���������ڵļ���������������
	vector<int> skill_num;//����
	vector<int> skill_sum;//����
	//ѵ��Ӫģʽ��ʹ�õ�������
	int skill;
	//����������·�� ��ͼ����
	vector<Point*> move_point;//�Ѿ���ת��Ϊ��ͼ��λ
	//�����һ��� ��ͼ����
	struct Point jidi_point;
	//��ұ�־ Red_Player = 0 Blue_Player = 1
	int flag;
	//��ʾ��־ δ��ʹ�� = 0 ʹ��ʱ > 0 && < 150
	int flag_window;
	//���Ԥѡλ�� -1����
	struct Point yuxuan_point;
	//�����һ�� -1����
	struct Point before_point;

	//class
	class Input* input;
	class Main_Window* main_window;
	class Map* map;
};
#pragma message("Player is loaded")

#endif // !PLAYER_H
