#pragma once
#include "Head.h"
#include "Logic.h"
#include "Engine.h"
#include "Classes.h"

void initText() {
    font.loadFromFile("Doom2016Right.ttf");
}

void drawExit() {
    Sprite exi;
    exi.setTexture(endText);
    double diff = proj / distance_point(Vec({ Exit.x, Exit.y }), Vec({ player.x, player.y }));
    exi.setScale(1 + diff, 1 + diff);
    exi.setOrigin(115 / 2, 0);
    Vec a = { Exit.x - player.x, Exit.y - player.y };
    Vec b = { player.x + 50 * cos(player.angle * PI / 180.0) - player.x, player.y + 50 * sin(player.angle * PI / 180.0) - player.y };
    double cosP = dot(a, b) / (modP(a) * modP(b));
    double radA = acos(cosP);
    double pAngle = radA * 180 / PI;
    if ((a.x) * (b.y) - (a.y) * (b.x) > 0) {
        pAngle = -pAngle;
    }
    if (abs(pAngle) > FOV) {
        Exit.isDraw = 0;
        return;
    }
    exi.setPosition(W / 2 + pAngle * 10, H / 2-100);
    window.draw(exi);
}
int indH = 0;
void drawHealth(Health &p) {
    Sprite heat;
    heat.setTexture(HealthText);
    heat.setTextureRect(IntRect(15 * indH, 0, 15, 18));
    double diff = proj / distance_point(Vec({ p.x, p.y }), Vec({ player.x, player.y }));
    heat.setScale(1 + diff, 1 + diff);
    heat.setOrigin(15 / 2, 0);
    Vec a = { p.x - player.x, p.y - player.y };
    Vec b = { player.x + 50 * cos(player.angle * PI / 180.0) - player.x, player.y + 50 * sin(player.angle * PI / 180.0) - player.y };
    double cosP = dot(a, b) / (modP(a) * modP(b));
    double radA = acos(cosP);
    double pAngle = radA * 180 / PI;
    if ((a.x) * (b.y) - (a.y) * (b.x) > 0) {
        pAngle = -pAngle;
    }
    if (abs(pAngle) > FOV) {
        p.isDraw = 0;
        return;
    }
    heat.setPosition(W / 2 + pAngle * 10, H / 2+50);

    double currTimeH = AnimP.getElapsedTime().asMilliseconds();
    if (currTimeH - prevTimeH > 160) {
        heat.setTexture(HealthText);
        heat.setTextureRect(IntRect(indH * 15, 0, 15, 18));
        prevTimeH = currTimeH;
        indH++;
        if (indH == 4) {
            indH = 0;
            heat.setTextureRect(IntRect(0, 0, 15, 18));
        }
    }
    window.draw(heat);
}

