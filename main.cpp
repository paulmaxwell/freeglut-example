#include <iostream>
#include <GL/freeglut.h>

#define X1   -200
#define X2   200
#define Y1   -200
#define Y2   200

#define ZOOM_STEP  3

#define SET_GLOBAL_STATE_SIZE(__w, __h) \
    gState.iWidth = __w; \
    gState.iHeight = __h;

using namespace std;

typedef struct {
    int iZoom = 0;
    int iWidth;
    int iHeight;
} globalState;

globalState gState;

GLvoid hSetupOrtho2D()
{
    glLoadIdentity();

    int iXCorrection = 0;
    int iYCorrection = 0;

    double dblDeltaAspectRatio;

    if (gState.iWidth > gState.iHeight) {
        dblDeltaAspectRatio = (double)gState.iWidth / (double)gState.iHeight;
        iXCorrection = ((double)(Y2 - Y1) * dblDeltaAspectRatio - (Y2 - Y1)) / 2;
    } else if (gState.iWidth < gState.iHeight) {
        dblDeltaAspectRatio = (double)gState.iHeight / (double)gState.iWidth;
        iYCorrection = ((double)(X2 - X1) * dblDeltaAspectRatio - (X2 - X1)) / 2;
    }

    gluOrtho2D(
                X1 - gState.iZoom - iXCorrection,
                X2 + gState.iZoom + iXCorrection,
                Y1 - gState.iZoom - iYCorrection,
                Y2 + gState.iZoom + iYCorrection
    );
}

GLvoid handleReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    SET_GLOBAL_STATE_SIZE(width, height);
    hSetupOrtho2D();
}

GLvoid handleDraw(GLvoid)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.5f, 0.0f);

    glLineWidth(1);

    glBegin(GL_LINES);
        glVertex2f(X1, 0);
        glVertex2f(X2, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0, Y1);
        glVertex2f(0, Y2);
    glEnd();

    glLineWidth(5);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, -100);
        glVertex2f(100, -100);
        glVertex2f(100, 100);
        glVertex2f(-100, 100);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

GLvoid handleMouse(int button, int state, int x, int y)
{
    if (state == 0) {
        switch (button) {
        case 3:
            gState.iZoom -= ZOOM_STEP;
            break;

        case 4:
            gState.iZoom += ZOOM_STEP;
            break;
        }
    }

    hSetupOrtho2D();
}

GLvoid handleIdle(GLvoid) {
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(300, 300);
    SET_GLOBAL_STATE_SIZE(300, 300);
    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("FreeGLUT example");

    glutReshapeFunc(handleReshape);
    glutDisplayFunc(handleDraw);
    glutMouseFunc(handleMouse);
    glutIdleFunc(handleIdle);

    glClearColor(1, 1, 1, 1);

    glutMainLoop();

    return 0;
}
