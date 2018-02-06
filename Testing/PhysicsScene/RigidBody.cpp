#include "RigidBody.h"





RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity.x += force.x / m_mass;
	m_velocity.y += force.y / m_mass;

}

void RigidBody::applyForceToActor(RigidBody * actor2, glm::vec2 force)
{
	glm::vec2 forceEquivalent;

	forceEquivalent.x = force.x * 2.0f;
	forceEquivalent.y = force.y * 2.0f;

	actor2->applyForce(forceEquivalent);
	this->applyForce(glm::vec2(-forceEquivalent.x,-forceEquivalent.y));
}
