#pragma once

#include "FireworksRule.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <core.h>
#include <deque>
#include <particle.h>
#include <pfgen.h>

class Fire {
public:
	Fire(const Fire &) = default;
	Fire(Fire &&) = delete;
	Fire &operator=(const Fire &) = default;
	Fire &operator=(Fire &&) = delete;
	Fire(int type); //Fire type (0=Init Fire, 1=Child fire)
	Fire(Fire *);	//Fire type (0=Init Fire, 1=Child fire)
	~Fire() = default;

	float m_size; // Fire size (0.5)
	int m_type;	  //Fire type (set in the constructor)
	float m_age;  //Fire’s current age
	cyclone::Particle *m_particle;
	cyclone::ParticleForceRegistry *m_forces;
	FireworksRule *m_rule;					//Which rule this particle is influenced by?
	cyclone::Vector3 m_color;				//Fire color
	std::deque<cyclone::Vector3> m_history; //history saving

	bool update(float duration); //return bool
	void draw(int shadow);
	void drawHistory();
	void setRule(FireworksRule *r); //set a particular rule
	void putHistory();				//Save current position in the m_history
};
