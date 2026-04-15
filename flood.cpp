//Flood Fill using OpenGL 
#include <GL/glut.h>  
int ww = 600, wh = 500; // window width and height
float bgCol[3] = { 0.0,0.9,0.7 };  // background color (cyan)
float intCol[3] = { 1.0,0.0,0.0 };  // interior color (red)
float fillCol[3] = { 0.4,0.5,0.0 };  // fill color (greenish)
void setPixel(int pointx, int pointy, float f[3])  // pixel draw function, এখানে pointx এবং pointy coordinate এ f color set করা হচ্ছে
{
  glBegin(GL_POINTS);  // pixel draw করার জন্য GL_POINTS mode এ glBegin() call করা হচ্ছে
  glColor3fv(f);  // pixel color set করা হচ্ছে, এখানে f array থেকে color value নেওয়া হচ্ছে
  glVertex2i(pointx, pointy);  // pixel position set করা হচ্ছে, এখানে pointx এবং pointy coordinate নেওয়া হচ্ছে
  glEnd();  // pixel draw করার জন্য glEnd() call করা হচ্ছে
  glFlush(); // pixel draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ pixel draw করে
}  
void getPixel(int x, int y, float pixels[3]) 
{  
  glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels); // x এবং y coordinate থেকে pixel color read করা হচ্ছে, এখানে 1x1 area থেকে color read করা হচ্ছে, color format RGB এবং data type float
}
void drawPolygon(int x1, int y1, int x2, int y2)  
{  
  glColor3f(1.0, 0.0, 0.0);  // polygon color set করা হচ্ছে, এখানে red color set করা হচ্ছে
  glBegin(GL_POLYGON);  // polygon draw করার জন্য GL_POLYGON mode এ glBegin() call করা হচ্ছে
  glVertex2i(x1, y1);  // polygon vertex set করা হচ্ছে, এখানে x1 এবং y1 coordinate নেওয়া হচ্ছে
  glVertex2i(x1, y2);  
  glVertex2i(x2, y2);  
  glVertex2i(x2, y1);  
  glEnd();  // polygon draw করার জন্য glEnd() call করা হচ্ছে
  glFlush(); // polygon draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ polygon draw করে
}  
void display()  
{  
  glClearColor(0.2, 0.4, 0.0, 0.6); // background color set করা হচ্ছে, এখানে dark green color set করা হচ্ছে
  glClear(GL_COLOR_BUFFER_BIT);  // screen clear করা হচ্ছে, এখানে color buffer clear করা হচ্ছে
  drawPolygon(150, 250, 200, 300);  // polygon draw করা হচ্ছে, এখানে start point (150, 250) এবং end point (200, 300) দেওয়া হচ্ছে
  glFlush(); // polygon draw করার জন্য glFlush() call করা হচ্ছে, এটি OpenGL command গুলো execute করে এবং screen এ polygon draw করে
}  
void floodfill4(int x, int y, float oldcolor[3], float newcolor[3])  { float color[3];  
getPixel(x, y, color);  
if (color[0] == oldcolor[0] && (color[1]) == oldcolor[1] && (color[2]) ==  oldcolor[2])  // x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
{ 
  setPixel(x, y, newcolor);  // x এবং y coordinate এ newcolor set করা হচ্ছে
  floodfill4(x + 1, y, oldcolor, newcolor);  // x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
  floodfill4(x - 1, y, oldcolor, newcolor);  // x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
  floodfill4(x, y + 1, oldcolor, newcolor);  // x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
  floodfill4(x, y - 1, oldcolor, newcolor);  // x এবং y coordinate এ pixel color oldcolor এর সাথে match করে কিনা check করা হচ্ছে, এখানে color array এ pixel color value store করা হচ্ছে
}  
} 
void mouse(int btn, int state, int x, int y)  
{  
if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // mouse left button click করা হয়েছে কিনা check করা হচ্ছে, এবং mouse button down state এ আছে কিনা check করা হচ্ছে
{
  int xi = x;  // mouse click করা হয়েছে এমন x coordinate set করা হচ্ছে
  int yi = (wh - y);  // mouse click করা হয়েছে এমন y coordinate set করা হচ্ছে, এখানে window height থেকে y coordinate subtract করা হচ্ছে কারণ OpenGL এ y coordinate এর direction opposite হয়
  floodfill4(xi, yi, intCol, fillCol);  // flood fill function call করা হচ্ছে, এখানে mouse click করা হয়েছে এমন coordinate এবং interior color এবং fill color দেওয়া হচ্ছে
} 
} 
void myinit() 
{  
  glViewport(0, 0, ww, wh);  // viewport set করা হচ্ছে, এখানে x=0, y=0 থেকে শুরু করে width=ww এবং height=wh পর্যন্ত
  glMatrixMode(GL_PROJECTION); // projection matrix mode set করা হচ্ছে, এটি coordinate system define করে
  glLoadIdentity();  // projection matrix reset করা হচ্ছে, এটি previous projection matrix কে identity matrix এ set করে
  gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);  glMatrixMode(GL_MODELVIEW);  // modelview matrix mode set করা হচ্ছে, এটি object transformation এবং viewing transformation define করে
}  
int main(int argc, char** argv)  // program entry point
{  
  glutInit(&argc, argv);  // program start করার জন্য basic setup
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  glutInitWindowSize(ww, wh); // window size set করা হচ্ছে 
  glutCreateWindow("Flood-Fill");  // window create করা হচ্ছে
  glutDisplayFunc(display);  // callback function set করা হচ্ছে, যখন window refresh হবে তখন display() function call হবে
  myinit();  // background color set, coordinate system set করা হচ্ছে
  glutMouseFunc(mouse);  // mouse event handle করার জন্য callback function set করা হচ্ছে, যখন mouse click হবে তখন mouse() function call হবে
  glutMainLoop();  //infinite loop চালায়, এখানে program run হবে যতক্ষণ না user window close করে
  return 0;  
} 