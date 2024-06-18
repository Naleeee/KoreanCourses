#include "Sphere.hpp"

#include "body.h"

void Sphere::render(int shadow)
{
	cyclone::Vector3 position;
	body->getPosition(&position);
	if (shadow)
		glColor3f(0.1f, 0.1f, 0.1f);
	else
		glColor3f(1.0, 0, 0);

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(this->radius, 30, 30);
	glPopMatrix();
}

void Sphere::setState(const cyclone::Vector3 &position, const cyclone::Vector3 &velocity)
{
	body->setPosition(position);
	body->setVelocity(velocity);
	body->setMass(40.0f);
	body->setLinearDamping(0.7f);
	// body->setAngularDamping(0.7f);
	body->setAcceleration(0.0f, -10.0f, 0.0f);
	body->setAwake();
	// body->setCanSleep(true);
	body->calculateDerivedData();
}
