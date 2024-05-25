#pragma once
#include "Drawing.h"
#include "Head.h"
#include "Classes.h"

void initWalls() {
    Wall a(50, 100, 30, 50);
    //Walls.push_back(a);
}

void draw_fig(RenderWindow& window) {
    
    //a.draw(window);
}

void draw_ray(RenderWindow& window) {
    for (int i = 0; i < Rays.size(); i++) {
        window.draw(Rays[i]);
    }
    Rays.clear();
}

void startEngine(RenderWindow& window) {
    Texture Hero_text;
    Hero_text.loadFromFile("Sprites/Player.png");
    player.Player_model.setTexture(Hero_text);

    draw_fig(window);
    player.draw_player(window);
    ray_throw();
    draw_ray(window);
}