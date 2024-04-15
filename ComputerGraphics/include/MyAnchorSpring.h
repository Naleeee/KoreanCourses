#include "Cyclone/pfgen.h"

#include <iostream>
namespace cyclone {

	class MyAnchoredSpring : public ParticleForceGenerator {
	protected:
		double springConstant {};	 /** spring constant. */
		double restLength {};		 /** rest length. */
		cyclone::Vector3 *anchor {}; /** Anchor position. */
	public:
		virtual ~MyAnchoredSpring() = default;
		MyAnchoredSpring() = default;
		MyAnchoredSpring(const MyAnchoredSpring &) = default;
		MyAnchoredSpring(MyAnchoredSpring &&) = delete;
		MyAnchoredSpring &operator=(const MyAnchoredSpring &) = default;
		MyAnchoredSpring &operator=(MyAnchoredSpring &&) = delete;
		MyAnchoredSpring(cyclone::Vector3 *newAnchor, double springConstant, double restLength)
		{
			this->anchor = newAnchor;
			this->springConstant = springConstant;
			this->restLength = restLength;
		}

		[[nodiscard]] const Vector3 *getAnchor() const
		{
			return anchor;
		} //return anchor position

		void init(cyclone::Vector3 *anchor, double springConstant, double restLength); //set values

		void updateForce(Particle *p, real duration) override
		{
			cyclone::Vector3 d = p->getPosition() - *anchor;
			cyclone::Vector3 normalised = d;
			normalised.normalise();
			cyclone::Vector3 force =
				normalised * -springConstant *
				(d.magnitude() - restLength); //A force that applies to the particles
			p->addForce(force);
		}
	};

} // namespace cyclone
