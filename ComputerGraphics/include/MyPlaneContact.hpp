#include "particle.h"
#include "pcontacts.h"

#include <vector>

namespace cyclone {
	class MyPlaneContact : public cyclone::ParticleContactGenerator {
		std::vector<cyclone::Particle *> particles;
		double size;							//size of the particle
		std::vector<cyclone::Vector3> vertices; //vertices of the plane
		cyclone::Vector3 contactNormal;			//Normal of the plane
		float delta;							//Delta of the plane

	public:
		MyPlaneContact(std::vector<cyclone::Vector3> &v);
		~MyPlaneContact();
		void init(cyclone::Particle *p, double size);
		virtual unsigned addContact(cyclone::ParticleContact *contact, unsigned limit) const;
	};
} // namespace cyclone
