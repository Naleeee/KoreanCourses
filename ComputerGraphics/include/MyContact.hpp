#include "particle.h"
#include "pcontacts.h"

#include <vector>

namespace cyclone {
	class MyGroundContact : public cyclone::ParticleContactGenerator {
		std::vector<cyclone::Particle *> particles;
		double size;

	public:
		MyGroundContact();
		~MyGroundContact();
		void init(cyclone::Particle *p, double size);
		virtual unsigned addContact(cyclone::ParticleContact *contact, unsigned limit) const;
	};
} // namespace cyclone
