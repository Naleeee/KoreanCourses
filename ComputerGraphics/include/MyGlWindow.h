#include "SimplePhysics.hpp"

#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <Vec3f.h>
#include <Viewer.h>

class MyGlWindow : public Fl_Gl_Window {
public:
	MyGlWindow(int x, int y, int w, int h);
	Fl_Light_Button *ui;

	void putText(char *string, int x, int y, float r, float g, float b);
	std::vector<Vec3f *> history;
	int score = 0;

	Fl_Slider *time;
	int run;
	void update();
	void drawStuff();
	void doPick();
	void resetEntities(bool, bool);
	void testValue(float t);

	int selected = -1;
	cyclone::Vector3 initialPos;

private:
	// Original members variables
	float fieldOfView;
	Viewer *m_viewer;

	// Added members variables
	SimplePhysics *simplePhysics;

	void draw() override;	  // standard FlTk
	int handle(int) override; // standard FlTk
	void setProjection(int clearProjection = 1);
	void getMouseNDC(float &x, float &y);
	void setupLight(float x, float y, float z);
};
