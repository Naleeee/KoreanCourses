#include "Fire.hpp"

#include "random.h"

#include <FL/glut.H>
#include <GL/gl.h>
#include <iostream>

Fire::Fire(int type)
{
	std::cout << "Create default values" << std::endl;
	auto *pos = new cyclone::Vector3(cyclone::Random().randomReal(-5, 5), 10,
									 cyclone::Random().randomReal(-5, 5));
	auto *vel = new cyclone::Vector3(
		cyclone::Random().randomVector(cyclone::Vector3(0, 0, 0), cyclone::Vector3(10, 30, 10)));
	auto *color = new cyclone::Vector3(
		cyclone::Random().randomVector(cyclone::Vector3(0, 0, 0), cyclone::Vector3(1, 1, 1)));
	// std::cout << "Default position: " << pos.x << "/" << pos.y << "/" << pos.z << std::endl;
	std::cout << "Default position: " << pos->x << "/" << pos->y << "/" << pos->z << std::endl;

	std::cout << "Assign default values" << std::endl;
	m_particle = new cyclone::Particle();
	m_particle->setPosition(*pos);
	m_particle->setPosition(*new cyclone::Vector3(0.0f, 0.0f, 0.0f));
	m_particle->setVelocity(*vel);
	m_particle->setMass(1.0f);
	m_particle->setDamping(0.99f);
	m_size = 1.0f;
	m_color = *color;
	std::cout << "Fire init ended" << std::endl;
}

bool Fire::update(float duration)
{
	m_particle->integrate(duration);
	return true;
}

void Fire::draw(int shadow)
{
	cyclone::Vector3 position;
	m_particle->getPosition(&position); // get the current pos of particle

	if (shadow)
		glColor3f(0.1f, 0.1f, 0.1f);
	else
		glColor3f(1.0, 0, 0);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(m_size, 30, 30);
	glPopMatrix();
}
void Fire::drawHistory() { }
void Fire::setRule(FireworksRule *r) { }
void Fire::putHistory() { }
