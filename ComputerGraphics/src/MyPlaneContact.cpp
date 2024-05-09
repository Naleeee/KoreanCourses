#include "MyPlaneContact.hpp"

using namespace cyclone;

MyPlaneContact::MyPlaneContact(std::vector<cyclone::Vector3> &v)
{
	vertices = v;
	cyclone::Vector3 p1 = vertices[0];
	cyclone::Vector3 p2 = vertices[1];
	cyclone::Vector3 p3 = vertices[2];
	cyclone::Vector3 v1 = p2 - p1;
	cyclone::Vector3 v2 = p3 - p1;
	v1.normalise();
	v2.normalise();

	contactNormal = v1.cross(v2);
	delta = -contactNormal.dot(p1);
}
MyPlaneContact::~MyPlaneContact() { }
void MyPlaneContact::init(cyclone::Particle *p, double size)
{
	if (p)
		particles.push_back(p);
	this->size = size;
}

unsigned MyPlaneContact::addContact(cyclone::ParticleContact *contact, unsigned limit) const
{
	unsigned count = 0;
	for (int i = 0; i < particles.size(); i++) {
		cyclone::Particle *p = particles[i];
		cyclone::Vector3 pos = p->getPosition();

		float dd = (pos - vertices[0]).dot(contactNormal);

		if (dd < size && vertices[2].x < pos.x && pos.x < vertices[0].x && vertices[1].z < pos.z &&
			pos.z < vertices[0].z) {
			contact->contactNormal = contactNormal;
			contact->particle[0] = p;	 //particle
			contact->particle[1] = NULL; //the plane does not move
			contact->penetration = size - dd;
			contact->restitution = 1.0f;
			count++;
		}
		if (count >= limit)
			return count;
	}
	return count;
}
