#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

const int W = 800;
const int H = 600;

double move_speed = 5.0;
double angle_dif = 5.0;
const double FOV = 150;
const double depth = 600;
vector<VertexArray> Rays;
//vector<Wall> Walls;

const double PI = atan(-1.0);

RenderWindow window(VideoMode(W, H), "Doom");



