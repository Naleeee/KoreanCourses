#pragma once

#include "Mover.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <core.h>
#include <particle.h>
#include <pfgen.h>

class MoverConnection {
public:
	Mover *m_MoverA {};
	Mover *m_MoverB {};

	MoverConnection();
	MoverConnection(const MoverConnection &) = default;
	MoverConnection(MoverConnection &&) = delete;
	MoverConnection &operator=(const MoverConnection &) = default;
	MoverConnection &operator=(MoverConnection &&) = delete;
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

	MoverConnection(Mover *mover)
	{
		m_forces = new cyclone::ParticleForceRegistry();
		m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
		mover->m_anchorSpring = new cyclone::MyAnchoredSpring(new cyclone::Vector3(5, 15, 5), 5, 3);

		m_forces->add(mover->m_particle, m_gravity);
		m_forces->add(mover->m_particle, mover->m_anchorSpring);
	}

	~MoverConnection();
	cyclone::ParticleGravity *m_gravity {};
	cyclone::ParticleForceRegistry *m_forces;

	void update(float duration);
	void draw(int shadow);
	void drawAnchor(int shadow, Mover *mover);
};
