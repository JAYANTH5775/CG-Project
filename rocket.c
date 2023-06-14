#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Rocket position
float rocketPosX = 0.0f;
float rocketPosY = 0.0f;

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

// Draw rocket
void drawRocket() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(rocketPosX, rocketPosY + 0.05f);
    glVertex2f(rocketPosX - 0.02f, rocketPosY - 0.05f);
    glVertex2f(rocketPosX + 0.02f, rocketPosY - 0.05f);
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
    rocketPosY += 0.01f;

    // Wrap the rocket position around the screen
    if (rocketPosY > 1.1f)
        rocketPosY = -1.1f;

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

// Display callback
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw rocket and stars
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

    glutMainLoop();
    return 0;
}
