#include "TXLib.h"
#include <iostream>
#include <sstream>
using namespace std;

struct Bita {
    double x, y;
    double w, h;

    void draw();
};

struct Ball {
    int x = 400, y = 300;
    int dx = 5;
    int dy = rand() % 4 + 2;
    int r = 10;
    COLORREF color = RGB(0, 0, 180);

    void draw ();
    void move (Bita, Bita);
};

int main () {
    int left_player = 0;
    int right_player = 0;
    txCreateWindow(800, 600);
    txBegin();
    int start = 0;
    int n = 1;

    while (left_player < 3 and right_player < 3) {
        Bita bitaL = {50, 150, 50, 300};
        Bita bitaR = {700, 150, 50, 300};
        Ball ball;
        if (start == 1) {
            while (ball.x >= 0 and ball.x <= 800) {
                txSetFillColor(TX_WHITE);
                txClear();

                txSelectFont("System", 40);
                char out [2];
                sprintf(out, "%d", left_player);
                txTextOut(350, 50, out);
                sprintf(out, "%d", right_player);
                txTextOut(450, 50, out);


                bitaL.draw();
                bitaR.draw();
                ball.draw();

                if (txGetAsyncKeyState('W')) bitaL.y -= 5.5;
                if (txGetAsyncKeyState('S')) bitaL.y += 5.5;
                if (txGetAsyncKeyState(VK_UP)) bitaR.y -= 5.5;
                if (txGetAsyncKeyState(VK_DOWN)) bitaR.y += 5.5;

                txSleep(10);

                ball.move(bitaL, bitaR);

                if (ball.x > 800) left_player += 1;
                if (ball.x < 0) right_player += 1;
            }
        }
        if (txGetAsyncKeyState(VK_SPACE)) {
            start = 1;
        }


    }
    while (start == 1) {
        txSetFillColor(TX_WHITE);
        txClear();
        txSelectFont("System", 40);
        char out [2];
        sprintf(out, "%d", left_player);
        txTextOut(350, 50, out);
        sprintf(out, "%d", right_player);
        txTextOut(450, 50, out);
        txTextOut(200, 350, "PRESS SPACE TO END");
        if (txGetAsyncKeyState(VK_SPACE)) {
            start = 0;
        }
        txSelectFont("System", 100);
        txTextOut(200, 200, "GAME OVER");
        if (txGetAsyncKeyState(VK_SPACE)) {
            start = 0;
        }
        txSleep(10);
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
    //if (x+r > 800 || x-r < 0) dx *= -1;
    if (y+r > 600 || y-r < 0) dy *= -1;


    if (x-r == bitaL.x + bitaL.w) {
        if (bitaL.y <= y && y <= bitaL.y + bitaL.h) dx *= -1;
    }
    if (x+r == bitaR.x) {
        if (bitaR.y <= y && y <= bitaR.y + bitaR.h) dx *= -1;
    }
    //if (x-r == bitaR.x + bitaR.w) {
    //    if (bitaR.y <= y && y <= bitaR.y + bitaR.h) dx *= -1;
    //}
    //if (x+r == bitaL.x) {
    //    if (bitaL.y <= y && y <= bitaL.y + bitaL.h) dx *= -1;
    //}


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

