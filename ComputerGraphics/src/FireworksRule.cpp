#include "FireworksRule.hpp"

void FireworksRule::setParameters(
	unsigned type, cyclone::real minAge, cyclone::real maxAge, const cyclone::Vector3 &minVelocity,
	const cyclone::Vector3 &maxVelocity, cyclone::real xMin, cyclone::real xMax, cyclone::real yMin,
	cyclone::real yMax, cyclone::real zMin, cyclone::real zMax, const cyclone::Vector3 &minColor,
	const cyclone::Vector3 &maxColor, cyclone::real damping, int count)
{
	this->type = type;
	this->minAge = minAge;
	this->maxAge = maxAge;
	this->minVelocity = minVelocity;
	this->maxVelocity = maxVelocity;
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
	this->zMin = zMin;
	this->zMax = zMax;
	this->minColor = minColor;
	this->maxColor = maxColor;
	this->damping = damping;
	this->payloadCount = count;
}
