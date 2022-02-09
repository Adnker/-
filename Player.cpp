#include "Player.h"
#include "Map.h"
#include "myFun.h"

const int TOO_LONG = 2;
const int THOUGH = 3;
const int NOPOINT = 4;


/*
* ��ʼ������
*/
int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, Player* player_,
	Skiller* skiller_, int flag_)
{
	//����class
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	player = player_;
	skiller = skiller_;
	skill_num = 1;
	move_num = 1;
	if (flag == Red_Player) {
		picture_name = "reddown.png";
	}
	else {
		picture_name = "bluedown.png";
	}
	if (main_window->GetGameModel() == FrightModel) {
		CreateAllSkill();
	}
	return 0;
}


/*
* �������
*/
int Player::Clear()
{
	move_num = 1;
	skill_num = 1;
	window_time = 0;
	yuxuan_point = { 0,0 };
	return true;
}


/*
* ����
*/
int Player::Updata()
{
	if (window_time > 0) {
		window_time++;
	}
	if (window_time >= 100) {
		window_time = 0;
	}

	//������Ҳ���
	//�ж�����Ƿ�����
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
			if (!SkillNeedShow()) {
				yuxuan_point.y--;
				picture_name = "redup.png";
			}
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_S) == Key_Down)
		{
			if (!SkillNeedShow()) {
				yuxuan_point.y++;
				picture_name = "reddown.png";
			}
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_A) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(-1);
			}
			else {
				yuxuan_point.x--;
				picture_name = "redleft.png";
			}
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_D) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(1);
			}
			else {
				yuxuan_point.x++;
				picture_name = "redright.png";
			}
		}
		//ѡ��
		//ѡ�����ʱ�ǵø��µ�ͼ
		//�ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down)
		{
			if (SkillNeedShow()) {
				Skill(skill_state);
				skill_state = -1;
			}
			else { Movetion(); }
		}
		//����
		else if (input->GetKeyState(SDL_SCANCODE_H) == Key_Down)
		{
			if (main_window->GetGameModel() != BaseModel) {
				if (SkillNeedShow()) { skill_state = -1; }
				else { skill_state = 0; }
			}
		}
		else if (input->GetKeyState(SDL_SCANCODE_J) == Key_Down)
		{
			Xuhand();
		}

	}
	//��ɫ���
	else
	{
		//Ԥѡλ�������ƶ�
		if (input->GetKeyState(SDL_SCANCODE_UP) == Key_Down)
		{
			if (!SkillNeedShow()) {
				yuxuan_point.y--;
				picture_name = "blueup.png";
			}
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_DOWN) == Key_Down)
		{
			if (!SkillNeedShow()) {
				yuxuan_point.y++;
				picture_name = "bluedown.png";
			}
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_LEFT) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(-1);
			}
			else {
				yuxuan_point.x--;
				picture_name = "blueleft.png";
			}
		}
		//Ԥѡλ�������ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_RIGHT) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(1);
			}
			else {
				yuxuan_point.x++;
				picture_name = "blueright.png";
			}
		}
		//ѡ��
		//ѡ�����ʱ�ǵø��µ�ͼ
		//�ƶ�
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down)
		{
			if (SkillNeedShow()) {
				Skill(skill_state);
				skill_state = -1;
			}
			else { Movetion(); }
		}
		else if (input->GetKeyState(SDL_SCANCODE_KP_2) == Key_Down)
		{
			if (main_window->GetGameModel() != BaseModel) {
				if (SkillNeedShow()) { skill_state = -1; }
				else { skill_state = 0; }
			}
		}
		else if (input->GetKeyState(SDL_SCANCODE_KP_3) == Key_Down)
		{
			Xuhand();
		}
	}
	//����Ԥѡλ���Ƿ񳬳���Χ
	if (yuxuan_point.x < 0) { yuxuan_point.x = 0; }
	else if (yuxuan_point.x > 6) { yuxuan_point.x = 6; }
	else if (yuxuan_point.y < 0) { yuxuan_point.y = 0; }
	else if (yuxuan_point.y > 6) { yuxuan_point.y = 6; }

	return 0;
}


/*
* ������ҵ��ƶ����������ܿ�ʹ�ô���
* ÿ�λغϸ��µ�ʱ����Ҫ���õ��˵��������
*/
void Player::UpdataSum()
{
	move_num = 1;
	skill_num = 1;
}


