#pragma once

#include "body.h"
#include "collide_fine.h"

#include <FL/glut.H>
#include <GL/gl.h>
#include <iostream>

class Sphere : public cyclone::CollisionSphere {
public:
	cyclone::Vector3 initPosition;

	Sphere(cyclone::Vector3 position, int radius)
	{
		std::cout << "[SPHERE] Creation" << std::endl;
		this->radius = radius;
		body = new cyclone::RigidBody();
		initPosition = position;

		setState(position, cyclone::Vector3(0.0f, 0.0f, 0.0f));
	}

	~Sphere()
	{
		delete body;
	};

	void render(int shadow);
	void setState(const cyclone::Vector3 &position, const cyclone::Vector3 &velocity);
};