int ind = 0;
void drawFire() {
    if (shotgun.isShoot) {
        Sprite fire;
        double currTimeA1 = Anim.getElapsedTime().asMilliseconds();
        if (currTimeA1 - prevTimeA1 > 160) {
            fire.setTextureRect(IntRect(0, 0, 500, 500));
            fire.setScale(2, 2);
            fire.setOrigin(50 / 2, 50);
            fire.setPosition(W / 2, H - 200);
            prevTimeA1 = currTimeA1;
            window.draw(fire);
            ind++;
        }
    }
}
int i = 1;
bool grow = 1;
void drawShoot() {
    if (shotgun.isShoot){
        if (i == 0) {
            shotgun.shotgunSpr.setTextureRect(IntRect(0, 0, 115, 200));
            shotgun.isShoot = 0;
            i = 1;
            grow = 1;
            return;
        }
        double currTimeA = Anim.getElapsedTime().asMilliseconds();
        if (currTimeA - prevTimeA > 160) {
            shotgun.shotgunSpr.setTextureRect(IntRect(165+155 * (i-1), 0, 155, 200));
            shotgun.shotgunSpr.setScale(2.5, 2.5);
            shotgun.shotgunSpr.setOrigin(158.5, 200);
            shotgun.shotgunSpr.setPosition(W / 2, H);
            shotgun.shotgunSpr.setTexture(shotgunText);
            prevTimeA = currTimeA;
            if (grow)i++;
            else i--;
        }
        window.draw(shotgun.shotgunSpr);
        if (i > 2) grow = 0;
    }
}
int ind1 = 0;
int ind2 = 0;
void drawPinky3D(Pinky &p) {
    Sprite pinky;
    if (!p.isEat) {
        pinky.setTexture(PinkyText);
        pinky.setTextureRect(IntRect(ind1 * 45, 0, 45, 62));
    }
    else {
        pinky.setTexture(PinkyEat);
        pinky.setTextureRect(IntRect(ind2 * 47, 0, 47, 62));
    }
    double diff = proj / distance_point(Vec({ p.x, p.y }), Vec({ player.x, player.y }));
    pinky.setScale(1.5+diff, 1.5+diff);
    pinky.setOrigin(23, 0);
    Vec a = { p.x - player.x, p.y - player.y };
    Vec b = { player.x + 50 * cos(player.angle * PI / 180.0) - player.x, player.y + 50 * sin(player.angle * PI / 180.0) - player.y };
    double cosP = dot(a, b) / (modP(a) * modP(b));
    double radA = acos(cosP);
    double pAngle = radA * 180 / PI;
    if ((a.x) * (b.y) - (a.y) * (b.x) > 0) {
        pAngle = -pAngle;
    }
    if (abs(pAngle) > FOV) {
        p.isDraw = 0;
        return;
    }
    pinky.setPosition(W/2+pAngle*10, H / 2);
    if (!p.isEat) {
        double currTimePA = AnimP.getElapsedTime().asMilliseconds();
        if (currTimePA - prevTimePA > 160) {
            pinky.setTexture(PinkyText);
            pinky.setTextureRect(IntRect(ind1 * 45, 0, 45, 62));
            prevTimePA = currTimePA;
            ind1++;
            if (ind1 == 4) {
                ind1 = 0;
                pinky.setTextureRect(IntRect(0, 0, 45, 62));
            }
            
        }
    }
    else {
        double currTimePA = AnimP.getElapsedTime().asMilliseconds();
        if (currTimePA - prevTimePA > 333) {
            pinky.setTexture(PinkyEat);
            pinky.setTextureRect(IntRect(ind2 * 47, 0, 47, 62));
            prevTimePA = currTimePA;
            ind2++;
            if (ind2 == 3) {
                ind2 = 0;
                pinky.setTextureRect(IntRect(0, 0, 47, 62));
            }

        }
    }
    window.draw(pinky);
}

void drawMap() {
    window.clear();
    RectangleShape flooor(Vector2f(W, H / 2));
    flooor.setPosition(0, H / 2);
    flooor.setFillColor(Color(128, 128, 128));
    window.draw(flooor);
    flooor.setPosition(0, 0);
    flooor.setFillColor(Color(50, 50, 50));
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
            stepY = diff * wallHeight/ WallsSize[i];
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
    screenX = 0;
    Rays.clear();
    PinkyDraw.clear();
}

void drawInfo() {
    Text text(to_string(player.HP), font, 70);
    text.setFillColor(Color::Red);
    text.setScale(1, 1);
    text.setPosition(10, H - 80);
    window.draw(text);
}

void gameOver() {
    window.clear();
    Text text("GAME OVER", font, 100);
    text.setFillColor(Color::Red);
    text.setScale(1, 1);
    text.setPosition(W / 2 - 130, H / 2 - 80);
    //text.setOrigin(100, 200);
    window.draw(text);
    window.display();
    sleep(Time(microseconds(3000000)));
    exit(0);
}

void start3D() {
    drawMap();
    collision();
    Exit.draw();
    Exit.check();
    if (Exit.isDraw) drawExit();
    if (Exit.isGet) gameOver();
    for (int i = 0; i < Healths.size(); i++) {
        Healths[i].draw();
        if (Healths[i].isDraw) {
            drawHealth(Healths[i]);
        }
        Healths[i].check();
        if (Healths[i].isGet) {
            Healths.erase(Healths.begin() + i);
            player.HP += 10;
        }
    }
    for (int i = 0; i < Pinkies.size(); i++) {
        Pinkies[i].movement();
        if (Pinkies[i].isDraw) {
            drawPinky3D(Pinkies[i]);
        }
    }
    shotgun.drawWeapon();
    drawFire();
    drawShoot();
    drawInfo();
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
