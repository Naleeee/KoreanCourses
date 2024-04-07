#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Value_Slider.H>
// #include <windows.h>
#include <FL/Fl_Double_Window.H>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "math.h"

#include "Vec3f.h"
#include "Viewer.h"
#include <vector>

#include "./Cyclone/core.h"

#include "object.h"
#include <FL/Fl_Light_Button.H>

class MyGlWindow : public Fl_Gl_Window {
public:
  MyGlWindow(int x, int y, int w, int h);
  Fl_Light_Button *ui;

  void putText(char *string, int x, int y, float r, float g, float b);
  std::vector<Vec3f *> history;

  Fl_Slider *time;
  int run;
  void update();
  void drawStuff();
  void doPick();
  void test();

private:
  void draw(); // standard FlTk

  int handle(int); // standard FlTk

  float fieldOfView;
  Viewer *m_viewer;

  Mover *mover;

  void setProjection(int clearProjection = 1);
  void getMouseNDC(float &x, float &y);
  void setupLight(float x, float y, float z);
};