/*
* ��ȡ��ҵ�Ԥѡ��λ
*/
Point Player::Getyuxuan_point()
{
	//��Ԥѡλ�õ����ת��Ϊ��������
	if (flag == Red_Player)
	{
		return { yuxuan_point.x * 100 + 10,yuxuan_point.y * 100 + 70 };
	}
	else
	{
		return { yuxuan_point.x * 100 + 70,yuxuan_point.y * 100 + 70 };
	}
}


/*
* ���ص�λת��Ϊ��ͨ��ͼ��λ
*/
Point Player::JidiToMap(Move_point* point_)
{
	if (point_->flag != JIDI) {
		return { -1,-1 };
	}
	else {
		return { point_->point->x * 100 + 30,point_->point->y * 100 + 30 };
	}
}


/*
* ��λת��Ϊ��ͼ��λ
*/
Point Player::ToMapPoint(Point* point_)
{
	return { point_->x * 100 + 50,point_->y * 100 + 50 };
}


/*
* ��ȡ��Ҽ�������
*/
vector<int>* Player::Getskill()
{
	return &skill;
}


/*
* ��ȡ��Ӧ����index���ܵ�ʣ����ô���
*/
int Player::Getskill_sum(int index)
{
	return skill_sum.at(index);
}


/*
* ��ȡ�ƶ�����
*/
vector<Move_point*>* Player::GetMove_point()
{
	return &move_point;
}


/*
* �޸���ҵļ���
*/
int Player::Changeskill(int index)
{
	if (skill.empty()) {
		skill.emplace_back(index);
		skill_sum.emplace_back(skiller->GetSkillSum(index));
		return true;
	}
	return false;
}


/*
* ��ȡ�����һ֡��Ҫ��ʾ��ͼƬ����
*/
string Player::Getpicture_name()
{
	return picture_name;
}


/*
* �ж�ս�������Ƿ���Ҫ���Ƽ���
* ����ֵΪtrueʱ ����ShowSkill_index����
*/
bool Player::SkillNeedShow()
{
	if (main_window->GetGameModel() == FrightModel) {
		return skill_state > -1 && skill_state < 3;
	}
	else {
		return skill_state > -1 && skill_state < 1;
	}
}


/*
* ��Ҫ���Ƽ���ʱ���ô˺�����ȡ��Ҫ���Ƶļ�������
* SkillNeedShow����Ϊtrueʱ����
*/
int Player::ShowSkill_index()
{
	return skill_state;
}


/*
* ��ȡ��Ҫ���Ƽ��ܵľ���
* SkillNeedShow����Ϊtrue�ǵ���
*/
SDL_Rect Player::ShowSkill_rect()
{
	return { Getyuxuan_point().x,Getyuxuan_point().y + 30,50,50 };
}


/*
* ����ģʽ���ô˺���Ϊ��ҷ��似��
*/
int Player::CreateAllSkill()
{
	for (SKILL i = 1; i < SKILLSUM; i++) {
		skill_all.emplace_back(i);
	}
	while (skill.size() < 3) {
		int rand = main_window->rander->GetARand(skill_all.size() - 1);
		skill.emplace_back(skill_all.at(rand));
		skill_all.erase(skill_all.begin() + rand, skill_all.begin() + rand + 1);
		skill_sum.emplace_back(skiller->GetSkillSum(skill.back()));
	}
	return 0;
}


/*
* ����ģʽÿ5�����ص���һ���������
*/
int Player::AddSkill()
{
	if (map->Gethuihe() % 10 != 0 || map->Gethuihe() < 1) { return false; }
	int index = 0;
	for (int i = 0; i < skill_sum.size(); i++) {
		if (skill_sum.at(i) < 0) {
			index = i;
			break;
		}
	}
	int rand = main_window->rander->GetARand(skill_all.size() - 1);
	skill.at(index) = skill_all.at(rand);
	skill_all.erase(skill_all.begin() + rand, skill_all.begin() + rand + 1);
	skill_sum.at(index) = skiller->GetSkillSum(skill.back());
	return true;
}


/*
* ��ȡ��һ�����ص�λ������ͨ��λ��һ����Ϊ����·�ߵ�����
* ��·�ߵ�λ����� GetBeforePointXu
*/
Point* Player::GetBeforePoint()
{
	int index = GetBeforePoint_index();
	auto point = index == -1 ? Point(-1, -1) : *move_point.at(index)->point;
	return &point;
}


