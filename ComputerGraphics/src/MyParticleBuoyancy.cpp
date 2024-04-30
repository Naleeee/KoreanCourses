#include "MyParticleBuoyancy.hpp"

cyclone::MyParticleBuoyancy::MyParticleBuoyancy(cyclone::real maxDepth, cyclone::real volume,
												cyclone::real waterHeight,
												cyclone::real liquidDensity)
	: maxDepth(maxDepth)
	, volume(volume)
	, waterHeight(waterHeight)
	, liquidDensity(liquidDensity)
{
}

void cyclone::MyParticleBuoyancy::updateForce(cyclone::Particle *particle, cyclone::real duration)
{
	cyclone::Vector3 force;
	cyclone::Vector3 pos = particle->getPosition();

	if (pos.y - maxDepth > waterHeight) {
		force = *new cyclone::Vector3(0, -9.8, 0);
	} else if (pos.y + maxDepth < waterHeight) {
		force = *new cyclone::Vector3(0, this->volume * this->liquidDensity, 0);
	} else {
		int d = (pos.y - waterHeight - maxDepth) / (2 * maxDepth);
		force = *new cyclone::Vector3(0, d * this->volume * this->liquidDensity, 0);
	}

	particle->addForce(force);
}
