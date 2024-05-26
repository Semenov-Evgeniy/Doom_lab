#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
using namespace sf;

const int W = 800;
const int H = 600;

double move_speed = 5.0;
double angle_dif = 10.0;
const double FOV = 150;
const double depth = 600;
const double proj = 30;
const double wallHeight = 400;
const double eps = 1e-5;
//column_height = win_h / (t * cos(angle - player_a))
vector<VertexArray> Rays;


const double PI = atan(-1.0);

RenderWindow window(VideoMode(W, H), "Doom");

Texture Hero_text;
Texture shotgunText;
Texture wallSpriteText;

void getTextures() {
	Hero_text.loadFromFile("Sprites/Player.png");
	shotgunText.loadFromFile("Sprites/Shotgun.png", IntRect(0, 0, 500, 500));
	wallSpriteText.loadFromFile("sprites/Wall.png");
}

bool equal(double a, double b) {
	return abs(abs(a) - abs(b)) < eps;
}