/*
* ��ȡ��һ����·�ߵ�λ
* ʵ·�ߵ�λ����� GetBeforePoint
*/
Point* Player::GetBeforePointXu()
{
	int index = GetBeforePointXu_index();
	auto point = index == -1 ? Point(-1, -1) : *move_point.at(index)->point;
	return &point;
}



/*
* ��ȡ��һ�����ص�λ����ͨ��λ������
* ��·����������� GetBeforePointXu_index
*/
int Player::GetBeforePoint_index()
{
	int index = move_point.size() - 1;
	while (move_point.at(index)->hand != ZHU_HAND) {
		index--;
	}
	return index;
}


/*
* ��ȡ��һ����·�ߵ�λ������
* ʵ·����������� GetBeforePoint_index
*/
int Player::GetBeforePointXu_index()
{
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	int index = move_point.size() - 1;
	if (move_point.empty()) {
		main_window->Player_Window(L"����·��", text_rect, window_time, flag);
		return -1;
	}
	while (move_point.at(index)->hand != XU_HAND) {
		index--;
		if (index == -1) {
			return -1;
		}
	}
	return index;
}


/*
* �ж�����ܷ�����ƶ�
* �ڻغ��ƶ�����ü�飬���Զ���ɻغϽ�������
*/
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


/*
* �ж��ƶ���λ�Ƿ���Ϲ淶
* flag_ �Ƿ���������λ
* point_ ������λ����flag_Ϊfalseʱ�˲���������
* xuhand_flag_ �Ƿ�����·��ͷ
*/
int Player::MoveIsRight(bool flag_, Point point_, bool xuhand_flag_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 0 || point_.x > 6 || point_.y < 0 || point_.y > 6) { return NOPOINT; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	//���һ����λ ��ֵ
	int index = move_point.size() - 1;
	Point before = ToMapPoint(xuhand_flag_ ? GetBeforePointXu() : GetBeforePoint());//��һ��λ
	Point now = ToMapPoint(temp);//���ڵĵ�λ
	//��������֮��ľ����Ƿ�����ȷ��
	int distance = static_cast<int>(
		sqrt((
			(before.x - now.x) * (before.x - now.x) +
			(before.y - now.y) * (before.y - now.y)
			))
		);
	Point* before_point = move_point.at(move_point.size() - 1)->point;
	if (distance > 199) { return TOO_LONG; }
	//�Ƿ���
	else if (
		map->IsThoughLine(
			before_point->x, temp->y, temp->x, before_point->y)
		) {
		return THOUGH;
	}
	else { return true; }
}


/*
* �ƶ�����
* flag_ �Ƿ���ǿ���ƶ�
*/
int Player::Movetion(int flag_)
{
	//��ʾ���ڴ�С
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//�ж��Ƿ�����ҵĻغ�
	if (map->Gethuihe() % 2 == flag || flag_)
	{
		//���û���ƶ�����
		if (move_num < 1) {
			if (window_time == 0 && !flag_) {
				main_window->Player_Window(L"�����ƶ�", text_rect, window_time, flag);
			}
			return false;
		}
		//��ͼ��λδ��ռ��
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//���ػ�ûȷ��������ȷ������
			if (move_point.empty()) {
				map->Updata(&yuxuan_point, flag, ZHAN, true);//���µ�ͼ���غ�����
				//�����µĵ�λ�������ж�������
				Move_point* temp_point = new Move_point(yuxuan_point, JIDI);
				move_point.emplace_back(temp_point);
				return true;
			}
			else {
				Move_point* point;
				switch (MoveIsRight()) {
				case true:
					point = new Move_point(yuxuan_point, NULL);
					move_point.emplace_back(point);//����λ����
					CanMove();
					return true;
				case TOO_LONG:
					//��ʾ��Ҿ������
					if (window_time == 0 && !flag_) {
						main_window->Player_Window(L"�������", text_rect, window_time, flag);
					}
					return false;
				case THOUGH:
					//��ʾ��ҽ�ֹ����
					if (window_time == 0 && !flag_) {
						main_window->Player_Window(L"��ֹ����", text_rect, window_time, flag);
					}
					return false;
				}
			}
		}
		else
		{
			//��λ��ռ��
			if (window_time == 0 && !flag_) {
				main_window->Player_Window(L"��λ��ռ", text_rect, window_time, flag);
			}
			return false;
		}
	}
	else {
		if (window_time == 0 && !flag_) {
			//�ֵ�����
			main_window->Player_Window(L"���˻غ�", text_rect, window_time, flag);
		}
		return false;
	}
}


