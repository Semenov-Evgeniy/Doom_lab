#pragma once
#include "Head.h"
#include "Logic.h"
#include "Engine.h"
#include "Classes.h"

void start3D(RenderWindow& window) {
    window.clear();
    RectangleShape floor(Vector2f(W, H / 2));
    floor.setPosition(0, H / 2);
    floor.setFillColor(Color(128, 128, 128));
    window.draw(floor);
    ray_throw();
    double screenX = 0, screenY;
    double stepX = W * 1.0 / Rays.size()*1.0, stepY;
    for (int i = 0; i < Rays.size(); i++) {
        Vec first = { Rays[i][0].position.x, Rays[i][0].position.y };
        Vec second = { Rays[i][1].position.x, Rays[i][1].position.y };
        if (distance_point(first, second) < depth-1) {
            double diff = proj / distance_point(first, second);
            stepY = diff * wallHeight;
            screenY = (H / 2) - (stepY / 2);
            RectangleShape drawWall;
            drawWall.setPosition(screenX, screenY);
            drawWall.setSize(Vector2f(stepX, stepY));
            if (distance_point(first, second) < 50) diff = 1;
            if (distance_point(first, second) > 500) diff = 0.1;
            if (distance_point(first, second) <= 500 && distance_point(first, second) > 50)
                diff =1 - (0.002 * (distance_point(first, second)-50));
            drawWall.setFillColor(Color(0, 255*diff, 255*diff));
            window.draw(drawWall);
        }
        screenX += stepX;
    }
    Rays.clear();
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
