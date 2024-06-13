#pragma once

#include "Box.hpp"
#include "body.h"
#include "collide_fine.h"
#include "contacts.h"

#include <vector>

class SimplePhysics {
public:
	cyclone::Contact *contacts;
	cyclone::CollisionData *cData;
	cyclone::ContactResolver *resolver;
	std::vector<Box *> boxData; // a set of boxes
	int maxContacts = 100;

	SimplePhysics()
	{
		std::cout << "Init simple physics" << std::endl;
		boxData.push_back(new Box(cyclone::Vector3(10, 10, 10), cyclone::Vector3(3, 5, 4)));
		boxData.push_back(new Box(cyclone::Vector3(2, 40, -2), cyclone::Vector3(5, 4, 8)));
		boxData.push_back(new Box(cyclone::Vector3(0, 5, 0), cyclone::Vector3(4, 4, 4)));
		boxData.push_back(new Box(cyclone::Vector3(0, 15, 5), cyclone::Vector3(10, 3, 5)));
		contacts = new cyclone::Contact[maxContacts];
		cData = new cyclone::CollisionData();
		//Put contact array into the CollisionData
		cData->contactArray = contacts;
		//init. the contactCount
		cData->contactCount = 0;
		//init the solver (must set the number of iterations)
		resolver = new cyclone::ContactResolver(maxContacts * 2);
	}
	~SimplePhysics();
	void reset();
	void generateContacts(); //Check contacts here
	void update(cyclone::real duration);
	void render(int shadow);
};
