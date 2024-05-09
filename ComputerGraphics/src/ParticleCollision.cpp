#include "ParticleCollision.hpp"

#include "particle.h"

#include <iostream>

cyclone::ParticleCollision::ParticleCollision(double size)
{
	this->size = size;
}

unsigned cyclone::ParticleCollision::addContact(ParticleContact *contact, unsigned limit) const
{
	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];
	cyclone::Vector3 pos1 = particle[0]->getPosition();
	cyclone::Vector3 pos2 = particle[1]->getPosition();

	cyclone::Vector3 distance = pos2 - pos1;

	auto magnitude = distance.magnitude();

	if (magnitude < size) {
		contact->contactNormal = distance * -1.0f;
		contact->penetration = 1;
		contact->penetration = magnitude - size;
		contact->restitution = 1.0;
		return 1;
	}
	return 0;
}
