#include "Player.h"
#include "Map.h"
#include "myMath.h"
#pragma message("Loading player.cpp")

const int TOO_LONG = 2;
const int THOUGH = 3;
const int NOPOINT = 4;

void Player::Clear()
{
	quyu_point.clear();
	skill_flag = -1;
	move_num = 1;
	skill_num = 1;
	move_point.clear();
	jidi_point.clear();
	flag_window = 0;
	yuxuan_point = Point_None;
	before_point = Point_None;
}

int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, Player* player_,
	Skiller* skiller_, int flag_)
{
	//����class
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	player = player_;
	Point* temp_point = new Point(0, 0);
	jidi_point.emplace_back(temp_point);
	skiller = skiller_;
	if (main_window->GetGameModel() == FrightModel) {
		CreateSkillSum();
	}

	return 0;
}

int Player::Updata()
{
	if (map->Gethuihe() % 10 != 0) {
		flag_add = false;
	}
	for (int i = 0; i < 3; i++) {
		if (hand_skill_flag->at(i) == -1 && map->Gethuihe() % 10 == 0 && flag_add == false) {
			ChangeHand();
			flag_add = true;
			break;
		}
	}
	if (flag_window > 0) {
		flag_window++;
	}
	if (flag_window >= 100) {
		flag_window = 0;
	}

	//������Ҳ���
	if (map->Gethuihe() > 2 && map->Gethuihe() % 2 == flag) {
		if (IsLife() == DEAD) {
			main_window->GameIsEnd(flag);
			return 0;
		}
	}
	//��ɫ���
	if (flag == Red_Player)
	{
		//Ԥѡλ�������ƶ�
		if (input->GetKeyState(SDL_SCANCODE_W) == Key_Down)
		{
			yuxuan_point.y--;
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_S) == Key_Down)
		{
			yuxuan_point.y++;
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_A) == Key_Down)
		{

			yuxuan_point.x--;
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_D) == Key_Down)
		{
			yuxuan_point.x++;
		}
		//ѡ��
		//ѡ�����ʱ�ǵø��µ�ͼ
		//�ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down) { Movetion(); }
		//����
		else if (input->GetKeyState(SDL_SCANCODE_H) == Key_Down) {
			if (main_window->GetGameModel() == FrightModel) {
				Skill(1);
			}
			else {
				Skill();
			}
		}
		//����
		else if (input->GetKeyState(SDL_SCANCODE_J) == Key_Down) { Skill(2); }
		//����
		else if (input->GetKeyState(SDL_SCANCODE_K) == Key_Down) { Skill(3); }

	}
	//��ɫ���
	else
	{
		//Ԥѡλ�������ƶ�
		if (input->GetKeyState(SDL_SCANCODE_UP) == Key_Down)
		{
			yuxuan_point.y--;
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_DOWN) == Key_Down)
		{
			yuxuan_point.y++;
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_LEFT) == Key_Down)
		{
			yuxuan_point.x--;
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_RIGHT) == Key_Down)
		{
			yuxuan_point.x++;
		}
		//Ͷ����
		else if (input->GetKeyState(SDL_SCANCODE_KP_9) == Key_Keep) {
			main_window->GameIsEnd(flag);
			return 0;
		}
		//ѡ��
		//ѡ�����ʱ�ǵø��µ�ͼ
		//�ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_KP_0) == Key_Down) { Movetion(); }
		//����
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down) { 
			if (main_window->GetGameModel() == FrightModel) {
				Skill(1);
			}
			else {
				Skill();
			}
		}
		//����
		else if (input->GetKeyState(SDL_SCANCODE_KP_2) == Key_Down) { Skill(2); }
		//����
		else if (input->GetKeyState(SDL_SCANCODE_KP_3) == Key_Down) { Skill(3); }
	}
	//����Ԥѡλ���Ƿ񳬳���Χ
	if (yuxuan_point.x < 1) { yuxuan_point.x = 1; }
	else if (yuxuan_point.x > 7) { yuxuan_point.x = 7; }
	else if (yuxuan_point.y < 1) { yuxuan_point.y = 1; }
	else if (yuxuan_point.y > 7) { yuxuan_point.y = 7; }

	return 0;
}

void Player::UpdataSum()
{
	move_num = 1;
	skill_num = 1;
}

Point Player::Getyuxuan_point()
{
	//��Ԥѡλ�õ����ת��Ϊ��������
	if (flag == Red_Player)
	{
		return { yuxuan_point.x * 100 - 30,yuxuan_point.y * 100 - 30 };
	}
	else
	{
		return { yuxuan_point.x * 100 - 90,yuxuan_point.y * 100 - 30 };
	}
}

const vector<Point*>* Player::Getjidi_point()
{
	return &jidi_point;
}

const vector<Point*>* Player::Getmove_point()
{
	return &move_point;
}

const vector<QuYu*>* Player::Getquyu_point()
{
	return &quyu_point;
}


void Player::Changeskill_flag(int skill_flag_)
{
	skill_flag = skill_flag_;
	skill_flag_num = skiller->Getskill_flag_sum(skill_flag);
}

