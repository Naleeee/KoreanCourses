#pragma once

#include "body.h"
#include "collide_fine.h"

#include <FL/glut.H>
#include <GL/gl.h>
#include <iostream>

class Box : public cyclone::CollisionBox {
public:
	cyclone::Vector3 initPosition;

	Box(cyclone::Vector3 position, cyclone::Vector3 size)
	{
		std::cout << "[BOX] Creation" << std::endl;
		halfSize = cyclone::Vector3(size.x / 2, size.y / 2, size.z / 2);
		// std::cout << "[BOX] Size:" << halfSize.x << "|" << halfSize.y << "|" << halfSize.z << "|"
		// 		  << std::endl;
		// std::cout << "[BOX] Position:" << position.x << "|" << position.y << "|" << position.z
		// 		  << "|" << std::endl;
		body = new cyclone::RigidBody();
		initPosition = position;

		setState(position, cyclone::Quaternion(0, 0, 0, 0), halfSize,
				 cyclone::Vector3(0.0f, 0.0f, 0.0f));
	}

	~Box()
	{
		delete body;
	};

	void render(int shadow);
	void setState(const cyclone::Vector3 &position, const cyclone::Quaternion &orientation,
				  const cyclone::Vector3 &extents, const cyclone::Vector3 &velocity);
};
