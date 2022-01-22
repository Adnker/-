#include "Main_Window.h"
#include "Game.h"

static SDL_Color WHITE = { 255,255,255,255 };//��ɫ
static SDL_Color BLACK = { 0,0,0,255 };//��ɫ
static SDL_Color RED = { 255,0,0,255 };//��ɫ
static SDL_Color BLUE = { 0,0,255,255 };//��ɫ
static SDL_Color LITTLE_BLACK = { 150,150,150,255 };//��ɫ

int Main_Window::CreatNewWindow(const char* title, int x, int y, int w, int h)
{
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

int Main_Window::CreatWindow(Game* game_,class Player* red_player_,
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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	//��ɫ
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	DrawLine(0, 0, 900, 0);

	switch (flagWindow)
	{
		//�׽���
	case MainWindow:
		Draw_MainWindow();
		break;
		//ս������
	case FrightWindow:
		Draw_FrightWindow();
		break;
	}

	//���ƻ�����
	SDL_RenderPresent(renderer);
	return 0;
}

int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;
	if (input->GetKeyState(SDL_SCANCODE_ESCAPE) == Key_Down) {
		//����ESC���˻ص�������
		flagWindow = MainWindow;//�޸Ĵ��ڱ�־
		//���´�������
		SDL_DestroyWindow(window);
		CreatNewWindow("Snake", 100, 100, 500, 500);
		//����Ϊ��ҷ�����ڴ�
		game->DestroyPlay();
		return 0;
	}
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
	move_point = red_player->Getmove_point();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	int now = 1;
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}
	move_point = blue_player->Getmove_point();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	now = 1;
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}

	//������һ���
	temp = red_player->Getjidi_point();
	if(temp.x > 0){ FillRect(temp.x, temp.y, 50, 50, &RED); }
	temp = blue_player->Getjidi_point();
	if (temp.x > 0) { FillRect(temp.x, temp.y, 50, 50, &BLUE); }

	//�������Ԥѡ��
	temp = red_player->Getyuxuan_point();
	FillRect(temp.x, temp.y, 20, 20, &RED);
	temp = blue_player->Getyuxuan_point();
	FillRect(temp.x, temp.y, 20, 20, &BLUE);
	
	//���������ʾ����
	int size = window_msg.size();
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (window_msg[i]->liveTime > 100) {
				window_msg.erase(
					window_msg.begin() + i, window_msg.begin() + i + 1);
				break;//����ѭ��
			}
			FillRect(window_msg[i]->rect.x, window_msg[i]->rect.y,
				window_msg[i]->rect.w, window_msg[i]->rect.h, &LITTLE_BLACK);
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
	DrawTTF(L"��ʼ��Ϸ", BLACK, {200,100,100,50});
	DrawLine(180, 150, 320, 150);
	//DrawRect(200, 200, 100, 50, &BLACK);
	DrawTTF(L"���ܽ���", BLACK, { 200,200,100,50 });
	DrawLine(180, 250, 320, 250);
	//��ȡ�������
	Point* nowPoint = input->GetNowPoint();
	//�ж�����Ƿ���롰��ʼ��Ϸ����ť��
	if (nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 100 && nowPoint->y < 150) 
	{
		//�ƶ�������
		FillRect(100, 100, 50, 50,&RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) 
		{
			flagWindow = FrightWindow;
			SDL_DestroyWindow(window);
			CreatNewWindow("Snake", 100, 50, 700, 800);
			game->CreatePlay();
		}
	}
	else if(nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 200 && nowPoint->y < 250)
	{
		//�ƶ�������
		FillRect(100, 200, 50, 50, &RED);
		//���¼�
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			flagWindow = FrightWindow;
			SDL_DestroyWindow(window);
			CreatNewWindow("Snake", 100, 50, 700, 800);
			game->CreatePlay();
		}
	}
	
	return 0;
}

void Main_Window::DrawLine(int x1, int y1, int x2, int y2)
{
	//������
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
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

void Main_Window::FillRect(int x, int y, int w, int h,SDL_Color* color)
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

void Main_Window::DrawTTF(const wchar_t * text, SDL_Color color,SDL_Rect rect)
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
