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

	m_particleWorld->update();
	m_rigidBodyWorld->update();
}

ParticleNodeWorld* PhysicsEngineWrapper::getParticleNodeWorld() const
{
	return m_particleWorld.get();
}

RigidBodyNodeWorld* PhysicsEngineWrapper::getRigidBodyNodeWorld() const
{
	return m_rigidBodyWorld.get();
}

void PhysicsEngineWrapper::init()
{
	m_particleWorld = std::make_unique<ParticleNodeWorld>();
	m_rigidBodyWorld = std::make_unique<RigidBodyNodeWorld>();

	m_physicsEngine.registerModule(m_particleWorld->getWorld(), "particle");
	m_physicsEngine.registerModule(m_rigidBodyWorld->getWorld(), "rigid_body");
}
