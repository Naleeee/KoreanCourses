#include "../include/MyAnchorSpring.h"

// const cyclone::Vector3 *cyclone::MyAnchoredSpring::getAnchor() const
// {
// 	std::cout << "Getter this.anchor: " << this->anchor->x << "/" << this->anchor->y << "/"
// 			  << this->anchor->z << std::endl;
// 	return anchor;
// }
//
// void cyclone::MyAnchoredSpring::updateForce(Particle *p, real duration)
// {
// 	cyclone::Vector3 d = p->getPosition() - *anchor;
// 	cyclone::Vector3 normalised = d;
// 	normalised.normalise();
// 	cyclone::Vector3 force = normalised * -springConstant *
// 							 (d.magnitude() - restLength); //A force that applies to the particles
// 	p->addForce(force);
// }
