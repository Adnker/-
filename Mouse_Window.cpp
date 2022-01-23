#include "Mouse_Window.h"

int Mouse_Window::DrawSnake()
{
	if (flag_mouse_time > 0) {
		flag_mouse_time++;
		if (flag_mouse_time > 3) { flag_mouse_time = 0; }
	}
	else if (flag_mouse_time == 0 && input->GetMouseMove()) {
		if (point_sum.size() > 4) {
			point_sum.erase(point_sum.begin(), point_sum.begin() + 1);//ɾ�������Ԫ��
		}
		Point* temp = new Point();//�����µ�����
		//��ȡ���ڵ����λ��
		temp->x = input->GetNowPoint()->x;
		temp->y = input->GetNowPoint()->y;
		point_sum.emplace_back(temp);//���뻺����
		flag_mouse_time++;//��ʼ��ʱ
	}

	//��������ƶ���·
	for (int i = 1; i < point_sum.size(); i++) {
		main_window->DrawLine(point_sum[i - 1]->x, point_sum[i - 1]->y, point_sum[i]->x, point_sum[i]->y);
	}

	return 0;
}

Mouse_Window::Mouse_Window(Input* input_,Main_Window* main_window_)
{
	input = input_;
	main_window = main_window_;
}
