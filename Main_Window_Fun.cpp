#include "Main_Window.h"
#include "Game.h"
#include <Windows.h>

int Main_Window::GameIsEnd(int flag_Player_)
{
	game->gameIsRun = false;//����Ϸ���б�ʶ����Ϊ����
	flag_Player = flag_Player_;//����ʧ�ܷ��ı�ʶ
	flagWindow = GameoverWindow;//��������Ϊ��Ϸ��������
	game->DestroyPlay();//���ٴ���
	CreatNewWindow(&rect_Main_Window);//�����µĴ���
	return 0;
}

int Main_Window::GetGameModel()
{
	return model;
}

void Main_Window::ChangeSkill(int index_)
{
	if (red_player->Getskill()->empty()) {
		red_player->Changeskill(index_);//�޸ĺ췽��ҵļ���ѡ��
	}
	else {
		blue_player->Changeskill(index_);//�޸�������Ҽ���
		b_flagWindow = flagWindow;
		flagWindow = FrightWindow;
		CreatNewWindow(&rect_Fright_Window);
		texture->LoadAllSkill();
	}
}

int Main_Window::CreatNewWindow(SDL_Rect* rect)
{
	SDL_DestroyWindow(window);
	//��������
	const char* name = "Snake";
	window = SDL_CreateWindow(name, rect->x, rect->y, rect->w, rect->h, SDL_WINDOW_SHOWN);
	//���
	if (!window) {
		SDL_Log("%s", SDL_GetError());
		return Window_error;
	}
	//��ȡ���ڶ�Ӧ����ͼ��
	surface = SDL_GetWindowSurface(window);

	//������ɫ��
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//���
	if (!renderer) {
		SDL_Log("%s", SDL_GetError());
		return Renderer_error;
	}
	texture->ChangRenderer(renderer);
	return All_true;
}

int Main_Window::CreatWindow(Game* game_)
{
	game = game_;
	input = game->GetInput();
	mouse_window = new Mouse_Window(input, this);
	rander = new Rander();
	texture = new Texture(renderer);
	button = new Button();
	b_flagWindow = FrightWindow;


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
	delete rander;
	delete button;
	delete texture;
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	return 0;
}

int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_, int& flag_window_, int flag_)
{
	if (flag_window_ != 0) { return false; }
	Window_Msg* temp = new Window_Msg(text_, rect_, flag_);
	window_msg.push_back(temp);
	flag_window_ = 1;
	return true;
}

int Main_Window::GetFlag()
{
	return flagWindow;
}

int Main_Window::Updata(class Player* red_player_, class Player* blue_player_)
{
	red_player = red_player_;
	blue_player = blue_player_;
	if (!window) {
		flagWindow = MainWindow;
		CreatNewWindow(&rect_Main_Window);
	}
	//ѭ������ɫ
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	DrawLineColor(0, 0, 700, 0, BLACK);

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
	case ModelWindow://ģʽѡ�����
		Draw_ModelWindow();
		break;
	default:
		DrawTTF(L"����", RED, { 0,0,100,50 });
		break;
	}

	//����һ��С��
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	mouse_window->DrawSnake();

	//���ƻ�����
	SDL_RenderPresent(renderer);
	return 0;
}