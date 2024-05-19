#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

const int W = 800;
const int H = 600;

const double PI = atan(-1.0);

RenderWindow window(VideoMode(W, H), "Prikolich))");

class Player {
public:
	double x = W/2, y = H/2;
    double angle = 0.0;
    Texture Hero_text;
    Sprite Player_model;
    void draw_player(RenderWindow& window) {
        //Player_model.setTexture(Hero_text);
        Player_model.setOrigin(Vector2f(25, 25));
        Player_model.setPosition(x, y);
        Player_model.setRotation(-angle/4);
        window.draw(Player_model);
    }
    double change_angle() {
        if (angle > 1440) {
            angle = angle - 1440;
        }
        if (angle < 0) {
            angle = 1440 + angle;
        }
        return angle;
    }
};

class Wall {
    int x, y, w, h;
    Color s = Color(128, 255, 255);
    Wall() : x(0), y(0), w(0), h(0) {};
    Wall(int x0, int y0, int w0, int h0) : x(x0), y(y0), w(w0), h(h0) {};
    bool is_colis(VertexArray& line) {
        //smth
    }
};

Player player;