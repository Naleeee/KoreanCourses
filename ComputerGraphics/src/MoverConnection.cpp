#include "MoverConnection.hpp"

void MoverConnection::update(float duration) { }

void MoverConnection::draw(int shadow)
{
	glBegin(GL_LINE_STRIP);
	cyclone::Vector3 posA = m_MoverA->m_particle->getPosition();
	glVertex3f(posA.x, posA.y, posA.z);
	cyclone::Vector3 posB = m_MoverB->m_particle->getPosition();
	glVertex3f(posB.x, posB.y, posB.z);
	glEnd();
};

void MoverConnection::drawAnchor(int shadow, Mover *mover)
{
	glColor3f(1, 1, 0); //Line color
	glLineWidth(3.0f);	//Line Width
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(mover->m_anchorSpring->getAnchor()->x, mover->m_anchorSpring->getAnchor()->y,
			   mover->m_anchorSpring->getAnchor()->z); //Starting point
	glVertex3f(mover->m_anchorSpring->getAnchor()->x, 0,
			   mover->m_anchorSpring->getAnchor()->z); //Ending point
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0); //Line color
	glLineWidth(3.0f);	//Line Width
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(mover->m_anchorSpring->getAnchor()->x, mover->m_anchorSpring->getAnchor()->y,
			   mover->m_anchorSpring->getAnchor()->z); //Starting point
	glVertex3f(mover->m_particle->getPosition().x, mover->m_particle->getPosition().y,
			   mover->m_particle->getPosition().z); //Ending point
	glEnd();
	glPopMatrix();
};
