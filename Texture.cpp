#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer_)
{
	renderer = renderer_;
}

SDL_Texture* Texture::Loading(const std::string fileName)
{
	//�����ļ�
	SDL_Surface* face = IMG_Load(fileName.c_str());
	if (!face)
	{
		SDL_Log("error is face %s",SDL_GetError());
		return 0;
	}
	//��������ͼƬ
	SDL_Texture* texture = SDL_CreateTexture(renderer, 0, 0, 0, 0);
	texture = SDL_CreateTextureFromSurface(renderer, face);
	//�ͷ��ڴ�
	SDL_FreeSurface(face);
	if (!texture)
	{
		SDL_Log("error is texture %s",SDL_GetError());
		return 0;
	}
	return texture;
}

int Texture::Draw(const std::string fileName, SDL_Rect* rect1, SDL_Rect* rect2)
{
	SDL_Texture* tex = nullptr;
	//����������������Ҫ��ͼ���ļ�
	auto iter = texture.find(fileName);
	if (iter != texture.end())
	{
		tex = iter->second;
	}
	else {
		tex = Loading(fileName);
		texture.emplace(fileName, tex);
	}
	if (SDL_RenderCopy(renderer, tex, rect1, rect2) == -1)
	{
		SDL_Log("Map is error %s", SDL_GetError());
		return false;
	}
	return true;
}

int Texture::ChangRenderer(SDL_Renderer* renderer_)
{
	renderer = renderer_;
	texture.clear();
	return 0;
}
