#include "Main_Window.h"

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

void Main_Window::DrawPicture(const std::string fileName, SDL_Rect* rect1, SDL_Rect rect2)
{
	texture->Draw(fileName, rect1, &rect2);
}

void Main_Window::DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect rect2, int flag_)
{
	texture->DrawSkill(skill_name, rect1, &rect2, flag_);
}