#include "Fire.hpp"

#include "random.h"

#include <FL/glut.H>
#include <GL/gl.h>
#include <iostream>

Fire::Fire(int type)
{
	m_size = 1.0f;
	m_particle = new cyclone::Particle();
	m_type = type;

	if (type) {
		m_particle->setAcceleration(cyclone::Vector3(0, -9.81, 0));
	}
}

bool Fire::update(float duration)
{
	m_particle->integrate(duration);
	m_age -= duration;
	if (m_age <= 0 || m_particle->getPosition().y <= 0) {
		return true;
	}
	return false;
}

void Fire::draw(int shadow)
{
	cyclone::Vector3 position;
	m_particle->getPosition(&position);

	if (shadow) {
		glColor3f(0.1f, 0.1f, 0.1f);
	} else {
		drawHistory();
		glColor3f(m_color.x, m_color.y, m_color.z);
	}

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(m_size, 30, 30);
	glPopMatrix();
}

void Fire::drawHistory()
{
	glColor3f(m_color.x, m_color.y, m_color.z);
	glLineWidth(2.0f);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < m_history.size(); i += 2) {
		cyclone::Vector3 p = m_history[i];
		glVertex3f(p.x, p.y, p.z);
	}
	glEnd();
	glPopMatrix();
	glLineWidth(1.0f);
}

void Fire::setRule(FireworksRule *r)
{
	auto *pos = new cyclone::Vector3(cyclone::Random().randomReal(r->xMin, r->xMax),
									 cyclone::Random().randomReal(r->yMin, r->yMax),
									 cyclone::Random().randomReal(r->zMin, r->zMax));
	auto *vel =
		new cyclone::Vector3(cyclone::Random().randomVector(r->minVelocity, r->maxVelocity));
	auto *color = new cyclone::Vector3(cyclone::Random().randomVector(r->minColor, r->maxColor));

	m_age = cyclone::Random().randomReal(r->minAge, r->maxAge);
	m_rule = r;
	m_particle->setPosition(*pos);
	m_particle->setVelocity(*vel);
	m_particle->setMass(1.0f);
	m_particle->setDamping(0.99f);
	m_color = *color;
}
void Fire::putHistory()
{
	if (m_history.size() > 30) {
		m_history.pop_front();
	}
	m_history.push_back(m_particle->getPosition());
}
