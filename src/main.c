#include <GL/gl.h>
#include "GL/freeglut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stb_image.cpp"
#include "import.c"


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // View matrix
    Vec3 fwd = forward(&CAM);
    Vec3 u = up(&CAM);
    Vec3 eye = CAM.position;
    Vec3 center = {eye.x + fwd.x, eye.y + fwd.y, eye.z + fwd.z};

    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, u.x, u.y, u.z);
    setup_lighting();

    draw_grid(25);

    int i;
    // Draw the air conditioner
    glBindTexture(GL_TEXTURE_2D, air_conditioner_tex_id);
    glBegin(GL_TRIANGLES);
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

void init_gl();
void setup_lighting();
int load_obj(const char* path, int object);
int load_all_objects();
unsigned int load_texture(const char* path);
void load_all_textures();

void display();
void idle();
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void reshape(int width, int height);

void draw_grid(int n);
void main_door();
void side_door();
void windows();
void move_fan();

Vec3 forward(Transform* t);
Vec3 right(Transform* t);
Vec3 up(Transform* t);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // Setting the window size, display mode, window name and placing the mouse pointer to the center of the screen
    glutInitWindowSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Room");
    glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);

    // Setting the callback functions
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutReshapeFunc(reshape);

    // Initializing some options of OpenGL and lighting
    init_gl();

    // Setting initial camera position outside the room and facing the main door
    CAM.position = (Vec3) {2.0f, 4.0f, -15.0f};
    CAM.rotation = (Vec3) {0.0f, 90.0f, 0.0f};

    // Loading the object files
    load_all_objects();

	load_all_textures();

    // Initializing main loop
    glutMainLoop();

    return 0;
}