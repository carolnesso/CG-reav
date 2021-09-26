#include <GL/gl.h>
#include "GL/freeglut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init_gl()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glutSetCursor(GLUT_CURSOR_NONE);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    // setup_lighting();
}

void setup_lighting()
{
    float mat_shininess[] = {80.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    float light_diffuse[] = {1.0f, 1.0f, 1.0f};
    float light_position[] = {2.0f, 4.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    float light_specular[] = {0.0f, 1.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    float light_spot_direction[] = {1.0f, 0.0f, 0.0f};
    float light_spot_diffuse[] = {1.0f, 0.0f, 1.0f};
    float light_spot_position[] = {-1.3f, 4.342580f, -0.310794f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light_spot_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_spot_diffuse);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_direction);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(1080, 900);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cozinha reav");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}