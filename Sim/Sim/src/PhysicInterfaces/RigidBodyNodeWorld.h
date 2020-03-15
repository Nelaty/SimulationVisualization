#pragma once

#include <memory>
#include <vector>

namespace r3
{
	class RigidBodyWorld;
	class RigidBody;
}

class RigidBodyNode;

class RigidBodyNodeWorld
{
public:
	using RigidBodyWorld_Ptr = std::unique_ptr<r3::RigidBodyWorld>;

	explicit RigidBodyNodeWorld();
	~RigidBodyNodeWorld();

	/** \brief Update all registered rigid body nodes. */
	void update();

	/** \brief Register a new rigid body node. */
	void addRigidBodyNode(RigidBodyNode* node);
	/**
	 * \brief Unregister an already registered rigid body node.
	 * \return True if the rigid body node was found, false otherwise.
	 */
	bool removeRigidBodyNode(RigidBodyNode* node);

	/** \brief Get all registered rigid bodies. */
	const std::vector<r3::RigidBody*>& getRigidBodies() const;
	/** \brief Get all registered rigid bodies. */
	std::vector<r3::RigidBody*>& getRigidBodies();

	/** \brief Get all registered rigid body nodes. */
	const std::vector<RigidBodyNode*>& getRigidBodyNodes() const;

	/** \brief Get all registered rigid body nodes. */
	std::vector<RigidBodyNode*>& getRigidBodyNodes();

	/** \brief Unregister all currently registered rigid body nodes. */
	void clear();

	/** \brief Get the rigid body world. */
	r3::RigidBodyWorld* getWorld() const;

private:
	void init();

	std::vector<RigidBodyNode*> m_rigidBodyNodes;

	RigidBodyWorld_Ptr m_world;
};