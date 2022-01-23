#include "Player.h"
#include "Map.h"
#include <math.h>

const int TOO_LONG = 2;
const int THOUGH = 3;

int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, int flag_)
{
	//����Input
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	return 0;
}

int Player::Updata()
{
	if (flag_window > 0) { flag_window++; }
	if (flag_window >= 150) { flag_window = 0; }
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
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down)
		{
			Movetion();
		}

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
		//ѡ��
		//ѡ�����ʱ�ǵø��µ�ͼ
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down)
		{
			Movetion();
		}
	}
	//����Ԥѡλ���Ƿ񳬳���Χ
	if (yuxuan_point.x < 1) { yuxuan_point.x = 1; }
	else if (yuxuan_point.x > 7) { yuxuan_point.x = 7; }
	else if (yuxuan_point.y < 1) { yuxuan_point.y = 1; }
	else if (yuxuan_point.y > 7) { yuxuan_point.y = 7; }

	return 0;
}

Point Player::Getyuxuan_point()
{
	//��Ԥѡλ�õ����ת��Ϊ��������
	Point temp;
	if (flag == Red_Player)
	{
		temp.x = yuxuan_point.x * 100 - 30;
		temp.y = yuxuan_point.y * 100 - 30;
	}
	else
	{
		temp.x = yuxuan_point.x * 100 - 90;
		temp.y = yuxuan_point.y * 100 - 30;
	}
	return temp;
}

Point Player::Getjidi_point()
{
	return jidi_point;
}

Point* Player::ToMapPoint(Point* point_)
{
	Point* temp = new Point();
	temp->x = point_->x * 100 - 50;
	temp->y = point_->y * 100 - 50;
	return temp;
}

int Player::MoveIsRight(bool flag_, Point point_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 1 || point_.x > 7 || point_.y < 1 || point_.y > 7) { return THOUGH; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	Point* before = move_point[move_point.size() - 1];//���һ����λ
	Point* now = ToMapPoint(temp);//���ڵĵ�λ
	//��������֮��ľ����Ƿ�����ȷ��
	int distance = static_cast<int>(
		sqrt((
			(before->x - now->x) * (before->x - now->x) +
			(before->y - now->y) * (before->y - now->y)
			))
		);
	if (distance > 190) { return TOO_LONG; }
	else if (map->IsThoughLine(
		before_point.x - 1, temp->y - 1, temp->x - 1, before_point.y - 1)
		) {
		return THOUGH;
	}
	else { return true; }
}

int Player::Movetion()
{
	//�ж��Ƿ�����ҵĻغ�
	if (map->Gethuihe() % 2 == flag)
	{
		//��ͼ��λδ��ռ��
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//���ػ�ûȷ��������ȷ������
			if (!jidi_point.x) {
				map->Update(&yuxuan_point, flag);//���µ�ͼ
				//��Ԥѡ��λת��Ϊ��ͼ��λ��������
				jidi_point.x = yuxuan_point.x * 100 - 75;
				jidi_point.y = yuxuan_point.y * 100 - 75;
				before_point = yuxuan_point;
				//����
				Point* point = new Point(jidi_point);
				point->x += 25;
				point->y += 25;
				move_point.emplace_back(point);//����λ����
			}
			else {
				switch (MoveIsRight()) {
				case 1:
					map->Update(&yuxuan_point, flag);//���µ�ͼ
					before_point = yuxuan_point;
					move_point.emplace_back(ToMapPoint(&yuxuan_point));//����λ����
					break;
				case TOO_LONG:
					//��ʾ��Ҿ������
					if (flag_window == 0) {
						flag_window++;
						main_window->Player_Window(L"�������",
							{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
					}
					break;
				case THOUGH:
					//��ʾ��ҽ�ֹ����
					if (flag_window == 0) {
						flag_window++;
						main_window->Player_Window(L"��ֹ����",
							{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
					}
					break;
				}
			}
		}
		else
		{
			//��λ��ռ��
			if (flag_window == 0) {
				flag_window++;
				main_window->Player_Window(L"��λ��ռ",
					{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
			}
		}
	}
	else {
		if (flag_window == 0) {
			flag_window++;
			//�ֵ�����
			main_window->Player_Window(L"���˻غ�",
				{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
		}
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
			if (map->GetMapStatexy(before_point.x + i, before_point.y + j).zhan_Point == NONE){
				if (MoveIsRight(true, { before_point.x + i,before_point.y + j }) == 1) {
					isLife = LIFE;
				}
			}
		}
	}
	return isLife;
}
