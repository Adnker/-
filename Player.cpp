#include "Player.h"
#include "Map.h"
#include "myMath.h"
#pragma message("Loading player.cpp")

const int TOO_LONG = 2;
const int THOUGH = 3;
const int NOPOINT = 4;

int Player::Clear()
{
	move_num = 1;
	skill_num = 1;
	window_time = 0;
	yuxuan_point = { 0,0 };
	return true;
}

int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, Player* player_,
	Skiller* skiller_, int flag_)
{
	//复制class
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	player = player_;
	skiller = skiller_;
	skill_num = 1;
	move_num = 1;
	/*if (main_window->GetGameModel() == FrightModel) {
		CreateSkillSum();
	}*/

	return 0;
}

int Player::Updata()
{
	if (window_time > 0) {
		window_time++;
	}
	if (window_time >= 100) {
		window_time = 0;
	}

	//更新玩家操作
	//判断玩家是否死亡
	if (map->Gethuihe() > 2 && map->Gethuihe() % 2 == flag) {
		if (IsLife() == DEAD) {
			main_window->GameIsEnd(flag);
			return 0;
		}
	}

	//红色玩家
	if (flag == Red_Player)
	{
		//预选位置向上移动
		if (input->GetKeyState(SDL_SCANCODE_W) == Key_Down)
		{
			yuxuan_point.y--;
		}
		//预选位置向下移动
		else if (input->GetKeyState(SDL_SCANCODE_S) == Key_Down)
		{
			yuxuan_point.y++;
		}
		//预选位置向左移动
		else if (input->GetKeyState(SDL_SCANCODE_A) == Key_Down)
		{

			yuxuan_point.x--;
		}
		//预选位置向右移动
		else if (input->GetKeyState(SDL_SCANCODE_D) == Key_Down)
		{
			yuxuan_point.x++;
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down) { Movetion(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_H) == Key_Down) { Skill(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_J) == Key_Down) { Skill(1); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_K) == Key_Down) { Skill(2); }

	}
	//蓝色玩家
	else
	{
		//预选位置向上移动
		if (input->GetKeyState(SDL_SCANCODE_UP) == Key_Down)
		{
			yuxuan_point.y--;
		}
		//预选位置向下移动
		else if (input->GetKeyState(SDL_SCANCODE_DOWN) == Key_Down)
		{
			yuxuan_point.y++;
		}
		//预选位置向左移动
		else if (input->GetKeyState(SDL_SCANCODE_LEFT) == Key_Down)
		{
			yuxuan_point.x--;
		}
		//预选位置向右移动
		else if (input->GetKeyState(SDL_SCANCODE_RIGHT) == Key_Down)
		{
			yuxuan_point.x++;
		}
		//投降键
		else if (input->GetKeyState(SDL_SCANCODE_KP_9) == Key_Keep) {
			main_window->GameIsEnd(flag);
			return 0;
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_KP_0) == Key_Down) { Movetion(); }
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down) { Skill(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_KP_2) == Key_Down) { Skill(1); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_KP_3) == Key_Down) { Skill(2); }
	}
	//检验预选位置是否超出范围
	if (yuxuan_point.x < 0) { yuxuan_point.x = 0; }
	else if (yuxuan_point.x > 6) { yuxuan_point.x = 6; }
	else if (yuxuan_point.y < 0) { yuxuan_point.y = 0; }
	else if (yuxuan_point.y > 6) { yuxuan_point.y = 6; }

	return 0;
}

void Player::UpdataSum()
{
	move_num = 1;
	skill_num = 1;
}

Point Player::Getyuxuan_point()
{
	//将预选位置的左边转化为窗口坐标
	if (flag == Red_Player)
	{
		return { yuxuan_point.x * 100 + 10,yuxuan_point.y * 100 + 70 };
	}
	else
	{
		return { yuxuan_point.x * 100 + 70,yuxuan_point.y * 100 + 70 };
	}
}

Point Player::JidiToMap(Move_point* point_)
{
	if (point_->flag != JIDI) {
		return { -1,-1 };
	}
	else {
		return { point_->point->x * 100 + 30,point_->point->y * 100 + 30 };
	}
}

Point Player::ToMapPoint(Point* point_)
{
	return { point_->x * 100 + 50,point_->y * 100 + 50 };
}

vector<int>* Player::Getskill()
{
	return &skill;
}

int Player::Getskill_sum(int index)
{
	return skill_sum.at(index);
}

vector<Move_point*>* Player::GetMove_point()
{
	return &move_point;
}

int Player::Changeskill(int index)
{
	if (skill.empty()) {
		skill.emplace_back(index);
		skill_sum.emplace_back(skiller->GetSkillSum(index));
		return true;
	}
	return false;
}

int Player::Getskill_num(int index_)
{
	return skill_sum.at(index_);
}

int Player::CanMove()
{
	skill_num--;
	move_num--;
	//还有移动次数时
	if (move_num >= 1) {
		//更新地图 但不更新回合
		map->Updata(&yuxuan_point, flag, ZHAN, false);
		return true;
	}
	//没有移动次数和技能次数时
	else if (move_num < 1 && skill_num < 1) {
		//更新敌人的移动和技能次数
		//更新地图
		player->UpdataSum();
		map->Updata(&yuxuan_point, flag, ZHAN, true);
		return false;
	}
}

