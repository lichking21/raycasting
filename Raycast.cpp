#include "Raycast.h"

void Raycast::player_move() {

	if (Keyboard::isKeyPressed(Keyboard::W)) {

		if (game_map[int(pos_x + dir_x * speed)][int(pos_y)] == 0)
			pos_x += dir_x * speed;
		if (game_map[int(pos_x)][int(pos_y + dir_y * speed)] == 0)
			pos_y += dir_y * speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {

		if (game_map[int(pos_x - dir_x * speed)][int(pos_y)] == 0)
			pos_x -= dir_x * speed;
		if (game_map[int(pos_x)][int(pos_y - dir_y * speed)] == 0)
			pos_y -= dir_y * speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {

		float old_dir_x = dir_x;
		dir_x = dir_x * cos(rotation_speed) - dir_y * sin(rotation_speed);
		dir_y = old_dir_x * sin(rotation_speed) + dir_y * cos(rotation_speed);

		float old_plane_x = plane_x;
		plane_x = plane_x * cos(rotation_speed) - plane_y * sin(rotation_speed);
		plane_y = old_plane_x * sin(rotation_speed) + plane_y * cos(rotation_speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {

		float old_dir_x = dir_x;
		dir_x = dir_x * cos(-rotation_speed) - dir_y * sin(-rotation_speed);
		dir_y = old_dir_x * sin(-rotation_speed) + dir_y * cos(-rotation_speed);

		float old_plane_x = plane_x;
		plane_x = plane_x * cos(-rotation_speed) - plane_y * sin(-rotation_speed);
		plane_y = old_plane_x * sin(-rotation_speed) + plane_y * cos(-rotation_speed);
	}

	player.setPosition(pos_x * wall_size, pos_y * wall_size);
}
void Raycast::raycast(RenderWindow& window) {

	for (int x = 0; x < WIDTH; x++) {

		float camera_x = 2 * x / static_cast<float>(WIDTH) - 1;
		float ray_dir_x = dir_x + plane_x * camera_x;
		float ray_dir_y = dir_y + plane_y * camera_x;

		int map_x = static_cast<int>(pos_x);
		int map_y = static_cast<int>(pos_y);

		float side_dist_x, side_dist_y;

		float delta_dist_x = (ray_dir_x == 0) ? INT_MAX : abs(1 / ray_dir_x);
		float delta_dist_y = (ray_dir_y == 0) ? INT_MAX : abs(1 / ray_dir_y);
		float ray_length;

		int step_x, step_y;

		int hit = 0;
		int side;

		if (ray_dir_x < 0) {

			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else {

			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}

		if (ray_dir_y < 0) {

			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}

		while (hit == 0) {

			if (side_dist_x < side_dist_y) {

				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else {

				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game_map[map_x][map_y] > 0) hit = 1;
		}

		if (side == 0)	ray_length = side_dist_x - delta_dist_x;
		else			ray_length = side_dist_y - delta_dist_y;

		int line_h = static_cast<int>(HEIGHT / ray_length);

		int draw_start = -line_h / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end = line_h / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		Color color;
		switch (game_map[map_x][map_y]) {

		case 1: color = color.Red; break;
		case 2: color = color.Green; break;
		case 3: color = color.Blue; break;
		case 4: color = color.White; break;
		case 5: color = color.Yellow; break;
		default: color = color.Magenta; break;
		}

		if (side == 1) {

			color.r /= 2;
			color.b /= 2;
			color.g /= 2;
		}

		Vertex line[] =
		{
			Vertex(Vector2f(x, draw_start), color),
			Vertex(Vector2f(x, draw_end), color)
		}; 
		
		window.draw(line, 2, sf::Lines);
	}
}