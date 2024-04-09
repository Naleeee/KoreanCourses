#include "particle.h"
#include "pfgen.h"

namespace cyclone {
	class MySpring : public ParticleForceGenerator //Generic Force generating class
	{
		cyclone::Particle *other; //Target particle
		double springConstant;	  //Spring constant (k)
		double restLength;		  //lest length
	public:
		virtual ~MySpring() = default;
		MySpring(const MySpring &) = default;
		MySpring(MySpring &&) = delete;
		MySpring &operator=(const MySpring &) = default;
		MySpring &operator=(MySpring &&) = delete;
		MySpring(cyclone::Particle *p, double springConstant, double restLenght)
		{
			other = p;
			this->springConstant = springConstant;
			this->restLength = restLenght;
		}
		void updateForce(cyclone::Particle *p, double duration) override
		{
			cyclone::Vector3 d = p->getPosition() - other->getPosition();
			cyclone::Vector3 normalised = d;
			normalised.normalise();
			Vector3 force = normalised * -springConstant *
							(d.magnitude() - restLength); //A force that applies to the particles
			p->addForce(force);
		}
	};

} // namespace cyclone
