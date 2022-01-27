#include "Main_Window.h"
#include "Game.h"

static SDL_Color WHITE = { 255,255,255,255 };//��ɫ
static SDL_Color BLACK = { 0,0,0,255 };//��ɫ
static SDL_Color RED = { 255,0,0,255 };//��ɫ
static SDL_Color BLUE = { 0,0,255,255 };//��ɫ
static SDL_Color LITTLE_BLACK = { 200,200,200,255 };//��ɫ


int Main_Window::GameIsEnd(int flag_Player_)
{
	game->gameIsRun = false;
	flag_Player = flag_Player_;
	flagWindow = GameoverWindow;
	SDL_DestroyWindow(window);
	CreatNewWindow("Snake", 300, 300, 200, 200);
	game->DestroyPlay();
	return 0;
}

int Main_Window::CreatNewWindow(const char* title, int x, int y, int w, int h)
{
	if (window) {
		SDL_DestroyWindow(window);
	}
	//��������
	window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	//���
	if (!window) {
		SDL_Log("%s", SDL_GetError());
		return Window_error;
	}
	//��ȡ���ڶ�Ӧ����ͼ��
	windowSurface = SDL_GetWindowSurface(window);

	//������ɫ��
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//���
	if (!renderer) {
		SDL_Log("%s", SDL_GetError());
		return Renderer_error;
	}

	return All_true;
}

int Main_Window::CreatWindow(Game* game_)
{
	game = game_;
	input = game->GetInput();
	mouse_window = new Mouse_Window(input, this);

	//��ʼ��TTF���ֿ�
	if (TTF_Init() == -1) {
		SDL_Log("%s", SDL_GetError());
		return TTF_Init_error;
	}
	//����TTF����
	font = TTF_OpenFont(fontText, fontSize);
	if (!font) {
		SDL_Log("%s", SDL_GetError());
		return TTF_Open_error;
	}
	return 0;
}

int Main_Window::Shutdown()
{
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	return 0;
}

int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_, int& flag_window_)
{
	if (flag_window_ != 0) { return false; }
	Window_Msg* temp = new Window_Msg();
	temp->text = text_;
	temp->rect = rect_;
	temp->liveTime = 0;
	window_msg.push_back(temp);
	flag_window_ = 1;
	return true;
}

int Main_Window::Updata(class Player* red_player_, class Player* blue_player_)
{
	red_player = red_player_;
	blue_player = blue_player_;
	if (!window) {
		CreatNewWindow("Snake", 100, 100, 500, 500);
		flagWindow = MainWindow;
	}
	//ѭ������ɫ
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	DrawLineColor(0, 0, 700, 0, BLACK);

	//����һ��С��
	mouse_window->DrawSnake();

	switch (flagWindow)
	{
	case MainWindow://�׽���
		Draw_MainWindow();
		break;
	case FrightWindow://ս������
		Draw_FrightWindow();
		break;
	case GameoverWindow://��Ϸ��������
		Draw_GameOverWindow();
		break;
	case SkillWindow://����ѡ�����
		Draw_SkillWindow();
		break;
	case ModelWindow:
		Draw_ModelWindow();
		break;
	default:
		DrawTTF(L"����", RED, { 0,0,100,50 });
		break;
	}

	//���ƻ�����
	SDL_RenderPresent(renderer);
	return 0;
}

