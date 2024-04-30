#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <core.h>
#include <particle.h>
#include <pfgen.h>

namespace cyclone {
	class MyParticleBuoyancy : public cyclone::ParticleForceGenerator {
	public:
		cyclone::real maxDepth;
		cyclone::real volume;
		cyclone::real waterHeight;
		cyclone::real liquidDensity;

		MyParticleBuoyancy() = default;
		MyParticleBuoyancy(cyclone::real maxDepth, cyclone::real volume, cyclone::real waterHeight,
						   cyclone::real liquidDensity);
		MyParticleBuoyancy(MyParticleBuoyancy &&) = default;
		MyParticleBuoyancy(const MyParticleBuoyancy &) = default;
		MyParticleBuoyancy &operator=(MyParticleBuoyancy &&) = default;
		MyParticleBuoyancy &operator=(const MyParticleBuoyancy &) = default;
		~MyParticleBuoyancy() = default;

		void updateForce(cyclone::Particle *particle, cyclone::real duration);

	private:
	};
} // namespace cyclone
