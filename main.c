#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

void display(){}

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