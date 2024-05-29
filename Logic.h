#pragma once
#include "Head.h"
#include "Classes.h"

Vector2f prevPos = { W / 2, H / 2 };

bool compare(VertexArray& line1, VertexArray& line2) {
	return distance_point(Vec({ line1[0].position.x, line1[0].position.y }), Vec({ line1[1].position.x, line1[1].position.y })) < distance_point(Vec({ line2[1].position.x, line2[1].position.y }), Vec({ line2[0].position.x, line2[0].position.y }));
}
bool fGo = true, bGo = true, lGo = true, rGo = true;
void Keyboard_func(Event& event) {

	double direction = player.angle;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (fGo) {
			player.x += move_speed* (times/2) * cos(player.angle * PI / 180.0);
			player.y += move_speed* (times/2) * sin(player.angle * PI / 180.0);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (bGo) {
			player.x -= move_speed * (times / 2) * cos(player.angle * PI / 180.0);
			player.y -= move_speed * (times / 2) * sin(player.angle * PI / 180.0);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (lGo) {
			player.x += move_speed * (times / 2) * sin(player.angle * PI / 180.0);
			player.y -= move_speed * (times / 2) * cos(player.angle * PI / 180.0);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (rGo) {
			player.x -= move_speed * (times / 2) * sin(player.angle * PI / 180.0);
			player.y += move_speed * (times / 2) * cos(player.angle * PI / 180.0);
		}
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
	double switchAngle = pos.x - W/2;
	player.angle += switchAngle*angle_dif;
	player.change_angle();
	prevPos = pos;
	Mouse::setPosition({ W/ 2, H/ 2 }, window);
}

void ray_throw() { 
	int rayLength = FOV/2;
	int indCnt = 0;
	for (double dir = player.angle - rayLength; dir <= player.angle + rayLength; dir += 1){
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
		indCnt++;
		WallsSize.push_back(cos(dir * PI / 180.0 - player.angle * PI / 180.0));
	}
}

void collision() {
	for (int col = player.angle; col < 360+player.angle; col += 90) {
		VertexArray line(Lines, 2);
		line[0].position = Vector2f(player.x, player.y);
		line[1].position = Vector2f(player.x + 5 * cos(col * PI / 180.0), player.y + 5 * sin(col * PI / 180.0));
		line[1].color = Color::Red;
		line[0].color = Color::Red;
		//window.draw(line);
		for (int i = 0; i < Walls.size(); i++) {
			Wall a(Walls[i].first.x, Walls[i].first.y, Walls[i].second.x, Walls[i].second.y);
			if (a.is_colis(line)) {
				if (equalA(col, player.angle)) fGo = false;
				if (equalA(col, player.angle+90)) rGo = false;
				if (equalA(col, player.angle+180)) bGo = false;
				if (equalA(col, player.angle+270)) lGo = false;
				break;
			}
			else {
				if (equalA(col, player.angle)) fGo = true;
				if (equalA(col, player.angle + 90)) rGo = true;
				if (equalA(col, player.angle + 180)) bGo = true;
				if (equalA(col, player.angle + 270)) lGo = true;
			}
		}
	}
}
