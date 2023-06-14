#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.141

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
    float satellitePosX = planetPosX + satelliteDistance;
    float satellitePosY = planetPosY;

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


void update(int value) {
    planetPosX += 0.01f; // Move the planet along the x-axis

    if (planetPosX > 1.0f + planetRadius) // Wrap around when the planet goes off-screen
        planetPosX = -1.0f - planetRadius;

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


void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define the 2D orthographic projection
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Satellite Animation");
    
   
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, update, 0);
 
    initializeStars();
   
    glutMainLoop();
    
    return 0;
}

