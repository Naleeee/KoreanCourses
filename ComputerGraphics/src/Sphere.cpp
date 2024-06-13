#include "Sphere.hpp"

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
	glutSolidSphere(1.0f, 30, 30);
	glPopMatrix();
}
