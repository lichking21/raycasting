#ifndef RAYCAST_H
#define RAYCAST_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Raycast
{

private:
	int  WIDTH = 800, HEIGHT = 600;
	static const int map_w = 15, map_h = 15;
	int tex_w = 64, tex_h = 64;
	int wall_size = 20;

	CircleShape player;
	RectangleShape wall;

	float speed = 0.005f;
	float rotation_speed = 0.002f;
	float PI = 3.14159265f;

	float pos_x = 1.5f, pos_y = 1.5f;
	float dir_x = -1, dir_y = 0;
	float plane_x = 0, plane_y = 0.66;

public:
	int game_map[map_w][map_h] = {

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	Raycast() : 
		player(7.f, 4.f),
		wall(Vector2f(wall_size, wall_size)) {}

	void player_move();
	void raycast(RenderWindow& window);
};


#endif // ! RAYCAST_H