int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;
	//��ɫ
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//����ս������
	int i = 0;
	while (i <= 700) {
		//Y
		DrawLine(i, 0, i, 700);
		//X
		DrawLine(0, i, 700, i);
		i += 100;
	}
	DrawLine(350, 700, 350, 800);

	switch (model)
	{
	case SkillModel:
		int skill = red_player->Getskill_flag();
		const wchar_t* skill_name = game->Getskill_name(skill);
		DrawTTF(skill_name, RED, { 0,700,fontSize * 3,40 });
		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_flag_num()), RED, { 1,740,40,40 });

		skill = blue_player->Getskill_flag();
		skill_name = game->Getskill_name(skill);
		DrawTTF(skill_name, BLUE, { 700 - fontSize * 3,700,fontSize * 3,40 });
		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_flag_num()), BLUE, { 700 - 41,740,40,40 });
		break;
	}

	//��������ƶ�
	{
		int jidi_h = 50;//���ؾ��α߳�
		vector<Point*>* jidi_point;
		vector<Point*>* move_point;
		vector<QuYu*>* quyu_point;
		//�������·��
		move_point = red_player->Getmove_point();//��ȡ�췽�ƶ�����
		jidi_point = red_player->Getjidi_point();//��ȡ�췽��������
		quyu_point = red_player->Getquyu_point();//��ȡ�췽��������
		//���ƺ췽����
		if (jidi_point->at(0)->x > 0) {
			FillRect(jidi_point->at(0)->x, jidi_point->at(0)->y, jidi_h, jidi_h, &RED);
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//������ɫ����ɫΪ��ɫ
		DrawMove(move_point, jidi_point, quyu_point, &RED);

		move_point = blue_player->Getmove_point();//��ȡ�����ƶ�����
		jidi_point = blue_player->Getjidi_point();//��ȡ������������
		quyu_point = blue_player->Getquyu_point();//��ȡ������������
		//������������
		if (jidi_point->at(0)->x > 0) {
			FillRect(jidi_point->at(0)->x, jidi_point->at(0)->y, jidi_h, jidi_h, &BLUE);
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//������ɫ����ɫΪ��ɫ
		DrawMove(move_point, jidi_point, quyu_point, &BLUE);
	}

	//�������Ԥѡ��
	Point temp;
	temp = red_player->Getyuxuan_point();//��ȡ�췽Ԥѡ������
	FillRect(temp.x, temp.y, 20, 20, &RED);
	temp = blue_player->Getyuxuan_point();//��ȡ����Ԥѡ������
	FillRect(temp.x, temp.y, 20, 20, &BLUE);

	//���������ʾ����
	int size = window_msg.size();
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (window_msg[i]->liveTime > 100) {
				//ÿ����ʾ��ѭ������99�� ������ɺ���ɾ��
				window_msg.erase(
					window_msg.begin() + i, window_msg.begin() + i + 1);
				break;//����ѭ��
			}
			FillRect(window_msg[i]->rect.x, window_msg[i]->rect.y,
				window_msg[i]->rect.w, window_msg[i]->rect.h, &LITTLE_BLACK);
			DrawRect(window_msg[i]->rect.x, window_msg[i]->rect.y,
				window_msg[i]->rect.w, window_msg[i]->rect.h, &BLACK);
			DrawTTF(window_msg[i]->text, BLACK, window_msg[i]->rect);
			window_msg[i]->liveTime++;
		}
	}

	return 0;
}

int Main_Window::Draw_MainWindow()
{
	flagWindow = MainWindow;

	//DrawRect(200, 100, 100, 50, &BLACK);
	DrawTTF(L"��ʼ��Ϸ", BLACK, { 200,100,100,40 });
	DrawLine(180, 150, 320, 150);
	//DrawRect(200, 200, 100, 50, &BLACK);
	DrawTTF(L"ģʽѡ��", BLACK, { 200,200,100,40 });
	DrawLine(180, 250, 320, 250);
	//��ȡ�������
	Point* nowPoint = input->GetNowPoint();
	//�ж�����Ƿ���롰��ʼ��Ϸ����ť��
	if (nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 100 && nowPoint->y < 150)
	{
		//�ƶ�������
		FillRect(150, 120, 20, 20, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			game->CreatePlay();//�������
			switch (model) {
			case BaseModel:
				flagWindow = FrightWindow;
				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				break;
			case SkillModel:
				flagWindow = SkillWindow;
				CreatNewWindow("Player1 chiose skill", 100, 100, 300, 300);
				break;
			case FrightModel:
				flagWindow = SkillWindow;
				CreatNewWindow("Player1 chiose skill", 100, 100, 300, 300);
				break;
			default:
				game->Shutdown();
				break;
			}
		}
	}
	else if (nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 200 && nowPoint->y < 250)
	{
		//�ƶ�������
		FillRect(150, 220, 20, 20, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			flagWindow = ModelWindow;
		}
	}

	return 0;
}

