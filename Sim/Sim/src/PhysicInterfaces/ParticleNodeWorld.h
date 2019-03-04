#pragma once
#include <memory>

#include <vector>

namespace r3
{
	class ParticleWorld;
}

class ParticleNode;

class ParticleNodeWorld
{
public:
	using ParticleWorld_Ptr = std::unique_ptr<r3::ParticleWorld>;

	explicit ParticleNodeWorld();
	~ParticleNodeWorld();

	/** \brief Update all particle nodes. */
	void update();

	/** \brief Register a new particle node. */
	void addParticleNode(ParticleNode* node);
	/** \brief Unregister an already registered particle node. */
	bool removeParticleNode(ParticleNode* node);

	/** \brief Unregister all currently registered particle nodes. */
	void clear();

	/** \brief Get the particle world. */
	r3::ParticleWorld* getWorld() const;

private:
	/** \brief Initialize the particle node world. */
	void init();

	std::vector<ParticleNode*> m_particleNodes;

	ParticleWorld_Ptr m_world;	
};