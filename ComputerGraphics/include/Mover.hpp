#pragma once

#include "MyAnchorSpring.h"
#include "MySpring.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <core.h>
#include <particle.h>
#include <pfgen.h>

class Mover {
public:
	float size {};
	cyclone::Particle *m_particle {};
	cyclone::ParticleGravity *m_gravity {};
	cyclone::ParticleDrag *m_drag {};
	cyclone::ParticleForceRegistry *m_forces {};
	cyclone::MySpring *m_spring {};
	cyclone::MyAnchoredSpring *m_anchorSpring {};

	Mover(cyclone::Vector3 pos)
	{
		size = 1.0f;

		m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
		m_drag = new cyclone::ParticleDrag(0.1, 0.01);

		m_forces = new cyclone::ParticleForceRegistry();
		m_particle = new cyclone::Particle();

		m_forces->add(m_particle, m_gravity);
		m_forces->add(m_particle, m_drag);

		// m_anchorSpring = new cyclone::MyAnchoredSpring(new cyclone::Vector3(5, 15, 5), 5, 3);

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

	void update(float duration);
	void draw(int shadow);
	void resetParameters(cyclone::Vector3 pos);
	void checkEdges();
	void checkCollide();
	void stop() { }
	void setConnection(Mover *a);
};