//point_ = {-1,-1}
//flag_ = false
int Player::MoveIsRight(bool flag_, Point point_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 0 || point_.x > 6 || point_.y < 0 || point_.y > 6) { return NOPOINT; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	//最后一个点位 赋值
	int index = move_point.size() - 1;
	Point before = ToMapPoint(move_point.at(index)->point);
	//判断标识
	if (move_point.at(index)->flag == JIDI) {
		before = JidiToMap(move_point.at(index));//将基地点位转化为中心点位
	}
	else if (move_point.at(index)->flag == QUYU) {
		//向前遍历知道找到可使用的点位
		while (index >= 0) {
			index--;
			if (move_point.at(index)->flag == JIDI) {
				before = JidiToMap(move_point.at(index));
				break;
			}
			else if (move_point.at(index) == NULL) {
				before = ToMapPoint(move_point.at(index)->point);
				break;
			}
		}
	}
	Point now = ToMapPoint(temp);//现在的点位
	//计算两点之间的距离是否是正确的
	int distance = static_cast<int>(
		sqrt((
			(before.x - now.x) * (before.x - now.x) +
			(before.y - now.y) * (before.y - now.y)
			))
		);
	Point* before_point = move_point.at(move_point.size() - 1)->point;
	if (distance > 199) { return TOO_LONG; }
	//是否穿线
	else if (
		map->IsThoughLine(
		before_point->x, temp->y, temp->x, before_point->y)
		) {
		return THOUGH;
	}
	else { return true; }
}

//flag = false 是否是强制移动
int Player::Movetion(int flag_)
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//判断是否是玩家的回合
	if (map->Gethuihe() % 2 == flag || flag_)
	{
		//如果没有移动次数
		if (move_num < 1) {
			if (window_time == 0 && !flag_) {
				main_window->Player_Window(L"不可移动", text_rect, window_time);
			}
			return false;
		}
		//地图点位未被占用
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//基地还没确定，优先确定基地
			if (move_point.empty()) {
				map->Updata(&yuxuan_point, flag, ZHAN, true);//更新地图，回合增加
				//创建新的点位并加入行动数组中
				Move_point* temp_point = new Move_point(yuxuan_point, JIDI);
				move_point.emplace_back(temp_point);
				return true;
			}
			else {
				Move_point* point;
				switch (MoveIsRight()) {
				case true:
					point = new Move_point(yuxuan_point, NULL);
					move_point.emplace_back(point);//将点位加入
					CanMove();
					return true;
				case TOO_LONG:
					//提示玩家距离过长
					if (window_time == 0 && !flag_) {
						main_window->Player_Window(L"距离过长", text_rect, window_time);
					}
					return false;
				case THOUGH:
					//提示玩家禁止穿线
					if (window_time == 0 && !flag_) {
						main_window->Player_Window(L"禁止穿线", text_rect, window_time);
					}
					return false;
				}
			}
		}
		else
		{
			//点位被占用
			if (window_time == 0 && !flag_) {
				main_window->Player_Window(L"点位被占", text_rect, window_time);
			}
			return false;
		}
	}
	else {
		if (window_time == 0 && !flag_) {
			//轮到敌人
			main_window->Player_Window(L"敌人回合", text_rect, window_time);
		}
		return false;
	}
}

int Player::Skill(int index_)
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//基地还未放置无法使用技能
	if (move_point.empty()) {
		main_window->Player_Window(L"基地未放", text_rect, window_time);
	}
	//技能使用次数少
	else if (skill_num < 1) {
		main_window->Player_Window(L"不可使用", text_rect, window_time);
	}
	//敌人的回合
	else if (map->Gethuihe() % 2 != flag) {
		main_window->Player_Window(L"敌人回合", text_rect, window_time);
	}
	//技能对应的使用次数小于1
	else if (skill_sum.at(index_) < 1) {
		main_window->Player_Window(L"使用失败", text_rect, window_time);
	}
	else {
		//调用技能使用函数
		//是否更新回合在技能使用中已经调用
		if (skiller->Use_Skill(skill.at(index_), flag)) {
			//回合技能数和技能总次数均-1
			skill_num--;
			skill_sum.at(index_)--;
		}
		else { main_window->Player_Window(L"使用失败", text_rect, window_time); }
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
	Point* before_point = move_point.at(move_point.size() - 1)->point;
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
	//判断玩家的技能是否可以使用
	int model = main_window->GetGameModel();
	if (model == FrightModel) {
		for (int i = 0; i < 3; i++) {
			if (skiller->IsLiveSkill(skill.at(i)) && skill.at(i) > 0) {
				isLife = LIFE;
			}
		}
	}
	else if(model == SkillModel){
		if (skiller->IsLiveSkill(skill.at(0)) && skill_sum.at(0) > 0) {
			isLife = LIFE;
		}
	}
	return isLife;
}

#pragma message("player.cpp is loaded")