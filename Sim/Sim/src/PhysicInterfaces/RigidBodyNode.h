#pragma once
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "EC3D/Core/Node.h"

class RigidBodyNode
{
public:
	RigidBodyNode(r3::RigidBody* rigidBody, ec::Node* node);
	~RigidBodyNode();

	/**
	 * \brief Update the scene graph node with the associated rigid body
	 * node.
	 */
	void update() const;

	/** \brief Get the current rigid body. */
	r3::RigidBody* getRigidBody() const;

	/** \brief Get the current node. */
	ec::Node* getNode() const;

private:
	r3::RigidBody* m_rigidBody;
	ec::Node* m_node;
};