/*
* ���ܺ���
* index_ ʹ�ü��������Ǹ�����index��Ӧ�ļ���
*/
int Player::Skill(int index_)
{
	//��ʾ���ڴ�С
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	if (main_window->GetGameModel() == SkillModel) {
		if (index_ > 0) {
			main_window->Player_Window(L"ʹ��ʧ��", text_rect, window_time, flag);
			return 0;
		}
	}
	//���ػ�δ�����޷�ʹ�ü���
	if (move_point.empty()) {
		main_window->Player_Window(L"����δ��", text_rect, window_time, flag);
	}
	//����ʹ�ô�����
	else if (skill_num < 1) {
		main_window->Player_Window(L"����ʹ��", text_rect, window_time, flag);
	}
	//���˵Ļغ�
	else if (map->Gethuihe() % 2 != flag) {
		main_window->Player_Window(L"���˻غ�", text_rect, window_time, flag);
	}
	//���ܶ�Ӧ��ʹ�ô���С��1
	else if (skill_sum.at(index_) < 1) {
		main_window->Player_Window(L"ʹ��ʧ��", text_rect, window_time, flag);
	}
	else {
		//���ü���ʹ�ú���
		//�Ƿ���»غ��ڼ���ʹ�����Ѿ�����
		if (skiller->Use_Skill(skill.at(index_), flag)) {
			//�غϼ������ͼ����ܴ�����-1
			skill_num--;
			skill_sum.at(index_)--;
			return true;
		}
		else { main_window->Player_Window(L"ʹ��ʧ��", text_rect, window_time, flag); }
	}
	return false;
}


/*
* ��·��ͷ�ƶ�����
*/
int Player::Xuhand()
{
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	if (main_window->GetGameModel() == BaseModel)
	{
		return false;
	}
	int index = GetBeforePointXu_index();
	if (index == -1) {
		main_window->Player_Window(L"����·��", text_rect, window_time, flag);
		return false;
	}
	switch (MoveIsRight(false, Point(-1, -1), true))
	{
	case NOPOINT:
		return false;
	case TOO_LONG:
		main_window->Player_Window(L"�������", text_rect, window_time, flag);
		return false;
	case THOUGH:
		main_window->Player_Window(L"��ֹ����", text_rect, window_time, flag);
		return false;
	default:
		Move_point* point = new Move_point(yuxuan_point, index, XU_HAND);
		move_point.emplace_back(point);
		CanMove();
		return true;
	}
}


/*
* �ж�����Ƿ�����
* ÿ���غ϶���Ҫ����һ���ж�
*/
int Player::IsLife()
{
	bool isLife = DEAD;
	Point* before_point = GetBeforePoint();
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map->GetMapStatexy(before_point->x + i, before_point->y + j).zhan_Point == NONE) {
				if (MoveIsRight(true, { before_point->x + i,before_point->y + j }) == true) {
					isLife = LIFE;
				}
			}
		}
	}
	if (skill_num < 1 && map->Gethuihe() % 2 == flag) {
		return isLife;
	}
	//�ж���ҵļ����Ƿ����ʹ��
	int model = main_window->GetGameModel();
	if (model == FrightModel) {
		for (int i = 0; i < 3; i++) {
			if (skiller->IsLiveSkill(skill.at(i)) && skill.at(i) > 0) {
				isLife = LIFE;
			}
		}
	}
	else if (model == SkillModel) {
		if (skiller->IsLiveSkill(skill.at(0)) && skill_sum.at(0) > 0) {
			isLife = LIFE;
		}
	}
	return isLife;
}


/*
* �޸���Ҫ��ʾ�ļ��ܵ�״̬
*/
int Player::Change_skill_state(int flag)
{
	if (SkillNeedShow() && main_window->GetGameModel() == FrightModel) {
		if (skill_state + flag > -1 && skill_state + flag < 3) {
			skill_state += flag;
			return true;
		}
	}
	return false;
}