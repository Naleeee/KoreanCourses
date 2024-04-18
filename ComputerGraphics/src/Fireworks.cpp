#include "Fireworks.hpp"

#include <iostream>

Fireworks::Fireworks()
{
	fireworks = {};
}

void Fireworks::update(float duration)
{
	for (auto it = fireworks.begin(); it != fireworks.end();) {
		Fire *fire = *it;
		fire->update(duration);
		auto pos = fire->m_particle->getPosition();
		if (pos.y < 0) {
			delete fire;			  // Delete the Fire object
			it = fireworks.erase(it); // Erase the element from the vector
		} else if (fire->m_age < 0) {
			create(fire);
			create(fire);
			create(fire);
			create(fire);
			create(fire);
			delete fire;			  // Delete the Fire object
			it = fireworks.erase(it); // Erase the element from the vector
		} else {
			++it;
		}
	}
}

void Fireworks::create()
{
	Fire *fire = new Fire(0);
	fireworks.push_back(fire);

	std::cout << "END OF CREATE" << std::endl;
}

void Fireworks::create(Fire *parent)
{
	Fire *fire = new Fire(1);
	fireworks.push_back(fire);

	std::cout << "END OF CHILD CREATE" << std::endl;
}

void Fireworks::draw(int shadow)
{
	for (Fire *fire : fireworks) {
		fire->draw(1);
	}
}
