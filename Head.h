#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
using namespace sf;

const int W = 800;
const int H = 600;

double move_speed = 0.02;
double angle_dif = 2.0;
const double FOV = 100;
const double depth = 600;
const double proj = 30;
const double wallHeight = 400;
const double EnemyHeight = 300;
const double eps = 1e-5;
vector<VertexArray> Rays;
vector<double> WallsSize;
vector<VertexArray> RaysEnemy;


const double PI = atan(-1.0);

RenderWindow window(VideoMode(W, H), "Doom");

Texture Hero_text;
Texture shotgunText;
Texture wallSpriteText;
Texture PinkyText;

void getTextures() {
	Hero_text.loadFromFile("Sprites/Player.png");
	shotgunText.loadFromFile("Sprites/Shotgun.png", IntRect(0, 0, 500, 500));
	wallSpriteText.loadFromFile("sprites/Wall.png");
	PinkyText.loadFromFile("sprites/Pinky.png", IntRect(0, 0, 45, 65));
}

bool equal(double a, double b) {
	return abs(abs(a) - abs(b)) < eps;
}

Clock clockk;
Clock shootDelay;
Clock PinkyBeatDelay;
double prevTime = shootDelay.getElapsedTime().asMilliseconds();
double prevTimeP = PinkyBeatDelay.getElapsedTime().asMilliseconds();

void timerUpdate() {
	if (shootDelay.getElapsedTime().asMilliseconds() > 100000000) {
		shootDelay.restart();
		prevTime = shootDelay.getElapsedTime().asMilliseconds();
	}
	if (PinkyBeatDelay.getElapsedTime().asMilliseconds() > 100000000) {
		PinkyBeatDelay.restart();
		prevTimeP = PinkyBeatDelay.getElapsedTime().asMilliseconds();
	}
}
Font font;

