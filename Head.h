#pragma once
#define _USE_MATH_DEFINES
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
using namespace sf;

const int W = 1024;
const int H = 768;

double move_speed = 0.02;
double angle_dif = 0.5;
const double FOV = 60;
const double depth = 600;
const double proj = 40;
const double wallHeight = 500;
const double EnemyHeight = 300;
const double eps = 1e-3;
const double epsA = 1;
vector<VertexArray> Rays;
vector<double> WallsSize;

const double PI = acos(-1.0);

RenderWindow window(VideoMode(W, H), "Doom");

Texture Hero_text;
Texture shotgunText;
Texture wallSpriteText;
Texture PinkyText;
Texture fireShot;
Texture PinkyEat;
Texture endText;
Texture HealthText;


void getTextures() {
	Hero_text.loadFromFile("Sprites/Player.png");
	shotgunText.loadFromFile("Sprites/Shoot.png");
	wallSpriteText.loadFromFile("sprites/Wall.png");
	PinkyText.loadFromFile("sprites/PinkyGo.png");
	fireShot.loadFromFile("sprites/fire.png");
	PinkyEat.loadFromFile("sprites/PinkyEat.png");
	HealthText.loadFromFile("sprites/Health.png");
	endText.loadFromFile("sprites/Exit.png");
}

bool equal(double a, double b) {
	return abs(abs(a) - abs(b)) < eps;
}
bool equalA(double a, double b) {
	return abs(abs(a) - abs(b)) < epsA;
}

Clock clockk;
Clock shootDelay;
Clock PinkyBeatDelay;
Clock Anim;
Clock AnimA1;
Clock AnimP;
Clock HealthA;

double prevTime = shootDelay.getElapsedTime().asMilliseconds();
double prevTimeP = PinkyBeatDelay.getElapsedTime().asMilliseconds();
double prevTimeA = Anim.getElapsedTime().asMilliseconds();
double prevTimeA1 = Anim.getElapsedTime().asMilliseconds();
double prevTimePA = AnimP.getElapsedTime().asMilliseconds();
double prevTimeH = HealthA.getElapsedTime().asMilliseconds();

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

