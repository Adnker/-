#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_MainWindow()
{
	flagWindow = MainWindow;
	int button_x = 200;
	int button_y = 100;
	int button_w = 100;
	int button_h = 40;
	int jianju = 45;
	int picture_h = 40;
	if (b_flagWindow != MainWindow) {
		button->Clear();
		button->AddButton(L"��ʼ��Ϸ", texture->GetTexture("k3.png"), NULL, { button_x,button_y * 1,button_w,button_h }, font, &BLACK);
		button->AddButton(L"ģʽѡ��", texture->GetTexture("k3.png"), NULL, { button_x,button_y * 2,button_w,button_h }, font, &BLACK);
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���
	button->DrawButton(renderer);//����ȫ����ť


	BUTTONER Button1 = 0;
	BUTTONER Button2 = 1;
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
			texture->LoadAllSkill();//��texture����ȫ���ļ���ͼƬ
			break;
		case FrightModel:
			b_flagWindow = flagWindow;
			flagWindow = FrightWindow;
			CreatNewWindow(&rect_Fright_Window);
			texture->LoadAllSkill();//��texture����ȫ���ļ���ͼƬ
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
	return 0;
}