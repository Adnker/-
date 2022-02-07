#include "Main_Window.h"
#include "Game.h"

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

	/*//////////////////////////////////////////////////////////////////////////////////*/
	//���Ƽ���
	int h_skill = 720;//����ͳһ�߶�
	int w_skill = 50;//����ͳһ���
	int j_skill = 30;//����ͳһ���
	////�ж�ѡ���ģʽ ��ͬ��ģʽ��Ҫ���ƵĶ�����ͬ
	//if (model == SkillModel) {
	//	//����ģʽ
	//	DrawSkill(game->Getskill_name(red_player->Getskill()->at(0)), NULL, { 350 - j_skill - w_skill, h_skill, w_skill, w_skill });//���ƺ췽��ҵļ���ͼ��
	//	DrawSkill(game->Getskill_name(blue_player->Getskill()->at(0)), NULL, { 350 + j_skill, h_skill, w_skill, w_skill });//����������ҵļ���ͼ��
	//}
	//else if (model == FrightModel) {
	//	//����ģʽ
	//	const vector<SKILL>* skill;//������ҵļ�������
	//	const wchar_t* skill_name;//�����Ӧ�ļ�������

	//	skill = red_player->Getskill();//��ȡ�췽��ҵļ�������
	//	//���ƺ췽�����������
	//	for (int i = 0; i < 3; i++) {
	//		DrawSkill(game->Getskill_name(skill->at(i)), NULL, { 700 - w_skill - j_skill,h_skill,w_skill,w_skill });
	//		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_num(i)), RED, { i * fontSize * 3,740,40,40 });
	//	}
	//	skill = blue_player->Getskill();//��ȡ������Ҽ�������
	//	//�������������������
	//	for (int i = 0; i < 3; i++) {
	//		DrawSkill(game->Getskill_name(skill->at(i)), NULL, { 700 - w_skill - j_skill,h_skill,w_skill,w_skill });
	//		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_num(i)), BLUE, { 700 - (i + 1) * fontSize * 3,740,40,40 });
	//	}
	//}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//��������ж�·��
	int jidi_h = 50;//ͳһ���ر߳�
	const vector<Move_point*>* move_point;//��������ƶ�����

	move_point = red_player->GetMove_point();//��ȡ��ҵ��ƶ�����
	if (!move_point->empty()) {
		FillRect(move_point->at(0)->point->x * 100 + 25, move_point->at(0)->point->y * 100 + 25, jidi_h, jidi_h, &RED);//������ҵĻ���
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//������ɫ����ɫΪ��ɫ
		DrawMove(move_point, &RED);
	}
	move_point = blue_player->GetMove_point();//��ȡ�����ƶ�����
	if (!move_point->empty()) {
		FillRect(move_point->at(0)->point->x * 100 + 25, move_point->at(0)->point->y * 100 + 25, jidi_h, jidi_h, &BLUE);//������������
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//������ɫ����ɫΪ��ɫ
		DrawMove(move_point, &BLUE);
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
				DrawPicture("backgroundPlayer.png", NULL, { window_msg.at(i)->rect.x, window_msg.at(i)->rect.y,
					window_msg.at(i)->rect.w, window_msg.at(i)->rect.h });//������ʾ���ڱ���
				DrawTTF(window_msg.at(i)->text, LITTLE_BLACK, window_msg.at(i)->rect);//������ʾ������ʾ����
				window_msg.at(i)->liveTime++;//������ʾ������ʾʱ��
			}
		}
	}

	if (red_player->SkillNeedShow()) 
	{
		DrawSkill(game->Getskill_name(red_player->ShowSkill_index()), NULL, red_player->ShowSkill_rect());
	}
	if (blue_player->SkillNeedShow())
	{
		DrawSkill(game->Getskill_name(blue_player->ShowSkill_index()), NULL, blue_player->ShowSkill_rect());
	}
	return 0;
}