int Main_Window::Draw_GameOverWindow()
{
	SDL_Rect rect = { 50,30,100,50 };
	flagWindow = GameoverWindow;
	if (flag_Player == Red_Player) {
		DrawTTF(L"����ʤ��", BLUE, rect);
	}
	else {
		DrawTTF(L"�췽ʤ��", RED, rect);
	}
	DrawTTF(L"����ص���ҳ", BLACK, { 20,100,160,50 });
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		CreatNewWindow("Snake", 100, 100, 500, 500);
		flagWindow = MainWindow;
	}
	return 0;
}

int Main_Window::Draw_SkillWindow()
{
	flagWindow = SkillWindow;
	//ѡ�������εı�
	int h = 20;
	SDL_Rect name1 = { 100,20,90,40 };//����һ����
	SDL_Rect name2 = { 100,90,90,40 };//���ܶ�����
	DrawLine(name1.x, name1.y + name1.h + 10, name1.x + name1.w, name1.y + name1.h + 10);
	DrawLine(name2.x, name2.y + name2.h + 10, name2.x + name2.w, name2.y + name2.h + 10);
	const wchar_t* skill_name = game->Getskill_name(index);
	if (skill_name) { DrawTTF(skill_name, BLACK, name1); }
	skill_name = game->Getskill_name(index + 1);
	if (skill_name) { DrawTTF(skill_name, BLACK, name2); }
	SDL_Rect text1 = { 0,250,fontSize * 3,40 };//�ı�һ����
	SDL_Rect text2 = { 300 - fontSize * 3,250,fontSize * 3,40 };//�ı�������
	DrawLine(text1.x, text1.y + text1.h + 10, text1.x + text1.w, text1.y + text1.h + 10);
	DrawLine(text2.x, text2.y + text2.h + 10, text2.x + text2.w, text2.y + text2.h + 10);
	DrawTTF(L"��һҳ", BLACK, text1);
	DrawTTF(L"��һҳ", BLACK, text2);
	//��ȡ�������
	Point* nowPoint = input->GetNowPoint();
	//�ж�����Ƿ���밴ť��
	//��һ��������
	if (nowPoint->x > name1.x && nowPoint->x < name1.x + name1.w
		&& nowPoint->y > name1.y && nowPoint->y < name1.y + name1.h + 10)
	{
		//�ƶ�������
		FillRect(name1.x - h * 2, name1.y + 10, h, h, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (red_player->Getskill_flag() == -1) {
				//�޸����һ�ļ���ѡ��
				red_player->Changeskill_flag(index);
				//�ֵ���Ҷ�ѡ����
				flagWindow = SkillWindow;
				index = 1;
				CreatNewWindow("Player2 chiose skill", 100, 100, 300, 300);
			}
			else {
				blue_player->Changeskill_flag(index);
				flagWindow = FrightWindow;
				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				index = 1;
			}
		}
	}
	//�ڶ���������
	else if (nowPoint->x > name2.x && nowPoint->x < name2.x + name2.w
		&& nowPoint->y > name2.y && nowPoint->y < name2.y + name2.h + 10)
	{
		//�ƶ�������
		FillRect(name2.x - h * 2, name2.y + 10, h, h, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (red_player->Getskill_flag() == -1) {
				//�޸����һ�ļ���ѡ��
				red_player->Changeskill_flag(index + 1);
				//�ֵ���Ҷ�ѡ����
				index = 1;//��������
				CreatNewWindow("Player2 chiose skill", 100, 100, 300, 300);
			}
			else {
				blue_player->Changeskill_flag(index + 1);
				flagWindow = FrightWindow;
				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				index = 1;
			}
		}
	}
	//��һҳ
	else if (nowPoint->x > text1.x && nowPoint->x < text1.x + text1.w
		&& nowPoint->y > text1.y && nowPoint->y < text1.y + text1.h + 10)
	{
		//�ƶ�������
		FillRect(text1.x + text1.w + h, text1.y + 10, h, h, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (index > 1) { index -= 2; }
		}
	}
	//��һҳ
	else if (nowPoint->x > text2.x && nowPoint->x < text2.x + text2.w
		&& nowPoint->y > text2.y && nowPoint->y < text2.y + text2.h + 10)
	{
		//�ƶ�������
		FillRect(text2.x - h * 2, text2.y + 10, h, h, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (index + 2 <= game->Getskill_sum()) { index += 2; }
		}
	}

	return 0;
}

