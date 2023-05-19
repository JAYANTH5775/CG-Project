#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.14159265358979323846

// Planet properties
float planetRadius = 0.5f;
float planetPosX = 0.0f;
float planetPosY = 0.0f;

// Satellite properties
float satelliteRadius = 0.03f;
float satelliteDistance = 0.6f;
float satelliteAngle = 0.0f;

// Star positions
float starPosX[100];
float starPosY[100];

// Initialize stars' positions
void initializeStars() {
    for (int i = 0; i < 100; i++) {
        starPosX[i] = (rand() % 2000) / 1000.0f - 1.0f;
        starPosY[i] = (rand() % 2000) / 1000.0f - 1.0f;
    }
}

// Draw planet
void drawPlanet() {
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(planetPosX, planetPosY);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * PI * i / numSegments;
        float x = planetPosX + planetRadius * cos(theta);
        float y = planetPosY + planetRadius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

// Draw satellite
void drawSatellite() {
    float satellitePosX = planetPosX + satelliteDistance * cos(satelliteAngle);
    float satellitePosY = planetPosY + satelliteDistance * sin(satelliteAngle);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(satellitePosX, satellitePosY + satelliteRadius);
    glVertex2f(satellitePosX - satelliteRadius, satellitePosY - satelliteRadius);
    glVertex2f(satellitePosX + satelliteRadius, satellitePosY - satelliteRadius);
    glEnd();
}

// Draw stars
void drawStars() {
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 100; i++) {
        glVertex2f(starPosX[i], starPosY[i]);
    }
    glEnd();
}

// Update satellite position
void update(int value) {
    satelliteAngle += 0.02f;
    if (satelliteAngle > 2.0f * PI)
        satelliteAngle -= 2.0f * PI;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

// Display callback
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw planet, satellite, and stars
    drawPlanet();
    drawSatellite();
    drawStars();

    glutSwapBuffers();
}

// Reshape callback
void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho
