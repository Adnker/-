#include "Main_Window.h"
#include "Game.h"


/*
* ��ʼ������
*/
int Main_Window::CreatWindow(Game* game_)
{
	game = game_;
	input = game->GetInput();
	mouse_window = new Mouse_Window(input, this);
	rander = new Rander();
	texture = new Texture(renderer);
	button = new Button();
	b_flagWindow = IniWindow;


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


/*
* ��������
*/
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


/*
* ����һ����
* �� x1,y1 ��һ���ߵ� x2,y2
* DrawLine����Ҫ�Լ��趨��ɫ
* DrawLineColoe��Ҫ������ɫֵ ��DrawLineColor
*/
void Main_Window::DrawLine(int x1, int y1, int x2, int y2)
{
	//������
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


/*
* ����һ����
* ʹ��color����ɫ����x1,y1 ��һ���ߵ� x2,y2
* DrawLine����Ҫ�Լ��趨��ɫ ��DrawLine
* DrawLineColoe��Ҫ������ɫֵ
*/
void Main_Window::DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawLine(x1, y1, x2, y2);
}


/*
* ����һ���߿����
* ��x,yΪ�������ϽǶ��㣬��ʼ����һ����Ϊw����Ϊh�ľ��Σ�������ɫΪcolor
* DrawRect���Ƶ���һ���߿����
* FillRect���Ƶ���һ�������� ��FillRect
*/
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


/*
* ����һ��������
* ��x,yΪ�������ϽǶ��㣬��ʼ����һ����Ϊw����Ϊh�ľ��Σ������ɫΪcolor
* DrawRect���Ƶ���һ���߿���� ��DrawRect
* FillRect���Ƶ���һ��������
*/
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


/*
* ��������
* ��rect��λ�û�����ɫΪcolor�ı�Ϊtext������
*/
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


/*
* ����ͼƬ
* ����Texture���Draw ��Texture��
* ��ͼƬ·��ΪfileName(������׺)��ͼƬ�н�ȡλ��Ϊrect1(NULLʱ��ȡȫ��)��СͼƬ������rect2��λ��
* ���Ƽ���ͼƬʱʹ��ר�õĺ���ͨ��DrawSkill ��DrawSkill
*/
void Main_Window::DrawPicture(const std::string fileName, SDL_Rect* rect1, SDL_Rect rect2)
{
	texture->Draw(fileName, rect1, &rect2);
}


/*
* ���Ƽ���ͼƬ
* ����Texture���DrawSkill ��Texture��
* ��ͼƬ����Ϊskill_name��ͼƬ�н�ȡλ��Ϊrect1(NULLʱ��ȡȫ��)��СͼƬ������rect2��λ��
* ���ƷǼ���ͼƬʱʹ��һ�㺯��ͨ��Draw ��Draw
* flag_ �Ƿ���Ҫ�߿�
*/
void Main_Window::DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect rect2, int flag_)
{
	texture->DrawSkill(skill_name, rect1, &rect2, flag_);
}


/*
* ��Ϸ����ʱ����
* ����ܷ���flag_player��ʶ
*/
int Main_Window::GameIsEnd(int flag_Player_)
{
	game->gameIsRun = false;//����Ϸ���б�ʶ����Ϊ����
	flag_Player = flag_Player_;//����ʧ�ܷ��ı�ʶ
	flagWindow = GameoverWindow;//��������Ϊ��Ϸ��������
	game->DestroyPlay();//���ٴ���
	CreatNewWindow(&rect_Main_Window);//�����µĴ���
	return 0;
}


/*
* �޸���ҵļ���
* �����Ӧ�ļ�������index_
*/
void Main_Window::ChangeSkill(int index_)
{
	if (red_player->Getskill()->empty()) {
		red_player->Changeskill(index_);//�޸ĺ췽��ҵļ���ѡ��
	}
	else {
		blue_player->Changeskill(index_);//�޸�������Ҽ���
		//˫����ѡ���꼼�ܣ���Ϸ��ʼ

		b_flagWindow = flagWindow;
		flagWindow = FrightWindow;
		CreatNewWindow(&rect_Fright_Window);
		texture->LoadAllSkill();
	}
}


