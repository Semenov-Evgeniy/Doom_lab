#pragma once
#include "Head.h"

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
    double x = W / 2, y = H / 2;
    double angle =470.0;
    Texture Hero_text;
    Sprite Player_model;
    void draw_player(RenderWindow& window) {
        //Player_model.setTexture(Hero_text);
        Player_model.setOrigin(Vector2f(25, 25));
        Player_model.setPosition(x, y);
        Player_model.setRotation(-angle / 4);
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

class Wall {
private:
    int x, y, w, h;
public:
    Color s = Color(128, 255, 255);
    Wall() : x(0), y(0), w(0), h(0) { init(); };
    Wall(double x0, double y0, double w0, double h0) : x(x0), y(y0), w(w0), h(h0) { init(); };
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
    void draw(RenderWindow& window) {
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

Player player;
