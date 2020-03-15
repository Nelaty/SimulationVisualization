#include "FallingCubeScene.h"

#include "PhysicInterfaces/ParticleNodeWorld.h"
#include "R3D/ParticleEngine/ParticleWorld.h"

#include "EC3D/Core/ResourceRegistry.h"
#include "EC3D/Core/Drawable.h"

FallingCubeScene::FallingCubeScene(const std::string& name, SimulationWindow* window)
	: SimulationScene(name, window)
{
	// Get a previously created drawable
	auto reg = window->getDrawableRegistry();
	m_drawable = reg.getResource("side_wall");

	auto particleNodeWorld = m_physicsEngine.getParticleNodeWorld();
	auto particleWorld = particleNodeWorld->getWorld();

	// Init scene graph node and add it to the scene graph
	m_node = new ec::Node();
	m_node->addDrawable(m_drawable);

	m_root->addChild(m_node);

	// Init particle
	m_particle = new r3::Particle();
	m_particle->setMass(1.0f);

	// Init particle node and register it
	m_particleNode = new ParticleNode(m_particle, m_node);
	particleNodeWorld->addParticleNode(m_particleNode);

	// Init force generator and register it
	m_particleGravity = new r3::ParticleGravity(glm::vec3(0.0f, -1.0f, 0.0f));
	particleWorld->getParticleForceRegistry().add(m_particle, m_particleGravity);
}

FallingCubeScene::~FallingCubeScene()
= default;

void FallingCubeScene::tick(const float timeDelta)
{
	SimulationScene::tick(timeDelta);
}

void FallingCubeScene::reset()
{
	m_particle->reset();
}
