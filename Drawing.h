#pragma once
#include "Head.h"
#include "Logic.h"
#include "Engine.h"
#include "Classes.h"

void initText() {
    font.loadFromFile("Doom2016Right.ttf");
}

void drawPinky3D(double screenX, double screenY, double stepY, double diff1) {
    Sprite Pinky;
    Pinky.setOrigin(22.5, -32.5);
    Pinky.setTexture(PinkyText);
    Pinky.setPosition(screenX, screenY);
    Pinky.setScale(Vector2f(1.5, stepY/22.5));
    Pinky.setColor(Color(255 * diff1, 255 * diff1, 255 * diff1));
    window.draw(Pinky);
}

void drawMap() {
    window.clear();
    RectangleShape flooor(Vector2f(W, H / 2));
    flooor.setPosition(0, H / 2);
    flooor.setFillColor(Color(128, 128, 128));
    window.draw(flooor);
    ray_throw();
    double screenX = 0, screenY;
    double stepX = W * 1.0 / Rays.size() * 1.0, stepY;
    double stepText = 0;
    wallSpriteText.setSmooth(1);
    for (int i = 0; i < Rays.size(); i++) {
        if (stepText > 128 + stepX) stepText = 0;
        Vec first = { Rays[i][0].position.x, Rays[i][0].position.y };
        Vec second = { Rays[i][1].position.x, Rays[i][1].position.y };
        if (distance_point(first, second) < depth - 1) {
            double diff = proj / distance_point(first, second);
            stepY = diff * wallHeight / WallsSize[i];
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
            for (int ind = 0; ind < PinkyDraw.size(); ind++) {
                if (i == PinkyDraw[ind]) {
                    drawPinky3D(screenX, screenY, stepY, diff1);
                }
            }
            window.draw(drawWall);
        }
        screenX += stepX;
    }
    screenX = 0;
    Rays.clear();
    PinkyDraw.clear();
    RaysEnemy.clear();
}

void drawInfo() {
    Text text(to_string(player.HP), font, 70);
    text.setFillColor(Color::Red);
    text.setScale(1, 1);
    text.setPosition(10, H - 80);
    window.draw(text);
}

void start3D() {
    drawMap();
    shotgun.drawWeapon();
    drawInfo();
    for (int i = 0; i < Pinkies.size(); i++) {
        Pinkies[i].movement();
    }
    
}

void gameOver() {
    window.clear();
    Text text("GAME OVER", font, 100);
    text.setFillColor(Color::Red);
    text.setScale(1, 1);
    text.setPosition(W / 2 - 130, H / 2-80);
    //text.setOrigin(100, 200);
    window.draw(text);
    window.display();
    sleep(Time(microseconds(3000000)));
    exit(0);
}

void draw_all(RenderWindow& window) {
    window.setFramerateLimit(30);
    while (window.isOpen()) {
        
        if (player.HP > 0) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
                Keyboard_func(event);
            }

            times = clockk.getElapsedTime().asMicroseconds();
            clockk.restart();
            times = times / 500;

            window.clear();
            timerUpdate();
            //startEngine();
            start3D();
            window.display();
        }
        else gameOver();
    }
}
