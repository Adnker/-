#include "Skill.h"
#include "Skill_flag.h"
#include "myMath.h"

int Skiller::Use_Skill(int skill_flag_, int flag_player_)
{
	//ÿ�����ܺ�����Ҫ��������
	//ÿ�����ܺ�����Ҫ��Ӧ�Ƿ���»غ�
	switch (skill_flag_) {
	case skill_flag_jipao:
		return skill_jipao(flag_player_);
	case skill_flag_luzhang:
		return skill_luzhang(flag_player_);
	case skill_flag_chuangsong:
		return skill_chuangsong(flag_player_);
	case skill_flag_kongzhi:
		return skill_kongzhi(flag_player_);
	case skill_flag_jiaohuan:
		return skill_jiaohuan(flag_player_);
	case skill_flag_chuanshen:
		return skill_chuanshen(flag_player_);
	case skill_flag_zhuiji:
		return skill_zhuiji(flag_player_);
	}
	return 0;
}

int Skiller::skill_jipao(int flag_player_)
{
	PlayerChoise(flag_player_);
	player->move_num++;
	return true;
}

int Skiller::skill_luzhang(int flag_player_)
{
	//�̶�����
	if (!PlayerChoise(flag_player_)) { return false; }
	//���������ʶ
	Point* temp_point = new Point(QUYU, player->quyu_point.size());
	player->move_point.emplace_back(temp_point);


	//����ж�
	//�����Ԥѡ����λ��ת��Ϊ�����ʽ��ͼ����λ��
	Point* temp_point1 = player->ToquyuPoint(&player->yuxuan_point);
	//�����µĵ�λ �����ڴ�
	QuYu* temp_quyu = new QuYu(skill_flag_luzhang, temp_point1->x, temp_point1->y);
	//��ToquyuPoint()�з�����ڴ棬�ɴ˽��л���
	delete temp_point1;
	//����λ������ҵ����򻺳���
	player->quyu_point.emplace_back(temp_quyu);


	//�̶�����
	player->move_num--;//��Ҳ������ƶ�
	map->Updata(&player->yuxuan_point, flag_player_, QUYU_ZHAN, true);//����ͼ��Ӧ�ĵ�λ����Ϊ����ռ��
	player->player->UpdataSum();	//���µ����ƶ������ͼ��ܴ���
	return true;
}

int Skiller::skill_chuangsong(int flag_player_)
{
	if (!PlayerChoise(flag_player_)) { return false; }
	//���������ʶ
	Point* temp_point = new Point(JIDI, player->jidi_point.size());
	player->move_point.emplace_back(temp_point);//�������ʶ���뻺����


	//����ж�
	//�����Ԥѡ����λ��ת��Ϊ�����ʽ��ͼ����λ��
	Point* temp_point1 = player->TojidiPoint(&player->yuxuan_point);
	player->jidi_point.emplace_back(temp_point1);
	player->before_point = player->MapToIndex(temp_point1);


	//�̶�����
	player->move_num--;//��Ҳ������ƶ�
	map->Updata(&player->yuxuan_point, flag_player_, ZHAN, true);//����ͼ��Ӧ�ĵ�λ����Ϊ����ռ��
	player->player->UpdataSum();//���µ����ƶ������ͼ��ܴ���
	return true;
}

int Skiller::skill_kongzhi(int flag_player_)
{
	//��ȡ�෴���
	if (!PlayerChoise(flag_player_,true)) { return false; }

	//�����෴��ҵ��ƶ��ͼ��ܴ���
	player->UpdataSum();
	//�޸��෴��ҵ�Ԥѡλ��
	Point temp_point = player->yuxuan_point;
	player->yuxuan_point = player->player->yuxuan_point;
	//�����෴��ҵ��ƶ�����
	if (!player->Movetion(true)) { 
		player->yuxuan_point = temp_point;
		return false;
	}
	player->yuxuan_point = temp_point;

	//�̶�����
	player->player->move_num--;//��Ҳ������ƶ�
	player->UpdataSum();//���µ����ƶ������ͼ��ܴ���
	return true;
}

int Skiller::skill_jiaohuan(int flag_player_)
{
	PlayerChoise(flag_player_);

	//���Է��Ļ������������һ��
	Point* temp_point = player->ToMapPoint(&player->player->before_point);
	player->jidi_point.emplace_back(temp_point);
	Point* temp_point1 = player->ToMapPoint(&player->before_point);
	player->player->jidi_point.emplace_back(temp_point1);
	//�ֱ�������ҵ��ƶ�������������ʶ
	Point* temp_point2 = new Point(JIDI, player->jidi_point.size() - 1);
	player->move_point.emplace_back(temp_point2);
	Point* temp_point3 = new Point(JIDI, player->player->jidi_point.size() - 1);
	player->player->move_point.emplace_back(temp_point3);

	//�̶�����
	player->move_num--;//��Ҳ������ƶ�
	map->Updatahuihe();//���»غ�
	player->player->UpdataSum();//���µ����ƶ������ͼ��ܴ���
	return true;
}

int Skiller::skill_chuanshen(int flag_player_)
{
	PlayerChoise(flag_player_);

	Point* temp_before = player->ToMapPoint(&player->before_point);
	Point* temp_yuxuan = player->ToMapPoint(&player->yuxuan_point);
	//�ж�Ԥѡλ���Ƿ����Լ�λ�õİ뾶��Χ
	//yuxuan_point and before
	if (distance((double)temp_before->x, (double)temp_before->y,
		(double)temp_yuxuan->x, (double)temp_yuxuan->y) > 199) {
		return false;
	}
	delete temp_before;

	//�����µĵ�λ
	Point* temp_point = player->ToMapPoint(&player->yuxuan_point);
	//����λ���뵽move_point��
	player->move_point.emplace_back(temp_point);

	//�̶�����
	player->move_num--;//��Ҳ������ƶ�
	map->Updata(&player->yuxuan_point, flag_player_, ZHAN, true);//���»غ�
	player->player->UpdataSum();//���µ����ƶ������ͼ��ܴ���
	return true;
}

int Skiller::skill_zhuiji(int flag_player_)
{
	if (!PlayerChoise(flag_player_)) { return false; }

	//�Ȼ�ȡ�Լ���Ԥѡλ�ò�ת��Ϊ���ĵ�λ
	//��ȡ���˵���һ��
	//�жϾ����Ƿ���ȷ
	Point* temp_before = player->ToMapPoint(&player->player->before_point);
	Point* temp_yuxuan = player->ToMapPoint(&player->yuxuan_point);
	//yuxuan and player->before
	if(distance((double)temp_before->x, (double)temp_before->y,
		(double)temp_yuxuan->x, (double)temp_yuxuan->y) > 199) {
		return false;
	}
	delete temp_before;

	//�����µĵ�λ�����������
	Point* temp_point = new Point(JIDI, player->jidi_point.size());
	player->move_point.emplace_back(temp_point);

	//����Ӧ�ĵ�λת��Ϊ���ظ�ʽ�������������
	Point* temp_point1 = player->TojidiPoint(&player->yuxuan_point);
	player->jidi_point.emplace_back(temp_point1);
	player->before_point = player->MapToIndex(temp_point1);

	//�̶�����
	//player->move_num--;//���Ҫ���ƶ�һ���ƶ�
	map->Updata(&player->yuxuan_point, flag_player_, ZHAN,false);
	player->player->UpdataSum();//���µ����ƶ������ͼ��ܴ���
	return true;
}
