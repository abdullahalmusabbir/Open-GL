#include <GL/glut.h>

void display()
{
/* draw unit square polygon */
  glClear(GL_COLOR_BUFFER_BIT);// screen clear করা হচ্ছে, এখানে color buffer clear করা হচ্ছে
  glBegin(GL_POLYGON);// polygon draw করার জন্য GL_POLYGON mode এ glBegin() call করা হচ্ছে
  glColor3f(1.0f, 0.0f, 1.0f);// polygon color set করা হচ্ছে, এখানে magenta color set করা হচ্ছে
  glVertex2f(150, 150);// polygon vertex set করা হচ্ছে, এখানে x=150 এবং y=150 coordinate নেওয়া হচ্ছে
  glVertex2f(300, 150);
  glVertex2f(225, 225);
  glEnd();// polygon draw করার জন্য glEnd() call করা হচ্ছে
  glFlush(); // polygon draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ polygon draw করে
}
void OptionsMenu(GLint selectedOpt)
{
  switch (selectedOpt)
  {
  case 1:
  /* draw unit square polygon */
  glBegin(GL_POLYGON);// polygon draw করার জন্য GL_POLYGON mode এ glBegin() call করা হচ্ছে
  glVertex2f(150, 150);// polygon vertex set করা হচ্ছে, এখানে x=150 এবং y=150 coordinate নেওয়া হচ্ছে
  glVertex2f(300, 150);
  glVertex2f(225, 225);
  glEnd();
  /* flush GL buffers */
  glFlush();// polygon draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ polygon draw করে
  break;
  case 2:
  glRotatef(15, 0, 0, 1);// polygon rotate করার জন্য glRotatef() call করা হচ্ছে, এখানে angle=15 degree এবং rotation axis z-axis (0, 0, 1) দেওয়া হচ্ছে
  glColor3f(1.0f, 0.0f, 0.0f);// polygon color set করা হচ্ছে, এখানে red color set করা হচ্ছে
  break;
  case 3:
  glScalef(1.5, 1.5, 0);// polygon scale করার জন্য glScalef() call করা হচ্ছে, এখানে x এবং y direction এ 1.5 গুণ বড় করা হচ্ছে
  glColor3f(0.0f, 1.0f, 0.0f);// polygon color set করা হচ্ছে, এখানে green color set করা হচ্ছে
  break;
  case 4:
  glTranslatef(100, 100, 0);// polygon translate করার জন্য glTranslatef() call করা হচ্ছে, এখানে x direction এ 100 এবং y direction এ 100 unit translate করা হচ্ছে
  glColor3f(0.0f, 1.0f, 1.0f);//    
  default: break;
  }
}
void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0); // background color set করা হচ্ছে, এখানে black color set করা হচ্ছে
  glPointSize(1.0);// pixel size set করা হচ্ছে, এখানে 1.0 unit pixel size set করা হচ্ছে
  glMatrixMode(GL_PROJECTION);// projection matrix mode set করা হচ্ছে, এটি coordinate system define করে
  glLoadIdentity();// projection matrix reset করা হচ্ছে, এটি previous projection matrix কে identity matrix এ set করে
  gluOrtho2D(0.0, 800.0, 0.0, 800.0);// orthographic projection set করা হচ্ছে, এখানে left=0, right=800, bottom=0, top=800, এটি 2D coordinate system define করে
 }
void main(int argc, char** argv)
{
  glutInit(&argc, argv);// GLUT library initialize করা হচ্ছে, এখানে command line arguments pass করা হচ্ছে
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// screen কিভাবে render হবে সেটা define করছে, এখানে single buffering এবং RGB color mode set করা হচ্ছে
  glutInitWindowSize(800, 800);// window size set করা হচ্ছে, এখানে width=800 এবং height=800 pixel set করা হচ্ছে
  glutInitWindowPosition(0, 0);// window position set করা হচ্ছে, এখানে x=0 এবং y=0 coordinate এ window position set করা হচ্ছে
  glutCreateWindow("simple");// window create করা হচ্ছে, এখানে window title "simple" set করা হচ্ছে
  glutDisplayFunc(display);// callback function set করা হচ্ছে, যখন window refresh হবে তখন display() function call হবে
  glutCreateMenu(OptionsMenu);// menu create করা হচ্ছে, এখানে menu option select করার জন্য callback function OptionsMenu() set করা হচ্ছে
  glutAddMenuEntry("Polygon ", 1);// menu entry add করা হচ্ছে, এখানে menu option "Polygon" এবং corresponding value 1 set করা হচ্ছে
  glutAddMenuEntry("Rotate ", 2);// menu entry add করা হচ্ছে, এখানে menu option "Rotate" এবং corresponding value 2 set করা হচ্ছে
   glutAddMenuEntry("Scale ", 3);// menu entry add করা হচ্ছে, এখানে menu option "Scale" এবং corresponding value 3 set করা হচ্ছে
  glutAddMenuEntry("Scale", 3);// menu entry add করা হচ্ছে, এখানে menu option "Scale" এবং corresponding value 3 set করা হচ্ছে
  glutAddMenuEntry("Translate ", 4);// menu entry add করা হচ্ছে, এখানে menu option "Translate" এবং corresponding value 4 set করা হচ্ছে
  glutAttachMenu(GLUT_RIGHT_BUTTON);// menu attach করা হচ্ছে, এখানে right mouse button এ menu attach করা হচ্ছে
  init();// background color set, pixel size set, coordinate system set করা হচ্ছে
  glutMainLoop();//infinite loop চালায়, এখানে program run হবে যতক্ষণ না user window close করে
}