#include "Mover.hpp"

void Mover::update(float duration)
{
	m_forces->updateForces(duration);
	m_particle->integrate(duration);
	// m_spring->updateForce(m_particle, duration);
	// m_anchorSpring->updateForce(m_particle, duration);
	// checkCollide();
	// m_particleBuoyancy->updateForce(m_particle, duration);
	checkEdges();
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
	m_particle->setPosition(pos); // initial posx
	m_particle->setVelocity(0.0f, 0.0f, 0.0f);
	// m_particle->setDamping(0.9f);
	m_particle->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc
	// m_particle->setMass(10.0f);					   // 1.0kg-mostly blast damage
}

void Mover::checkEdges()
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
	m_particle->setPosition(pos);
	m_particle->setVelocity(vel);
}

void Mover::checkCollide()
{
	cyclone::Vector3 p1 = *new cyclone::Vector3(20.0f, 0.0f, -25.0f);
	cyclone::Vector3 p2 = *new cyclone::Vector3(20.0f, 0.0f, 25.0f);
	cyclone::Vector3 p3 = *new cyclone::Vector3(-20.0f, 30.0f, 25.0f);
	cyclone::Vector3 p4 = *new cyclone::Vector3(-20.0f, 30.0f, -25.0f);

	cyclone::Vector3 pos;
	m_particle->getPosition(&pos);
	cyclone::Vector3 v1 = p2 - p1;
	cyclone::Vector3 v2 = p3 - p1;
	v1.normalise();
	v2.normalise();

	auto n = v2.cross(v1);

	float d = -n.dot(p1);

	float checkOnPlane = n.x * pos.x + n.x * pos.y + n.y * pos.z + d;

	if (checkOnPlane > -0.5 && checkOnPlane < 0.5) {
		m_particle->setPosition(pos + n * size);

		auto vel = m_particle->getVelocity();
		auto tmp = 2 * (vel.dot(n));
		m_particle->setVelocity(vel - n * tmp);
	}
}

void Mover::setConnection(Mover *a)
{
	m_spring = new cyclone::MySpring(a->m_particle, 20.0f, 3);
}

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
		glColor3f(0.2f, 0.2f, 0.2f);
	} else {
		glColor3f(1, 0., 0);
	}
	glPushMatrix();
	glMultMatrixf(mat);
	glutSolidCube(size * 2);
	glPopMatrix();
}
