#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
// pivot point
int cx;
int cy;

int length = 200;//rod length
float angle = 0;//current angle
int dir = 1;//1->right, -1->left

int r = 20;//radius ball

// pixel draw
void draw_pixel(int x,int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

// Bresenham Line Algorithm
void draw_line(int x1,int x2,int y1,int y2)
{
    int dx,dy,i,e;
    int incx,incy,inc1,inc2;
    int x,y;

    dx = x2-x1;
    dy = y2-y1;

    if(dx<0) dx = -dx;
    if(dy<0) dy = -dy;

    incx = 1;
    if(x2<x1) incx = -1;//+1 right dike jabe, -1 left er dike jabe

    incy = 1;
    if(y2<y1) incy = -1;// +1 up a jabe , -1 down er dike jabe

    x = x1;
    y = y1;

    if(dx>dy)// slope +1 or 1 hole vertical
    {
        draw_pixel(x,y);

        e = 2*dy - dx;// Decision parameter
        inc1 = 2*(dy-dx);//
        inc2 = 2*dy;//

        for(i=0;i<dx;i++)
        {
            if(e>=0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;

            x += incx;
            draw_pixel(x,y);
        }
    }
    else // slope -1 hole horizontal hobe
    {
        draw_pixel(x,y);

        e = 2*dx - dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;

        for(i=0;i<dy;i++)
        {
            if(e>=0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;

            y += incy;
            draw_pixel(x,y);
        }
    }
}

// circle pixel plot
void plot(int x,int y,int cx,int cy)//x, y → circle-এর relative point, cx, cy → circle-এর center point
{
    glBegin(GL_POINTS);//drawing mode start
    glVertex2i(x+cx,y+cy);// actual pixel position calculate করা হচ্ছে
    glEnd();//drawing শেষ
}

// Midpoint Circle Algorithm
void midPointCircleAlgo(int cx,int cy,int r)
{
    int x=0;
    int y=r;

    int decision = 1-r;

    while(x<=y)
    {
        plot(x,y,cx,cy);
        plot(x,-y,cx,cy);
        plot(-x,y,cx,cy);
        plot(-x,-y,cx,cy);

        plot(y,x,cx,cy);
        plot(-y,x,cx,cy);
        plot(y,-x,cx,cy);
        plot(-y,-x,cx,cy);

        x++;

        if(decision<0)
            decision += 2*x+1;
        else
        {
            y--;
            decision += 2*(x-y)+1;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);//screen clear করে

    // support line
    draw_line(200,440,420,420);//horizontal line আঁকা হচ্ছে, start: (200, 420), end: (440, 420)

    // pendulum position
    int x = cx + length*sin(angle*3.1416/180);
    int y = cy - length*cos(angle*3.1416/180);

    // pendulum rod
    draw_line(cx,x,cy,y);

    // pendulum ball
    midPointCircleAlgo(x,y,r);

    glFlush();
}

// animation
void update(int value)
{
    if(angle>40)
        dir = -1;

    if(angle<-40)
        dir = 1;

    angle += dir*1.5;

    glutPostRedisplay();//display() function আবার call করো

    glutTimerFunc(30,update,0);//30 milliseconds পরে update() function আবার call হবে
}

void init()
{
    glClearColor(1,1,1,1);//মানে white color
    glColor3f(0,0,0);//মানে তুমি যাই draw করো → সব কালো হবে
    glPointSize(2);//এখানে pixel er size bole disse

    glMatrixMode(GL_PROJECTION);//এখানে আমরা screen coordinate system set করবো
    gluOrtho2D(0,640,0,480);//screen কে একটা grid বানানো হলো
}

int main(int argc,char** argv)
{
    cout<<"Enter pivot point (cx cy): ";
    cin>>cx>>cy;

    glutInit(&argc,argv);//program start করার জন্য basic setup

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//screen কিভাবে render হবে সেটা define করছে

    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Pendulum Animation");

    init(); //background color set, drawing color set, coordinate system set

    glutDisplayFunc(display); // callback func call hobe

    glutTimerFunc(30,update,0);// 30ms por por update hobe

    glutMainLoop();//infinite loop চালায়
}
