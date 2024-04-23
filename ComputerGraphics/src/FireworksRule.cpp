#include "FireworksRule.hpp"

void FireworksRule::setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge,
								  const cyclone::Vector3 &minVelocity,
								  const cyclone::Vector3 &maxVelocity, cyclone::real damping,
								  int count)
{
	this->type = type;
	this->minAge = minAge;
	this->maxAge = maxAge;
	this->minVelocity = minVelocity;
	this->maxVelocity = maxVelocity;
	this->damping = damping;
	this->payloadCount = count;
}
