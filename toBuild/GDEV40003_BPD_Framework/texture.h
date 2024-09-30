#pragma once

#include <string>
#include <iostream>

#include "SDL_image.h"

class texture
{
private:
	SDL_Renderer* c_renderer = nullptr;
	SDL_Texture* c_texture = nullptr;
public:
	texture(SDL_Renderer* p_renderer, std::string p_path);
	~texture();

	SDL_Renderer* getRenderer() { return c_renderer; };
	SDL_Texture* getTexture() { return c_texture; };

	void setRenderer(SDL_Renderer* p_renderer) { c_renderer = p_renderer; }
	void setTexture(SDL_Texture* p_texture) { c_texture = p_texture; }

	bool load(std::string p_path);
	bool clean();
};

