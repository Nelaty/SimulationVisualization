#pragma once
#include  "R3D/PhysicsEngine.h"

#include <memory>

class ParticleNodeWorld;
class RigidBodyNodeWorld;


class PhysicsEngineWrapper
{
public:
	using ParticleNodeWorld_Ptr = std::unique_ptr<ParticleNodeWorld>;
	using RigidBodyNodeWorld_Ptr = std::unique_ptr<RigidBodyNodeWorld>;

	explicit PhysicsEngineWrapper();
	~PhysicsEngineWrapper();

	void tick(float timeDelta);

	ParticleNodeWorld* getParticleNodeWorld() const;
	RigidBodyNodeWorld* getRigidBodyNodeWorld() const;

private:
	void init();

	r3::PhysicsEngine m_physicsEngine;

	ParticleNodeWorld_Ptr m_particleNodeWorld;
	RigidBodyNodeWorld_Ptr m_rigidBodyNodeWorld;
};