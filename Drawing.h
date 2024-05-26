#pragma once
#include "Head.h"
#include "Logic.h"
#include "Engine.h"
#include "Classes.h"

void drawMap(RenderWindow& window) {
    window.clear();
    RectangleShape flooor(Vector2f(W, H / 2));
    flooor.setPosition(0, H / 2);
    flooor.setFillColor(Color(128, 128, 128));
    window.draw(flooor);
    ray_throw();
    double screenX = 0, screenY;
    double stepX = W * 1.0 / Rays.size() * 1.0, stepY;
    double stepText = 0;
    wallSpriteText.loadFromFile("Sprites/Wall.png");
    wallSpriteText.setSmooth(1);
    for (int i = 0; i < Rays.size(); i++) {
        if (stepText > 128 + stepX) stepText = 0;
        Vec first = { Rays[i][0].position.x, Rays[i][0].position.y };
        Vec second = { Rays[i][1].position.x, Rays[i][1].position.y };
        if (distance_point(first, second) < depth - 1) {
            double diff = proj / distance_point(first, second);
            stepY = diff * wallHeight;
            screenY = (H / 2) - (stepY / 2);
            //RectangleShape drawWall;
            Sprite drawWall;
            drawWall.setPosition(screenX, screenY);
            //drawWall.setSize(Vector2f(stepX, stepY));
            drawWall.setTexture(wallSpriteText);
            drawWall.setTextureRect(IntRect(stepText / 1.15, 0, stepX, 128));
            double diff1 = 1;
            if (distance_point(first, second) < 50) diff1 = 1;
            if (distance_point(first, second) > 500) diff1 = 0.1;
            if (distance_point(first, second) <= 500 && distance_point(first, second) > 50)
                diff1 = 1 - (0.002 * (distance_point(first, second) - 50));
            //drawWall.setFillColor(Color(0, 255*diff1, 255*diff1));
            drawWall.setScale(Vector2f(1.5, stepY / 128));
            drawWall.setColor(Color(255*diff1, 255*diff1, 255*diff1));
            stepText += stepX;
            window.draw(drawWall);
            
        }
        
        screenX += stepX;
    }
    Rays.clear();
}

void drawWeapon(RenderWindow& window) {
    Sprite shotgunSpr;
    shotgunSpr.setScale(0.7, 0.7);
    shotgunSpr.setOrigin(W / 3.7, 0);
    shotgunSpr.setTexture(shotgunText);
    shotgunSpr.setPosition(W/2, H/2+H/8);
    window.draw(shotgunSpr);
}

void start3D(RenderWindow& window) {
    drawMap(window);
    drawWeapon(window);
}

void draw_all(RenderWindow& window) {
    window.setFramerateLimit(30);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            Keyboard_func(event);
        }
        window.clear();
        //startEngine(window);
        start3D(window);
        window.display();
    }
}
