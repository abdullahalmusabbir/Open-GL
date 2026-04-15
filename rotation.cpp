#include <windows.h>
#include <GL/GLU.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string>

float currentAngle = 0.0f;// current rotation angle of the triangle

void drawOriginDot() {
    glLoadIdentity();// modelview matrix reset করা হচ্ছে, এটি previous transformations কে identity matrix এ set করে
    glColor3f(1.0f, 0.2f, 0.2f);// origin point color set করা হচ্ছে, এখানে red color set করা হচ্ছে
    glPointSize(8.0f);// origin point size set করা হচ্ছে, এখানে 8.0 unit pixel size set করা হচ্ছে
    glBegin(GL_POINTS);// origin point draw করার জন্য GL_POINTS mode এ glBegin() call করা হচ্ছে
    glVertex2f(0.0f, 0.0f);// origin point position set করা হচ্ছে, এখানে x=0 এবং y=0 coordinate এ origin point draw করা হচ্ছে
    glEnd();// origin point draw করার জন্য glEnd() call করা হচ্ছে
    glPointSize(1.0f);// origin point size reset করা হচ্ছে, যাতে পরবর্তী drawing এ normal pixel size ব্যবহার করা হয়
}

void draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);// background color set করা হচ্ছে, এখানে dark gray color set করা হচ্ছে
    glClear(GL_COLOR_BUFFER_BIT);// screen clear করা হচ্ছে, এখানে color buffer clear করা হচ্ছে

    glLoadIdentity();// modelview matrix reset করা হচ্ছে, এটি previous transformations কে identity matrix এ set করে
    glRotatef(currentAngle, 0.0f, 0.0f, 1.0f);// triangle rotate করার জন্য glRotatef() call করা হচ্ছে, এখানে currentAngle variable এর value অনুযায়ী angle set করা হচ্ছে এবং rotation axis z-axis (0, 0, 1) দেওয়া হচ্ছে

    glColor3f(0.2f, 0.8f, 0.4f);// triangle color set করা হচ্ছে, এখানে light green color set করা হচ্ছে
    glBegin(GL_TRIANGLES);// triangle draw করার জন্য GL_TRIANGLES mode এ glBegin() call করা হচ্ছে
    glVertex2f( 0.4f,  0.8f);// triangle vertex set করা হচ্ছে, এখানে x=0.4 এবং y=0.8 coordinate নেওয়া হচ্ছে
    glVertex2f( 0.2f,  0.3f);
    glVertex2f( 0.7f,  0.3f);
    glEnd();// triangle draw করার জন্য glEnd() call করা হচ্ছে

    glColor3f(1.0f, 1.0f, 1.0f);// triangle outline color set করা হচ্ছে, এখানে white color set করা হচ্ছে
    glLineWidth(2.0f);// triangle outline width set করা হচ্ছে, এখানে 2.0 unit line width set করা হচ্ছে
    glBegin(GL_LINE_LOOP);// triangle outline draw করার জন্য GL_LINE_LOOP mode এ glBegin() call করা হচ্ছে, এটি closed loop তৈরি করে
    glVertex2f( 0.4f,  0.8f);// triangle vertex set করা হচ্ছে, এখানে x=0.4 এবং y=0.8 coordinate নেওয়া হচ্ছে
    glVertex2f( 0.2f,  0.3f);
    glVertex2f( 0.7f,  0.3f);
    glEnd();// triangle outline draw করার জন্য glEnd() call করা হচ্ছে

    drawOriginDot();// origin point draw করার জন্য drawOriginDot() function call করা হচ্ছে

    glFlush();// drawing command গুলো execute করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ drawing show করে
}



void init() {
    glMatrixMode(GL_PROJECTION);// projection matrix mode set করা হচ্ছে, এটি coordinate system define করে
    glLoadIdentity();// projection matrix reset করা হচ্ছে, এটি previous projection matrix কে identity matrix এ set করে
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);// orthographic projection set করা হচ্ছে, এখানে left=-1, right=1, bottom=-1, top=1, এটি 2D coordinate system define করে
    glMatrixMode(GL_MODELVIEW);// modelview matrix mode set করা হচ্ছে, এটি object transformations define করে
    glLoadIdentity();// modelview matrix reset করা হচ্ছে, এটি previous transformations কে identity matrix এ set করে
}

