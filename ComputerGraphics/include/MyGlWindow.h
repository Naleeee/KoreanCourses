#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Value_Slider.H>
// #include <windows.h>
#include "./Cyclone/core.h"
#include "Vec3f.h"
#include "Viewer.h"
#include "math.h"
#include "object.h"

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Light_Button.H>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

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

	int selected = -1;
	cyclone::Vector3 initialPos;

private:
	void draw() override; // standard FlTk

	int handle(int) override; // standard FlTk

	float fieldOfView;
	Viewer *m_viewer;

	std::vector<Mover *> movables;

	MoverConnection *movableLinks;

	void setProjection(int clearProjection = 1);
	void getMouseNDC(float &x, float &y);
	void setupLight(float x, float y, float z);
};
