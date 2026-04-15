#include <iostream>
#include <GL/glut.h>
using namespace std;
int pntX1 = 250, pntY1 =300, r = 100;
void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + pntX1, y + pntY1);
    glEnd();
}
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void midPointCircleAlgo()
{
    int x = 0;
    int y = r;
    float decision = 5 / 4 - r;
    plot(x, y);
    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x +3;
        }
        else
        {
            y--;
            x++;
            decision += 2 * (x - y) + 5;
        }
        Sleep(200);
        glColor3f(1.0, 0.0,0.0);
        plot(x, y);
        glFlush();
        glColor3f(0.0, 1.0,0.0);
        plot(x, -y);
        glFlush();
        glColor3f(0.0, 0.0,1.0);
        plot(-x, y);
        glFlush();
        glColor3f(1.0, 1.0,0.0);
        plot(-x, -y);
        glFlush();
        glColor3f(0.0, 1.0,1.0);
        plot(y, x);
        glFlush();
        glColor3f(1.0, 0.0,0.0);
        plot(-y, x);
        glFlush();
        glColor3f(1.0, 0.0,1.0);
        plot(y, -x);
        glFlush();
        glColor3f(0.0, 0.0,0.0);
        plot(-y, -x);
        glFlush();
    }
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    midPointCircleAlgo();
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Line Drawing Alogrithms");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
