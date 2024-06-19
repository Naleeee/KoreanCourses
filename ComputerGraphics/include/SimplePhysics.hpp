#pragma once

#include "Box.hpp"
#include "Sphere.hpp"
#include "body.h"
#include "collide_fine.h"
#include "contacts.h"

#include <tuple>
#include <vector>

class SimplePhysics {
public:
	cyclone::Contact *contacts;
	cyclone::CollisionData *cData;
	cyclone::ContactResolver *resolver;
	std::vector<std::tuple<Box *, bool>> boxData;
	std::vector<Sphere *> sphereData;
	int maxContacts = 100;

	SimplePhysics()
	{
		// Row 1
		boxData.emplace_back(new Box(cyclone::Vector3(0, 7, 50), cyclone::Vector3(5, 15, 5)),
							 false);
		// Row 2
		boxData.emplace_back(new Box(cyclone::Vector3(4, 7, 58), cyclone::Vector3(5, 15, 5)),
							 false);
		boxData.emplace_back(new Box(cyclone::Vector3(-4, 7, 58), cyclone::Vector3(5, 15, 5)),
							 false);
		// Row 3
		boxData.emplace_back(new Box(cyclone::Vector3(0, 7, 66), cyclone::Vector3(5, 15, 5)),
							 false);
		boxData.emplace_back(new Box(cyclone::Vector3(8, 7, 66), cyclone::Vector3(5, 15, 5)),
							 false);
		boxData.emplace_back(new Box(cyclone::Vector3(-8, 7, 66), cyclone::Vector3(5, 15, 5)),
							 false);
		// Row 4
		boxData.emplace_back(new Box(cyclone::Vector3(12, 7, 72), cyclone::Vector3(5, 15, 5)),
							 false);
		boxData.emplace_back(new Box(cyclone::Vector3(4, 7, 72), cyclone::Vector3(5, 15, 5)),
							 false);
		boxData.emplace_back(new Box(cyclone::Vector3(-4, 7, 72), cyclone::Vector3(5, 15, 5)),
							 false);
		boxData.emplace_back(new Box(cyclone::Vector3(-12, 7, 72), cyclone::Vector3(5, 15, 5)),
							 false);

		sphereData.push_back(new Sphere(cyclone::Vector3(0, 6, -80), 4));
		contacts = new cyclone::Contact[maxContacts];
		cData = new cyclone::CollisionData();
		cData->contactArray = contacts;
		cData->contactCount = 0;
		resolver = new cyclone::ContactResolver(maxContacts * 2);
	}
	~SimplePhysics();
	void reset(bool resetKeels, bool resetBall);
	void generateContacts(); //Check contacts here
	int update(cyclone::real duration);
	void render(int shadow);
	void checkEdgesBox(cyclone::CollisionBox *entity);
	void checkEdgesSphere(cyclone::CollisionSphere *entity);
};