int Player::Getskill_flag()
{
	return skill_flag;
}

int Player::Getskill_flag_num()
{
	return skill_flag_num;
}

int Player::CreateSkillSum()
{
	int max = skiller->Getskill_sum();
	all_skill_sum = new vector<int>;
	//�����ܱ�ʶ��ӽ����ƶ�
	for (int i = 1; i < max + 1; i++) {
		all_skill_sum->emplace_back(i);
	}
	hand_skill_flag = new vector<int>;
	hand_skill_num = new vector<int>;

	for (int i = 0; i < 3; i++) {
		int rands = main_window->rander->GetARand(max - i);
		rands--;
		//����Ӧ�ļ��ܼ�������
		hand_skill_flag->emplace_back(all_skill_sum->at(rands));
		hand_skill_num->emplace_back(skiller->Getskill_flag_sum(all_skill_sum->at(rands)));
		//���ܵ��ƶ���ɾ���������Ƶļ�����
		all_skill_sum->erase(all_skill_sum->begin() + rands, all_skill_sum->begin() + rands + 1);
	}

	return 0;
}

int Player::ChangeHand()
{
	if (map->Gethuihe() % 10 == 0) {
		//�ж��ƶ����Ƿ��п���
		if (all_skill_sum->size() < 1) { return false; }
		int rands = main_window->rander->GetARand(all_skill_sum->size() - 1);
		rands--;
		int index = 0;
		for (int i = 0; i < 3; i++) {
			if (hand_skill_num->at(i) < 1) { index = i; break; }
		}
		//����Ӧ�ļ��ܼ�������
		int temp_skill = all_skill_sum->at(rands);
		hand_skill_flag->at(index) = temp_skill;
		hand_skill_num->at(index) = skiller->Getskill_flag_sum(temp_skill);
		//���ܵ��ƶ���ɾ���������Ƶļ�����
		all_skill_sum->erase(all_skill_sum->begin() + rands, all_skill_sum->begin() + rands + 1);
		return true;
	}
	return false;
}

const vector<int>* Player::GetHand()
{
	return hand_skill_flag;
}

int Player::GetHandNum(int index_)
{
	return hand_skill_num->at(index_);
}

Point* Player::ToMapPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 50, point_->y * 100 - 50);
	return temp;
}

Point* Player::TojidiPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 75, point_->y * 100 - 75);
	return temp;
}

Point* Player::ToquyuPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 60, point_->y * 100 - 60);
	return temp;
}

Point Player::MapToIndex(Point* point_)
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (i * 100 < point_->x && (i + 1) * 100 > point_->x && j * 100 < point_->y && (j + 1) * 100 > point_->y) {
				return { i + 1,j + 1 };
			}
		}
	}
	return { -1,0 };
}

Point Player::MapToMap(Point* point_)
{
	//����ת��Ϊ��ͼ����+1
	Point temp_point = MapToIndex(point_);
	//ת��Ϊ���ĵ�λ
	temp_point.x = temp_point.x * 100 - 50;
	temp_point.y = temp_point.y * 100 - 50;
	return temp_point;
}

int Player::CanMove()
{
	skill_num--;
	move_num--;
	//�����ƶ�����ʱ
	if (move_num >= 1) {
		//���µ�ͼ �������»غ�
		map->Updata(&yuxuan_point, flag, ZHAN, false);
		return true;
	}
	//û���ƶ������ͼ��ܴ���ʱ
	else if (move_num < 1 && skill_num < 1) {
		//���µ��˵��ƶ��ͼ��ܴ���
		//���µ�ͼ
		player->UpdataSum();
		map->Updata(&yuxuan_point, flag, ZHAN, true);
		return false;
	}
}

int Player::MoveIsRight(bool flag_, Point point_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 1 || point_.x > 7 || point_.y < 1 || point_.y > 7) { return NOPOINT; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	//���һ����λ ��ֵ
	int index = move_point.size() - 1;
	Point before = *move_point.at(index);
	//�жϱ�ʶ
	if (before.x == JIDI) {
		before = MapToMap(jidi_point.back());//�����ص�λת��Ϊ���ĵ�λ
	}
	else if (before.x == QUYU) {
		//��ǰ����֪���ҵ���ʹ�õĵ�λ
		while (index >= 0) {
			index--;
			before = *move_point.at(index);
			if (before.x == JIDI) {
				before = MapToMap(jidi_point.at(before.y));
				break;
			}
			else if (before.x > QUYU) {
				break;
			}
		}
	}
	Point* now = ToMapPoint(temp);//���ڵĵ�λ
	//��������֮��ľ����Ƿ�����ȷ��
	int distance = static_cast<int>(
		sqrt((
			(before.x - now->x) * (before.x - now->x) +
			(before.y - now->y) * (before.y - now->y)
			))
		);
	if (distance > 199) { return TOO_LONG; }
	//�Ƿ���
	else if (map->IsThoughLine(
		before_point.x - 1, temp->y - 1, temp->x - 1, before_point.y - 1)
		) {
		return THOUGH;
	}
	else { return true; }
}

