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

int Main_Window::CreatWindow(Game* game_, class Player* red_player_,
	Player* blue_player_)
{
	game = game_;
	input = game->GetInput();
	red_player = red_player_;
	blue_player = blue_player_;

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

int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_)
{
	Window_Msg* temp = new Window_Msg();
	temp->text = text_;
	temp->rect = rect_;
	temp->liveTime = 0;
	window_msg.push_back(temp);
	return 0;
}

int Main_Window::Updata()
{
	if (!window) {
		CreatNewWindow("Snake", 100, 100, 500, 500);
		flagWindow = MainWindow;
	}
	//ѭ������ɫ
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	DrawLineColor(0, 0, 700, 0,BLACK);

	//����һ��С��
	if (!mouse_window) {
		mouse_window = new Mouse_Window(input);
	}
	mouse_window->Updata();//��������ƶ�
	//��������ƶ���·
	auto point_sum = mouse_window->Getpoint();
	for (int i = 1; i < point_sum.size(); i++) {
		DrawLine(point_sum[i - 1]->x, point_sum[i - 1]->y, point_sum[i]->x, point_sum[i]->y);
	}

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

	Point temp;
	vector<Point*> move_point;

	//�������·��
	move_point = red_player->Getmove_point();//��ȡ�췽�ƶ�����
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//������ɫ����ɫΪ��ɫ
	int now = 1;
	//�����ƶ����鲢����
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}
	move_point = blue_player->Getmove_point();//��ȡ�����ƶ�����
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//������ɫ����ɫΪ��ɫ
	now = 1;
	//�����ƶ����鲢����
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}

	//������һ���
	//temp.x����ʼΪ0����x>0ʱ��һ��ر�ѡ��
	temp = red_player->Getjidi_point();//��ȡ�췽��������
	if (temp.x > 0) { FillRect(temp.x, temp.y, 50, 50, &RED); }
	temp = blue_player->Getjidi_point();//��ȡ������������
	if (temp.x > 0) { FillRect(temp.x, temp.y, 50, 50, &BLUE); }

	//�������Ԥѡ��
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
	DrawTTF(L"���ܽ���", BLACK, { 200,200,100,40 });
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
			flagWindow = FrightWindow;
			CreatNewWindow("Snake", 100,100,700,800);
			game->CreatePlay();
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
			flagWindow = FrightWindow;
			CreatNewWindow("Snake", 100, 100, 700, 800);
			game->CreatePlay();
		}
	}

	return 0;
}

int Main_Window::Draw_GameOverWindow()
{
	SDL_Rect rect = { 50,30,100,50 };
	flagWindow = GameoverWindow;
	game->DestroyPlay();
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
