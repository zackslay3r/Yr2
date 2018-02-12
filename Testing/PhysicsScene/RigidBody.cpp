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

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	
	
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

void RigidBody::setVelocity(glm::vec2 newVelocity)
{
	m_velocity.x = newVelocity.x;
	m_velocity.y = newVelocity.y;
}

void RigidBody::resolveCollision(RigidBody * actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass + (1 / actor2->getMass()))));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, force);
}

void RigidBody::setLinearDrag(float value)
{
	m_linearDrag = value;
}

void RigidBody::setAngularDrag(float value)
{
	m_angularDrag = value;
}

void RigidBody::setAngularVelocity(float value)
{
	m_angularVelocity = value;
}