//flag = false
int Player::Movetion(int flag_)
{
	//��ʾ���ڴ�С
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//�ж��Ƿ�����ҵĻغ�
	if (map->Gethuihe() % 2 == flag || flag_)
	{
		//���û���ƶ�����
		if (move_num < 1) {
			if (flag_window == 0 && !flag_) {
				main_window->Player_Window(L"�����ƶ�", text_rect, flag_window);
			}
			return false;
		}
		//��ͼ��λδ��ռ��
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//���ػ�ûȷ��������ȷ������
			if (!(*jidi_point[0]).x) {
				map->Updata(&yuxuan_point, flag, ZHAN, true);//���µ�ͼ���غ�����
				//��Ԥѡ��λת��Ϊ��ͼ��λ��������
				jidi_point[0]->x = yuxuan_point.x * 100 - 75;
				jidi_point[0]->y = yuxuan_point.y * 100 - 75;
				before_point = yuxuan_point;
				//����
				Point* point = new Point(*jidi_point[0]);
				point->x += 25;
				point->y += 25;
				move_point.emplace_back(point);//����λ����
				return true;
			}
			else {
				switch (MoveIsRight()) {
				case true:
					before_point = yuxuan_point;
					move_point.emplace_back(ToMapPoint(&yuxuan_point));//����λ����
					CanMove();
					return true;
				case TOO_LONG:
					//��ʾ��Ҿ������
					if (flag_window == 0 && !flag_) {
						main_window->Player_Window(L"�������", text_rect, flag_window);
					}
					return false;
				case THOUGH:
					//��ʾ��ҽ�ֹ����
					if (flag_window == 0 && !flag_) {
						main_window->Player_Window(L"��ֹ����", text_rect, flag_window);
					}
					return false;
				}
			}
		}
		else
		{
			//��λ��ռ��
			if (flag_window == 0 && !flag_) {
				main_window->Player_Window(L"��λ��ռ", text_rect, flag_window);
			}
			return false;
		}
	}
	else {
		if (flag_window == 0 && !flag_) {
			//�ֵ�����
			main_window->Player_Window(L"���˻غ�", text_rect, flag_window);
		}
		return false;
	}
}

int Player::Skill(int flag_)
{
	//��ʾ���ڴ�С
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//���ػ�δ�����޷�ʹ�ü���
	if (jidi_point[0]->x == 0) {
		main_window->Player_Window(L"����δ��", text_rect, flag_window);
	}
	//����ʹ�ô�����
	else if (skill_num < 1) {
		main_window->Player_Window(L"����ʹ��", text_rect, flag_window);
	}
	//���˵Ļغ�
	else if (map->Gethuihe() % 2 != flag) {
		main_window->Player_Window(L"���˻غ�", text_rect, flag_window);
	}
	else {
		if (main_window->GetGameModel() != FrightModel && skill_flag_num < 1) {
			main_window->Player_Window(L"ʹ��ʧ��", text_rect, flag_window);
			return false;
		}
		else if (main_window->GetGameModel() == FrightModel && hand_skill_num->at(flag_ - 1) < 1) {
			main_window->Player_Window(L"ʹ��ʧ��", text_rect, flag_window);
			return false;
		}
		//���ü���ʹ�ú���
		//�Ƿ���»غ��ڼ���ʹ�����Ѿ�����
		int temp_skill_flag = skill_flag;
		if (flag_ > 0) {
			temp_skill_flag = hand_skill_flag->at(flag_ - 1);
		}
		if (skiller->Use_Skill(temp_skill_flag, flag)) { 
			//�غϼ������ͼ����ܴ�����-1
			skill_num--;
			if (main_window->GetGameModel() == FrightModel) {
				hand_skill_num->at(flag_ - 1)--;
				if (hand_skill_num->at(flag_ - 1) < 1) {
					hand_skill_flag->at(flag_ - 1) = -1;
				}
			}
			else {
				skill_flag_num--;
			}
		}
		else { main_window->Player_Window(L"ʹ��ʧ��", text_rect, flag_window); }
	}
	return 0;
}

/*
* (x-1,y-1)(x,y-1)(x+1,y-1)
* (x-1,y)  (x,y)  (x+1,y)
* (x-1,y+1)(x,y+1)(x+1,y+1)
*/
int Player::IsLife()
{
	bool isLife = DEAD;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map->GetMapStatexy(before_point.x + i, before_point.y + j).zhan_Point == NONE) {
				if (MoveIsRight(true, { before_point.x + i,before_point.y + j }) == true) {
					isLife = LIFE;
				}
			}
		}
	}
	if (main_window->GetGameModel() == FrightModel) {
		for (int i = 0; i < 3; i++) {
			if (skiller->IsLiveSkill(hand_skill_flag->at(i)) && hand_skill_num->at(i) > 0) {
				isLife = LIFE;
			}
		}
	}
	else {
		if (skiller->IsLiveSkill(skill_flag) && skill_flag_num > 0) {
			isLife = LIFE;
		}
	}
	return isLife;
}

#pragma message("player.cpp is loaded")