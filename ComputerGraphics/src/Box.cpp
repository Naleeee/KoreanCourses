#include "Box.hpp"

#include <iostream>

void Box::render(int shadow)
{
	GLfloat mat[16];
	body->getGLTransform(mat);
	if (shadow)
		glColor4f(0.2f, 0.2f, .2f, 0.5f);
	else if (body->getAwake())
		glColor3f(0.7f, 0.7f, 1.0f);
	else if (!body->getAwake())
		glColor3f(1.0f, 0.7f, 0.7f);
	glPushMatrix();
	glMultMatrixf(mat);
	glScalef(halfSize.x * 2, halfSize.y * 2, halfSize.z * 2);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void Box::setState(const cyclone::Vector3 &position, const cyclone::Quaternion &orientation,
				   const cyclone::Vector3 &extents, const cyclone::Vector3 &velocity)
{
	body->setPosition(position);
	body->setOrientation(orientation);
	body->setVelocity(velocity);
	body->setRotation(cyclone::Vector3(0, 0, 0));
	halfSize = extents;												  //size info
	cyclone::real mass = halfSize.x * halfSize.y * halfSize.z * 2.0f; //automatically set the mass
	body->setMass(mass);
	cyclone::Matrix3 tensor;
	tensor.setBlockInertiaTensor(halfSize, mass); //Inertia tensor matrix
	body->setInertiaTensor(tensor);
	body->setLinearDamping(0.95f); //Set the damping for linear and angular motion
	body->setAngularDamping(0.8f);
	body->clearAccumulators();
	body->setAcceleration(0, -10.0f, 0); //Set the gravity
	body->setAwake();
	// body->setCanSleep(true);
	body->calculateDerivedData();
}