int Main_Window::Draw_ModelWindow()
{
	flagWindow = ModelWindow;

	//�ı����
	int x = 200;
	int y = 100;
	int w = 100;
	int h = 40;

	//�ı�1
	DrawTTF(L"��ͨѵ��", BLACK, { x,y * 1,w,h });
	DrawLine(180, 150, 320, 150);
	//�ı�2
	DrawTTF(L"����ѵ��", BLACK, { x,y * 2,w,h });
	DrawLine(180, 250, 320, 250);
	//�ı�3
	DrawTTF(L"�ݲ�����", BLACK, { x,y * 3,w,h });
	DrawLine(180, 350, 320, 350);

	//��ȡ�������
	Point* nowPoint = input->GetNowPoint();
	for (int flag_model = 1; flag_model <= 3; flag_model++) {
		//�ж�����Ƿ���롰��ʼ��Ϸ����ť��
		if (nowPoint->x < x + w && nowPoint->x > x
			&& nowPoint->y < y * flag_model + 50 + h && nowPoint->y > y * flag_model)
		{
			//�ƶ�������
			FillRect(x - 50, y * flag_model + 20, 20, 20, &RED);
			//���¼�
			if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
			{
				flagWindow = MainWindow;
				model = flag_model;
			}
		}
	}
	return 0;
}

int Main_Window::DrawMove(vector<Point*>* move_point, vector<Point*>* jidi_point,
	vector<QuYu*>* quyu_point, SDL_Color* color_)
{
	int jidi_h = 50;
	int quyu_h = 30;
	int now = 1;
	int before = 0;
	while (now < (*move_point).size()) {
		Point* now_point = (*move_point).at(now);
		Point* before_point = (*move_point).at(before);
		switch (now_point->x) {
		case QUYU:
			FillRect((*quyu_point).at(now_point->y)->x, (*quyu_point).at(now_point->y)->y, quyu_h, quyu_h, color_);
			break;
		case JIDI:
			FillRect((*jidi_point).at(now_point->y)->x, (*jidi_point).at(now_point->y)->y, jidi_h, jidi_h, color_);
			break;
		default:
			switch (before_point->x)
			{
			case QUYU:
				for (int k = before - 1; k >= 0; k--) {
					if ((*move_point).at(k)->x == JIDI) {
						DrawLine((*jidi_point).at((*move_point).at(k)->y)->x, (*jidi_point).at((*move_point).at(k)->y)->y,
							now_point->x, now_point->y);
						break;
					}
					else if ((*move_point).at(k)->x != QUYU) {
						DrawLine((*move_point).at(k)->x, (*move_point).at(k)->y, now_point->x, now_point->y);
						break;
					}
				}
				break;
			case JIDI:
				DrawLine((*jidi_point).at(before_point->y)->x + 25, (*jidi_point).at(before_point->y)->y + 25, now_point->x, now_point->y);
				break;
			default:
				DrawLine(before_point->x, before_point->y, now_point->x, now_point->y);
				break;
			}
			break;
		}
		before++;
		now++;
	}
	return 0;
}

void Main_Window::DrawLine(int x1, int y1, int x2, int y2)
{
	//������
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Main_Window::DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawLine(x1, y1, x2, y2);
}

void Main_Window::DrawRect(int x, int y, int w, int h, SDL_Color* color)
{
	//���þ�����Ϣ
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	//���������ɫ
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	//���ƾ���
	SDL_RenderDrawRect(renderer, &rect);
}

void Main_Window::FillRect(int x, int y, int w, int h, SDL_Color* color)
{
	//���þ�����Ϣ
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	//���������ɫ
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	//���ƾ���
	SDL_RenderFillRect(renderer, &rect);
}

void Main_Window::DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect)
{
	//��wchar_tת��ΪUint16
	Uint16* inText = (Uint16*)text;
	//��������Ϣת��Ϊ��ͼ����Ϣ
	SDL_Surface* fontSurface = TTF_RenderUNICODE_Solid(font, inText, color);
	//����ͼ����Ϣת��Ϊ������Ϣ
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	//�ͷ���ͼ���ڴ�
	SDL_FreeSurface(fontSurface);
	//��������Ϣ���Ƶ�����
	SDL_RenderCopy(renderer, texture, 0, &rect);
}
