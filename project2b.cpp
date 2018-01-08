#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


GLdouble left = -60;
GLdouble right = 60;
GLdouble bottom = -60;
GLdouble top = 60;
float b = 70.0;
float vx = 1.0;
float vy = 2.0;
float vz = 4.0;
float scaleFactor = 1.0;/*for increasing and decreasing of size*/
bool growing = true;/*when increasing happens*/


void myinit(void)
{
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -10, 120);
    glMatrixMode(GL_MODELVIEW);

    glNewList(1, GL_COMPILE);/*create list of polygons*/
    glBegin(GL_POLYGON);
    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    glEnd();
    glEndList();

}
bool aFlag = false;

static void display(void)
{
    double a = 0.025;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (aFlag == false) {
        glTranslatef(0,0,-b);
        aFlag = true;
    }
    glTranslated(0,0,-8*b/10);/*translation of cude*/
    glRotated(a,vx,vy,vz);/* rotation of cube*/
    glTranslated(0,0,8*b/10);/*translation of cude*/
	
    glPushMatrix();/* Creating one side of the cube */
        glTranslatef(0,0,3.5*scaleFactor);/* translating*/
        glScalef(3.5*scaleFactor,3.5*scaleFactor,0);/*scaling */
        glTranslatef(0,0,-1);/* translating*/

        glColor3d(1,0,0);/*set the color*/
        glCallList(1);/*call the list */
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,3.5*scaleFactor,0);
        glRotated(90,1,0,0);
        glScalef(3.5*scaleFactor,3.5*scaleFactor,0);
        glTranslatef(0,0,-1);

        glColor3d(0,1,0);
        glCallList(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,-3.5*scaleFactor);
        glScalef(3.5*scaleFactor,3.5*scaleFactor,0);
        glTranslatef(0,0,-1);

        glColor3d(0,0,1);
        glCallList(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,-3.5*scaleFactor,0);
        glRotated(-90,1,0,0);
        glScalef(3.5*scaleFactor,3.5*scaleFactor,0);
        glTranslatef(0,0,-1);

        glColor3d(1,1,0);
        glCallList(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.5*scaleFactor,0,0);
        glRotated(90,0,1,0);
        glScalef(3.5*scaleFactor,3.5*scaleFactor,0);
        glTranslatef(0,0,-1);

        glColor3d(1,0,1);
        glCallList(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.5*scaleFactor,0,0);
        glRotated(-90,0,1,0);
        glScalef(3.5*scaleFactor,3.5*scaleFactor,0);
        glTranslatef(0,0,-1);

        glColor3d(0,1,1);
        glCallList(1);
    glPopMatrix();



    glutSwapBuffers();
}

static void idle(void)
{
    if ( growing == true) {
        scaleFactor = scaleFactor + 0.0001;/*increasing the size*/
        if (scaleFactor > 2) {
            scaleFactor = 2;
            growing = false;
        }
    } else {
        scaleFactor = scaleFactor - 0.0001;/* decreasing the size*/
        if (scaleFactor < 1) {
            scaleFactor = 1;
            growing = true;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	/* initialization */
    glutInit(&argc, argv);
    glutInitWindowSize(1024,720);/* 1024 x 720 pixel window */
    glutInitWindowPosition(10,10);/* place window top left on display */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("TheCube ");/* window title */

    glutDisplayFunc(display);/* create a cube and movements */
    glutIdleFunc(idle);/*Increase and decrease the size of cube */

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    myinit();/* set attributes */

    glutMainLoop();/* enter event loop */

    return EXIT_SUCCESS;
}
