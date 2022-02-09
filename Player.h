#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Input.h"
#include "Main_Window.h"
#include "Skill.h"
#include "Map.h"
using namespace std;
static const int ZHU_HAND = 0;
static const int XU_HAND = 1;
static const int NONE_HAND = 2;

//���ڱ�ʶ��ҵ��ж���λ
//��������
struct Move_point {
	/*
	* flag = �����ʶ
	* JIDI �������ױ�ʶ
	* QUYU ���������ʶ
	* NULL �ƶ� �������ʶ
	* >0 ����
	*/
	Move_point(Point point_, int flag_,int hand_ = ZHU_HAND) {
		point = new Point(point_);
		flag = flag_;
		hand = flag_ == QUYU ? NONE_HAND : hand_;
	}
	struct Point* point;
	int flag;
	int hand;
};

//������ұ�ʶ
const int Red_Player = 0;
//�췽��ұ�ʶ
const int Blue_Player = 1;

//����
const int DEAD = 0;
//���
const int LIFE = 1;

class Player{
public:
	friend class Skiller;
	int CreatePlayer(class Main_Window* main_window_, class Input* input_, class Map* map_, class Player* player_,
		class Skiller* skiller_, int flag_);
	int Updata();
	void UpdataSum();//������ҵ��ƶ��ͼ��ܴ���
	int Clear();//�������
	Point Getyuxuan_point();//��ȡ���Ԥѡ��λ
	Point JidiToMap(struct Move_point* point_);//�����ص���������ת��Ϊ��ͼ����
	Point ToMapPoint(Point* point_);//������ת��Ϊ��ͼ����
	vector<int>* Getskill();//��ȡ��Ҽ���
	int Getskill_sum(int index = 0);//��ȡ��Ҷ�Ӧ���ܵĿ�ʹ�ô���
	vector<Move_point*>* GetMove_point();//��ȡ����ƶ�����
	int Changeskill(int index);//�޸���ҵļ���ѡ��
	int Getskill_num(int index_);//��ȡ��Ҽ��ܶ�Ӧ�Ŀ�ʹ�ô���
	string Getpicture_name();//��ȡ���ͼƬ����
	bool SkillNeedShow();//��ȡ��ҵļ����Ƿ���Ҫ����
	int ShowSkill_index();//��ȡ�����Ҫչʾ�ļ��ܵ�����
	SDL_Rect ShowSkill_rect();//��ȡ�����Ҫչʾ�ļ��ܾ���
	int CreateAllSkill();//Ϊ��ҷַ����� ֻ�ھ���ģʽ��ʹ��
	int AddSkill();//Ϊ��ҷַ����� ֻ�ھ���ģʽ��ʹ��
private:
	Point* GetBeforePoint();//��ȡ�����һ�����õ�λ
	int GetBeforePoint_index();
	Point* GetBeforePointXu();//��ȡ�����һ����·��ͷ
	int GetBeforePointXu_index();
	int CanMove();//�ж�����Ƿ��ܼ����ƶ�
	int MoveIsRight(bool flag_ = false, Point point_ = { -1,-1 },bool xuhang_flag = false);//�ж����ѡ��ĵ�λ�Ƿ���ȷ flag_�Ƿ���������λ
	int Movetion(int flag_ = false);//���ѡ���ƶ�
	int Skill(int index_ = 0);//���ѡ��ʹ�ü���
	int Xuhand();//��·��ͷ�ж�
	int IsLife();//����Ƿ���
	int Change_skill_state(int flag);//�޸�skill_state��״̬


	int flag;//��ұ�ʶ��������Ҵ˶����Ǻ췽��������
	int window_time;//���ڼ�¼�����ʾ���ڵ���ʾʱ��
	int skill_state = -1;//���ڼ�¼��Ҽ���չʾ��״̬ -1ʱ��չʾ > -1 ʱչʾ����Ϊ��Ҫչʾ�ļ�������
	int skill_num;//������ҿ�ʹ�ü��ܵĴ���
	int move_num;//������ҿ��ƶ��Ĵ���
	Point yuxuan_point;//�������Ԥѡ��λ
	vector<int> skill;//������ҵļ���
	vector<int> skill_sum;//������Ҽ��ܶ�Ӧ�Ŀ�ʹ�ô���
	vector<int> skill_all;//������Ҽ��ܿ���ʣ�༼��
	std::string picture_name;//������ҵ�ͼƬ·��

	/*
	* flag:
	* = 0 ��ʾ����������
	* = -1 ��ʾ���ص�λ
	* = -2 ��ʾ�����λ
	* > 0 ����
	* 
	* ��һ����λ�ض��ǻ���
	*/
	vector<struct Move_point*> move_point;//��������ж�·��

	//class
	class Input* input;
	class Main_Window* main_window;
	class Map* map;
	class Player* player;//����
	class Skiller* skiller;
};

#endif // !PLAYER_H
