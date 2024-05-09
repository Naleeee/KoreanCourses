#include "pcontacts.h"
#include "plinks.h"

namespace cyclone {
	class ParticleCollision : public ParticleLink {
	public:
		double size; //particle size (We assume that two particles have the same time)
	public:
		virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
		ParticleCollision() = delete;
		ParticleCollision(double size);
	};
} // namespace cyclone
