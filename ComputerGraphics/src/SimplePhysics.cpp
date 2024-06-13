#include "SimplePhysics.hpp"

void SimplePhysics::generateContacts()
{
	// Set up the collision data structure
	cData->reset(maxContacts);				 //reset the count, left, all pointers
	cData->friction = (cyclone::real)0.1;	 //can change (how slippery it is?)
	cData->restitution = (cyclone::real)0.6; //can change
	cData->tolerance = (cyclone::real)0.1;	 //if distance is less than 0.1, it is collision
	cyclone::CollisionPlane plane;
	plane.direction = cyclone::Vector3(0, 1, 0); //normal
	plane.offset = 0;							 //distance from the origin
	for (Box *box : boxData) {
		// Check for collisions with the ground plane
		if (!cData->hasMoreContacts())
			return;
		cyclone::CollisionDetector::boxAndHalfSpace(*box, plane, cData);
		// Check for collisions with each other box
		for (Box *box2 : boxData) {
			if (box2 == box) {
				continue;
			}
			if (!cData->hasMoreContacts())
				return;
			cyclone::CollisionDetector::boxAndBox(*box, *box2, cData);
		}
	}
}

void SimplePhysics::update(cyclone::real duration)
{
	// std::cout << "SimplePhysics update" << std::endl;
	generateContacts();
	resolver->resolveContacts(cData->contactArray, cData->contactCount, duration);
	for (Box *box : boxData) {
		// Run the physics
		box->body->integrate(duration);
		box->calculateInternals();
	}
}

void SimplePhysics::render(int shadow)
{
	// std::cout << "SimplePhysics render" << std::endl;
	for (Box *box : boxData) {
		// std::cout << "Call render" << std::endl;
		box->render(shadow);
	}
}

void SimplePhysics::reset()
{
	for (Box *box : boxData) {
		box->setState(cyclone::Vector3(0.0f, 20.0f, 0.0f), cyclone::Quaternion(0, 0, 0, 0),
					  box->halfSize, cyclone::Vector3(0.0f, 0.0f, 0.0f));
	}
}
