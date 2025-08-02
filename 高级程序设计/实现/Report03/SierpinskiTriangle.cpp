/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the Sierpinski Triangle problem 
 * from Assignment #3.
 * [TODO: extend the documentation]
 */

/*
 * File: SierpinskiTriangle.cpp
 * Assignment #3.
 */
#include <iostream>
#include "gwindow.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */
void drawSierpinskiTriangle(GWindow & gw, double x, double y, double size, int order);

/* Constants */
const double WINDOW_WIDTH = 700;
const double WINDOW_HEIGHT = 470;
// ???
const double SIN60 = sqrt(3.0) / 2;
const double SIZE = 520;
//const int ORDER = 4;

/* Main program */
int main()
{
    while(true)
    {
        int order = getInteger("Please input the order(>0):");
        if (order <= 0)
        {
            cout<<"Program finished !";
            break;
        }
        GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
        gw.setLocation(50,50);
        gw.setColor("Black");
        double x0 = (WINDOW_WIDTH - SIZE) / 2;
        double y0 = WINDOW_HEIGHT - (WINDOW_HEIGHT - SIZE * SIN60) / 2;
        drawSierpinskiTriangle(gw, x0, y0, SIZE, order);
    }
    return 0;
}

/*
 * Function: drawSierpinskiTriangle
 * Usage: drawSierpinskiTriangle(gw, x, y, size, order);
 * -----------------------------------------------------
 * Draws a Sierpinski Triangle of the specified size and order.
 * The upper left corner of the triangle is at the point (x, y).
 */

void drawSierpinskiTriangle(GWindow & gw, double x, double y, double size, int order)
{
    if (order == 1){
        gw.drawLine(x, y, x + size, y);
        gw.drawLine(x, y, x + size / 2, y - size * SIN60);
        gw.drawLine(x + size, y, x + size / 2, y - size * SIN60);
        return;
    }
    drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
    drawSierpinskiTriangle(gw, x + size / 4, y - size * SIN60 * 0.5, size / 2, order - 1);
    drawSierpinskiTriangle(gw, x + size / 2, y, size / 2, order - 1);
}

