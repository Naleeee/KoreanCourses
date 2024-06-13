#pragma once

#include "MyAnchorSpring.h"
#include "MyParticleBuoyancy.hpp"
#include "MySpring.h"
#include "body.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <core.h>
#include <iostream>
#include <particle.h>
#include <pfgen.h>

class Mover {
public:
	float size {};
	// cyclone::Particle *m_particle {};
	cyclone::ParticleGravity *m_gravity {};
	cyclone::ParticleDrag *m_drag {};
	cyclone::ParticleForceRegistry *m_forces {};
	cyclone::MySpring *m_spring {};
	cyclone::MyAnchoredSpring *m_anchorSpring {};
	cyclone::MyParticleBuoyancy *m_particleBuoyancy {};
	cyclone::Quaternion orientation;
	cyclone::Matrix4 transformMatrix;
	cyclone::Vector3 rotation;			   //Angular velocity
	cyclone::Matrix3 inverseInertiaMatrix; //Inverse of local Inertia matrix
	cyclone::Vector3 torqueAccum;		   //Torque
	cyclone::Matrix3 inverseInertiaTensorWorld;
	cyclone::RigidBody *rb;
	cyclone::Vector3 halfSize;

	Mover(cyclone::Vector3 pos, float size)
	{
		this->size = size;
		rb = new cyclone::RigidBody();
		// m_particle = new cyclone::Particle();
		//
		// m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
		// m_drag = new cyclone::ParticleDrag(0.1, 0.01);
		//
		m_forces = new cyclone::ParticleForceRegistry();

		// m_forces->add(m_particle, m_gravity);
		// m_forces->add(m_particle, m_drag);

		// m_spring = new cyclone::MySpring(m_particle, 20, 1);
		// m_anchorSpring = new cyclone::MyAnchoredSpring(new cyclone::Vector3(5, 15, 5), 5, 3);

		// m_particle->setPosition(pos);
		// m_particle->setVelocity(0.0f, 0.0f, 0.0f);
		// m_particle->setMass(5.0f);					   // mass
		// m_particle->setDamping(0.7f);				   // damping
		// m_particle->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc

		//Inverse of Local Inertia Matrix
		cyclone::Matrix3 inertiaMatrix;
		inertiaMatrix.setBlockInertiaTensor(cyclone::Vector3(1, 1, 1), 3.0f);
		inverseInertiaMatrix = inertiaMatrix.inverse();

		//Convert to 3x3 matrix from mover’s quaternion : use setOrientation()
		cyclone::Matrix3 orientationMatrix;
		orientationMatrix.setOrientation(orientation); //Quaternion->matrix

		cyclone::Matrix3 TransposeOrientationMatrix =
			orientationMatrix.transpose(); //transpose of orintationMatrix

		inverseInertiaTensorWorld =
			orientationMatrix * inverseInertiaMatrix * TransposeOrientationMatrix;
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
	void getGLTransform(float *matrix);
	void addTorque(cyclone::Vector3 force, cyclone::Vector3 point); //Apply Force on Point
	void setState(const cyclone::Vector3 &position, const cyclone::Quaternion &orientation,
				  const cyclone::Vector3 &extents, const cyclone::Vector3 &velocity);
};
