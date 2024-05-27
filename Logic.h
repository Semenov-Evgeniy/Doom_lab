#pragma once
#include "Head.h"
#include "Classes.h"

Vector2f prevPos = { W / 2, H / 2 };

void Keyboard_func(Event& event) {
	
	//Mouse::setPosition(Vector2i(W/2, H/2), window);

	double direction = player.angle;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		player.x += move_speed * times * cos(player.angle*PI/180.0);
		player.y += move_speed * times * sin(player.angle * PI / 180.0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		player.x -= move_speed * times * cos(player.angle * PI / 180.0);
		player.y -= move_speed * times * sin(player.angle * PI / 180.0);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.x -= move_speed * times * sin(player.angle * PI / 180.0);
		player.y += move_speed * times * cos(player.angle * PI / 180.0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.x += move_speed * times * sin(player.angle * PI / 180.0);
		player.y -= move_speed * times * cos(player.angle * PI / 180.0);
	}
	
	if ((event.type == Event::MouseButtonPressed)&&(event.key.code == Mouse::Left)) {
		double currTime = shootDelay.getElapsedTime().asMilliseconds();
		if (currTime - prevTime > 1000) {
			shotgun.shoot(player.angle);
			prevTime = currTime;
		}
		
	}
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
		exit(0);
	}
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	double switchAngle = pos.x - prevPos.x;
	player.angle += switchAngle*angle_dif;
	prevPos = pos;
}

void ray_throw() { 
	int rayLength = FOV;
	int indCnt = 0;
	for (int dir = player.angle - rayLength; dir <= player.angle + rayLength; dir += 3){
		VertexArray line(Lines, 2);
		line[0].position = Vector2f(player.x, player.y);
		line[1].position = Vector2f(player.x + depth * cos(dir * PI / 180.0), player.y + depth * sin(dir * PI / 180.0));
		line[1].color = Color::Green;
		line[0].color = Color::Green;
		for (int ind = 0; ind < Walls.size(); ind++) {
			Wall a(Walls[ind].first.x, Walls[ind].first.y, Walls[ind].second.x, Walls[ind].second.y);
			Vec newLine;
			if (a.is_colis(line)) {
				line[1].position = Vector2f(a.newCoords(line, newLine).x, a.newCoords(line, newLine).y);
			}
		}
		Rays.push_back(line);
		for (int i = 0; i < Pinkies.size(); i++) {
			Wall a(Pinkies[i].x, Pinkies[i].y, Pinkies[i].w, Pinkies[i].h);
			Vec newLine;
			if (a.is_colis(line)) {
				line[1].position = Vector2f(a.newCoords(line, newLine).x, a.newCoords(line, newLine).y);
				PinkyDraw.push_back(indCnt);
				continue;
			}
		}
		RaysEnemy.push_back(line);
		indCnt++;
		WallsSize.push_back(cos(dir * PI / 180.0 - player.angle * PI / 180.0));
	}
}
