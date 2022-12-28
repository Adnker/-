#pragma once
#ifndef SKILLER_H
#define SKILLER_H

#include "Player.h"
#include "Map.h"

//���ܱ�ʶ
typedef int SKILL;
const int SKILL_FLAG_JIPAO = 1;
const int SKILL_FLAG_LUZHANG = 2;
const int SKILL_FLAG_CHUANSONG = 3;
const int SKILL_FLAG_CHUANSHEN = 4;
const int SKILL_FLAG_ZHUIJI = 5;
const int SKILL_FLAG_JIANXING = 6;
const int SKILL_FLAG_KONGZHI = 7;
const int SKILL_FLAG_HUDUN = 8;
const int SKILL_FLAG_JIAOHUAN = 9;
static const int SKILLSUM = 10;

class Skiller
{
public:
	int CreateSkiller(class Map* map);
	int Use_Skill(int index_, int player_flag_);//���ʹ�ü���

	class Player* GetRed_Player();//��ȡ�췽���
	class Player* GetBlue_Player();//��ȡ�������
	int Getskill_sum();//��ȡ����ȫ���ļ�������
	int GetSkillSum(int index_);//��ȡ���ܶ�Ӧ��ʹ�ô���
	bool IsLiveSkill(int index_);//�ж϶�Ӧ�ļ����Ƿ��������Լ���
	const wchar_t* GetSkillName(int index_);//��ȡ��������
	const wchar_t* Getskill_jieshao(int index);//��ȡ���ܽ���
private:
	const wchar_t* skill_name[SKILLSUM] = { L"����", L"·��", L"����", L"����",L"׷��",L"����",L"����",L"����",L"����", };
	const int skill_num[SKILLSUM] = { 8,       3,       1,       2,      1,      1,      2 ,     1,      1 };
	int nolifeskill[3] = { SKILL_FLAG_ZHUIJI ,SKILL_FLAG_JIPAO ,SKILL_FLAG_JIANXING };
	int skill_sum = SKILLSUM;

	class Player* player;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;

	const wchar_t* skill_jieshao[1] = { L" ·�ϣ������谭���˵��ж���ʹ���˵�·������" };

	int Skill_luzhang();
	int Skill_chuansong();
	int Skill_chuanshen();
	int Skill_zhuiji();
	int Skill_jipao();
	int Skill_jianxing();
	int Skill_kongzhi();
	int Skill_hudun();
	int Skill_jiaohuan();
};

#endif