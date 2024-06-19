#include "SimplePhysics.hpp"

#include "collide_fine.h"

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
	for (auto &[box, isDown] : boxData) {
		checkEdgesBox(box);
		// Check for collisions with the ground plane
		if (!cData->hasMoreContacts())
			return;
		cyclone::CollisionDetector::boxAndHalfSpace(*box, plane, cData);
		// Check for collisions with each other box
		for (auto &[box2, isDown2] : boxData) {
			if (box2 == box) {
				continue;
			}
			if (!cData->hasMoreContacts())
				return;
			cyclone::CollisionDetector::boxAndBox(*box, *box2, cData);
		}
	}

	for (Sphere *sphere : sphereData) {
		checkEdgesSphere(sphere);
		// Check for collisions with the ground plane
		if (!cData->hasMoreContacts())
			return;
		cyclone::CollisionDetector::sphereAndHalfSpace(*sphere, plane, cData);
		// Check for collisions with each other box
		for (auto &[box, isDown] : boxData) {
			if (!cData->hasMoreContacts())
				return;
			cyclone::CollisionDetector::boxAndSphere(*box, *sphere, cData);
		}
	}
}

void SimplePhysics::checkEdgesBox(cyclone::CollisionBox *entity)
{
	cyclone::Vector3 pos = entity->body->getPosition();
	cyclone::Vector3 vel = entity->body->getVelocity();

	if (pos.x >= 30 - entity->halfSize.x) {
		pos.x = 30 - entity->halfSize.x;
		vel.x *= -1;
	} else if (pos.x <= -30 + entity->halfSize.x) {
		pos.x = -30 + entity->halfSize.x;
		vel.x *= -1;
	}
	if (pos.z >= 100 - entity->halfSize.z) {
		pos.z = 100 - entity->halfSize.z;
		vel.z *= -1;
	} else if (pos.z <= -100 + entity->halfSize.z) {
		pos.z = -100 + entity->halfSize.z;
		vel.z *= -1;
	}
	entity->body->setPosition(pos);
	entity->body->setVelocity(vel);
}

void SimplePhysics::checkEdgesSphere(cyclone::CollisionSphere *entity)
{
	cyclone::Vector3 pos = entity->body->getPosition();
	cyclone::Vector3 vel = entity->body->getVelocity();

	if (pos.x >= 30 - entity->radius) {
		pos.x = 30 - entity->radius;
		vel.x *= -1;
	} else if (pos.x <= -30 + entity->radius) {
		pos.x = -30 + entity->radius;
		vel.x *= -1;
	}
	if (pos.z >= 100 - entity->radius) {
		pos.z = 100 - entity->radius;
		vel.z *= -1;
	} else if (pos.z <= -100 + entity->radius) {
		pos.z = -100 + entity->radius;
		vel.z *= -1;
	}
	entity->body->setPosition(pos);
	entity->body->setVelocity(vel);
}

int SimplePhysics::update(cyclone::real duration)
{
	int score = 0;
	generateContacts();
	resolver->resolveContacts(cData->contactArray, cData->contactCount, duration);
	for (auto &[box, isDown] : boxData) {
		// Run the physics
		box->body->integrate(duration);
		box->calculateInternals();
		if (box->body->getPosition().y <= 6 && isDown == 0) {
			isDown = true;
			score++;
		}
	}

	for (Sphere *sphere : sphereData) {
		// Run the physics
		sphere->body->integrate(duration);
		sphere->calculateInternals();
	}

	return score;
}

void SimplePhysics::render(int shadow)
{
	for (auto &[box, isDown] : boxData) {
		box->render(shadow);
	}

	for (Sphere *sphere : sphereData) {
		sphere->render(shadow);
	}
}

void SimplePhysics::reset(bool resetKeels, bool resetBall)
{
	if (resetKeels) {
		for (auto &[box, isDown] : boxData) {
			box->setState(box->initPosition, cyclone::Quaternion(0, 0, 0, 0), box->halfSize,
						  cyclone::Vector3(0.0f, 0.0f, 0.0f));
		}
	}

	if (resetBall) {
		for (Sphere *sphere : sphereData) {
			sphere->setState(sphere->initPosition, cyclone::Vector3(0.0f, 0.0f, 0.0f));
		}
	}
}
