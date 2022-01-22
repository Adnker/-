#include "Input.h"

int Input::CreateInput()
{
	//��ʼ��
	const Uint8* temp = SDL_GetKeyboardState(NULL);
	memcpy(nowKeyState, temp, SDL_NUM_SCANCODES);

	//��ǰһ֡�������ʼ��Ϊ0
	memset(beforeKeyState, 0, SDL_NUM_SCANCODES);
	return 0;
}

int Input::Updata()
{
	//��������ֵ
	memcpy(beforeKeyState, nowKeyState, SDL_NUM_SCANCODES);

	//��ȡ�µļ���״̬
	const Uint8* temp = SDL_GetKeyboardState(NULL);
	memcpy(nowKeyState, temp, SDL_NUM_SCANCODES);
	
	
	//�������״̬
	beforeMouseState = nowMouseState;
	beforePoint = nowPoint;

	//��ȡ�µ����״̬
	nowMouseState = SDL_GetMouseState(&nowPoint.x, &nowPoint.y);

	return 0;
}

int Input::GetKeyState(SDL_Scancode key)
{
	//�жϼ���״̬
	if (beforeKeyState[key] == 0)
	{
		if (nowKeyState[key] == 0)
		{
			return Key_None;
		}
		else
		{
			return Key_Down;
		}
	}
	else
	{
		if (nowKeyState[key] == 0)
		{
			return Key_Up;
		}
		else
		{
			return Key_Keep;
		}
	}
}

int Input::GetMouseState(int button)
{
	//�ж����״̬
	if ((beforeMouseState & SDL_BUTTON(button)) == 0)
	{
		if ((nowMouseState & SDL_BUTTON(button)) == 0)
		{
			return Key_None;
		}
		else
		{
			return Key_Down;
		}
	}
	else
	{
		if ((nowMouseState & SDL_BUTTON(button)) == 0)
		{
			return Key_Up;
		}
		else
		{
			return Key_Keep;
		}
	}
}
