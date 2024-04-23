#include "Fireworks.hpp"

#include <vector>

Fireworks::Fireworks()
{
	auto rule1 = new FireworksRule();
	rule1->setParameters(0, 1.5, 2.5, cyclone::Vector3(-5, 10, -5), cyclone::Vector3(5, 30, 5),
						 0.99, 5);
	m_rules.push_back(rule1);
}

void Fireworks::update(float duration)
{
	for (int i = fireworks.size() - 1; i >= 0; i--) {
		Fire *fire = fireworks[i];

		fire->putHistory();

		if (fire->update(duration)) {
			if (fire->m_type == 0) {
				create(fire);
			}
			fireworks.erase(fireworks.begin() + i);
		}
	}
}

void Fireworks::create()
{
	Fire *fire = new Fire(0);
	fire->setRule(m_rules.front());
	fireworks.push_back(fire);
}

void Fireworks::create(Fire *parent)
{
	for (int i = 0; i < parent->m_rule->payloadCount; i++) {
		Fire *fire = new Fire(1);
		fire->setRule(parent->m_rule);
		fire->m_particle->setPosition(parent->m_particle->getPosition());

		fireworks.push_back(fire);
	}
}

void Fireworks::draw(int shadow)
{
	for (Fire *fire : fireworks) {
		fire->draw(shadow);
	}
}
