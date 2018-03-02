#include "RigidBody.h"

#include "Sphere.h"
inline glm::vec2 cross2D(float a, const glm::vec2& v) { return glm::vec2(-a * v.y, a * v.x); }



RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_elasticity = 1;
	m_angularVelocity = 0.0f;
	m_angularDrag = 0;
	m_isKinematic = false;
}

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float angularVelocity, float elasticity)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
	m_angularVelocity = angularVelocity;
	m_elasticity = elasticity;
	m_isKinematic = false;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	if (m_isKinematic)
	{
		return;
	}
	applyForce(gravity * m_mass * timeStep,glm::vec2(0,0));
	m_velocity += gravity * timeStep;
	m_position += m_velocity * timeStep;


	m_velocity -= m_velocity * timeStep;
	//m_rotation += m_angularVelocity * timeStep;
	//m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	
	//m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	
	if (length(m_velocity) < MIN_LINEAR_THRESHOLD)
	{
		if (length(m_velocity) < length(gravity)*m_linearDrag*timeStep)
		{
			m_velocity = glm::vec2(0, 0);
		}
	}
	//if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	//{
	//	m_angularVelocity = 0;
	//}

}



// When applying the force, it will apply a force at a position (hence, the collision detection needs to know AT WHAT POSITION STUFF TOUCHED.)
void RigidBody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	m_velocity += force / m_mass;
	
	//m_angularVelocity += (force.y * pos.x - force.x * pos.y) / (m_moment);


}



void RigidBody::setVelocity(glm::vec2 newVelocity)
{
	m_velocity.x = newVelocity.x;
	m_velocity.y = newVelocity.y;
}

void RigidBody::resolveCollision(RigidBody * actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{

	if (m_shapeID == ShapeType::PLANE || m_isKinematic == true)
	{
		m_mass = INFINITY;
	}
	if (actor2->m_shapeID == ShapeType::PLANE || actor2->m_isKinematic == true)
	{
		actor2->m_mass = INFINITY;
	}
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass + (1 / actor2->getMass()))));

	glm::vec2 force = normal * j;

	

	//apply equal and opposite forces
	applyForce(-force, contact - m_position);
	actor2->applyForce(force, contact - actor2->m_position);

}

float RigidBody::getRotation()
{
	return m_rotation;
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

void RigidBody::setElasticity(float elasticity)
{
	m_elasticity = elasticity;
}

void RigidBody::setPosition(glm::vec2 position)
{
	m_position.x = position.x;
	m_position.y = position.y;
}
