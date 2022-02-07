#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_SkillWindow()
{
	flagWindow = SkillWindow;
	//��ť����
	int button_x = 200;//��ť��ʾλ��
	int button_y = 100;//��ť��ʾλ��
	int button_w = 100;//��ť��
	int button_h = 40;//��ť��
	SDL_Rect text1 = { 0,420,80,50 };//��һҳ��ť
	SDL_Rect text2 = { 420,420,80,50 };//��һҳ��ť
	BUTTONER Button1 = 0;//��ť1��ʶ
	BUTTONER Button2 = 1;//��ť2��ʶ
	BUTTONER Button3 = 2;//��ť3��ʶ
	BUTTONER Button4 = 3;//��ť4��ʶ
	BUTTONER Button5 = 4;//��ť5��ʶ


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
		button->GetButton(Button4)->drawFlag = false;//һ��ʼ��ʱ����һҳ���û���
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���



	//index + Button_ = ��Ӧ�ļ�������
	int Skill1 = index + Button1;//����1����
	int Skill2 = index + Button2;//����2����
	int Skill3 = index + Button3;//����3����
	//�޸İ�ť��ʾ�ļ�������
	button->GetButton(Button1)->text = game->Getskill_name(Skill1);
	button->GetButton(Button2)->text = game->Getskill_name(Skill2);
	button->GetButton(Button3)->text = game->Getskill_name(Skill3);
	button->DrawButton(renderer);//����ȫ����ť


	button->Updata(input);//����ȫ����ť��״̬
	int picture_h = 40;//ѡ����ʾͼƬ�߳�
	int skill_index = -1;//��Ҫ��ʾ�ļ�������
	int picture_index = -1;//��Ҫ��ʾ����ʾͼƬ����
	//��һ����ť
	bool Skill1_index_isTrue = Skill1 <= game->Getskill_sum();
	if (Skill1_index_isTrue) {
		switch (button->GetButtonLeftState(Button1))
		{
		case Key_Down:
			ChangeSkill(Skill1);//�޸���Ҽ��ܱ�ʶ
			index = 1;
			break;
		case Key_Move:
			picture_index = Button1;
			skill_index = Skill1;
			break;
		}
	}


	//�ڶ�����ť
	bool Skill2_index_isTrue = Skill2 <= game->Getskill_sum();
	if (Skill2_index_isTrue) {
		switch (button->GetButtonLeftState(Button2))
		{
		case Key_Down:
			ChangeSkill(Skill2);;//�޸���Ҽ��ܱ�ʶ
			index = 1;
			break;
		case Key_Move:
			picture_index = Button2;
			skill_index = Skill2;
			break;
		}
	}


	//��������ť
	bool Skill3_index_isTrue = Skill3 <= game->Getskill_sum();
	if (Skill3_index_isTrue) {
		switch (button->GetButtonLeftState(Button3))
		{
		case Key_Down:
			ChangeSkill(Skill3);;//�޸���Ҽ��ܱ�ʶ
			index = 1;
			break;
		case Key_Move:
			picture_index = Button3;
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
		button->GetButton(Button4)->drawFlag = true;
		//��һҳ ���ĸ���ť
		int& Button4_x = button->GetButton(Button4)->rectxy->x;//��ť4x����
		int& Button4_flag = button->GetButton(Button4)->flag;//��ť4�����ʶ
		index_isTrue = index - 3 > 0;
		switch (button->GetButtonLeftState(Button4))
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
		button->GetButton(Button4)->drawFlag = false;
	}


	needToDraw = Skill3 < game->Getskill_sum();
	if (needToDraw) {
		button->GetButton(Button5)->drawFlag = true;
		//��һҳ �������ť
		int& Button5_x = button->GetButton(Button5)->rectxy->x;//��ť5x����
		int& Button5_flag = button->GetButton(Button5)->flag;//��ť5���ױ�ʶ
		index_isTrue = index + 3 <= game->Getskill_sum();
		switch (button->GetButtonLeftState(Button5))
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
		button->GetButton(Button5)->drawFlag = false;
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