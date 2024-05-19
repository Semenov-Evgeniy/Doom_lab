#pragma once
#include "Head.h"
#include "Logic.h"

RectangleShape Wall;

void draw_fig(RenderWindow& window) {
    Wall.setSize(Vector2f(50, 100));
    Wall.setFillColor(Color::Green);
    Wall.setPosition(0, 0);
    window.draw(Wall);

    RectangleShape Wall1(Vector2f(100, 50));
    Wall1.setFillColor(Color::Blue);
    Wall1.setPosition(100, 0);
    window.draw(Wall1);
}

void draw_ray(RenderWindow& window) {
    for (int i = 0; i < Rays.size(); i++) {
        window.draw(Rays[i]);
    }
    Rays.clear();
}

void draw_all(RenderWindow& window) {

    Texture Hero_text;
    Hero_text.loadFromFile("Sprites/Player.png");
    player.Player_model.setTexture(Hero_text);

    RectangleShape floor(Vector2f(W, H / 2));
    floor.setPosition(0, H / 2);
    floor.setFillColor(Color(128, 128, 128));

    while (window.isOpen()) {

        
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            Keyboard_func(event);
        }

        window.clear();
        window.draw(floor);
        draw_fig(window);
        player.draw_player(window);
        ray_throw();
        draw_ray(window);
        window.display();
    }
}
