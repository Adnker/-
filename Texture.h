#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "SDL_image.h"
#include <string>
#include <unordered_map>

//ͼƬ
/*
* ��Ҫ���ڼ���ͼƬ�����⿪��ͼƬ�ӿ�
*/
class Texture
{
public:
	Texture(SDL_Renderer* renderer);//���ػ���ͼƬ
	SDL_Texture* Loading(const std::string fileName);//����ͼƬ
	int Draw(const std::string fileName, SDL_Rect* rect1, SDL_Rect* rect2);//����ͼƬ
	int ChangRenderer(SDL_Renderer* renderer);//�޸���ɫ��
private:
	//��ɫ��
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> texture;
};

#endif