/*
* ����һ���µĴ���
* ����ԭ�ȵĴ��ڣ�������һ���µĴ��ڣ�����λ��Ϊrect
*/
int Main_Window::CreatNewWindow(SDL_Rect* rect)
{
	if (window) {
		SDL_DestroyWindow(window);
	}
	//��������
	window = SDL_CreateWindow("Snake", rect->x, rect->y, rect->w, rect->h, SDL_WINDOW_SHOWN);
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

	//����ͼƬ����Ϣ
	texture->ChangRenderer(renderer);
	texture->LoadAllSkill();

	return All_true;
}


/*
* �����ṩ��Player��
* ����ս���������һ����ʾ���ڣ���ʾ�ı�Ϊtext_ λ��Ϊrect_, ��ʾʱ��Ϊwindow_time_, ��ұ�ʶΪflag_
*/
int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_, int& window_time_, int flag_player_)
{
	//���ʱ���Ƿ����
	if (window_time_ != 0) { return false; }
	Window_Msg* temp = new Window_Msg(text_, rect_, flag_player_);
	window_msg.push_back(temp);
	window_time_ = 1;//��ʼ��ʱ
	return true;
}


/*
* ��ȡ��ǰ����״̬
*/
int Main_Window::GetFlag()
{
	return flagWindow;
}


/*
* ��ȡ����ģʽ
*/
int Main_Window::GetGameModel()
{
	return model;
}


/*
* �����ƶ�
* ��һЩҳ��������Ʈ�����ƶ�
*/
int Main_Window::DrawYun()
{
	//�ж��Ƿ��ǵ�һ�ν����µĽ���
		//�����µ��ƶ�
	while (yun.size() < 3) {
		if (rander->GetARand(1) == 0) {
			Yun_Msg* yun1 = new Yun_Msg(-100, rander->GetARand(150), LEFT, rander->GetARand(2, 1));
			yun.emplace_back(yun1);
		}
		else {
			Yun_Msg* yun1 = new Yun_Msg(rect_Main_Window.w, rander->GetARand(150), RIGHT, rander->GetARand(2, 1));
			yun.emplace_back(yun1);
		}
	}
	//����ÿһ���ƶ䣬�������ƶ�
	for (int i = 0; i < yun.size(); i++) {
		DrawPicture("yun.png", NULL, { yun.at(i)->x,yun.at(i)->y,100,30 });
		if (yun.at(i)->flag == LEFT) {
			yun.at(i)->x += yun.at(i)->v;
		}
		else {
			yun.at(i)->x -= yun.at(i)->v;
		}
		if (yun.at(i)->x > rect_Main_Window.w + 100 || yun.at(i)->x < -100) {
			yun.erase(yun.begin() + i, yun.begin() + i + 1);
		}
	}
	return true;
}


/*
* ���º���
*/
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
	case JieshaoWindow://���ܽ��ܽ���
		Draw_JieshaoWindow();
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


