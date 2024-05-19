#pragma once
#include "Head.h"

double move_speed = 5.0;
double angle_dif = 10.0;
const double FOV = 120;
vector<VertexArray> Rays;

void Keyboard_func(Event& event) {
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);

	double direction = player.angle;
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
		player.x += move_speed * cos(player.angle*PI/180.0);
		player.y += move_speed * sin(player.angle * PI / 180.0);
	}
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
		player.x -= move_speed * cos(player.angle * PI / 180.0);
		player.y -= move_speed * sin(player.angle * PI / 180.0);
	}
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
		player.angle += angle_dif;
		player.change_angle();
	}
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
		player.angle -= angle_dif;
		player.change_angle();
	}
}

void ray_throw() {
	int rayLength = FOV / 2;
	for (int dir = player.angle - rayLength; dir <= player.angle + rayLength; dir += 3){
			VertexArray line(Lines, 2);
			line[0].position = Vector2f(player.x, player.y);
			line[1].position = Vector2f(player.x + 1000 * cos(dir * PI / 180.0), player.y + 1000 * sin(dir * PI / 180.0));
			line[1].color = Color::Green;
			line[0].color = Color::Green;
			Rays.push_back(line);
	}
}

void distance_to_wall() {

}
