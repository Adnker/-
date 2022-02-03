#pragma once
#ifndef SKILLER_H
#define SKILLER_H

#include "Player.h"
#include "Map.h"

const int SKILL_FLAG_LUZHANG = 1;
const int SKILL_FLAG_CHUANSONG = 2;
const int SKILL_FLAG_CHUANSHEN = 3;
const int SKILL_FLAG_ZHUIJI = 4;

class Skiller
{
public:
	int CreateSkiller(class Map* map);
	int GetSkillSum(int index_);//��ȡ���ܶ�Ӧ��ʹ�ô���
	const wchar_t* GetSkillName(int index_);//��ȡ��������
	int Use_Skill(int index_, int player_flag_);//���ʹ�ü���
	class Player* GetRed_Player();//��ȡ�췽���
	class Player* GetBlue_Player();//��ȡ�������
	int Getskill_sum();//��ȡ����ȫ���ļ�������
	bool IsLiveSkill(int index_);//�ж϶�Ӧ�ļ����Ƿ��������Լ���
private:
	const wchar_t* skill_name[4] = { L"·��", L"����", L"����",L"׷��"};
	const int skill_num[4] = { 3,1,2,1 };
	int skill_sum = 4;
	int nolifeskill[1] = { SKILL_FLAG_ZHUIJI };
	
	class Player* player;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;
};

#endif
