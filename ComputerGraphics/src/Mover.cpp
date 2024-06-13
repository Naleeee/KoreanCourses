#include "Mover.hpp"

#include "particle.h"
#include "pfgen.h"

#include <iostream>

void Mover::update(float duration)
{
	cyclone::Vector3 angularAcceleration = inverseInertiaTensorWorld.transform(torqueAccum);
	// cyclone::Vector3 angularAcceleration(0, 0.1, 0);
	rotation.addScaledVector(angularAcceleration, duration);
	double angularDamping = 0.9;
	rotation *= real_pow(angularDamping, duration); //𝛚=𝛚∙𝒅𝒂𝒎𝒑𝒊𝒏𝒈 (Multiply damping)
	orientation.addScaledVector(rotation, duration);
	orientation.normalise(); // normalize quaternion
	transformMatrix.setOrientationAndPos(orientation, rb->getPosition());

	// m_forces->updateForces(duration);
	// m_particle->integrate(duration);
	// m_spring->updateForce(m_particle, duration);
	// m_anchorSpring->updateForce(m_particle, duration);
	// checkCollide();
	// m_particleBuoyancy->updateForce(m_particle, duration);

	if (rb) {
		rb->integrate(duration);
		rb->calculateDerivedData(); //re-calculate the transformation matrix
	}
	checkEdges();
	torqueAccum.clear();
}

// void Mover::draw(int shadow)
// {
// 	cyclone::Vector3 position;
// 	m_particle->getPosition(&position);
// 	if (shadow)
// 		glColor3f(0.1f, 0.1f, 0.1f);
// 	else
// 		glColor3f(1.0, 0, 0);
//
// 	glPushMatrix();
// 	glTranslatef(position.x, position.y, position.z);
// 	glutSolidSphere(size, 30, 30);
// 	glPopMatrix();
// }

void Mover::resetParameters(cyclone::Vector3 pos)
{
	rb->setPosition(pos); // initial posx
	rb->setVelocity(0.0f, 0.0f, 0.0f);
	// m_particle->setDamping(0.9f);
	rb->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc
	// m_particle->setMass(10.0f);					   // 1.0kg-mostly blast damage
}

void Mover::checkEdges()
{
	cyclone::Vector3 pos = rb->getPosition();
	cyclone::Vector3 vel = rb->getVelocity();

	if (pos.x >= 100 - size / 2) {
		pos.x = 100 - size / 2;
		vel.x *= -1;
	} else if (pos.x <= -100 + size / 2) {
		pos.x = -100 + size / 2;
		vel.x *= -1;
	}
	// if (pos.y <= size / 2) {
	// 	pos.y = size / 2;
	// 	vel.y *= -1;
	// }
	if (pos.z >= 100 - size / 2) {
		pos.z = 100 - size / 2;
		vel.z *= -1;
	} else if (pos.z <= -100 + size / 2) {
		pos.z = -100 + size / 2;
		vel.z *= -1;
	}
	rb->setPosition(pos);
	rb->setVelocity(vel);
}

void Mover::checkCollide()
{
	cyclone::Vector3 p1 = *new cyclone::Vector3(20.0f, 0.0f, -25.0f);
	cyclone::Vector3 p2 = *new cyclone::Vector3(20.0f, 0.0f, 25.0f);
	cyclone::Vector3 p3 = *new cyclone::Vector3(-20.0f, 30.0f, 25.0f);
	cyclone::Vector3 p4 = *new cyclone::Vector3(-20.0f, 30.0f, -25.0f);

	cyclone::Vector3 pos;
	rb->getPosition(&pos);
	cyclone::Vector3 v1 = p2 - p1;
	cyclone::Vector3 v2 = p3 - p1;
	v1.normalise();
	v2.normalise();

	auto n = v2.cross(v1);

	float d = -n.dot(p1);

	float checkOnPlane = n.x * pos.x + n.x * pos.y + n.y * pos.z + d;

	if (checkOnPlane > -0.5 && checkOnPlane < 0.5) {
		rb->setPosition(pos + n * size);

		auto vel = rb->getVelocity();
		auto tmp = 2 * (vel.dot(n));
		rb->setVelocity(vel - n * tmp);
	}
}

// void Mover::setConnection(Mover *a)
// {
// 	m_spring = new cyclone::MySpring(a->rb, 20.0f, 3);
// }

void Mover::getGLTransform(float matrix[16])
{
	matrix[0] = (float)transformMatrix.data[0];
	matrix[1] = (float)transformMatrix.data[4];
	matrix[2] = (float)transformMatrix.data[8];
	matrix[3] = 0;
	matrix[4] = (float)transformMatrix.data[1];
	matrix[5] = (float)transformMatrix.data[5];
	matrix[6] = (float)transformMatrix.data[9];
	matrix[7] = 0;
	matrix[8] = (float)transformMatrix.data[2];
	matrix[9] = (float)transformMatrix.data[6];
	matrix[10] = (float)transformMatrix.data[10];
	matrix[11] = 0;
	matrix[12] = (float)transformMatrix.data[3];
	matrix[13] = (float)transformMatrix.data[7];
	matrix[14] = (float)transformMatrix.data[11];
	matrix[15] = 1;
}

void Mover::draw(int shadow)
{
	// Get the OpenGL transformation
	GLfloat mat[16];
	getGLTransform(mat);
	if (!shadow) {
		glPushMatrix();
		glMultMatrixf(mat);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 10, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0.1, 0);
		glVertex3f(10, 0.1, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0.1, 0);
		glVertex3f(0, 0.1, 10);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0f);
	}
	if (shadow) {
		glColor4f(0.2f, 0.2f, .2f, 0.5f);
	} else {
		glColor3f(0.7f, 0.1f, .1f);
	}
	glPushMatrix();
	glMultMatrixf(mat);
	// glScalef(2, 1, 1);
	// glutSolidCube(size * 2);
	glScalef(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void Mover::addTorque(cyclone::Vector3 force, cyclone::Vector3 point)
{
	cyclone::Vector3 d = point - rb->getPosition();
	torqueAccum = d.cross(force);
}

void Mover::setState(const cyclone::Vector3 &position, const cyclone::Quaternion &orientation,
					 const cyclone::Vector3 &extents, const cyclone::Vector3 &velocity)
{
	rb->setPosition(position);
	rb->setOrientation(orientation);
	rb->setVelocity(velocity);
	rb->setRotation(cyclone::Vector3(0, 0, 0));
	halfSize = extents;												  //size info
	cyclone::real mass = halfSize.x * halfSize.y * halfSize.z * 2.0f; //automatically set the mass
	rb->setMass(mass);
	cyclone::Matrix3 tensor;
	tensor.setBlockInertiaTensor(halfSize, mass); //Inertia tensor matrix
	rb->setInertiaTensor(tensor);
	rb->setLinearDamping(0.95f); //Set the damping for linear and angular motion
	rb->setAngularDamping(0.8f);
	rb->clearAccumulators();
	rb->setAcceleration(0, -10.0f, 0); //Set the gravity
	rb->setAwake();
	rb->setCanSleep(true);
	//Calculate the transformation matrix and convert to world inertia tensor matrix
	rb->calculateDerivedData();
}