float getDegreeFromUser() {
    float deg = 0.0f;// user input থেকে degree read করার জন্য variable declare করা হচ্ছে
    printf("\n  Enter degrees of rotation: ");// user input prompt print করা হচ্ছে
    scanf("%f", &deg);// user input থেকে degree read করা হচ্ছে, এখানে deg variable এ user input value store করা হচ্ছে
    return deg;
}

void OptionsMenu(GLint selectedOpt) {
    float deg = getDegreeFromUser();// user input থেকে degree read করা হচ্ছে, এখানে getDegreeFromUser() function call করা হচ্ছে এবং return value deg variable এ store করা হচ্ছে
    switch (selectedOpt) {
    case 1:
        currentAngle -= deg;// currentAngle variable থেকে deg value subtract করা হচ্ছে, যাতে triangle clockwise rotate হয়
        printf("  >> Rotated CLOCKWISE by %.1f degrees. Total angle: %.1f\n", deg, currentAngle);// user input এবং current angle print করা হচ্ছে
        break;
    case 2:
        currentAngle += deg;// currentAngle variable এ deg value add করা হচ্ছে, যাতে triangle anti-clockwise rotate হয়
        printf("  >> Rotated ANTI-CLOCKWISE by %.1f degrees. Total angle: %.1f\n", deg, currentAngle);// user input এবং current angle print করা হচ্ছে
        break;
    case 3:
        currentAngle = 0.0f;// currentAngle variable reset করা হচ্ছে, যাতে triangle original position এ চলে আসে
        printf("  >> Reset to original position.\n");// reset action print করা হচ্ছে
        break;
    }

    glutPostRedisplay();// display() function আবার call করা হচ্ছে, যাতে screen refresh হয় এবং updated rotation angle অনুযায়ী triangle redraw হয়
}

int main(int argc, char* argv[]) {
    printf("===========================================\n");
    printf("   Triangle Rotation - OpenGL\n");
    printf("===========================================\n");
    printf("  Right-click to open the menu.\n");
    printf("  Choose Clockwise or Anti-Clockwise,\n");
    printf("  then type the degree in this console.\n");
    printf("===========================================\n\n");

    glutInit(&argc, argv);// program start করার জন্য basic setup
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);// screen কিভাবে render হবে সেটা define করছে, এখানে RGB color mode এবং single buffering set করা হচ্ছে
    glutInitWindowPosition(200, 100);// window position set করা হচ্ছে, এখানে x=200 এবং y=100 coordinate এ window position set করা হচ্ছে
    glutInitWindowSize(700, 700);// window size set করা হচ্ছে, এখানে width=700 এবং height=700 pixel set করা হচ্ছে
    glutCreateWindow("Triangle Rotation");// window create করা হচ্ছে, এখানে window title "Triangle Rotation" set করা হচ্ছে

    init();// background color set, coordinate system set করার জন্য init() function call করা হচ্ছে
    glutDisplayFunc(draw);// callback function set করা হচ্ছে, যখন window refresh হবে তখন draw() function call হবে

    glutCreateMenu(OptionsMenu);// menu create করা হচ্ছে, এখানে menu option select করার জন্য callback function OptionsMenu() set করা হচ্ছে
    glutAddMenuEntry("Rotate Clockwise", 1);// menu entry add করা হচ্ছে, এখানে menu option "Rotate Clockwise" এবং corresponding value 1 set করা হচ্ছে
    glutAddMenuEntry("Rotate Anti-Clockwise", 2);// menu entry add করা হচ্ছে, এখানে menu option "Rotate Anti-Clockwise" এবং corresponding value 2 set করা হচ্ছে
    glutAttachMenu(GLUT_RIGHT_BUTTON);// menu attach করা হচ্ছে, এখানে right mouse button এ menu attach করা হচ্ছে

    glutMainLoop();
    return 0;
}