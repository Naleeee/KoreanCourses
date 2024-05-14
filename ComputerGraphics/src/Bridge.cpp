#include "Bridge.hpp"

#include "particle.h"
#include "plinks.h"

#include <FL/glut.H>
#include <GL/gl.h>

Bridge::Bridge()
{
	cyclone::Vector3 position = *new cyclone::Vector3(0.0f, 10.0f, 10.0f);
	m_particleWorld = new cyclone::ParticleWorld(particleCount * 10);

	for (int i = 0; i < particleCount; i++) {
		cyclone::Particle *particle = new cyclone::Particle();
		particle->setPosition(position);
		particle->setVelocity(0, 0, 0);
		particle->setDamping(0.8f);
		particle->setMass(5.0f);
		particle->setAcceleration(cyclone::Vector3::GRAVITY);
		particle->clearAccumulator();

		m_particleArray.push_back(particle);

		m_particleWorld->getParticles().push_back(m_particleArray[i]);
		if (position.x == 10 && position.z == 10) {
			position.x = 0;
			position.z += 2;
		} else {
			position.x += 2;
		}
	}

	int currentParticle = 0;
	for (int i = 0; i < cableCount; i++, currentParticle++) {
		cyclone::ParticleCable *cable = new cyclone::ParticleCable();
		cable->particle[0] = m_particleArray[currentParticle];
		particleCount++;
		cable->particle[1] = m_particleArray[currentParticle + 1];
		cable->maxLength = 3.0f;
		cable->restitution = 0.1f;

		cables.push_back(cable);

		m_particleWorld->getContactGenerators().push_back(cables[i]);
		if (currentParticle == 4) {
			currentParticle++;
		}
	}

	currentParticle = 0;
	for (int i = 0; i < rodCount; i++, currentParticle++) {
		cyclone::ParticleRod *rod = new cyclone::ParticleRod();
		rod->particle[0] = m_particleArray[currentParticle];
		particleCount++;
		rod->particle[1] = m_particleArray[currentParticle + rodCount];
		rod->length = 2;

		rods.push_back(rod);

		m_particleWorld->getContactGenerators().push_back(rods[i]);
	}

	currentParticle = 0;
	int maxLength = 3.0f;
	bool lowering = true;
	for (int i = 0; i < supportCount; i++, currentParticle++) {
		cyclone::ParticleCableConstraint *support = new cyclone::ParticleCableConstraint();
		support->particle = m_particleArray[currentParticle];
		cyclone::Vector3 anchor =
			*new cyclone::Vector3(m_particleArray[currentParticle]->getPosition() +
								  *new cyclone::Vector3(0.0f, 3.0f, 0.0f));
		support->anchor = anchor;
		support->maxLength = maxLength;
		support->restitution = 0.5f;

		supports.push_back(support);

		m_particleWorld->getContactGenerators().push_back(supports[i]);
		if (lowering && maxLength == 5) {
			lowering = false;
		} else if (!lowering && maxLength == 3) {
			lowering = true;
		} else if (lowering) {
			maxLength += 1;
		} else {
			maxLength -= 1;
		}
	}
}

void Bridge::update(float duration)
{
	m_particleWorld->runPhysics(duration);
}

void Bridge::draw(int shadow)
{
	glLineWidth(3.0);

	if (shadow)
		glColor3f(0.2, 0.2, 0.2);
	else
		glColor3f(0.8, 0, 0);

	int name = 1;
	cyclone::ParticleWorld::Particles &particles = m_particleWorld->getParticles();
	for (cyclone::ParticleWorld::Particles::iterator p = particles.begin(); p != particles.end();
		 p++) {
		cyclone::Particle *particle = *p;
		const cyclone::Vector3 &pos = particle->getPosition();
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		if (!shadow)
			glLoadName(name);
		glutSolidSphere(0.2f, 20, 10);
		glPopMatrix();
		name++;
	}

	glBegin(GL_LINES);

	if (shadow)
		glColor3f(0.2, 0.2, 0.2);
	else
		glColor3f(0, 0, 1);
	for (unsigned i = 0; i < rodCount; i++) {
		cyclone::Particle **particles = rods[i]->particle;
		const cyclone::Vector3 &p0 = particles[0]->getPosition();
		const cyclone::Vector3 &p1 = particles[1]->getPosition();
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
	}

	if (shadow)
		glColor3f(0.2, 0.2, 0.2);
	else
		glColor3f(0, 1, 0);
	for (unsigned i = 0; i < cableCount; i++) {
		cyclone::Particle **particles = cables[i]->particle;
		const cyclone::Vector3 &p0 = particles[0]->getPosition();
		const cyclone::Vector3 &p1 = particles[1]->getPosition();
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
	}

	if (shadow)
		glColor3f(0.2, 0.2, 0.2);
	else
		glColor3f(0.7f, 0.7f, 0.7f);
	for (unsigned i = 0; i < supportCount; i++) {
		const cyclone::Vector3 &p0 = supports[i]->particle->getPosition();
		const cyclone::Vector3 &p1 = supports[i]->anchor;
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
	}
	glEnd();

	glLineWidth(1.0);
}
