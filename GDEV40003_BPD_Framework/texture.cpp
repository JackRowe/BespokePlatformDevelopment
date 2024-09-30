#include "texture.h"

texture::texture(SDL_Renderer* p_renderer, std::string p_path) {
	clean();

	c_renderer = p_renderer;
	load(p_path);
}

texture::~texture() {
	clean();
}

bool texture::load(std::string p_path) {
	if (c_renderer == nullptr) {
		std::cout << "Renderer does not exist: " << SDL_GetError() << std::endl;
		return false;
	};

	SDL_Surface* surface = IMG_Load(p_path.c_str());

	if (surface == nullptr) {
		std::cout << "Surface was not created: " << IMG_GetError() << std::endl;
		return false;
	}

	c_texture = SDL_CreateTextureFromSurface(c_renderer, surface);

	if (c_texture == nullptr) {
		std::cout << "Texture was not created: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_FreeSurface(surface);
	return true;
}

bool texture::clean() {
	if (c_texture == nullptr) return false;

	SDL_DestroyTexture(c_texture);
	c_texture = nullptr;
	return true;
}