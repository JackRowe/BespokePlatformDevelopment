#include "sprite.h"

sprite::sprite(texture* p_texture, Vector2<int> p_position, Vector2<int> p_scale, Vector4<int> p_colour) {
	c_texture = p_texture == nullptr ? c_texture : p_texture;
	c_position = p_position.length() == 0 ? c_position : p_position;
	c_scale = p_scale.length() == 0 ? c_scale : p_scale;
	c_colour = p_colour.length() == 0 ? c_colour : p_colour;
}

sprite::~sprite() {

}

void sprite::draw(SDL_Renderer* renderer) {
	SDL_Rect rect = {};
	rect.x = c_position.x;
	rect.y = c_position.y;
	rect.w = c_scale.x;
	rect.h = c_scale.y;

	SDL_SetRenderDrawColor(renderer, c_colour.x - c_colourShift, c_colour.y - c_colourShift, c_colour.z - c_colourShift, c_colour.w);
	SDL_RenderFillRect(renderer, &rect);

	if (c_texture == nullptr) return;

	SDL_RenderCopyEx(renderer, c_texture->getTexture(), NULL, &rect, 0, NULL, SDL_FLIP_NONE);
}