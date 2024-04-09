#pragma once

#include "./Cyclone/core.h"
#include "./Cyclone/particle.h"
#include "./Cyclone/pfgen.h"
#include "./MySpring.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

class Mover {
public:
	float size {};
	cyclone::Particle *m_particle {};
	cyclone::ParticleGravity *m_gravity {};
	cyclone::ParticleDrag *m_drag {};
	cyclone::ParticleForceRegistry *m_forces {};
	cyclone::MySpring *m_spring {};

	Mover(cyclone::Vector3 pos)
	{
		size = 1.0f;

		m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
		m_drag = new cyclone::ParticleDrag(0.1, 0.01);

		m_forces = new cyclone::ParticleForceRegistry();
		m_particle = new cyclone::Particle();

		m_forces->add(m_particle, m_gravity);
		m_forces->add(m_particle, m_drag);

		m_particle->setPosition(pos);
		m_particle->setVelocity(0.0f, 0.0f, 0.0f);
		m_particle->setMass(10.0f);					   // mass
		m_particle->setDamping(0.9f);				   // damping
		m_particle->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc
	};
	Mover(const Mover &) = default;
	Mover(Mover &&) = delete;
	Mover &operator=(const Mover &) = default;
	Mover &operator=(Mover &&) = delete;
	Mover(cyclone::Vector3 &p); //p: initial position

	~Mover();

	void update(float duration)
	{
		m_forces->updateForces(duration);
		m_particle->integrate(duration);
		m_spring->updateForce(m_particle, duration);
		checkEdges();
	}

	void resetParameters(cyclone::Vector3 pos)
	{
		m_particle->setPosition(pos); // initial posx
		m_particle->setVelocity(0.0f, 0.0f, 0.0f);
		m_particle->setDamping(0.9f);
		m_particle->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc
		m_particle->setMass(10.0f);					   // 1.0kg-mostly blast damage
	}

	void checkEdges()
	{
		cyclone::Vector3 pos = m_particle->getPosition();
		cyclone::Vector3 vel = m_particle->getVelocity();

		if (pos.x >= 100 - size / 2) {
			pos.x = 100 - size / 2;
			vel.x *= -1;
		} else if (pos.x <= -100 + size / 2) {
			pos.x = -100 + size / 2;
			vel.x *= -1;
		}
		if (pos.y <= size / 2) {
			pos.y = size / 2;
			vel.y *= -1;
		}
		if (pos.z >= 100 - size / 2) {
			pos.z = 100 - size / 2;
			vel.z *= -1;
		} else if (pos.z <= -100 + size / 2) {
			pos.z = -100 + size / 2;
			vel.z *= -1;
		}
		m_particle->setPosition(pos);
		m_particle->setVelocity(vel);
	}

	void stop() { }

	void draw(int shadow)
	{
		cyclone::Vector3 position;
		m_particle->getPosition(&position); // get the current pos of particle

		if (shadow)
			glColor3f(0.1f, 0.1f, 0.1f);
		else
			glColor3f(1.0, 0, 0);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glutSolidSphere(size, 30, 30);
		glPopMatrix();
	}
	void setConnection(Mover *a)
	{
		m_spring = new cyclone::MySpring(a->m_particle, 20.0f, 3);
	}
};

class MoverConnection {
public:
	Mover *m_MoverA {};
	Mover *m_MoverB {};

	MoverConnection();
	MoverConnection(const MoverConnection &) = default;
	MoverConnection(MoverConnection &&) = delete;
	MoverConnection &operator=(const MoverConnection &) = default;
	MoverConnection &operator=(MoverConnection &&) = delete;
	MoverConnection(cyclone::ParticleGravity *m_gravity, cyclone::ParticleForceRegistry *m_forces,
					std::vector<Mover *> m_movers)
		: m_gravity(m_gravity)
		, m_forces(m_forces)
	// , m_movers(std::move(m_movers))
	{
	}
	MoverConnection(Mover *MoverA, Mover *MoverB)
	{
		m_forces = new cyclone::ParticleForceRegistry();
		m_forces->add(MoverA->m_particle, m_gravity);
		m_forces->add(MoverB->m_particle, m_gravity);
		m_forces->add(MoverA->m_particle, MoverA->m_spring);
		m_forces->add(MoverB->m_particle, MoverB->m_spring);
		MoverA->setConnection(MoverB);
		MoverB->setConnection(MoverA);
		m_MoverA = MoverA;
		m_MoverB = MoverB;
	}
	~MoverConnection();
	cyclone::ParticleGravity *m_gravity {};
	cyclone::ParticleForceRegistry *m_forces;
	void update(float duration) { }
	void draw(int shadow)
	{
		//Drawing a line for representing connection
		glBegin(GL_LINE_STRIP);
		cyclone::Vector3 posA = m_MoverA->m_particle->getPosition();
		glVertex3f(posA.x, posA.y, posA.z);
		cyclone::Vector3 posB = m_MoverB->m_particle->getPosition();
		glVertex3f(posB.x, posB.y, posB.z);
		glEnd();
	};
};
