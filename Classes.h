#pragma once
#include "Head.h"

double times;

struct Vec {
    double x, y;
    Vec() {
        x = 0;
        y = 0;
    }
    Vec(double x_r, double y_r) {
        x = x_r;
        y = y_r;
    }

    Vec operator + (Vec B) {
        Vec res;
        res.x = x + B.x;
        res.y = y + B.y;
        return res;
    }

    Vec operator - (Vec B) {
        Vec res;
        res.x = x - B.x;
        res.y = y - B.y;
        return res;
    }

    Vec operator * (double k) {
        Vec res;
        res.x = x * k;
        res.y = y * k;
        return res;
    }
};

double cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}

double distance_point(Vec A, Vec B) {
    return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}

bool are_crossing(Vec v11, Vec v12, Vec v21, Vec v22, Vec &vCross) {
    Vec cut1(v12 - v11), cut2(v22 - v21);
    double prod1, prod2;
    prod1 = cross(cut1, (v21 - v11));
    prod2 = cross(cut1, (v22 - v11));
    if (prod1 * prod2 >= 0) 
        return false;
    prod1 = cross(cut2, (v11 - v21));
    prod2 = cross(cut2, (v12 - v21));
    if (prod1 * prod2 >= 0) 
        return false;
    vCross.x = v11.x + cut1.x * fabs(prod1) / fabs(prod2 - prod1);
    vCross.y = v11.y + cut1.y * fabs(prod1) / fabs(prod2 - prod1);
    return true;
}

class Player {
public:
    double x = 20, y = 20;
    int HP = 100;
    double angle =1080.0;
    Texture Hero_text;
    RectangleShape Player_model;
    void draw_player() {
        //Player_model.setTexture(Hero_text);
        Player_model.setFillColor(Color::Red);
        Player_model.setOrigin(Vector2f(5, 5));
        Player_model.setPosition(x, y);
        Player_model.setSize(Vector2f(10, 10));
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
Player player;

class Wall {
private:
    int x, y, w, h;
public:
    Color s = Color(128, 255, 255);
    Wall() : x(0), y(0), w(0), h(0) { init(); };
    Wall(double x0, double y0, double w0, double h0) : x(x0), y(y0), w(w0), h(h0) { init(); };
    ~Wall() {};
    RectangleShape wall;
    vector<VertexArray> segments;
    void init() {
        wall.setPosition(Vector2f(x, y));
        wall.setSize(Vector2f(w, h));
        wall.setFillColor(s);
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(x, y);
        line[1].position = Vector2f(x + w, y);
        segments.push_back(line);
        line[0].position = Vector2f(x + w, y);
        line[1].position = Vector2f(x + w, y + h);
        segments.push_back(line);
        line[0].position = Vector2f(x, y);
        line[1].position = Vector2f(x, y + h);
        segments.push_back(line);
        line[0].position = Vector2f(x, y + h);
        line[1].position = Vector2f(x+w, y+h);
        segments.push_back(line);
    }
    void draw() {
        window.draw(wall);
    }
    bool is_colis(VertexArray& line) {
        for (int i = 0; i < segments.size(); i++) {
            Vec v11 = { segments[i][0].position.x, segments[i][0].position.y };
            Vec v12 = { segments[i][1].position.x, segments[i][1].position.y };
            Vec v21 = { line[0].position.x, line[0].position.y };
            Vec v22 = { line[1].position.x, line[1].position.y };
            Vec vCross;
            if (are_crossing(v11, v12, v21, v22, vCross)) {
                return true;
                break;
            }
        }
        return false;
    }
    Vec newCoords(VertexArray& line, Vec& newLine) {
        double minim = 1e9;
        for (int i = 0; i < segments.size(); i++) {
            Vec v11 = { segments[i][0].position.x, segments[i][0].position.y };
            Vec v12 = { segments[i][1].position.x, segments[i][1].position.y };
            Vec v21 = { line[0].position.x, line[0].position.y };
            Vec v22 = { line[1].position.x, line[1].position.y };
            Vec vCross;
            if (are_crossing(v11, v12, v21, v22, vCross)) {
                if (distance_point(v21, vCross) < minim) {
                    newLine.x = vCross.x;
                    newLine.y = vCross.y;
                    minim = distance_point(v21, vCross);
                }
            }
        }
        return newLine;
    }
};
vector<pair<Vec, Vec>> Walls;

struct Pinky {
    double w, h, x, y, eRange = 15, eAngle = 0, HP = 100;
    bool isSee = true;
    Pinky(double x1, double y1, double w1, double h1) : x(x1), y(y1), w(w1), h(h1) {};
    void engineDraw() {
        RectangleShape enemy;
        enemy.setPosition(Vector2f(x, y));
        enemy.setSize(Vector2f(w, h));
        enemy.setFillColor(Color::Yellow);
        window.draw(enemy);
    }
    void movement() {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(x+w/2,y+h/2);
        line[1].position = Vector2f(player.x, player.y);
        line[1].color = Color::Red;
        line[0].color = Color::Red;
        //window.draw(line);

        isSee = true;
        for (int i = 0; i < Walls.size(); i++) {
            Wall a(Walls[i].first.x, Walls[i].first.y, Walls[i].second.x, Walls[i].second.y);
            if (a.is_colis(line)) {
                isSee = false;
                break;
            }
        }
        if (isSee) {
            double dY = player.y - y;
            double dX = player.x - x;
            eAngle = atan2(dY, dX);
            if (distance_point(Vec(x+w/2, y+h/2), Vec(player.x, player.y)) > 20) {
                x += (move_speed - 0.01) * times * cos(eAngle);
                y += (move_speed - 0.01) * times * sin(eAngle);
            }
            else {
                double currTimeP = PinkyBeatDelay.getElapsedTime().asMilliseconds();
                if (currTimeP - prevTimeP > 1000) {
                    player.HP -= 10;
                    prevTimeP = currTimeP;
                }
            }
        }
    }
};

vector<int> PinkyDraw;
vector<Pinky> Pinkies;

struct Shotgun {
    Sprite shotgunSpr;
    void shoot(double angle) {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(player.x, player.y);
        line[1].position = Vector2f(player.x + depth * cos(angle * PI / 180.0), player.y + depth * sin(angle * PI / 180.0));
        line[1].color = Color::Red;
        line[0].color = Color::Red;
        for (int i = 0; i < Pinkies.size(); i++) {
            Wall a(Pinkies[i].x, Pinkies[i].y, Pinkies[i].w, Pinkies[i].h);
            if (a.is_colis(line) && Pinkies[i].isSee) {
                Pinkies[i].HP -= 50;
                if (Pinkies[i].HP <= 0) {
                    Pinkies.erase(Pinkies.begin() + i);
                }
                break;
            }
        }
    }
    void drawWeapon() {
        shotgunSpr.setScale(0.7, 0.7);
        shotgunSpr.setOrigin(W / 3.7, 0);
        shotgunSpr.setTexture(shotgunText);
        shotgunSpr.setPosition(W / 2, H / 2 + H / 8);
        window.draw(shotgunSpr);
    }
};

Shotgun shotgun;