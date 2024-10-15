#pragma once
#include <raylib.h>

class camera
{
	Vector2 position;
	//Vector2 scale;
	float zoom;

public:
	camera(Vector2 pos, float sc);

	Vector2 worldtocamspace(Vector2 p);

	Vector2 camtoworldspace(Vector2 p);

	float rescale(float x);

	Vector2 get_pos() { return position; };

	float get_zoom() { return zoom; };

	void changepos(Vector2 fac);

	void changezoom(float fac);

	void set_pos(Vector2 pos);

	void set_zoom(float sc);
};