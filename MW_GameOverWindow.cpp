#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_GameOverWindow()
{
	SDL_Rect rect = { 50,30,100,50 };//���־���
	flagWindow = GameoverWindow;//�����ڱ�ʶ����Ϊ��Ϸ�������ڱ�ʶ
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//���Ʊ���ͼƬ
	//�ж���һ��ʧ�� ��һ��ʧ�ܾͻ��ƶ���ʤ��
	if (flag_Player == Red_Player) {
		DrawTTF(L"����ʤ��", BLUE, rect);
	}
	else {
		DrawTTF(L"�췽ʤ��", RED, rect);
	}
	DrawTTF(L"����ص���ҳ", BLACK, { 20,100,160,50 });//��ʾ�û��������������
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		b_flagWindow = flagWindow;
		flagWindow = MainWindow;//�����ڱ�ʶ����Ϊ�����ڱ�ʶ
	}
	return 0;
}