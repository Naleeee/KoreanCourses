#include "MyContact.hpp"
using namespace cyclone;
MyGroundContact::MyGroundContact() { }
MyGroundContact::~MyGroundContact() { }
void MyGroundContact::init(cyclone::Particle *p, double size)
{
	if (p)
		particles.push_back(p);
	this->size = size;
}

unsigned MyGroundContact::addContact(cyclone::ParticleContact *contact, unsigned limit) const
{
	unsigned count = 0;
	for (int i = 0; i < particles.size(); i++) {
		cyclone::Particle *p = particles[i];
		cyclone::real x = p->getPosition().x;
		cyclone::real y = p->getPosition().y;
		if (y < 0) {
			contact->contactNormal = cyclone::Vector3(0, 1, 0);
			contact->particle[0] = p;
			contact->particle[1] = NULL;
			contact->penetration = size - (y - x);
			contact->restitution = 1.0;
			count++;
		}
		//Detect collision (Consider particle’s size)
		//if there is a collision
		// 1. contact->contctNormal = ?
		//set the two particles
		// 2. contact->particles[0] = p;
		// contact->particles[1] = NULL; //why? floor is static
		//how much interpenetrate?
		// 3. contact->penetration = ?
		// 4. contact->restitution = 1.0
		// 5. count++
		if (count >= limit)
			return count;
	}
	return count;
}
