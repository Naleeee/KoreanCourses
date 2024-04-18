#include "Fire.hpp"

#include "random.h"

#include <FL/glut.H>
#include <GL/gl.h>
#include <iostream>

Fire::Fire(int type)
{
	auto *pos = new cyclone::Vector3(cyclone::Random().randomReal(-5.0f, 5.0f), 10.0f,
									 cyclone::Random().randomReal(-5.0f, 5.0f));
	auto *vel = new cyclone::Vector3(cyclone::Random().randomVector(
		cyclone::Vector3(0.0f, 0.0f, 0.0f), cyclone::Vector3(10.0f, 30.0f, 10.0f)));

	auto *color = new cyclone::Vector3(
		cyclone::Random().randomVector(cyclone::Vector3(0, 0, 0), cyclone::Vector3(1, 1, 1)));
	m_age = cyclone::Random().randomReal(0.5f, 3.0f);
	std::cout << "Default color: " << color->x << "/" << color->y << "/" << color->z
			  << " | Default position: " << pos->x << "/" << pos->y << "/" << pos->z << std::endl;

	m_size = 1.0f;
	auto m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
	m_forces = new cyclone::ParticleForceRegistry();

	m_particle = new cyclone::Particle();

	m_particle->setPosition(*pos);
	m_particle->setVelocity(*vel);
	m_particle->setMass(1.0f);
	m_particle->setDamping(0.99f);
	m_color = *color;

	m_forces->add(m_particle, m_gravity);
}

Fire::Fire(Fire *fire)
{
	auto pos = fire->m_particle->getPosition();

	auto vel = new cyclone::Vector3(cyclone::Random().randomVector(
		cyclone::Vector3(-5.0f, 10.0f, -5.0f), cyclone::Vector3(5.0f, 15.0f, 5.0f)));
	// vel = fire->m_particle->getVelocity() + vel;
	auto oldVel = fire->m_particle->getVelocity();
	auto final = new cyclone::Vector3(oldVel.x + vel->x, oldVel.y + vel->y, oldVel.z + vel->z);

	auto m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
	m_forces = new cyclone::ParticleForceRegistry();

	m_particle = new cyclone::Particle();

	m_particle->setPosition(fire->m_particle->getPosition());
	m_particle->setVelocity(*final);
	m_particle->setMass(1.0f);
	m_particle->setDamping(0.99f);
	m_color = fire->m_color;

	m_forces->add(m_particle, m_gravity);
}

bool Fire::update(float duration)
{
	m_forces->updateForces(duration);
	m_particle->integrate(duration);
	m_age -= duration;
	return true;
}

void Fire::draw(int shadow)
{
	cyclone::Vector3 position;
	m_particle->getPosition(&position); // get the current pos of particle

	// if (shadow) {
	// 	glColor3f(0, 0, 0);
	// } else {
	glColor3f(m_color.x, m_color.y, m_color.z);
	// }

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(m_size, 30, 30);
	glPopMatrix();
}

void Fire::drawHistory() { }
void Fire::setRule(FireworksRule *r) { }
void Fire::putHistory() { }
