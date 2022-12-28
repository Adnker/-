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
	if (index_ > skill_sum) {
		return L"���޼���";
	}
	return skill_name[index_-1];
}

const wchar_t* Skiller::Getskill_jieshao(int index)
{
	return skill_jieshao[index - 1];
}

int Skiller::Use_Skill(int index_, int player_flag_)
{
	//��player����Ϊ���ܵ�ʹ����
	player = player_flag_ == Red_Player ? red_player : blue_player;

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
	case SKILL_FLAG_JIPAO:
		return Skill_jipao();
	case SKILL_FLAG_JIANXING:
		return Skill_jianxing();
	case SKILL_FLAG_KONGZHI:
		return Skill_kongzhi();
	case SKILL_FLAG_HUDUN:
		return Skill_hudun();
	case SKILL_FLAG_JIAOHUAN:
		return Skill_jiaohuan();
	default:
		return false;
	}
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
	return SKILLSUM;
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
	if (distance(player->GetBeforePoint().x,player->GetBeforePoint().y,
		player->player->GetBeforePoint().x, player->player->GetBeforePoint().y) > 199) {
		return false;
	}//�жϵз�����Ƿ��ھ�����
	if (distance(player->player->GetBeforePoint().x,player->player->GetBeforePoint().y,
		player->yuxuan_point.x, player->yuxuan_point.y) > 199) {
		return false;
	}//�ж����Ԥѡ��λ�Ƿ��ھ�����
	Move_point* point_new = new Move_point(player->yuxuan_point, JIDI);//�����µĵ�λ
	player->move_point.emplace_back(point_new);//�������ĵ�λ���뵽�ж�������
	map->Updata(&player->yuxuan_point, player->flag, ZHAN, false);//���µ�λ�����»غ�
	player->player->UpdataSum();//���µ���
	return true;
}

int Skiller::Skill_jipao()
{
	player->move_num = 2;
	return true;
}

int Skiller::Skill_jianxing()
{
	if (map->Gethuihe() > 10) {
		player->move_num = 4;
		return true;
	}
	return false;
}

int Skiller::Skill_kongzhi()
{
	if (player->player->MoveIsRight(true, player->yuxuan_point) == true) 
	{
		Point point = player->player->yuxuan_point;
		player->player->yuxuan_point = player->yuxuan_point;
		player->player->move_num = 1;
		player->player->Movetion(true);
		player->player->yuxuan_point = point;
		map->Updata(&player->yuxuan_point, player->player->flag, ZHAN, false);//���µ�λ,�����»غ�
		player->player->UpdataSum();//���µ���
		return true;
	}
	return false;
}

int Skiller::Skill_hudun()
{
	player->player->move_num = 5;
	player->player->skill_num = 0;
	map->Updatahuihe();
	return true;
}

int Skiller::Skill_jiaohuan()
{
	Move_point* temp_point1 = new Move_point(player->player->GetBeforePoint(),JIDI);
	Move_point* temp_point2 = new Move_point(player->GetBeforePoint(), JIDI);
	player->move_point.emplace_back(temp_point1);
	player->player->move_point.emplace_back(temp_point2);
	map->Updatahuihe();
	player->player->UpdataSum();
	return true;
}
