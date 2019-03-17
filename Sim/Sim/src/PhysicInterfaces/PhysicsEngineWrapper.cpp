#include "PhysicsEngineWrapper.h"
#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/RigidBodyEngine/RigidBodyWorld.h"

#include "ParticleNodeWorld.h"
#include "RigidBodyNodeWorld.h"

PhysicsEngineWrapper::PhysicsEngineWrapper()
{
	init();
}

PhysicsEngineWrapper::~PhysicsEngineWrapper()
= default;

void PhysicsEngineWrapper::tick(float timeDelta)
{
	static const auto limit = 1.0f / 60.0f;
	if(timeDelta > limit)
	{
		timeDelta = limit;
	}

	m_physicsEngine.tick(timeDelta);

	m_particleNodeWorld->update();
	m_rigidBodyNodeWorld->update();
}

ParticleNodeWorld* PhysicsEngineWrapper::getParticleNodeWorld() const
{
	return m_particleNodeWorld.get();
}

RigidBodyNodeWorld* PhysicsEngineWrapper::getRigidBodyNodeWorld() const
{
	return m_rigidBodyNodeWorld.get();
}

void PhysicsEngineWrapper::init()
{
	m_particleNodeWorld = std::make_unique<ParticleNodeWorld>();
	m_rigidBodyNodeWorld = std::make_unique<RigidBodyNodeWorld>();

	m_physicsEngine.registerModule(m_particleNodeWorld->getWorld(), "particle");
	m_physicsEngine.registerModule(m_rigidBodyNodeWorld->getWorld(), "rigid_body");
}
