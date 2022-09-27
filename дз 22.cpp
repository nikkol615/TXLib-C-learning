#include "TXLib.h"

struct Bita {
    double x, y;
    double w, h;

    void draw();
};

struct Ball {
    int x = 780, y = 300;
    int dx = 5, dy = 5;
    int r = 10;
    COLORREF color = RGB(0, 0, 180);

    void draw ();
    void move (Bita, Bita);
};

int main () {
    txCreateWindow(800, 600);
    txBegin();

    Bita bitaL = {50, 150, 50, 300};
    Bita bitaR = {700, 150, 50, 300};
    Ball ball;

    while (true) {
        txSetFillColor(TX_WHITE);
        txClear();

        bitaL.draw();
        bitaR.draw();
        ball.draw();

        if (txGetAsyncKeyState('W')) bitaL.y -= 4.5;
        if (txGetAsyncKeyState('S')) bitaL.y += 4.5;
        if (txGetAsyncKeyState(VK_UP)) bitaR.y -= 4.5;
        if (txGetAsyncKeyState(VK_DOWN)) bitaR.y += 4.5;

        txSleep(10);
        ball.move(bitaL, bitaR);
    }

}

void Bita::draw() {
    txSetFillColor(TX_ORANGE);
    txRectangle(x, y, x+w, y+h);
}

void Ball::draw () {
    txSetColor (color);
    txSetFillColor(color);
    txCircle (x, y, r);
}

void Ball::move (Bita bitaL, Bita bitaR) {
    x += dx;
    y += dy;
    if (x+r > 800 || x-r < 0) dx *= -1;
    if (y+r > 600 || y-r < 0) dy *= -1;


    if (x-r == bitaL.x + bitaL.w) {
        if (bitaL.y <= y && y <= bitaL.y + bitaL.h) dx *= -1;
    }
    if (x+r == bitaR.x) {
        if (bitaR.y <= y && y <= bitaR.y + bitaR.h) dx *= -1;
    }
    if (x-r == bitaR.x + bitaR.w) {
        if (bitaR.y <= y && y <= bitaR.y + bitaR.h) dx *= -1;
    }
    if (x+r == bitaL.x) {
        if (bitaL.y <= y && y <= bitaL.y + bitaL.h) dx *= -1;
    }


    if (y+r == bitaL.y) {
        if (bitaL.x <= x && x <= bitaL.x + bitaL.w) dy *= -1;
    }
    if (y-r == bitaL.y + bitaL.h) {
        if (bitaL.x <= x && x <= bitaL.x + bitaL.w) dy *= -1;
    }
    if (y+r == bitaR.y) {
        if (bitaR.x <= x && x <= bitaR.x + bitaR.w) dy *= -1;
    }
    if (y-r == bitaR.y + bitaR.h) {
        if (bitaR.x <= x && x <= bitaR.x + bitaR.w) dy *= -1;
    }


}

