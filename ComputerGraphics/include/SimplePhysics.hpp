#pragma once

#include "Box.hpp"
#include "Sphere.hpp"
#include "body.h"
#include "collide_fine.h"
#include "contacts.h"

#include <vector>

class SimplePhysics {
public:
	cyclone::Contact *contacts;
	cyclone::CollisionData *cData;
	cyclone::ContactResolver *resolver;
	std::vector<Box *> boxData;		  // a set of boxes
	std::vector<Sphere *> sphereData; // a set of boxes
	int maxContacts = 100;

	SimplePhysics()
	{
		std::cout << "[KNEELS] Init" << std::endl;
		// Row 1
		boxData.push_back(new Box(cyclone::Vector3(0, 7, 50), cyclone::Vector3(5, 15, 5)));
		// Row 2
		boxData.push_back(new Box(cyclone::Vector3(4, 7, 58), cyclone::Vector3(5, 15, 5)));
		boxData.push_back(new Box(cyclone::Vector3(-4, 7, 58), cyclone::Vector3(5, 15, 5)));
		// Row 3
		boxData.push_back(new Box(cyclone::Vector3(0, 7, 66), cyclone::Vector3(5, 15, 5)));
		boxData.push_back(new Box(cyclone::Vector3(8, 7, 66), cyclone::Vector3(5, 15, 5)));
		boxData.push_back(new Box(cyclone::Vector3(-8, 7, 66), cyclone::Vector3(5, 15, 5)));
		// Row 4
		boxData.push_back(new Box(cyclone::Vector3(12, 7, 72), cyclone::Vector3(5, 15, 5)));
		boxData.push_back(new Box(cyclone::Vector3(4, 7, 72), cyclone::Vector3(5, 15, 5)));
		boxData.push_back(new Box(cyclone::Vector3(-4, 7, 72), cyclone::Vector3(5, 15, 5)));
		boxData.push_back(new Box(cyclone::Vector3(-12, 7, 72), cyclone::Vector3(5, 15, 5)));

		std::cout << "[BALL] Init" << std::endl;
		sphereData.push_back(new Sphere(cyclone::Vector3(0, 6, -80), 4));
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
	void checkEdgesBox(cyclone::CollisionBox *entity);
	void checkEdgesSphere(cyclone::CollisionSphere *entity);
};
