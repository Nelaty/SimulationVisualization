#pragma once
#include "SimulationScene.h"
#include "SimulationWindow.h"
#include "PhysicInterfaces/ParticleNode.h"

#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleGravity.h"

#include "EC3D/Core/Node.h"

#include <string>

class FallingCubeScene : public SimulationScene
{
public:
	explicit FallingCubeScene(const std::string& name, SimulationWindow* window);
	~FallingCubeScene();

	void tick(float timeDelta) override;

private:
	ec::Node* m_node;
	ec::Drawable* m_drawable;

	r3::Particle* m_particle;
	ParticleNode* m_particleNode;

	r3::ParticleGravity* m_particleGravity;
};