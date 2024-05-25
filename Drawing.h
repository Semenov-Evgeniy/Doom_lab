#pragma once
#include "Head.h"
#include "Logic.h"
#include "Engine.h"
#include "Classes.h"

void start3D(RenderWindow& window) {
    RectangleShape floor(Vector2f(W, H / 2));
    floor.setPosition(0, H / 2);
    floor.setFillColor(Color(128, 128, 128));

    window.draw(floor);
}

void draw_all(RenderWindow& window) {

    while (window.isOpen()) {
        
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            Keyboard_func(event);
        }

        window.clear();
        //start3D(window);
        startEngine(window);
        window.display();
    }
}
