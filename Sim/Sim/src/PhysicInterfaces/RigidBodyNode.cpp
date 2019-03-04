#include "RigidBodyNode.h"

RigidBodyNode::RigidBodyNode(r3::RigidBody* rigidBody, ec::Node* node)
	: m_rigidBody(rigidBody),
	m_node(node)
{
}

RigidBodyNode::~RigidBodyNode()
= default;

void RigidBodyNode::update() const
{
	const auto& transform = m_rigidBody->getTransform();
	m_node->setTranslation(transform.getPosition());
	m_node->setRotation(transform.getRotationMat());	
}

r3::RigidBody* RigidBodyNode::getRigidBody() const
{
	return m_rigidBody;
}

ec::Node* RigidBodyNode::getNode() const
{
	return m_node;
}
