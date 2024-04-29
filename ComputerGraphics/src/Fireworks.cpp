#include "Fireworks.hpp"

#include <vector>

Fireworks::Fireworks()
{
	auto plRed = new FireworksRule();
	plRed->setParameters(0, 3.0, 3.5, cyclone::Vector3(-3, 20, -3), cyclone::Vector3(3, 30, 3), 10,
						 20, 0, 10, -2, 2, cyclone::Vector3(0.8, 0, 0), cyclone::Vector3(1, 0, 0),
						 0.99, 5);
	auto plYellow = new FireworksRule();
	plYellow->setParameters(0, 3.0, 3.5, cyclone::Vector3(-6, 20, -6), cyclone::Vector3(6, 25, 6),
							10, 20, 0, 10, -2, 2, cyclone::Vector3(0.5, 0.5, 0),
							cyclone::Vector3(0.7, 0.7, 0), 0.99, 5);
	auto srGreen = new FireworksRule();
	srGreen->setParameters(0, 1.3, 1.9, cyclone::Vector3(-3, 10, -5), cyclone::Vector3(3, 20, -15),
						   10, 20, 0, 10, -2, 2, cyclone::Vector3(0, 0.6, 0),
						   cyclone::Vector3(0, 1, 0), 0.99, 10);
	auto srBlue = new FireworksRule();
	srBlue->setParameters(0, 1.0, 1.6, cyclone::Vector3(-3, 5, -5), cyclone::Vector3(3, 15, -15),
						  10, 20, 0, 10, -2, 2, cyclone::Vector3(0, 0, 0.6),
						  cyclone::Vector3(0, 0, 1), 0.99, 10);
	auto slGreen = new FireworksRule();
	slGreen->setParameters(0, 1.3, 1.9, cyclone::Vector3(-3, 10, 5), cyclone::Vector3(3, 20, 15),
						   10, 20, 0, 10, -2, 2, cyclone::Vector3(0, 0.6, 0),
						   cyclone::Vector3(0, 1, 0), 0.99, 10);
	auto slBlue = new FireworksRule();
	slBlue->setParameters(0, 1.0, 1.6, cyclone::Vector3(-3, 5, 5), cyclone::Vector3(3, 15, 15), 10,
						  20, 0, 10, -2, 2, cyclone::Vector3(0, 0, 0.6), cyclone::Vector3(0, 0, 1),
						  0.99, 10);
	m_rules.push_back(plRed);
	m_rules.push_back(plRed);
	m_rules.push_back(plRed);
	m_rules.push_back(plRed);
	m_rules.push_back(plRed);
	m_rules.push_back(plYellow);
	m_rules.push_back(plYellow);
	m_rules.push_back(plYellow);
	m_rules.push_back(plYellow);
	m_rules.push_back(plYellow);
	m_rules.push_back(srGreen);
	m_rules.push_back(srGreen);
	m_rules.push_back(srGreen);
	m_rules.push_back(srGreen);
	m_rules.push_back(srGreen);
	m_rules.push_back(srBlue);
	m_rules.push_back(srBlue);
	m_rules.push_back(srBlue);
	m_rules.push_back(srBlue);
	m_rules.push_back(srBlue);
	m_rules.push_back(slGreen);
	m_rules.push_back(slGreen);
	m_rules.push_back(slGreen);
	m_rules.push_back(slGreen);
	m_rules.push_back(slGreen);
	m_rules.push_back(slBlue);
	m_rules.push_back(slBlue);
	m_rules.push_back(slBlue);
	m_rules.push_back(slBlue);
	m_rules.push_back(slBlue);
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
	fire->setRule(m_rules.back());
	m_rules.pop_back();
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
