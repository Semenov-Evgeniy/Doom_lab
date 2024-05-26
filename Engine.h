#pragma once
#include "Drawing.h"
#include "Head.h"
#include "Classes.h"

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

void draw_fig(RenderWindow& window) {
    for (int i = 0; i < Walls.size(); i++) {
        Wall a(Walls[i].first.x, Walls[i].first.y, Walls[i].second.x, Walls[i].second.y);
        a.draw(window);
    }
}

void draw_ray(RenderWindow& window) {
    for (int i = 0; i < Rays.size(); i++) {
        window.draw(Rays[i]);
    }
    Rays.clear();
}

void startEngine(RenderWindow& window) {
    draw_fig(window);
    player.draw_player(window);
    ray_throw();
    draw_ray(window);
}