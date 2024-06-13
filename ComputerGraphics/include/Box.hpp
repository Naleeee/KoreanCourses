#pragma once

#include "body.h"
#include "collide_fine.h"

#include <FL/glut.H>
#include <GL/gl.h>
#include <iostream>

class Box : public cyclone::CollisionBox {
public:
	Box(cyclone::Vector3 position, cyclone::Vector3 size)
	{
		halfSize = cyclone::Vector3(size.x / 2, size.y / 2, size.z / 2);
		std::cout << halfSize.x << "|" << halfSize.y << "|" << halfSize.z << "|" << std::endl;
		// std::cout << "Box Creation" << std::endl;
		body = new cyclone::RigidBody();

		setState(cyclone::Vector3(0.0f, 10.0f, 0.0f), cyclone::Quaternion(0, 0, 0, 0), halfSize,
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
