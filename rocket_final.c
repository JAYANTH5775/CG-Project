#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


float rocketPosX = 0.0f;
float rocketPosY = 0.0f;
float rocketSpeed = 0.01f;

// Star positions
float starPosX[100];
float starPosY[100];

void initializeStars() {
    for (int i = 0; i < 100; i++) {
        starPosX[i] = (rand() % 2000) / 1000.0f - 1.0f;
        starPosY[i] = (rand() % 2000) / 1000.0f - 1.0f;
    }
}

// Draw rocket
void drawRocket() {
    float rocketWidth = 0.2f;  
    float rocketHeight = 0.5f;  
    // Draw rectangle body
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(rocketPosX - rocketWidth / 2.0f, rocketPosY - rocketHeight / 2.0f,
            rocketPosX + rocketWidth / 2.0f, rocketPosY + rocketHeight / 2.0f);

    // Draw cone
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(rocketPosX - rocketWidth / 2.0f, rocketPosY + rocketHeight / 2.0f);
    glVertex2f(rocketPosX + rocketWidth / 2.0f, rocketPosY + rocketHeight / 2.0f);
    glVertex2f(rocketPosX, rocketPosY + rocketHeight);
    glEnd();

    // Draw fire
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(rocketPosX - rocketWidth / 2.0f, rocketPosY - rocketHeight / 2.0f);  // Vertex 1
    glVertex2f(rocketPosX + rocketWidth / 2.0f, rocketPosY - rocketHeight / 2.0f);  // Vertex 2
    glVertex2f(rocketPosX + (rocketWidth / 2.0f) + 0.28f, rocketPosY - (rocketHeight / 2.0f) - 0.28f);  
    glVertex2f(rocketPosX - (rocketWidth / 2.0f) - 0.28f, rocketPosY - (rocketHeight / 2.0f) - 0.28f);  
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

// Update rocket and stars positions
void update(int value) {
    rocketPosY += rocketSpeed;

    // Wrap the rocket position around the screen
    if (rocketPosY > 1.1f)
        rocketPosY = -1.1f;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

// Menu callback
void menu(int value) {
    switch (value) {
        case 1:  // Fast
            rocketSpeed = 0.02f;
            break;
        case 2:  // Slow
            rocketSpeed = 0.005f;
            break;
    }
}

// Display callback
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawRocket();
    drawStars();

    glutSwapBuffers();
}

// Reshape callback
void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rocket and Stars");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);

    initializeStars();

    // Create menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Fast", 1);
    glutAddMenuEntry("Slow", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

