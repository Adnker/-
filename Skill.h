#pragma once
#ifndef SKILL_H
#define SKILL_H
#include "Player.h"

//���ܼ��ܱ�ʶ
const int skill_flag_jipao = 0;
//·�ϼ��ܱ�ʶ
const int skill_flag_luzhang = 1;
//���ͼ��ܱ�ʶ
const int skill_flag_chuangsong = 2;

#pragma message("Loading skill...")

class Skiller
{
public:
	~Skiller();
	int CreateSkiller(class Player* red_player_, class Player* blue_player_);
	//����ɸѡ�� ʹ�ü���
	void Use_Skill(int skill_flag_,int flag_player);
	//��ȡ�������� �Զ�ת��Ϊ����
	const wchar_t* Getskill_name(int index);
	//��ȡ��������
	int Getskill_sum();
private:
	//ɸѡ ��player����Ϊ��Ӧ�����
	void PlayerChoise(int flag_player_);
	//���ܺ���
	int skill_jipao(int flag_player_);
	int skill_luzhang(int flag_player_);
	int skill_chuangsong(int flag_player_);
	//��ż�������
	const wchar_t* skill_name[3] = { L"����",L"·��",L"����" };
	//���м�������
	int skill_sum = 3;
	class Player* red_player;
	class Player* blue_player;
	class Player* player;
};

#pragma message("Skill is loaded")

#endif // !SKILL_H
