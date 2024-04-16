#include "./Fire.hpp"
#include "FireworksRule.hpp"

#include <array>
#include <cstddef>
#include <vector>

class Fireworks {
public:
	Fireworks();
	Fireworks(const Fireworks &) = default;
	Fireworks(Fireworks &&) = delete;
	Fireworks &operator=(const Fireworks &) = default;
	Fireworks &operator=(Fireworks &&) = delete;
	~Fireworks();

	// FireworksRule m_rule[3];	   //rules
	std::array<FireworksRule, std::size_t(3)> m_rule;
	std::vector<Fire *> fireworks; //contains Fires

	void update(float duration); //Fire create/update
	void create();				 //create init Fires
	void create(Fire *parent);	 //create Child Fires
	void draw(int shadow);		 //draw
};