/*
* ���������洰��
*/
int Main_Window::Draw_MainWindow()
{
	flagWindow = MainWindow;
	int button_x = 200;
	int button_y = 100;
	int button_w = 100;
	int button_h = 40;
	int jianju = 45;
	int picture_h = 40;
	//�״ν��������Ҫ��Ӱ�ť
	if (b_flagWindow != MainWindow) {
		//��Ӱ�ť
		button->Clear();
		button->AddButton(L"��ʼ��Ϸ", texture->GetTexture("yun.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 1,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 1,button_w,button_h }, font, &BLACK);
		button->AddButton(L"ģʽѡ��", texture->GetTexture("yun.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 2,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 2,button_w,button_h }, font, &BLACK);
		button->AddButton(L"���ܽ���", texture->GetTexture("yun.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 3,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 3,button_w,button_h }, font, &BLACK);
	}
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���
	DrawYun();//�����ƶ�
	button->DrawButton(renderer);//����ȫ����ť
	b_flagWindow = flagWindow;


	BUTTONER Button1 = 0;
	BUTTONER Button2 = 1;
	BUTTONER Button3 = 2;
	button->Updata(input);//����ȫ����ť״̬
	//��һ����ť
	switch (button->GetButtonLeftState(Button1))
	{
	case Key_Move:
		DrawPicture("buttonRight.png", NULL, { button_x - jianju, button_y * 1, picture_h, picture_h });//����ѡ����ʾͼƬ
		break;
	case Key_Down:
		game->CreatePlay();//�������
		switch (model) {
		case BaseModel:
			b_flagWindow = flagWindow;
			flagWindow = FrightWindow;
			CreatNewWindow(&rect_Fright_Window);
			break;
		case SkillModel:
			b_flagWindow = flagWindow;
			flagWindow = SkillWindow;
			break;
		case FrightModel:
			b_flagWindow = flagWindow;
			flagWindow = FrightWindow;
			CreatNewWindow(&rect_Fright_Window);
			break;
		default:
			game->Shutdown();
			break;
		}
		break;
	}
	//�ڶ�����ť
	switch (button->GetButtonLeftState(Button2))
	{
	case Key_Move:
		DrawPicture("buttonRight.png", NULL, { button_x - jianju, button_y * 2, picture_h, picture_h });
		break;
	case Key_Down:
		b_flagWindow = flagWindow;
		flagWindow = ModelWindow;
	}
	//��������ť
	switch (button->GetButtonLeftState(Button3))
	{
	case Key_Move:
		DrawPicture("buttonRight.png", NULL, { button_x - jianju, button_y * 3, picture_h, picture_h });
		break;
	case Key_Down:
		b_flagWindow = flagWindow;
		flagWindow = JieshaoWindow;
	}
	DrawTTF(L"������", BLACK, { 210,25,fontSize * 3,30 });
	return 0;
}


/*
* ������Ϸ�������洰��
*/
int Main_Window::Draw_GameOverWindow()
{
	flagWindow = GameoverWindow;//�����ڱ�ʶ����Ϊ��Ϸ�������ڱ�ʶ
	const wchar_t* text;//��ʾ���ı�����
	SDL_Color color;//�ı���ɫ
	std::string name;//ͼƬ����
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���ͼƬ
	DrawYun();//�����ƶ�
	//�ж���һ��ʧ�� ��һ��ʧ�ܾͻ��ƶ���ʤ��
	if (flag_Player == Red_Player) {
		text = L"�������ʤ��";
		name = "bluedown.png";
		color = BLUE;
	}
	else {
		text = L"�췽���ʤ��";
		name = "reddown.png";
		color = RED;
	}
	DrawTTF(L"����ص���ҳ", BLACK, { 50,200,160,50 });//��ʾ�û��������������
	DrawTTF(text, color, { 175,25,fontSize * 6,25 });
	SDL_Rect rect = { 140,25,25,25 };
	texture->Draw(name, NULL, &rect);
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		b_flagWindow = flagWindow;
		flagWindow = MainWindow;//�����ڱ�ʶ����Ϊ�����ڱ�ʶ
	}
	return 0;
}


/*
* ����ģʽѡ����洰��
*/
int Main_Window::Draw_ModelWindow()
{
	flagWindow = ModelWindow;
	//�ı����
	int x = 200;
	int y = 100;
	int w = 100;
	int h = 40;
	if (b_flagWindow != flagWindow) {
		button->Clear();
		button->AddButton(L"��ͨѵ��", texture->GetTexture("yun.png"), NULL,
			{ x - picture_jianju_x,y * 1,w + picture_jianju_w,h },
			{ x,y * 1,w,h }, font, &BLACK);
		button->AddButton(L"����ѵ��", texture->GetTexture("yun.png"), NULL,
			{ x - picture_jianju_x,y * 2,w + picture_jianju_w,h },
			{ x,y * 2,w,h }, font, &BLACK);
		button->AddButton(L"����ģʽ", texture->GetTexture("yun.png"), NULL,
			{ x - picture_jianju_x,y * 3,w + picture_jianju_w,h },
			{ x,y * 3,w,h }, font, &BLACK);
	}
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });
	DrawYun();//�����ƶ�
	button->DrawButton(renderer);
	b_flagWindow = flagWindow;


	button->Updata(input);
	for (int flag_model = 1; flag_model <= 3; flag_model++) {
		switch (button->GetButtonLeftState(flag_model - 1))
		{
		case Key_Down:
			b_flagWindow = flagWindow;
			flagWindow = MainWindow;
			model = flag_model;
			break;
		case Key_Move:
			DrawPicture("buttonRight.png", NULL, { x - 45, y * flag_model, 40, 40 });
			break;
		default:
			break;
		}
	}
	DrawTTF(L"ѡ��ģʽ", BLACK, { 195,25,fontSize * 4,30 });
	return 0;
}


/*
* ���Ƽ��ܽ��ܽ��洰��
*/
int Main_Window::Draw_JieshaoWindow()
{

	SDL_Rect text1 = { 0,420,80,50 };//��һҳ��ť
	SDL_Rect text2 = { 420,420,80,50 };//��һҳ��ť
	SDL_Rect text3 = { 5,15,50,50 };//���ذ�ť
	BUTTONER Button1 = 0;//��ť1��ʶ
	BUTTONER Button2 = 1;//��ť2��ʶ
	BUTTONER Button3 = 2;//��ť3��ʶ
	flagWindow = JieshaoWindow;
	if (b_flagWindow != JieshaoWindow)
	{
		button->Clear();
		button->AddButton(NULL, texture->GetTexture("buttonLeft.png"), NULL, text1, text1, font, &BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonRight.png"), NULL, text2, text2, font, &BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonLeft.png"), NULL, text3, text3, font, &BLACK);
		button->GetButton(Button1)->drawFlag = false;//һ��ʼ��ʱ����һҳ���û���
	}
	b_flagWindow = flagWindow;
	DrawPicture("backgroundskill.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���
	button->DrawButton(renderer);//���ư�ť
	DrawSkill(game->Getskill_name(index), NULL, { 10,80,100,100 });//����չʾ�ļ���
	DrawTTF(game->Getskill_name(index), BLACK, { 220,25,fontSize * 2,30 });


	button->Updata(input);
	bool index_isTrue;
	bool needToDraw;
	needToDraw = index > 1;
	if (needToDraw) {
		button->GetButton(Button1)->drawFlag = true;
		//��һҳ ���ĸ���ť
		int& Button1_x = button->GetButton(Button1)->rectxy->x;//��ť4x����
		int& Button1_flag = button->GetButton(Button1)->flag;//��ť4�����ʶ
		index_isTrue = index - 1 > 0;
		switch (button->GetButtonLeftState(Button1))
		{
		case Key_Down:
			if (index_isTrue) { index -= 1; }
			break;
		case Key_Move:
			if (Button1_flag == 0) { Button1_x++; if (Button1_x > 30) { Button1_flag = 1; } }
			else { Button1_x--; if (Button1_x < 1) { Button1_flag = 0; } }
			break;
		default:
			Button1_x = text1.x;
			Button1_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Button1)->drawFlag = false;
	}


	needToDraw = index < game->Getskill_sum();
	if (needToDraw) {
		button->GetButton(Button2)->drawFlag = true;
		//��һҳ �������ť
		int& Button2_x = button->GetButton(Button2)->rectxy->x;//��ť5x����
		int& Button2_flag = button->GetButton(Button2)->flag;//��ť5���ױ�ʶ
		index_isTrue = index + 1 <= game->Getskill_sum();
		switch (button->GetButtonLeftState(Button2))
		{
		case Key_Down:
			if (index_isTrue) { index += 1; }
			break;
		case Key_Move:
			if (Button2_flag == 0) { Button2_x--; if (Button2_x < 500 - text2.w - 30) { Button2_flag = 1; } }
			else { Button2_x++; if (Button2_x > 500 - text2.w) { Button2_flag = 0; } }
			break;
		default:
			Button2_x = text2.x;
			Button2_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Button2)->drawFlag = false;
	}

	if (button->GetButtonLeftState(Button3) == Key_Down) {
		flagWindow = MainWindow;
		index = 1;
	}
	return 0;
}


//����λת��Ϊ��ͨ��ͼ��λ
#define MAPXY * 100 + 50
//����λת��Ϊ���ص�ͼ��λ
#define JIDIXY * 100 + 25
//����λת��Ϊ�����ͼ��λ
#define QUYUXU * 100 + 20
/*
* ����ս�����洰��
*/
int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;//���ô��ڱ�ʶΪrect_Main_Window
	DrawPicture("backgroundFright.png", NULL, { 0,0,rect_Fright_Window.w,rect_Fright_Window.h });//���Ʊ���ͼƬ
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//������ɫ����ɫΪ��ɫ

	/*//////////////////////////////////////////////////////////////////////////////////*/
	//����ս�����ڵ�����
	int i = 0;
	while (i <= 700) {
		//Y
		DrawLine(i, 0, i, 700);
		//X
		DrawLine(0, i, 700, i);
		i += 100;
	}
	DrawLine(350, 700, 350, 800);//��ϵ�����

	if (model == FrightModel) {
		red_player->AddSkill();
		blue_player->AddSkill();
	}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//��������ж�·��
	int jidi_h = 50;//ͳһ���ر߳�
	int quyu_h = 30;

	int index_now = 1;
	int index_before = 0;

	Point* point_before;
	SDL_Color color;
	bool needToDrawMove = true;
	const vector<Move_point*>* red_point;//��������ƶ�����
	const vector<Move_point*>* blue_point;//��������ƶ�����

	red_point = red_player->GetMove_point();//��ȡ�췽���ƶ�����
	blue_point = blue_player->GetMove_point();//��ȡ�����ƶ�����

	if (!red_point->empty()) {
		//���ƻ��أ�һ����Ӧ��ɫ�ľ��Σ�
		FillRect(red_point->at(0)->point->x JIDIXY, red_point->at(0)->point->y JIDIXY, jidi_h, jidi_h, &RED);//������ҵĻ���
	}
	if (!blue_point->empty()) {
		//���ƻ��أ�һ����Ӧ��ɫ�ľ��Σ�
		FillRect(blue_point->at(0)->point->x JIDIXY, blue_point->at(0)->point->y JIDIXY, jidi_h, jidi_h, &BLUE);//������������
	}
	while (needToDrawMove) {
		needToDrawMove = false;
		//�췽
		if (index_now < red_point->size()) {
			needToDrawMove = true;
			color = RED;
			//�ƶ�·��
			if (red_point->at(index_now)->flag == NULL) {
				point_before = red_point->at(index_before)->point;
				if (red_point->at(index_before)->flag == QUYU || red_point->at(index_before)->flag > 0) {
					int i = index_before - 1;
					while (red_point->at(i)->flag == QUYU || red_point->at(i)->flag > 0) {
						i--;
					}
					point_before = red_point->at(i)->point;
				}
				DrawLineColor(red_point->at(index_now)->point->x MAPXY, red_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
			//����
			else if (red_point->at(index_now)->flag == JIDI) {
				FillRect(red_point->at(index_now)->point->x JIDIXY, red_point->at(index_now)->point->y JIDIXY,
					jidi_h, jidi_h, &color);
			}
			//����
			else if (red_point->at(index_now)->flag == QUYU) {
				FillRect(red_point->at(index_now)->point->x QUYUXU, red_point->at(index_now)->point->y QUYUXU,
					quyu_h, quyu_h, &color);
			}
			//��·��
			else {
				point_before = red_point->at(red_point->at(index_now)->flag)->point;
				DrawLineColor(red_point->at(index_now)->point->x MAPXY, red_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
		}
		//����
		if (index_now < blue_point->size()) {
			needToDrawMove = true;
			color = BLUE;
			//��ͨ·��
			if (blue_point->at(index_now)->flag == NULL) {
				point_before = blue_point->at(index_before)->point;
				if (blue_point->at(index_before)->flag == QUYU || blue_point->at(index_before)->flag > 0) {
					int i = index_before - 1;
					while (blue_point->at(i)->flag == QUYU || blue_point->at(i)->flag > 0) {
						i--;
					}
					point_before = blue_point->at(i)->point;
				}
				DrawLineColor(blue_point->at(index_now)->point->x MAPXY, blue_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
			//����
			else if (blue_point->at(index_now)->flag == JIDI) {
				FillRect(blue_point->at(index_now)->point->x JIDIXY, blue_point->at(index_now)->point->y JIDIXY,
					jidi_h, jidi_h, &color);
			}
			//����
			else if (blue_point->at(index_now)->flag == QUYU) {
				FillRect(blue_point->at(index_now)->point->x QUYUXU, blue_point->at(index_now)->point->y QUYUXU,
					quyu_h, quyu_h, &color);
			}
			//��·��
			else {
				point_before = blue_point->at(blue_point->at(index_now)->flag)->point;
				DrawLineColor(blue_point->at(index_now)->point->x MAPXY, blue_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
		}
		index_now++;
		index_before++;
	}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//�������Ԥѡ��
	Point temp;//�������Ԥѡ�������
	string name;//�������ͼƬ����
	SDL_Rect rect;//�������ͼƬ����
	int h_yu = 30;//ͳһԤѡ��ĸ߶�
	temp = red_player->Getyuxuan_point();//��ȡ�췽Ԥѡ������
	name = red_player->Getpicture_name();//��ȡ�췽ͼƬ����
	rect = { temp.x, temp.y, h_yu, h_yu };
	texture->Draw(name, NULL, &rect);
	temp = blue_player->Getyuxuan_point();//��ȡ����Ԥѡ������
	name = blue_player->Getpicture_name();//��ȡ����ͼƬ����
	rect = { temp.x, temp.y, h_yu, h_yu };
	texture->Draw(name, NULL, &rect);

	/*/////////////////////////////////////////////////////////////////////////////*/
	//���������ʾ����
	if (window_msg.size() > 0)
	{
		for (int i = 0; i < window_msg.size(); i++)
		{
			//��ÿ����ʾ���ڽ����жϣ�������ڵ���ʾʱ�������ʾ������ʾʱ�䣬Ҫ�Դ��ڽ������٣���֮���л���
			if (window_msg.at(i)->liveTime > DeadTime) {
				//���ٴ���
				window_msg.erase(window_msg.begin() + i, window_msg.begin() + i + 1);
			}
			else {
				if (window_msg.at(i)->flag == Red_Player) {
					window_msg.at(i)->rect.x = red_player->Getyuxuan_point().x;
					window_msg.at(i)->rect.y = red_player->Getyuxuan_point().y + window_msg.at(i)->rect.h;
				}
				else {
					window_msg.at(i)->rect.x = blue_player->Getyuxuan_point().x;
					window_msg.at(i)->rect.y = blue_player->Getyuxuan_point().y + window_msg.at(i)->rect.h;
				}
				//���ƴ���
				//�ж���ʾ�����Ƿ񳬳����壬����������Դ�����Ϣ����������������ʾ��Խ������

				if (window_msg.at(i)->rect.x + window_msg.at(i)->rect.w > rect_Fright_Window.w) {
					window_msg.at(i)->rect.x = rect_Fright_Window.w - window_msg.at(i)->rect.w;
				}
				if (window_msg.at(i)->rect.y + window_msg.at(i)->rect.h > rect_Fright_Window.h) {
					window_msg.at(i)->rect.y = rect_Fright_Window.h - window_msg.at(i)->rect.h - 30;
				}

				DrawPicture("backgroundPlayer.png", NULL, { window_msg.at(i)->rect.x, window_msg.at(i)->rect.y,
					window_msg.at(i)->rect.w, window_msg.at(i)->rect.h });//������ʾ���ڱ���
				DrawTTF(window_msg.at(i)->text, LITTLE_BLACK, window_msg.at(i)->rect);//������ʾ������ʾ����
				window_msg.at(i)->liveTime++;//������ʾ������ʾʱ��
			}
		}
	}

	int skill_sum_h = 25;
	if (red_player->SkillNeedShow())
	{
		SDL_Rect rectShow = red_player->ShowSkill_rect();
		if (rectShow.x + rectShow.w * 2 + 5 > rect_Fright_Window.w) {
			rectShow.x = rect_Fright_Window.w - rectShow.w * 2 - 5;
		}
		if (rectShow.y + rectShow.h > rect_Fright_Window.h) {
			rectShow.y = rect_Fright_Window.h - rectShow.h - 30;
		}
		DrawSkill(game->Getskill_name(red_player->Getskill()->at(red_player->ShowSkill_index())), NULL, rectShow);
		rectShow.x = rectShow.x + rectShow.w - skill_sum_h;
		rectShow.y = rectShow.y + rectShow.h - skill_sum_h;
		rectShow.h = skill_sum_h;
		rectShow.w = skill_sum_h;
		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_sum(red_player->ShowSkill_index())), WHITE, rectShow);
	}
	if (blue_player->SkillNeedShow())
	{
		SDL_Rect rectShow = blue_player->ShowSkill_rect();
		if (rectShow.x + rectShow.w * 2 + 5 > rect_Fright_Window.w) {
			rectShow.x = rect_Fright_Window.w - rectShow.w * 2 - 5;
		}
		if (rectShow.y + rectShow.h > rect_Fright_Window.h) {
			rectShow.y = rect_Fright_Window.h - rectShow.h - 30;
		}
		DrawSkill(game->Getskill_name(blue_player->Getskill()->at(blue_player->ShowSkill_index())), NULL, rectShow);
		rectShow.x = rectShow.x + rectShow.w - skill_sum_h;
		rectShow.y = rectShow.y + rectShow.h - skill_sum_h;
		rectShow.h = skill_sum_h;
		rectShow.w = skill_sum_h;
		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_sum(blue_player->ShowSkill_index())), WHITE, rectShow);
	}
	return 0;
}


/*
* ���Ƽ���ѡ����洰��
*/
int Main_Window::Draw_SkillWindow()
{
	//���ñ�ʶ
	flagWindow = SkillWindow;

	//��ť����
	int button_x = 200;//��ť��ʾλ��
	int button_y = 100;//��ť��ʾλ��
	int button_w = 100;//��ť��
	int button_h = 40;//��ť��
	SDL_Rect text1 = { 0,420,80,50 };//��һҳ��ť
	SDL_Rect text2 = { 420,420,80,50 };//��һҳ��ť
	BUTTONER Skill_Button1 = 0;//��ť1��ʶ����һ������
	BUTTONER Skill_Button2 = 1;//��ť2��ʶ���ڶ�������
	BUTTONER Skill_Button3 = 2;//��ť3��ʶ������������
	BUTTONER Pre_Page = 3;//��ť4��ʶ����һҳ��ť
	BUTTONER Nex_Page = 4;//��ť5��ʶ����һҳ��ť


	//��һ�ν��뼼��ѡ�������м���
	/*
	* ���ؽ���
	* ��ʾ������ť�����ڴ�ż���
	* ��ʾ������ť�����ڴ����һҳ����һҳ����һ����������ť����һҳ����ʾ��һҳ�����һҳ����ʾ��һҳ��
	*/
	if (b_flagWindow != flagWindow) {
		button->Clear();
		button->AddButton(L"�޼���", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 1,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 1,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(L"�޼���", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 2,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 2,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(L"�޼���", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 3,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 3,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonLeft.png"), NULL, text1, text1, font, &BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonRight.png"), NULL, text2, text2, font, &BLACK);
		button->GetButton(Pre_Page)->drawFlag = false;//һ��ʼ��ʱ����һҳ���û���

		//������Ϻ����ô����ʶ
		b_flagWindow = flagWindow;
	}




	//���ƽ���
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���
	DrawYun();//�����ƶ�
	//index + Button_ = ��Ӧ�ļ�������
	int Skill1 = index + Skill_Button1;//����1����
	int Skill2 = index + Skill_Button2;//����2����
	int Skill3 = index + Skill_Button3;//����3����
	//�޸İ�ť��ʾ�ļ�������
	button->GetButton(Skill_Button1)->text = game->Getskill_name(Skill1);
	button->GetButton(Skill_Button2)->text = game->Getskill_name(Skill2);
	button->GetButton(Skill_Button3)->text = game->Getskill_name(Skill3);
	button->DrawButton(renderer);//����ȫ����ť


	button->Updata(input);//����ȫ����ť��״̬
	int picture_h = 40;//ѡ����ʾͼƬ�߳�
	int skill_index = -1;//��Ҫ��ʾ�ļ�������
	int picture_index = -1;//��Ҫ��ʾ����ʾͼƬ����
	//��һ����ť
	bool Skill1_index_isTrue = Skill1 <= game->Getskill_sum();
	if (Skill1_index_isTrue) {
		switch (button->GetButtonLeftState(Skill_Button1))
		{
		case Key_Down:
			ChangeSkill(Skill1);//�޸���Ҽ��ܱ�ʶ
			index = 1;
			break;
		case Key_Move:
			picture_index = Skill_Button1;
			skill_index = Skill1;
			break;
		}
	}


	//�ڶ�����ť
	bool Skill2_index_isTrue = Skill2 <= game->Getskill_sum();
	if (Skill2_index_isTrue) {
		switch (button->GetButtonLeftState(Skill_Button2))
		{
		case Key_Down:
			ChangeSkill(Skill2);;//�޸���Ҽ��ܱ�ʶ
			index = 1;
			break;
		case Key_Move:
			picture_index = Skill_Button2;
			skill_index = Skill2;
			break;
		}
	}


	//��������ť
	bool Skill3_index_isTrue = Skill3 <= game->Getskill_sum();
	if (Skill3_index_isTrue) {
		switch (button->GetButtonLeftState(Skill_Button3))
		{
		case Key_Down:
			ChangeSkill(Skill3);;//�޸���Ҽ��ܱ�ʶ
			index = 1;
			break;
		case Key_Move:
			picture_index = Skill_Button3;
			skill_index = Skill3;
			break;
		}
	}


	//������Ҫ��ʾ�ļ���
	if (skill_index > -1) {
		int y = button_y * (skill_index % 3);
		if (y == 0) { y = button_y * 3; }
		DrawSkill(game->Getskill_name(skill_index), NULL, { button_x - picture_jianju_x - button_h,y,button_h,button_h });//���Ƽ���ͼ����ʾ
	}
	if (picture_index > -1) {
		picture_index++;
		DrawPicture("buttonRight.png", NULL, { button_x - picture_h, button_y * picture_index, picture_h, picture_h });//����ѡ����ʾͼƬ
	}


	bool index_isTrue;
	bool needToDraw;
	needToDraw = index > 3;
	if (needToDraw) {
		button->GetButton(Pre_Page)->drawFlag = true;
		//��һҳ ���ĸ���ť
		int& Button4_x = button->GetButton(Pre_Page)->rectxy->x;//��ť4x����
		int& Button4_flag = button->GetButton(Pre_Page)->flag;//��ť4�����ʶ
		index_isTrue = index - 3 > 0;
		switch (button->GetButtonLeftState(Pre_Page))
		{
		case Key_Down:
			if (index_isTrue) { index -= 3; }
			break;
		case Key_Move:
			if (Button4_flag == 0) { Button4_x++; if (Button4_x > 30) { Button4_flag = 1; } }
			else { Button4_x--; if (Button4_x < 1) { Button4_flag = 0; } }
			break;
		default:
			Button4_x = text1.x;
			Button4_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Pre_Page)->drawFlag = false;
	}


	needToDraw = Skill3 < game->Getskill_sum();
	if (needToDraw) {
		button->GetButton(Nex_Page)->drawFlag = true;
		//��һҳ �������ť
		int& Button5_x = button->GetButton(Nex_Page)->rectxy->x;//��ť5x����
		int& Button5_flag = button->GetButton(Nex_Page)->flag;//��ť5���ױ�ʶ
		index_isTrue = index + 3 <= game->Getskill_sum();
		switch (button->GetButtonLeftState(Nex_Page))
		{
		case Key_Down:
			if (index_isTrue) { index += 3; }
			break;
		case Key_Move:
			if (Button5_flag == 0) { Button5_x--; if (Button5_x < 500 - text2.w - 30) { Button5_flag = 1; } }
			else { Button5_x++; if (Button5_x > 500 - text2.w) { Button5_flag = 0; } }
			break;
		default:
			Button5_x = text2.x;
			Button5_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Nex_Page)->drawFlag = false;
	}



	const wchar_t* text;//��ʾ���ı�����
	SDL_Color color;//�ı���ɫ
	std::string name;//ͼƬ����
	if (red_player->Getskill()->empty()) {
		text = L"�췽ѡ����";
		name = "reddown.png";
		color = RED;
	}
	else {
		text = L"����ѡ����";
		name = "bluedown.png";
		color = BLUE;
	}
	DrawTTF(text, color, { 175,25,fontSize * 6,30 });
	SDL_Rect rect = { 140,25,30,30 };
	texture->Draw(name, NULL, &rect);
	return 0;
}