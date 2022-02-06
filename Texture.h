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
	int DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect* rect2,int flag_);//���Ƽ���ͼƬ flagΪ�Ƿ���Ҫ�߿�
	int ChangRenderer(SDL_Renderer* renderer);//�޸���ɫ��
	int LoadAllSkill();//����ȫ������ͼƬ
	SDL_Texture* GetSkillTexture(const wchar_t* name);//��ȡͼƬ
	SDL_Texture* GetTexture(std::string name);//��ȡͼƬ
private:
	//��ɫ��
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> texture;
	std::unordered_map<const wchar_t*, SDL_Texture*> tex_skill;
};

#endif