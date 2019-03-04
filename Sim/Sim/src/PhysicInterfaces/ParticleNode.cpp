#include "ParticleNode.h"
#include "R3D/ParticleEngine/Particle.h"

ParticleNode::ParticleNode(r3::Particle* particle, ec::Node* node)
	: m_particle(particle),
	m_node(node)
{
}

ParticleNode::~ParticleNode()
= default;

void ParticleNode::update() const
{	
	const auto& pos = m_particle->getPosition();
	m_node->setTranslation(pos);
}

r3::Particle* ParticleNode::getParticle() const
{
	return m_particle;
}

ec::Node* ParticleNode::getNode() const
{
	return m_node;
}
