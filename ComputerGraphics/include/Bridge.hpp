#include "particle.h"
#include "plinks.h"
#include "pworld.h"

#include <vector>

class Bridge {
public:
	Bridge();
	~Bridge();

	int particleCount = 12;
	int cableCount = particleCount - 2;
	int rodCount = particleCount / 2;
	int supportCount = particleCount;
	cyclone::ParticleWorld *m_particleWorld;
	std::vector<cyclone::Particle *> m_particleArray;
	std::vector<cyclone::ParticleCable *> cables;
	std::vector<cyclone::ParticleRod *> rods;
	std::vector<cyclone::ParticleCableConstraint *> supports;

	void draw(int shadow);
	void update(float duration);

private:
};
