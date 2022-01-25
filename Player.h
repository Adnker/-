#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Main_Window.h"
#include "Input.h"
#include "Skill.h"
using namespace std;

//�����ʶ
//���ڱ�ʶ����
struct QuYu {
	QuYu(int skill_, int x_, int y_) {
		skill = skill_;
		x = x_;
		y = y_;
	}
	//�Ǹ����ܵ�����
	int skill;
	//�ڵ�ͼ���� ��ͼ����
	int x;
	int y;
};

//������ұ�ʶ
const int Red_Player = 0;
//�췽��ұ�ʶ
const int Blue_Player = 1;
//����
const int DEAD = 0;
//���
const int LIFE = 1;

//�����ʶ ���������ʶ��ӻ��ػ������м����»���
const Point Point_None = { 0,0 };
#pragma message ("Loading Player...")
class Player{
public:
	friend class Skiller;
	//���������
	void Clear();
	int CreatePlayer(class Main_Window* main_window,
		class Input* input_,class Map* map_,class Player* player_, int flag_);
	int Updata();

	//�����ƶ��ͼ��ܵ�ʹ�ô���
	void UpdataSum();
	//��ȡԤѡλ�õ����� ��ͼ����
	struct Point Getyuxuan_point();
	//��ȡ����λ�õ����� ��ͼ����
	vector<Point*>* Getjidi_point();
	//��ȡ�������·�� ��ͼ����
	vector<Point*>* Getmove_point();
	//���ü���
	void ChangeSkill(int skill_);
	//��ȡ���ܱ�ʶ
	int Getskill_flag();
private:
	//ת��Ϊ��ͼ���ľ�������
	//�����µĵ�λ �����ڴ�
	//point_ = ��������
	Point* ToMapPoint(Point* point_);
	//ת��Ϊ���ظ�ʽ�ĵ�ͼ���
	//�����µĵ�λ �����ڴ�
	Point* TojidiPoint(Point* point_);
	//�ж�������ߵ�λ�Ƿ���ȷ
	//flag_ = �����־
	//point_ = ʹ���ĸ�������ж�
	int MoveIsRight(bool flag_ = false, Point point_ = { 0,0 });
	//����ж�
	int Movetion();
	//���ʹ�ü���
	int Skill();
	//�ж�����Ƿ�����
	int IsLife();
	//���������ڵļ���������������
	vector<int> skill_num;//����
	vector<int> skill_sum;//����
	//ѵ��Ӫģʽ��ʹ�õ�������
	int skill = -1;
	//�������
	vector<QuYu*> quyu;
	//��ҿ��ƶ�����
	int move_flag = 1;
	//���ʹ�ü��ܴ�ʱ Ϊ-1ʱΪ��δȷ������
	int skill_flag = 1;
	//����������·�� ��ͼ����
	vector<Point*> move_point;//�Ѿ���ת��Ϊ��ͼ��λ
	//�����һ��� ��ͼ����
	vector<Point*> jidi_point;
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
	class Player* player;//����
	class Skiller* skiller;
};
#pragma message("Player is loaded")

#endif // !PLAYER_H
