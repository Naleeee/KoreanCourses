#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "./Cyclone/core.h"
#include "./Cyclone/particle.h"
#include "./Cyclone/pfgen.h"

class Mover {

public:
  float size;
  cyclone::Particle *m_particle;
  cyclone::ParticleGravity *m_gravity;
  cyclone::ParticleDrag *m_drag;
  cyclone::ParticleForceRegistry *m_forces;

  Mover() {
    size = 1.0f;

    m_gravity = new cyclone::ParticleGravity(cyclone::Vector3(0, -9.81, 0));
    m_drag = new cyclone::ParticleDrag(0.1, 0.01);

    m_forces = new cyclone::ParticleForceRegistry();
    m_particle = new cyclone::Particle();

    m_forces->add(m_particle, m_gravity);
    m_forces->add(m_particle, m_drag);

    m_particle->setPosition(0.0f, 20.0f, 0.0f); // initial posx
    m_particle->setVelocity(0.0f, 0.0f, 0.0f);
    m_particle->setDamping(1.0f);                  // damping
    m_particle->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc
    m_particle->setMass(1.0f);                     // mass
  };

  void update(float duration) {
    m_forces->updateForces(duration);
    m_particle->integrate(duration);
    checkEdges();
  }

  void resetParameters() {
    m_particle->setPosition(0.0f, 20.0f, 0.0f); // initial posx
    m_particle->setVelocity(0.0f, 0.0f, 0.0f);
    m_particle->setDamping(1.0f);
    m_particle->setAcceleration(0.0f, 0.0f, 0.0f); // initial acc
    m_particle->setMass(1.0f);                     // 1.0kg-mostly blast damage
  }

  void checkEdges() {
    cyclone::Vector3 pos = m_particle->getPosition();
    cyclone::Vector3 vel = m_particle->getVelocity();

    if (pos.x >= 100 - size / 2) {
      pos.x = 100 - size / 2;
      vel.x *= -1;
    } else if (pos.x <= -100 + size / 2) {
      pos.x = -100 + size / 2;
      vel.x *= -1;
    }
    if (pos.y <= size / 2) {
      pos.y = size / 2;
      vel.y *= -1;
    }
    if (pos.z >= 100 - size / 2) {
      pos.z = 100 - size / 2;
      vel.z *= -1;
    } else if (pos.z <= -100 + size / 2) {
      pos.z = -100 + size / 2;
      vel.z *= -1;
    }
    m_particle->setPosition(pos);
    m_particle->setVelocity(vel);
  }

  void stop() {}

  void draw(int shadow) {
    cyclone::Vector3 position;
    m_particle->getPosition(&position); // get the current pos of particle

    if (shadow)
      glColor3f(0.1f, 0.1f, 0.1f);
    else
      glColor3f(1.0, 0, 0);

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(size, 30, 30);
    glPopMatrix();
  }
};
