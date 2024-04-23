#pragma once
#include "particle.h"

class FireworksRule {
public:
	FireworksRule() = default;
	FireworksRule(const FireworksRule &) = default;
	FireworksRule(FireworksRule &&) = delete;
	FireworksRule &operator=(const FireworksRule &) = default;
	FireworksRule &operator=(FireworksRule &&) = delete;

	~FireworksRule() = default;

	unsigned type {};			  //Fire type
	cyclone::real minAge {};	  //minimum age of Fire
	cyclone::real maxAge {};	  //maximum age of Fire
	cyclone::Vector3 minVelocity; //minimum velocity of Fire
	cyclone::Vector3 maxVelocity; //maximum velocity of Fire
	cyclone::real damping {};	  //Fire’s damping
	unsigned payloadCount {};	  //how many Child Fires are spawned?

	void setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge,
					   const cyclone::Vector3 &minVelocity, const cyclone::Vector3 &maxVelocity,
					   cyclone::real damping, int count);
};
