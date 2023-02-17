#include"setup.h"
#include"display.h"
#include<vector>
using namespace std;

const double pi = 3.1415926535;

class rectangle {

public:
    void build(float x, float y, float width, float height, u32 color) {

        for (int i = 0; i <= width; i++) {
            for (int j = 0; j <= height; j++) {
                pixel(x + i, y + j, color);
            }
        }
    }
};
rectangle rect;

class Circle {
private:
    rectangle square;

    float xp; float yp; float rad; u32 c;

public:
    void build(float x, float y, float radius, float thickness, u32 color) {
        xp = x; yp = y; rad = radius; c = color;

        for (int i = 0; i <= 360; i++) {
            square.build(x + cos(i * pi / 180) * radius, y + sin(i * pi / 180) * radius, thickness, thickness, color);

        }

    }
    void fill() {
        for (int r = 0; r <= rad; r++) {
            for (int i = 0; i <= 360; i++) {
                square.build(xp + cos(i * pi / 180) * r, yp + sin(i * pi / 180) * r, 1, 1, c);

            }
        }
    }
};
Circle circle;

class Line {
private:
    double radient;
    float quality = 0.01;

    rectangle rect;

public:
    void build(float x1, float y1, float x2, float y2, float thickness, u32 color) {

        radient = (y2 - y1) / (x2 - x1);

        if (x2 > x1) {

            for (float j = 0; j <= x2 - x1; j+=quality) {
                rect.build(x1 + j, y1 + j * radient, thickness, thickness, color);
            }
        }
        else if(x1>x2){
            for (float j = 0; j <= x1 - x2; j+=quality) {
                rect.build(x1 - j, y1 + j * -radient, thickness, thickness, color);
            }
        }
        else if (x2 == x1) {
            if (y2 > y1) {
                for (float k = 0; k <= y2 - y1; k++) {
                    rect.build(x1, y1 + k, thickness, thickness, color);
                }
            }
            else {
                for (float k = 0; k <= y1 - y2; k++) {
                    rect.build(x1, y1 - k, thickness, thickness, color);
                }
            }
        }
        
    }
};
