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
	cyclone::real xMin;			  //minimum x position of Fire
	cyclone::real xMax;			  //maximum x position of Fire
	cyclone::real yMin;			  //minimum y position of Fire
	cyclone::real yMax;			  //maximum y position of Fire
	cyclone::real zMin;			  //minimum z position of Fire
	cyclone::real zMax;			  //maximum z position of Fire
	cyclone::Vector3 minColor;	  //minimum color of Fire
	cyclone::Vector3 maxColor;	  //maximum color of Fire
	cyclone::real damping {};	  //Fire’s damping
	unsigned payloadCount {};	  //how many Child Fires are spawned?

	void setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge,
					   const cyclone::Vector3 &minVelocity, const cyclone::Vector3 &maxVelocity,
					   cyclone::real xMin, cyclone::real xMax, cyclone::real yMin,
					   cyclone::real yMax, cyclone::real zMin, cyclone::real zMax,
					   const cyclone::Vector3 &minColor, const cyclone::Vector3 &maxColor,
					   cyclone::real damping, int count);
};
