#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Scene IDs
#define SCENE_PLANE 1
#define SCENE_ROCKET 2
#define SCENE_SATELLITE 3
#define SCENE_SOLAR_SYSTEM 4

// Current scene
int currentScene = SCENE_PLANE;

// Function prototypes
void initializeStars();
void drawPlaneScene();
void drawRocketScene();
void drawSatelliteScene();
void drawSolarSystemScene();
void display();
void menu(int value);


void menu(int value) {
    switch (value) {
        case SCENE_PLANE:
            currentScene = SCENE_PLANE;
            break;
        case SCENE_ROCKET:
            currentScene = SCENE_ROCKET;
            break;
        case SCENE_SATELLITE:
            currentScene = SCENE_SATELLITE;
            break;
        case SCENE_SOLAR_SYSTEM:
            currentScene = SCENE_SOLAR_SYSTEM;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    // Initialize OpenGL and GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Menu Example");

    // Create menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Plane", SCENE_PLANE);
    glutAddMenuEntry("Rocket", SCENE_ROCKET);
    glutAddMenuEntry("Satellite", SCENE_SATELLITE);
    glutAddMenuEntry("Solar System", SCENE_SOLAR_SYSTEM);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Register callback functions
    glutDisplayFunc(display);

    // Initialize stars' positions
    initializeStars();

    // Enter the main loop
    glutMainLoop();

    return 0;
}

