#include "RigidBody.h"
#include "Global.h"
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
	if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
	{
		m_angularVelocity = 0;
	}

}

void RigidBody::debug()
{
}

// When applying the force, it will apply a force at a position (hence, the collision detection needs to know AT WHAT POSITION STUFF TOUCHED.)
void RigidBody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	m_velocity += force / m_mass;
	
	m_angularVelocity += (force.y * pos.x - force.x * pos.y) / (m_moment);


}

//void RigidBody::applyForceToActor(RigidBody * actor2, glm::vec2 force)
//{
//	glm::vec2 forceEquivalent;
//
//	forceEquivalent.x = force.x * 2.0f;
//	forceEquivalent.y = force.y * 2.0f;
//
//	actor2->applyForce(forceEquivalent);
//	this->applyForce(glm::vec2(-forceEquivalent.x,-forceEquivalent.y));
//}

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

	//applyForceToActor(actor2, force);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//find the vector between their centres, or use the provided direction of force.
	//glm::vec2 normal = collisionNormal ? *collisionNormal : glm::normalize(actor2->m_position - m_position);

	//// get the vector perpendicular to the collision normal.
	//glm::vec2 perp = glm::vec2(normal.y, -normal.x);

	////determine the total velocity of the contact points for the two objects, for both linear and rotational
	//// r is the radius from axis to application of force
	//float r1 = glm::dot(contact - m_position, -perp);
	//float r2 = glm::dot(contact - actor2->m_position, perp);
	////// velocity of the contact point on this object
	//float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	////// velocity of contact point on actor2
	//float v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_angularVelocity;


	//////Define contact points on both objects relative to their COM.
	////glm::vec2 rA = contact - m_position;
	////glm::vec2 rB = contact - actor2->m_position;

	//////Calculate relative velocity between the colliding objects.
	////glm::vec2 rv = actor2->m_velocity + cross2D(actor2->m_angularVelocity, rB) -
	////	m_velocity - cross2D(m_angularVelocity, rA);

	//////Calculate relative velocity in the normal direction.
	////float velAlongNormal = glm::dot(rv,normal);

	//////Early exit if objects are separating.
	//////if (velAlongNormal > 0) return;

	////if (velAlongNormal <= 0) // if they are moving closer
	////{
	//// // calculate the effective mass at the contact point of each object
	////// ie how much the contact point will move due to the force applied.
	//if (v1 > v2)
	//{
	//	/*float mass1 = 1.0f / (1.0f / m_mass + (((Sphere*)this)->getRadius()*((Sphere*)this)->getRadius()) / m_moment);
	//	float mass2 = 1.0f / (1.0f / actor2->m_mass + (((Sphere*)actor2)->getRadius()*((Sphere*)actor2)->getRadius()) / actor2->m_moment);*/
	//	float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
	//	float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2 * r2) / actor2->m_moment);


	//	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

	//	glm::vec2 force = ((1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal);

		//apply equal and opposite forces
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);
	//}
	//}
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
