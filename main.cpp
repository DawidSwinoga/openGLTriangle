//#include “stdafx.h”
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <cstdio>
#include <iostream>

//zrobić z trójkątów tak jakby 3 pierścienie i obroty były konfigurowalne względem środka ciężkości trójkąta
// obrót względem środka wszystkich trójkątow też konfigurowalny, wszystkie trójkąty mają się przybliżać i oddalać wszystkie
// obrót zrobić poprzez zmienną globalną kąt, użyć glutTimerFunction(czas w milisekundach, wskaźnik do funkcji, jezeli chcemy przesłać argument do funkcji w timerze wywołać glutPostRedisplay)

enum DIRECTION {
    POSITIVE = 1,
    NEGATIVE = -1
};

static const double size = 100.0;
int currentDirection = POSITIVE;

double currentMoveDistance = 0;
const double maxMoveDistance = (3 * sqrt(pow(size, 2) + pow(size, 2)));

int move = 0;
static const int moveSpeed = 1;

int triangleAngle0 = 0;
int triangleRotateSpeed0 = 0;

int triangleAngle1 = 0;
int triangleRotateSpeed1 = 0;

int triangleAngle2 = 0;
int triangleRotateSpeed2 = 0;

int firstRingAngle = 0;
int firstRingRotateSpeed = 0;

int secondRingAngle = 0;
int secondRingRotateSpeed = 0;

int thirdRingAngle = 0;
int thirdRingRotateSpeed = 0;

void blueColor();

void orangeColor();

void cyanColor();

void greenColor();

void redColor();

void yellowColor();

void drawQuarter(int i);

void drawTriangle(int angle, double translateX, double translateY, double moveDistance);

void moveTriangle(double x, double y, double distance);

void firstRing();

void secondRing();

void thirdRing();

void triangle() {
    glBegin(GL_POLYGON);
    glVertex2d(0.0, size);
    glVertex2d(size, 0.0);
    glVertex2d(0.0, 0.0);
    glEnd();
}

void timer(int test) {
    firstRingAngle += firstRingRotateSpeed;
    secondRingAngle += secondRingRotateSpeed;
    thirdRingAngle += thirdRingRotateSpeed;

    move += moveSpeed;

    triangleAngle0 += (triangleRotateSpeed0 * thirdRingRotateSpeed);
    triangleAngle1 += (triangleRotateSpeed1 * thirdRingRotateSpeed);
    triangleAngle2 += (triangleRotateSpeed2 * thirdRingRotateSpeed);

    if (move % 360 == 0 && move != 0) {
        currentDirection = -currentDirection;
    }

//    currentMoveDistance += ((currentDirection * maxMoveDistance)/3600);
    currentMoveDistance += (currentDirection * maxMoveDistance)/360;
    glutPostRedisplay();
}

void MyDisplay() {
    // Wyswietlana scena - poczatek
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 4; i++) {
        drawQuarter(i);
    }


    glFlush();
    glutTimerFunc(10, timer, 0);
}

void rotateTriangle(int angle, double x, double y) {
    double sX = (2 * x + x + size) / 3;
    double sY = (2 * y + y + size) / 3;
    glTranslated(sX, sY, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-sX, -sY, 0);
}

void drawQuarter(int i) {

    glPushMatrix();
    glRotated(i * 90, 0, 0, 1);

    firstRing();
    secondRing();
    thirdRing();

    glPopMatrix();
}

void thirdRing() {
    glPushMatrix();
    glRotated(thirdRingAngle, 0, 0, 1);

    cyanColor();
    drawTriangle(triangleAngle2, 2 * size, 0, currentMoveDistance);

    redColor();
    drawTriangle(triangleAngle2, 0, 2 * size, currentMoveDistance);

    yellowColor();
    drawTriangle(triangleAngle2, size, size, currentMoveDistance);

    glPopMatrix();
}

void secondRing() {
    glPushMatrix();
    glRotated(secondRingAngle, 0, 0, 1);

    orangeColor();
    drawTriangle(triangleAngle1, size, 0, currentMoveDistance);

    greenColor();
    drawTriangle(triangleAngle1, 0, size, currentMoveDistance);

    glPopMatrix();
}

void firstRing() {
    glPushMatrix();
    glRotated(firstRingAngle, 0, 0, 1);
    blueColor();
    drawTriangle(triangleAngle0, 0, 0, currentMoveDistance);
    glPopMatrix();
}

void drawTriangle(int angle, double translateX, double translateY, double moveDistance) {
    glPushMatrix();
    moveTriangle(translateX, translateY, moveDistance);
    rotateTriangle(angle, translateX, translateY);
    glTranslated(translateX, translateY, 0);
    triangle();
    glPopMatrix();
}

void moveTriangle(double x, double y, double distance) {
    double sX = (2 * x + x + size) / 3;
    double sY = (2 * y + y + size) / 3;

    double angle = atan(sY/sX);
    double dx = cos(angle) * distance;
    double dy = sin(angle) * distance;

    glTranslated(dx, dy, 0);
}

void yellowColor() { glColor3f(1, 1, 0); }

void redColor() { glColor3f(1, 0, 0); }

void greenColor() { glColor3f(0, 1, 0); }

void cyanColor() { glColor3f(1, 0, 1); }

void orangeColor() { glColor3f(1, 0.5, 0); }

void blueColor() { glColor3f(0.0f, 0.0f, 1.0f); }

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //select clearing (background) color
    /* initialize viewing values */
    glViewport(0, 0, 800, 800);
    //pocz•tek u.ws. lewy górny róg
    glMatrixMode(GL_PROJECTION);//Nast•pne 2 wiersze b•d• modyfikowały m. PROJECTION
    glLoadIdentity();
    //inicjalizacja
    gluOrtho2D(-800.0, 800, -800, 800.0);
    glMatrixMode(GL_MODELVIEW);
    //Nast•pny wiersz b•dzie modyfikował m. MODELVIEW
    glLoadIdentity();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //single buffer and RGBA
    glutInitWindowSize(800, 800);
    //initial window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My window");
    //create widnow, hello title bar
    myInit();
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    //enter main loop and process events
    return 0;
}