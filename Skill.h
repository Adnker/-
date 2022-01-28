#pragma once
#ifndef SKILL_H
#define SKILL_H
#include "Player.h"
#include "Map.h"
#include "Skill_flag.h"

#pragma message("Loading skill...")

class Skiller
{
public:
	~Skiller();
	//��ʼ��Skiller
	int CreateSkiller(class Map* map);

	//����ɸѡ�� ʹ�ü���
	int Use_Skill(int skill_flag_, int flag_player);
	//��ȡ��������
	//index = �ڼ�������
	const wchar_t* Getskill_name(int index);
	//��ȡ��Ӧ�����ܴ���
	//index = �ڼ�������
	int Getskill_flag_sum(int index_);
	//��ȡ��������
	int Getskill_sum();
	//��ȡ���ָ��
	class Player* GetRed_Player();
	class Player* GetBlue_Player();
	//�жϼ����Ƿ��������Լ���
	//skill_flag_ = ���ܱ�ʶ
	int IsLiveSkill(int skill_flag_);
private:
	//ɸѡ ��player����Ϊ��Ӧ�����
	//flag_  = false �Ƿ�ת���(����췽���ȡ����)
	//����ֵ = ��ѡ��Ҷ�Ӧ��Ԥѡ��λ�Ƿ�ռ��
	int PlayerChoise(int flag_player_, bool flag_ = false);

	//��ż�������
	const wchar_t* skill_name[7] = { L"����",L"·��",L"����",L"����",L"����",L"����",L"׷��" };
	//��ż���ʹ�ô���
	int skill_flag_sum[7] = { 8,3,1 ,2,1 ,2,1 };
	//���м�������
	int skill_sum = 7;
	//�����������Լ���
	int skill_flag_live[2] = {
		skill_flag_jipao,
		skill_flag_zhuiji
	};

	//���ܺ���
	int skill_jipao(int flag_player_);
	int skill_luzhang(int flag_player_);
	int skill_chuangsong(int flag_player_);
	int skill_kongzhi(int flag_player);
	int skill_jiaohuan(int flag_player_);
	int skill_chuanshen(int flag_player_);
	int skill_zhuiji(int flag_player_);

	class Map* map;
	class Player* red_player;
	class Player* blue_player;
	class Player* player;
};

#pragma message("Skill is loaded")

#endif // !SKILL_H
