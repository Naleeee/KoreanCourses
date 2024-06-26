#include "MyGlWindow.h"

#include "3DUtils.h"
#include "DrawUtils.h"
#include "timing.h"

#include <GL/glu.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <string>

static double DEFAULT_VIEW_POINT[3] = {0, 50, -95};
static double DEFAULT_VIEW_CENTER[3] = {0, 1, -50};
static double DEFAULT_UP_VECTOR[3] = {0, 1, 0};

void drawStrokeText(char *string, int x, int y, int z)
{
	char *c = nullptr;
	glPushMatrix();
	glTranslated(x, y + 8, z);
	glScaled(0.2, 0.2, 0.2);
	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void MyGlWindow::putText(char *string, int x, int y, float r, float g, float b)
{
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ortho();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glColor3f(r, g, b);
	drawStrokeText(string, x, y, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

MyGlWindow::MyGlWindow(int x, int y, int w, int h)
	: Fl_Gl_Window(x, y, w, h)
//==========================================================================
{
	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);

	fieldOfView = 80;

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);

	//	glutInit(0,0);

	// Setup elements
	simplePhysics = new SimplePhysics();

	TimingData::init();
	run = 0;
}

void MyGlWindow::setupLight(float x, float y, float z)
{
	// set up the lighting
	GLfloat lightPosition[] = {500.0f, 900.0f, 500.0f, 1.0f};
	GLfloat lightPosition2[] = {1, 0, 0, 0};
	GLfloat lightPosition3[] = {0, -1, 0, 0};

	GLfloat violetLight[] = {0.5f, 0.1f, .5f, 1.0f};
	GLfloat whiteLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat whiteLight2[] = {.3f, .3f, .3f, 1.0f};
	GLfloat blueLight[] = {.1f, .1f, .3f, 1.0f};

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteLight2);
	//
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteLight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MyGlWindow::drawStuff()
{
	// Draw board game in yellow
	glColor4f(1, 1, 0, 0.5); // yellow
							 // Left pane
	polygonf(4, 30.0f, 0.0f, 100.0f, 30.0f, 10.0f, 100.0f, 30.0f, 10.0f, -100.0f, 30.0f, 0.0f,
			 -100.0f);
	// Right pane
	polygonf(4, -30.0f, 0.0f, 100.0f, -30.0f, 10.0f, 100.0f, -30.0f, 10.0f, -100.0f, -30.0f, 0.0f,
			 -100.0f);
	// Front pane
	polygonf(4, 30.0f, 0.0f, 100.0f, 30.0f, 10.0f, 100.0f, -30.0f, 10.0f, 100.0f, -30.0f, 0.0f,
			 100.0f);
	// Back pane
	polygonf(4, 30.0f, 0.0f, -100.0f, 30.0f, 10.0f, -100.0f, -30.0f, 10.0f, -100.0f, -30.0f, 0.0f,
			 -100.0f);
}

//==========================================================================
void MyGlWindow::draw()
//==========================================================================
{
	glViewport(0, 0, w(), h());

	// clear the window, be sure to clear the Z-Buffer too
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // background should be blue

	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// now draw the ground plane
	setProjection();
	setupFloor();
	glPushMatrix();
	drawFloor(200, 20);
	glPopMatrix();

	setupLight(m_viewer->getViewPoint().x, m_viewer->getViewPoint().y, m_viewer->getViewPoint().z);

	// Add a sphere to the scene.
	// Draw axises
	// glLineWidth(3.0f);
	// glBegin(GL_LINES);
	// glColor3f(1, 0, 0);
	//
	// glVertex3f(0.0f, 0.1f, 0.0f);
	// glVertex3f(0.0f, 100.0f, 0.0f);
	//
	// glColor3f(0.0f, 11.0f, 0.0f);
	//
	// glVertex3d(0.0f, 0.1f, 0.0f);
	// glVertex3d(100.0f, 0.1, 0.0f);
	//
	// glColor3f(0.0f, 0.0f, 1.0f);
	//
	// glVertex3f(0.0f, 0.1f, 0.0f);
	// glVertex3f(0.0f, 0.1f, 100.0f);
	// glEnd();
	// glLineWidth(1.0f);

	// draw shadow
	setupShadows();
	glColor3f(0.1f, 0.1f, 0.1f);

	simplePhysics->render(1);

	unsetupShadows();

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	drawStuff();

	// draw objects
	glPushMatrix();
	glColor3f(1, 0, 0);

	// Draw entities
	simplePhysics->render(0);

	glPopMatrix();

	////////////////////
	char name[20] = "Current score: ";
	std::string s = std::to_string(score);
	char const *pchar = s.c_str();

	strcat(name, pchar);
	char *mutableName = const_cast<char *>(name);
	putText(mutableName, 0, 0, 1, 1, 0); /////
	glViewport(0, 0, w(), h());
	setProjection();
	glEnable(GL_COLOR_MATERIAL);
}

void MyGlWindow::testValue(float t) { }

void MyGlWindow::resetEntities(bool resetKeels, bool resetBall)
{
	if (resetKeels) {
		score = 0;
	}
	simplePhysics->reset(resetKeels, resetBall);
}

cyclone::Vector3 lerp(const float t, const cyclone::Vector3 &p0, const cyclone::Vector3 &p1)
{
	return (p0 + (p1 - p0) * t);
}

void MyGlWindow::update()
{
	TimingData::get().update();

	if (!run)
		return;

	float duration = (float)TimingData::get().lastFrameDuration * 0.003f;

	// Update entities
	score += simplePhysics->update(duration);
}

void MyGlWindow::doPick()
{
	make_current(); // since we'll need to do some GL stuff

	int mx = Fl::event_x(); // where is the mouse?
	int my = Fl::event_y();

	// get the viewport - most reliable way to turn mouse coords into GL coords
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	// set up the pick matrix on the stack - remember, FlTk is
	// upside down!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPickMatrix((double)mx, (double)(viewport[3] - my), 5, 5, viewport);

	// now set up the projection
	setProjection(false);

	// now draw the objects - but really only see what we hit
	GLuint buf[100];
	glSelectBuffer(100, buf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);

	for (int i = 0; i < simplePhysics->sphereData.size(); i++) {
		glLoadName(i + 1);

		simplePhysics->sphereData[i]->render(0);
	}

	// go back to drawing mode, and see how picking did
	int hits = glRenderMode(GL_RENDER);
	if (hits) {
		// warning; this just grabs the first object hit - if there
		// are multiple objects, you really want to pick the closest
		// one - see the OpenGL manual
		// remember: we load names that are one more than the index
		// selectedCube = buf[3] - 1;

		selected = buf[3] - 1;
	} else { // nothing hit, nothing selected
		selected = -1;
	}
}

void MyGlWindow::setProjection(int clearProjection)
//==========================================================================
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, w(), h());
	if (clearProjection)
		glLoadIdentity();
	// compute the aspect ratio so we don't distort things
	double aspect = ((double)w()) / ((double)h());
	gluPerspective(fieldOfView, aspect, 1, 1000);

	// put the camera where we want it to be
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// use the transformation in the ArcBall

	gluLookAt(m_viewer->getViewPoint().x, m_viewer->getViewPoint().y, m_viewer->getViewPoint().z,
			  m_viewer->getViewCenter().x, m_viewer->getViewCenter().y, m_viewer->getViewCenter().z,
			  m_viewer->getUpVector().x, m_viewer->getUpVector().y, m_viewer->getUpVector().z);

	glDisable(GL_BLEND);
}

