#pragma once
#ifndef SKILLER_H
#define SKILLER_H

#include "Player.h"
#include "Map.h"

//���ܱ�ʶ
typedef int SKILL;
const int SKILL_FLAG_LUZHANG = 1;
const int SKILL_FLAG_CHUANSONG = 2;
const int SKILL_FLAG_CHUANSHEN = 3;
const int SKILL_FLAG_ZHUIJI = 4;
const int SKILL_FLAG_JIPAO = 5;

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
	const wchar_t* skill_name[5] = { L"·��", L"����", L"����",L"׷��",L"����" };
	const int skill_num[5] = { 3,1,2,1 ,8 };
	int skill_sum = 5;
	int nolifeskill[2] = { SKILL_FLAG_ZHUIJI ,SKILL_FLAG_JIPAO };

	class Player* player;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;

	int Skill_luzhang();
	int Skill_chuansong();
	int Skill_chuanshen();
	int Skill_zhuiji();
	int Skill_jipao();
};

#endif