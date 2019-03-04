#pragma once
#include "EC3D/Core/Node.h"

namespace r3
{
	class Particle;
}

class ParticleNode
{
public:
	explicit ParticleNode(r3::Particle* particle, ec::Node* node);
	~ParticleNode();

	/** \brief Update the scene graph node with the associated particle node. */
	void update() const;

	/** \brief Get the current particle. */
	r3::Particle* getParticle() const;

	/** \briefGet the current node. */
	ec::Node* getNode() const;

private:
	r3::Particle* m_particle;
	ec::Node* m_node;
};