static int last_push;
int m_pressedMouseButton;
int m_lastMouseX;
int m_lastMouseY;
// cyclone::Vector3 initialPos;

int MyGlWindow::handle(int e)
//==========================================================================
{
	switch (e) {
		case FL_SHOW: // you must handle this, or not be seen!
			show();
			return 1;
		case FL_PUSH: {
			m_pressedMouseButton = Fl::event_button();
			m_lastMouseX = Fl::event_x();
			m_lastMouseY = Fl::event_y();
			if (m_pressedMouseButton == 1) {
				doPick();
				if (selected >= 0) {
					initialPos = simplePhysics->sphereData[selected]->body->getPosition();
				}
				damage(1);
				return 1;
			};
			break;
		}
			damage(1);
			return 1;
		case FL_RELEASE:
			m_pressedMouseButton = -1;
			if (selected >= 0) {
				cyclone::Vector3 finalPos =
					simplePhysics->sphereData[selected]->body->getPosition();
				cyclone::Vector3 newVelocity = finalPos - initialPos;
				simplePhysics->sphereData[selected]->body->setVelocity(newVelocity);
				// simplePhysics->boxData[selected]->body->setVelocity(newVelocity);
				run = 1;
				selected = -1;

				selected = -1;
			}
			damage(1);
			return 1;
		case FL_DRAG: // if the user drags the mouse
		{
			float fractionChangeX =
				static_cast<float>(Fl::event_x() - m_lastMouseX) / static_cast<float>(this->w());
			float fractionChangeY =
				static_cast<float>(m_lastMouseY - Fl::event_y()) / static_cast<float>(this->h());

			if (selected >= 0 && m_pressedMouseButton == 1) {
				double r1x = NAN, r1y = NAN, r1z = NAN, r2x = NAN, r2y = NAN, r2z = NAN;
				getMouseLine(r1x, r1y, r1z, r2x, r2y, r2z);
				double rx = NAN, ry = NAN, rz = NAN;
				mousePoleGo(
					r1x, r1y, r1z, r2x, r2y, r2z,
					static_cast<double>(simplePhysics->sphereData[selected]->body->getPosition().x),
					static_cast<double>(simplePhysics->sphereData[selected]->body->getPosition().y),
					static_cast<double>(simplePhysics->sphereData[selected]->body->getPosition().z),
					rx, ry, rz, (Fl::event_state() & FL_CTRL) != 0);

				simplePhysics->sphereData[selected]->body->setPosition(rx, ry, rz);
				damage(1);
			} else if (m_pressedMouseButton == 1) {
				m_viewer->rotate(fractionChangeX, fractionChangeY);
			} else if (m_pressedMouseButton == 2) {
				m_viewer->zoom(fractionChangeY);
			} else if (m_pressedMouseButton == 3) {
				m_viewer->translate(-fractionChangeX, -fractionChangeY,
									(Fl::event_key(FL_Shift_L) == 0) ||
										(Fl::event_key(FL_Shift_R) == 0));
			} else {
				std::cout << "Warning: dragging with unknown mouse button!  Nothing will "
							 "be done"
						  << std::endl;
				damage(1);
			}

			m_lastMouseX = Fl::event_x();
			m_lastMouseY = Fl::event_y();
			redraw();
		}

			return 1;

		case FL_KEYBOARD:
			return 0;

		default:
			return 0;
	}
	return 0;
}

//
// get the mouse in NDC
//==========================================================================
void MyGlWindow::getMouseNDC(float &x, float &y)
//==========================================================================
{
	// notice, we put everything into doubles so we can do the math
	auto mx = (float)Fl::event_x(); // remeber where the mouse went down
	auto my = (float)Fl::event_y();

	// we will assume that the viewport is the same as the window size
	auto wd = (float)w();
	auto hd = (float)h();

	// remember that FlTk has Y going the wrong way!
	my = hd - my;

	x = (mx / wd) * 2.0f - 1.f;
	y = (my / hd) * 2.0f - 1.f;
}
