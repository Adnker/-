#pragma once
#ifndef MAP_H
#define MAP_H
#include "Input.h"

struct Map_Point
{
	//��ͼ��λ�Ƿ�ռ��
	int zhan_Point;
	//��ұ�ʶ
	int flag_player;
	//�ڼ���
	int huihe;
};

//���������ʶ��λ
const int QUYU = -2;
const int JIDI = -1;

//��ͼ��λ����ʹ�ã���������
const int QUYU_NONE = 3;
//��ͼ��λ����ռ�ã�����������
const int QUYU_ZHAN = 2;
//��ͼ��λ��ռ��
const int ZHAN = 1;
//��ͼ��λδ��ռ��
const int NONE = 0;

//��ͼ��λ����ռ��
//const int Red_Player = 0;
//const int Blue_Player = 1;
const int NOONE = -1;

//�յ�ͼ��λ
static struct Map_Point Map_None = { NONE, NOONE , 49 };

#pragma message ("Loading Map...")
class Map {
public:
	int Clear();
	int CreateMap();
	/*  
		//point_ ���� �Զ�ת��Ϊ����
		//flag_ �Ƿ���»غ�
		//flag_point_ ��λ����Ϊʲô״̬
		//��ͼ��λ����ʹ�ã���������
		const int QUYU_NONE = 3;
		//��ͼ��λ����ռ�ã�����������
		const int QUYU_ZHAN = 2;
		//��ͼ��λ��ռ��
		const int ZHAN = 1;
		//��ͼ��λδ��ռ��
		const int NONE = 0;
	*/
	int Updata(Point* point_, int flag_player_, int flag_point, bool flag_);
	//���»غ�
	int Updatahuihe();

	//��ʾ��ͼ��λ���
	int Print();

	//��ȡ�غ���
	int Gethuihe();
	//��ȡ��ͼ��λ �����Զ�ת��Ϊ������-1��
	Map_Point GetMapState(Point* point_);
	//��ȡ��ͼ��λ �����Զ�ת��Ϊ������-1��
	Map_Point GetMapStatexy(int x, int y);
	//�ж��Ƿ���
	bool IsThoughLine(int x1, int y1, int x2, int y2);
private:
	//�غ���
	int huihe;
	//��ʼ��ͼλ���趨
	struct Map_Point map[7][7] = {
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None}
	};
};
#pragma message ("Map is loaded")

#endif // !MAP_H
