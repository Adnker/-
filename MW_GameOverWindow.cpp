#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_GameOverWindow()
{
	flagWindow = GameoverWindow;//�����ڱ�ʶ����Ϊ��Ϸ�������ڱ�ʶ
	const wchar_t* text;//��ʾ���ı�����
	SDL_Color color;//�ı���ɫ
	std::string name;//ͼƬ����
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���ͼƬ
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