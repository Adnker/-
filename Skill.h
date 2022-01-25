#pragma once
#ifndef SKILL_H
#define SKILL_H
#include "Player.h"
#include "Map.h"

//���ܼ��ܱ�ʶ
const int skill_flag_jipao = 1;
//·�ϼ��ܱ�ʶ
const int skill_flag_luzhang = 2;
//���ͼ��ܱ�ʶ
const int skill_flag_chuangsong = 3;

#pragma message("Loading skill...")

class Skiller
{
public:
	~Skiller();
	int CreateSkiller(class Map* map);
	//����ɸѡ�� ʹ�ü���
	int Use_Skill(int skill_flag_,int flag_player);
	//��ȡ�������� �Զ�ת��Ϊ����
	const wchar_t* Getskill_name(int index);
	//��ȡ��������
	int Getskill_sum();
	//��ȡ���ָ��
	class Player* GetRed_Player();
	class Player* GetBlue_Player();
private:
	//ɸѡ ��player����Ϊ��Ӧ�����
	//����ֵΪ��Ӧʹ��Ԥѡ��λ�Ƿ�ռ��
	int PlayerChoise(int flag_player_);
	//���ܺ���
	int skill_jipao(int flag_player_);
	int skill_luzhang(int flag_player_);
	int skill_chuangsong(int flag_player_);
	//��ż�������
	const wchar_t* skill_name[3] = { L"����",L"·��",L"����" };
	//���м�������
	int skill_sum = 3;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;
	class Player* player;
};

#pragma message("Skill is loaded")

#endif // !SKILL_H
