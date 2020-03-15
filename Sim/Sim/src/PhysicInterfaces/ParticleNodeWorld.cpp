#include "ParticleNodeWorld.h"
#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/DefaultParticleEngineCI.h"

#include "ParticleNode.h"

#include <algorithm>

ParticleNodeWorld::ParticleNodeWorld()
{
	init();
}

ParticleNodeWorld::~ParticleNodeWorld()
{
}

void ParticleNodeWorld::update()
{
	for(auto& it : m_particleNodes)
	{
		it->update();
	}
}

const std::vector<ParticleNode*>& ParticleNodeWorld::getParticleNodes() const
{
	return m_particleNodes;
}

std::vector<ParticleNode*>& ParticleNodeWorld::getParticleNodes()
{
	return m_particleNodes;
}

const std::vector<r3::Particle*>& ParticleNodeWorld::getParticles() const
{
	return m_world->getParticles();
}

std::vector<r3::Particle*>& ParticleNodeWorld::getParticles()
{
	return m_world->getParticles();
}

void ParticleNodeWorld::addParticleNode(ParticleNode* node)
{
	m_particleNodes.emplace_back(node);
	m_world->addParticle(node->getParticle());
}

bool ParticleNodeWorld::removeParticleNode(ParticleNode* node)
{
	const auto removedNode = std::remove(m_particleNodes.begin(),
										 m_particleNodes.end(),
										 node);

	const bool found = removedNode != m_particleNodes.end();
	if(found)
	{
		m_world->removeParticle(node->getParticle());
		m_particleNodes.erase(removedNode);
	}

	return found;
}

void ParticleNodeWorld::clear()
{
	m_particleNodes.clear();
}

r3::ParticleWorld* ParticleNodeWorld::getWorld() const
{
	return m_world.get();
}

void ParticleNodeWorld::init()
{
	m_world = std::make_unique<r3::ParticleWorld>();

	const auto ci = new r3::DefaultParticleEngineCI(1000, 0, m_world.get());
	m_world->setComputationInterface(ci);
}
