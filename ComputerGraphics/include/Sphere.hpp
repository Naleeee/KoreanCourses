#pragma once

#include "collide_fine.h"

#include <FL/glut.H>
#include <GL/gl.h>

class Sphere : public cyclone::CollisionSphere {
public:
	Sphere()
	{
		body = new cyclone::RigidBody();
	}
	~Sphere()
	{
		delete body;
	};

	void render(int shadow);
};
