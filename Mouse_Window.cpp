#include "Mouse_Window.h"

int Mouse_Window::Updata()
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

	return 0;
}

Mouse_Window::Mouse_Window(Input* input_)
{
	input = input_;
}

vector<Point*> Mouse_Window::Getpoint()
{
	return point_sum;
}
