#include "MyContact.hpp"

#include <iostream>

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
		if (y < size) {
			std::cout << "Collide on GROUND" << std::endl;
			contact->contactNormal = cyclone::Vector3(0, 1, 0);
			contact->particle[0] = p;
			contact->particle[1] = NULL;
			contact->penetration = size - y;
			contact->restitution = 1.0;
			count++;
		}
		if (count >= limit)
			return count;
	}
	return count;
}
