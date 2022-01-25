#include "Skill.h"
#pragma message("Loading skill.cpp")

Skiller::~Skiller()
{
	delete red_player;
	delete blue_player;
}
int Skiller::CreateSkiller(Map* map_)
{
	red_player = new Player();
	blue_player = new Player();
	map = map_;
	return 0;
}

int Skiller::Use_Skill(int skill_flag_, int flag_player_)
{
	switch (skill_flag_) {
	case skill_flag_jipao:
		return skill_jipao(flag_player_);
	case skill_flag_luzhang:
		return skill_luzhang(flag_player_);
	case skill_flag_chuangsong:
		return skill_chuangsong(flag_player_);
	}
}

const wchar_t* Skiller::Getskill_name(int index)
{
	//�������м���������������
	if (index > skill_sum) { return 0; }
	index--;
	return skill_name[index];
}

int Skiller::Getskill_sum()
{
	return skill_sum;
}

Player* Skiller::GetRed_Player()
{
	return red_player;
}

Player* Skiller::GetBlue_Player()
{
	return blue_player;
}

int Skiller::PlayerChoise(int flag_player_)
{
	if (flag_player_ == Red_Player) {
		player = red_player;
	}
	else {
		player = blue_player;
	}
	//�жϵ�λ�Ƿ�ռ��
	if (map->GetMapState(&player->yuxuan_point).zhan_Point == NONE) { return true; }
	else { return false; }
}

int Skiller::skill_jipao(int flag_player_)
{
	PlayerChoise(flag_player_);
	player->move_flag++;
	return true;
}

int Skiller::skill_luzhang(int flag_player_)
{
	//�̶�����
	if (!PlayerChoise(flag_player_)) { return false; }
	//���������ʶ
	Point* temp_point = new Point(QUYU,0);
	player->move_point.emplace_back(temp_point);


	//����ж�
	//�����Ԥѡ����λ��ת��Ϊ�����ʽ��ͼ����λ��
	Point* temp_point1 = player->ToquyuPoint(&player->yuxuan_point);
	//�����µĵ�λ �����ڴ�
	QuYu* temp_quyu = new QuYu(skill_flag_luzhang, temp_point1->x, temp_point1->y);
	//����λ������ҵ����򻺳���
	player->quyu_point.emplace_back(temp_quyu);


	//�̶�����
	player->move_flag--;//��Ҳ������ƶ�
	map->Update(&player->yuxuan_point, flag_player_, true);//����ͼ��Ӧ�ĵ�λ����Ϊ����ռ��
	player->player->UpdataSum();	//���µ����ƶ������ͼ��ܴ���
	return true;
}

int Skiller::skill_chuangsong(int flag_player_)
{
	if (!PlayerChoise(flag_player_)) { return false; }
	//���������ʶ
	Point* temp_point = new Point(JIDI, 0);
	player->move_point.emplace_back(temp_point);//�������ʶ���뻺����


	//����ж�
	//�����Ԥѡ����λ��ת��Ϊ�����ʽ��ͼ����λ��
	Point* temp_point1 = player->TojidiPoint(&player->yuxuan_point);
	player->jidi_point.emplace_back(temp_point1);


	//�̶�����
	player->move_flag--;//��Ҳ������ƶ�
	map->Update(&player->yuxuan_point, flag_player_, true);//����ͼ��Ӧ�ĵ�λ����Ϊ����ռ��
	player->player->UpdataSum();	//���µ����ƶ������ͼ��ܴ���
	return true;
}
#pragma message("skill.cpp is loaded")