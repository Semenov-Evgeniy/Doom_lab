#pragma once
#include "Drawing.h"
#include "Head.h"
#include "Classes.h"

void initHealths() {
    double x, y;
    ifstream in("Map/Healths.txt");
    while (in >> x >> y) {
        Health a(x, y);
        Healths.push_back(a);
    }
    in.close();
}

void drawHealths() {
    for (int i = 0; i < Healths.size(); i++) {
        Healths[i].engineDraw();
    } 
}

void initEnemies() {
    double x, y, w, h;
    ifstream in("Map/Enemy.txt");
    while (in >> x >> y >> w >> h) {
        Pinky a(x, y, w, h);
        Pinkies.push_back(a);
    }
    in.close();
}

void drawEnemy() {
    for (int i = 0; i < Pinkies.size(); i++) {
        Pinkies[i].engineDraw();
        Pinkies[i].movement();
    }
}

void initWalls() {
    double x, y, w, h;
    ifstream in("Map/Walls.txt");
    while (in >> x >> y >> w >> h) {
        Vec a = { x, y };
        Vec b = { w, h };
        Walls.push_back({a, b});
    }
    in.close();
}

void draw_fig() {
    for (int i = 0; i < Walls.size(); i++) {
        Wall a(Walls[i].first.x, Walls[i].first.y, Walls[i].second.x, Walls[i].second.y);
        a.draw();
    }
}

void draw_ray() {
    for (int i = 0; i < Rays.size(); i++) {
        window.draw(Rays[i]);
    }
    Rays.clear();
}

void startEngine() {
    draw_fig();
    player.draw_player();
    ray_throw();
    drawEnemy();
    draw_ray();
    drawHealths();
    collision();
}