#pragma once
#include "Head.h"
#include "Classes.h"


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
		player.angle -= angle_dif;
		player.change_angle();
	}
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
		player.angle += angle_dif;
		player.change_angle();
	}
}

void ray_throw() { 
	int rayLength = FOV;
	for (int dir = player.angle - rayLength; dir <= player.angle + rayLength; dir += 3){
		VertexArray line(Lines, 2);
		line[0].position = Vector2f(player.x, player.y);
		line[1].position = Vector2f(player.x + depth * cos(dir * PI / 180.0), player.y + depth * sin(dir * PI / 180.0));
		line[1].color = Color::Green;
		line[0].color = Color::Green;
		Wall a(50, 100, 30, 50);
			Vec newLine;
			if (a.is_colis(line)) {
				line[1].position = Vector2f(a.newCoords(line, newLine).x, a.newCoords(line, newLine).y);
			}
			Rays.push_back(line);
	}
}

void distance_to_wall() {
	
}
