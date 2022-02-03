#pragma once
#ifndef SKILLER_H
#define SKILLER_H

#include "Player.h"
class Skiller
{
public:
	int CreatSkiller(class Player* red_player_, class Player* blue_player_);
	int GetSkillSum(int index_);//��ȡ���ܶ�Ӧ��ʹ�ô���
	const wchar_t* GetSkillName(int index_);//��ȡ��������
private:
	const wchar_t* skill_name[3] = { L"·��", L"����", L"����" };
	const int skill_sum[3] = { 3,1,2 };
	
	class Player* player;
	class Player* red_player;
	class Player* blue_player;
};

#endif
