#include <GL/glut.h>

int ww = 600;// window width 
int wh = 500;// window height

float intCol1[3] = {1.0, 0.0, 0.0};// interior color (red)
float intCol2[3] = {0.0, 0.0, 1.0};// interior color (blue)
float fillCol[3] = {0.4, 0.5, 0.0};// fill color (greenish)

void setPixel(int x, int y, float f[3])
{
    glBegin(GL_POINTS);// pixel draw করার জন্য GL_POINTS mode এ glBegin() call করা হচ্ছে
    glColor3fv(f);// pixel color set করা হচ্ছে, এখানে f array থেকে color value নেওয়া হচ্ছে
    glVertex2i(x, y);// pixel position set করা হচ্ছে, এখানে x এবং y coordinate নেওয়া হচ্ছে
    glEnd();// pixel draw করার জন্য glEnd() call করা হচ্ছে
    glFlush();// pixel draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ pixel draw করে
}

void getPixel(int x, int y, float pixels[3])
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels);// x এবং y coordinate থেকে pixel color read করা হচ্ছে, এখানে 1x1 area থেকে color read করা হচ্ছে, color format RGB এবং data type float
}

void drawSquare(int x1, int y1, int x2, int y2, float col[3])
{
    glColor3fv(col);// square color set করা হচ্ছে, এখানে col array থেকে color value নেওয়া হচ্ছে
    glBegin(GL_POLYGON);// square draw করার জন্য GL_POLYGON mode এ glBegin() call করা হচ্ছে
    glVertex2i(x1, y1);// square vertex set করা হচ্ছে, এখানে x1 এবং y1 coordinate নেওয়া হচ্ছে
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();// square draw করার জন্য glEnd() call করা হচ্ছে
    glFlush();// square draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ square draw করে
}

void display()
{
    glClearColor(0.2, 0.4, 0.0, 1.0);// background color set করা হচ্ছে, এখানে dark green color set করা হচ্ছে
    glClear(GL_COLOR_BUFFER_BIT);// screen clear করা হচ্ছে, এখানে color buffer clear করা হচ্ছে

    drawSquare(100, 200, 150, 250, intCol1);// first square draw করা হচ্ছে, এখানে start point (100, 200) এবং end point (150, 250) দেওয়া হচ্ছে, এবং interior color intCol1 set করা হচ্ছে
    drawSquare(200, 200, 250, 250, intCol2);

    glFlush();// square draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ square draw করে
}

void floodfill4(int x, int y, float oldcolor[3], float newcolor[3])
{
    float color[3];// pixel color read করার জন্য array declare করা হচ্ছে
    getPixel(x, y, color);// x এবং y coordinate থেকে pixel color read করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে

    if (color[0] == oldcolor[0] && color[1] == oldcolor[1] && color[2] == oldcolor[2])// x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
    {
        setPixel(x, y, newcolor);// x এবং y coordinate এ newcolor set করা হচ্ছে

        floodfill4(x + 1, y, oldcolor, newcolor);// x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
        floodfill4(x - 1, y, oldcolor, newcolor);
        floodfill4(x, y + 1, oldcolor, newcolor);
        floodfill4(x, y - 1, oldcolor, newcolor);
    }
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// mouse left button click করা হয়েছে কিনা check করা হচ্ছে, এবং mouse button down state এ আছে কিনা check করা হচ্ছে
    {
        int xi = x;// mouse click করা হয়েছে এমন x coordinate set করা হচ্ছে
        int yi = wh - y;// mouse click করা হয়েছে এমন y coordinate set করা হচ্ছে, এখানে window height থেকে y coordinate subtract করা হচ্ছে কারণ OpenGL এ y coordinate এর direction opposite হয়

        float color[3];// mouse click করা হয়েছে এমন coordinate এর pixel color read করার জন্য array declare করা হচ্ছে
        getPixel(xi, yi, color);// mouse click করা হয়েছে এমন coordinate থেকে pixel color read করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে

        if (color[0] == intCol1[0] && color[1] == intCol1[1] && color[2] == intCol1[2])// mouse click করা হয়েছে এমন coordinate এর pixel color intCol1 এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
            floodfill4(xi, yi, intCol1, fillCol);// mouse click করা হয়েছে এমন coordinate এবং interior color intCol1 এবং fill color fillCol দেওয়া হচ্ছে

        else if (color[0] == intCol2[0] && color[1] == intCol2[1] && color[2] == intCol2[2])//mouse click করা হয়েছে এমন coordinate এর pixel color intCol2 এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
            floodfill4(xi, yi, intCol2, fillCol);// mouse click করা হয়েছে এমন coordinate এবং interior color intCol2 এবং fill color fillCol দেওয়া হচ্ছে
    }
}

void myinit()
{
    glViewport(0, 0, ww, wh);// viewport set করা হচ্ছে, এখানে x=0, y=0 থেকে শুরু করে width=ww এবং height=wh পর্যন্ত
    glMatrixMode(GL_PROJECTION);// projection matrix mode set করা হচ্ছে, এটি coordinate system define করে
    glLoadIdentity();// projection matrix reset করা হচ্ছে, এটি previous projection matrix কে identity matrix এ set করে
    gluOrtho2D(0.0, ww, 0.0, wh);// orthographic projection set করা হচ্ছে, এখানে left=0, right=ww, bottom=0, top=wh, এটি 2D coordinate system define করে
    glMatrixMode(GL_MODELVIEW);// modelview matrix mode set করা হচ্ছে, এটি object transformation এবং viewing transformation define করে
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);// program start করার জন্য basic setup
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// screen কিভাবে render হবে সেটা define করছে, এখানে RGB color mode এবং single buffering set করা হচ্ছে
    glutInitWindowSize(ww, wh);// window size set করা হচ্ছে, এখানে width=ww এবং height=wh pixel set করা হচ্ছে
    glutCreateWindow("Flood Fill Multiple");// window create করা হচ্ছে, এখানে window title "Flood Fill Multiple" set করা হচ্ছে

    glutDisplayFunc(display);// callback function set করা হচ্ছে, যখন window refresh হবে তখন display() function call হবে
    myinit();// background color set, coordinate system set করা হচ্ছে
    glutMouseFunc(mouse);// mouse event handle করার জন্য callback function set করা হচ্ছে, যখন mouse click হবে তখন mouse() function call হবে

    glutMainLoop();
    return 0;
}