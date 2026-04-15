#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int ww = 600; //width 
int wh = 500;//height

float fillCol[3] = { 0.4, 1.0, 0.0 };   // fixed (greenish)
float borderCol[3] = { 0.0, 0.0, 0.0 }; // boundery coloer (black)

void setPixel(int, int, float[]);
void getPixel(int, int, float[]);
void resize(int, int);
void drawPolygon(int, int, int, int);
void boundaryFill4(int, int, float[], float[]);
void display();
void mouse(int, int, int, int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv); //GLUT initialize করা হচ্ছে
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //screen কিভাবে render হবে সেটা define করছে
    glutInitWindowSize(ww, wh); //window size set করা হচ্ছে
    glutInitWindowPosition(500, 50); //window position set করা হচ্ছে
    glutCreateWindow("Boundary Fill"); //window create করা হচ্ছে

    glutDisplayFunc(display); // callback function set করা হচ্ছে, যখন window refresh হবে তখন display() function call হবে
    glutMouseFunc(mouse); // mouse event handle করার জন্য callback function set করা হচ্ছে, যখন mouse click হবে তখন mouse() function call হবে
    glutReshapeFunc(resize); // window resize event handle করার জন্য callback function set করা হচ্ছে, যখন window resize হবে তখন resize() function call হবে

    glutMainLoop(); //infinite loop চালায়, এখানে program run হবে যতক্ষণ না user window close করে
    return 0; // program exit হবে
}

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
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels); //x এবং y coordinate থেকে pixel color read করা হচ্ছে, এখানে 1x1 area থেকে color read করা হচ্ছে, color format RGB এবং data type float
}

void resize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);// projection matrix mode set করা হচ্ছে, এটি coordinate system define করে
    glLoadIdentity();  // projection matrix reset করা হচ্ছে, এটি previous projection matrix কে identity matrix এ set করে
    gluOrtho2D(0.0, w, 0.0, h);// orthographic projection set করা হচ্ছে, এখানে left=0, right=w, bottom=0, top=h, এটি 2D coordinate system define করে
    glViewport(0, 0, w, h);// viewport set করা হচ্ছে, এখানে x=0, y=0 থেকে শুরু করে width=w এবং height=h পর্যন্ত
}

void drawPolygon(int x1, int y1, int x2, int y2)
{
    glColor3f(0.0, 0.0, 0.0);// polygon color set করা হচ্ছে, এখানে black color set করা হচ্ছে

    glBegin(GL_LINE_LOOP);// polygon draw করার জন্য GL_LINE_LOOP mode এ glBegin() call করা হচ্ছে, এটি closed loop তৈরি করে
    glVertex2i(x1, y1);// polygon vertex set করা হচ্ছে, এখানে x1 এবং y1 coordinate নেওয়া হচ্ছে
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();// polygon draw করার জন্য glEnd() call করা হচ্ছে

    glFlush();// polygon draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ polygon draw করে
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);// background color set করা হচ্ছে, এখানে white color set করা হচ্ছে
    glClear(GL_COLOR_BUFFER_BIT);// screen clear করা হচ্ছে, এখানে color buffer clear করা হচ্ছে

    drawPolygon(150, 250, 200, 300); // polygon draw করা হচ্ছে, এখানে start point (150, 250) এবং end point (200, 300) দেওয়া হচ্ছে

    glFlush();// polygon draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ polygon draw করে
}

void boundaryFill4(int x, int y, float fillColor[3], float borderColor[3])
{
    float interiorColor[3];// interior color read করার জন্য array declare করা হচ্ছে
    getPixel(x, y, interiorColor);// x এবং y coordinate থেকে interior color read করা হচ্ছে, এখানে interiorColor array এ color value store করা হচ্ছে

    if ((interiorColor[0] != borderColor[0] ||// interior color border color থেকে different কিনা check করা হচ্ছে
         interiorColor[1] != borderColor[1] ||
         interiorColor[2] != borderColor[2]) &&
        (interiorColor[0] != fillColor[0] ||
         interiorColor[1] != fillColor[1] ||
         interiorColor[2] != fillColor[2]))
    {
        setPixel(x, y, fillColor);// x এবং y coordinate এ fill color set করা হচ্ছে

        boundaryFill4(x + 1, y, fillColor, borderColor);// x coordinate increase করে next pixel এ boundary fill function call করা হচ্ছে
        boundaryFill4(x - 1, y, fillColor, borderColor);// x coordinate decrease করে previous pixel এ boundary fill function call করা হচ্ছে
        boundaryFill4(x, y + 1, fillColor, borderColor);// y coordinate increase করে next pixel এ boundary fill function call করা হচ্ছে
        boundaryFill4(x, y - 1, fillColor, borderColor);// y coordinate decrease করে previous pixel এ boundary fill function call করা হচ্ছে
    }
}

void mouse(int btn, int state, int x, int y)
{
    if ((x < 150 || x > 200) || (y < 200 || y > 250))// mouse click করা হয়েছে কিনা check করা হচ্ছে, এখানে polygon এর boundary এর বাইরে click করা হয়েছে কিনা check করা হচ্ছে
    {
        printf("Invalid click !!\n");
        return;
    }

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// mouse left button click করা হয়েছে কিনা check করা হচ্ছে, এবং mouse button down state এ আছে কিনা check করা হচ্ছে
    {
        int xi = x;// mouse click করা হয়েছে এমন x coordinate set করা হচ্ছে
        int yi = (wh - y);// mouse click করা হয়েছে এমন y coordinate set করা হচ্ছে, এখানে window height থেকে y coordinate subtract করা হচ্ছে কারণ OpenGL এ y coordinate এর direction opposite হয়

        boundaryFill4(xi, yi, fillCol, borderCol);// boundary fill function call করা হচ্ছে, এখানে mouse click করা হয়েছে এমন coordinate এবং fill color এবং border color দেওয়া হচ্ছে
    }
}
