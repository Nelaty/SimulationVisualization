#include "RigidBodyNodeWorld.h"
#include "RigidBodyNode.h"
#include "R3D/RigidBodyEngine/RigidBodyWorld.h"
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/DefaultRigidBodyEngineCI.h"

#include <algorithm>

RigidBodyNodeWorld::RigidBodyNodeWorld()
{
	init();
}

RigidBodyNodeWorld::~RigidBodyNodeWorld()
= default;

void RigidBodyNodeWorld::update()
{
	for (auto& it : m_rigidBodyNodes)
	{
		it->update();
	}
}

void RigidBodyNodeWorld::addRigidBodyNode(RigidBodyNode* node)
{
	m_rigidBodyNodes.emplace_back(node);
	m_world->addRigidBody(node->getRigidBody());
}

bool RigidBodyNodeWorld::removeRigidBodyNode(RigidBodyNode* node)
{
	const auto removedBody = std::remove(m_rigidBodyNodes.begin(),
	                                     m_rigidBodyNodes.end(),
	                                     node);

	const bool found = removedBody != m_rigidBodyNodes.end();
	if (found)
	{
		m_world->removeRigidBody(node->getRigidBody());
		m_rigidBodyNodes.erase(removedBody);
	}
	return found;
}

const std::vector<r3::RigidBody*>& RigidBodyNodeWorld::getRigidBodies() const
{
	return m_world->getRigidBodies();
}

std::vector<r3::RigidBody*>& RigidBodyNodeWorld::getRigidBodies()
{
	return m_world->getRigidBodies();
}

const std::vector<RigidBodyNode*>& RigidBodyNodeWorld::getRigidBodyNodes() const
{
	return m_rigidBodyNodes;
}

std::vector<RigidBodyNode*>& RigidBodyNodeWorld::getRigidBodyNodes()
{
	return m_rigidBodyNodes;
}

void RigidBodyNodeWorld::clear()
{
	m_rigidBodyNodes.clear();
}

r3::RigidBodyWorld* RigidBodyNodeWorld::getWorld() const
{
	return m_world.get();
}

void RigidBodyNodeWorld::init()
{
	m_world = std::make_unique<r3::RigidBodyWorld>();

	const auto ci = new r3::DefaultRigidBodyEngineCI();
	ci->setRigidBodyWorld(m_world.get());
	m_world->setComputationInterface(ci);
}
