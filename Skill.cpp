#include "Skill.h"

int Skiller::CreateSkiller(Map* map_)
{
	map = map_;
	red_player = new Player();
	blue_player = new Player();
	return true;
}

int Skiller::GetSkillSum(int index_)
{
	return skill_num[index_-1];
}

const wchar_t* Skiller::GetSkillName(int index_)
{
	return skill_name[index_-1];
}

int Skiller::Use_Skill(int index_, int player_flag_)
{
	//��player����Ϊ���ܵ�ʹ����
	if (player_flag_ == Red_Player) {
		player = red_player;
	}
	else {
		player = blue_player;
	}

	//ѡ���ܺ���
	switch (index_)
	{
	case SKILL_FLAG_LUZHANG:
		return Skill_luzhang();
	case SKILL_FLAG_CHUANSONG:
		return Skill_chuansong();
	case SKILL_FLAG_CHUANSHEN:
		return Skill_chuanshen();
	case SKILL_FLAG_ZHUIJI:
		return Skill_zhuiji();
	default:
		break;
	}
	return true;
}

bool Skiller::IsLiveSkill(int index_) {
	for (int i : nolifeskill) {
		if (index_ == i) {
			return false;
		}
	}
	return true;
}

class Player* Skiller::GetRed_Player() {
	return red_player;
}

class Player* Skiller::GetBlue_Player() {
	return blue_player;
}

int Skiller::Getskill_sum()
{
	return skill_sum;
}

int Skiller::Skill_luzhang()
{
	if (map->GetMapState(&player->yuxuan_point).zhan_Point == NONE) {
		//ѡ��ĵ�λδ��ռ��

		Move_point* point_new = new Move_point(player->yuxuan_point,QUYU);//�����µĵ�λ
		player->move_point.emplace_back(point_new);//���´����ĵ�λ���뵽�ж�������
		map->Updata(&player->yuxuan_point, player->flag, QUYU_ZHAN, true);//���µ�ͼ��λ����غ�
		player->player->UpdataSum();//���µ���
		return true;
	}
	return false;
}

int Skiller::Skill_chuansong()
{
	if (map->GetMapState(&player->yuxuan_point).zhan_Point == NONE) {
		//ѡ���λδ��ռ��

		Move_point* point_new = new Move_point(player->yuxuan_point, JIDI);//�����µĵ�λ
		player->move_point.emplace_back(point_new);//�������ĵ�λ���뵽�ж�������
		map->Updata(&player->yuxuan_point, player->flag, ZHAN, true);//���µ�ͼ��λ����غ�
		player->player->UpdataSum();//���µ���
		return true;
	}
	return false;
}

int Skiller::Skill_chuanshen()
{
	if (!player->MoveIsRight()) { return false; }
	Move_point* point_new = new Move_point(player->yuxuan_point, NULL);//�����µĵ�λ
	player->move_point.emplace_back(point_new);//�������ĵ�λ���뵽�ж�������
	map->Updata(&player->yuxuan_point, player->flag, ZHAN, true);//���µ�ͼ��λ����غ�
	player->player->UpdataSum();//���µ���
	return true;
}

int Skiller::Skill_zhuiji()
{
	if (distance(player->GetBeforePoint()->x,player->GetBeforePoint()->y,
		player->player->GetBeforePoint()->x, player->player->GetBeforePoint()->y) > 199) {
		return false;
	}//�жϵз�����Ƿ��ھ�����
	if (distance(player->player->GetBeforePoint()->x,player->player->GetBeforePoint()->y,
		player->yuxuan_point.x, player->yuxuan_point.y) > 199) {
		return false;
	}//�ж����Ԥѡ��λ�Ƿ��ھ�����
	Move_point* point_new = new Move_point(player->yuxuan_point, JIDI);//�����µĵ�λ
	player->move_point.emplace_back(point_new);//�������ĵ�λ���뵽�ж�������
	map->Updata(&player->yuxuan_point, player->flag, ZHAN, false);//���µ�λ�����»غ�
	player->player->UpdataSum();//���µ���
	return true;
}
