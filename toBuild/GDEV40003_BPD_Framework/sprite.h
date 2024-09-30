#pragma once

#include "SDL.h"
#include "texture.h"
#include "vectors.h"

class sprite
{
private:
	texture* c_texture = nullptr;

	Vector2<int> c_position = { 0 };
	Vector2<int> c_scale = { 0 };
	Vector4<int> c_colour = { 1 };

	int c_colourShift = 0;
public:
	sprite(
		texture* p_texture = nullptr,
		Vector2<int> p_position = { 0 },
		Vector2<int> p_scale = { 0 },
		Vector4<int> p_colour = { 0 }
	);

	~sprite();

	texture* getTexture() { return c_texture; };
	void setTexture(texture* p_texture) { c_texture = p_texture; };

	Vector2<int> getPosition() { return c_position; };
	Vector2<int> getScale() { return c_scale; };
	Vector4<int> getColour() { return c_colour; };

	// consider sending each individual component of the vector to save memory
	void setPosition(Vector2<int> p_position) { c_position = p_position; };
	void setScale(Vector2<int> p_scale) { c_scale = p_scale; };
	void setColour(Vector4<int> p_colour) { c_colour = p_colour; };

	int getColourShift() { return c_colourShift; };
	void setColourShift(int p_newColourShift) { c_colourShift = p_newColourShift; };
	void addColourShift(int p_addedColourShift) { c_colourShift += p_addedColourShift; };
	void subColourShift(int p_subbedColourShift) { c_colourShift -= p_subbedColourShift; };

	void draw(SDL_Renderer* renderer);
};

