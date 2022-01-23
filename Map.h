#pragma once
#ifndef MAP_H
#define MAP_H
#include "Input.h"

struct Map_Point
{
	//��ͼ��λ�Ƿ�ռ��
	bool zhan_Point;
	//��ұ�ʶ
	int flag_player;
	//�ڼ���
	int huihe;
};

const int NOONE = 3;
const int QUYU = 2;
const int ZHAN = 1;
const int NONE = 0;

static struct Map_Point Map_None = { NONE, NOONE , 49};

#pragma message ("Loading Map...")
class Map {
public:
	int CreateMap();
	int Update(Point* point_,int flag_);

	//��ȡ�غ���
	int Gethuihe();
	//��ȡ��ͼ��λ �����Զ�ת��Ϊ������-1��
	Map_Point GetMapState(Point* point_);
	//��ȡ��ͼ��λ �����Զ�ת��Ϊ������-1��
	Map_Point GetMapStatexy(int x, int y);
	//�ж��Ƿ���
	bool IsThoughLine(int x1, int y1,int x2,int y2);
private:
	//�غ���
	int huihe;
	//��ʼ��ͼλ���趨
	struct Map_Point map[7][7] = 
	{
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
