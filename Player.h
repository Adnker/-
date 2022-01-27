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
	//xy�����ͼ����
	QuYu(int skill_, int x_, int y_) {
		skill = skill_;
		x = x_;
		y = y_;
	}
	//�Ǹ����ܵı�ʶ
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
	int CreatePlayer(class Main_Window* main_window, class Input* input_,
		class Map* map_, class Player* player_, class Skiller* skiller_, int flag_);
	int Updata();

	//�����ƶ��ͼ��ܵ�ʹ�ô���
	void UpdataSum();
	//��ȡԤѡλ�õ����� ��ͼ����
	struct Point Getyuxuan_point();
	//��ȡ����λ�õ����� ��ͼ����
	vector<Point*>* Getjidi_point();
	//��ȡ�������·�� ��ͼ����
	vector<Point*>* Getmove_point();
	//��ȡ����λ������ ��ͼ����
	vector<QuYu*>* Getquyu_point();
	//���ü���
	void Changeskill_flag(int skill_flag_);
	//��ȡ���ܱ�ʶ
	int Getskill_flag();
	//��ȡ���ܴ���
	int Getskill_flag_num();
private:
	//ת��Ϊ��ͼ���ľ�������
	//�����µĵ�λ �����ڴ�
	//point_ = ��������
	Point* ToMapPoint(Point* point_);
	//ת��Ϊ���ظ�ʽ�ĵ�ͼ����
	//�����µĵ�λ �����ڴ�
	Point* TojidiPoint(Point* point_);
	//ת��Ϊ�����ʽ�ĵ�ͼ����
	//�����µĵ�λ �����ڴ�
	Point* ToquyuPoint(Point* point_);
	//��ͼ��λת��Ϊ����+1
	Point MapToIndex(Point* point_);
	//��ͼ��λת��Ϊ��ͼ���ĵ�λ
	Point MapToMap(Point* point_);
	//�ж�����Ƿ񻹿����ж�
	//ֻ����� �Զ���ɸ��²���
	int CanMove();
	//�ж�������ߵ�λ�Ƿ���ȷ
	//flag_ = �Ƿ����λ
	//point_ = ���ڵ�λ
	int MoveIsRight(bool flag_ = false, Point point_ = { 0,0 });
	//����ж�
	//flag  = false�Ƿ���ǿ�Ƶ���
	int Movetion(int flag = false);
	//���ʹ�ü���
	int Skill();
	//�ж�����Ƿ�����
	int IsLife();

	//ѵ��Ӫģʽ��ʹ�õ�������
	//���ܱ�ʶ  Ϊ-1ʱΪ��δȷ������
	int skill_flag = -1;
	//��Ҽ��ܶ�Ӧ�ļ��ܴ���
	int skill_flag_num;
	//�˻غ���ҿ��ƶ�����
	int move_num = 1;
	//�˻غ���ҿ�ʹ�ü��ܴ���
	int skill_num = 1;
	//����������·�� ��ͼ����
	//x = 0 �� 1��Ϊ�����ʶ 0��jidi_point����һ�����ƶ� 1��quyu����һ��
	vector<Point*> move_point;
	//�����һ��� ��ͼ����
	vector<Point*> jidi_point;
	//������� ��ͼ����
	vector<QuYu*> quyu_point;
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
