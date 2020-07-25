#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

/* Global Variables */
float angle = 0.0f;
float legAngle[2] = {0.0f, 0.0f};
float armAngle[2] = {0.0f, 0.0f};

void resizeViewPort(int width, int height)
{
    /* Reset the viewport to the new dimensions */
    glViewport(0, 0, width, height);

    /* Set current Matrix to projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset projection matrix

    /* Calculate aspect ratio of our view port */
    gluPerspective(54.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW); // set modelview matrix
    glLoadIdentity();           // reset modelview matrix
}