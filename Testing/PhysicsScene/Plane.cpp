#include "Plane.h"



Plane::Plane() : PhysicsObject(m_shapeID = ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);

}

Plane::Plane(glm::vec2 normal, float distance)
{
	// the vector for the normal of a plane must be a normalized vector.
	m_normal = glm::normalize(normal);
	m_distanceToOrigin = distance;
	m_shapeID = ShapeType::PLANE;
}


Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

void Plane::makeGizmo()
{
	float lineSegmentLength = 10000;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);

}

void Plane::resetPosition()
{
}

void Plane::resolveCollision(RigidBody * actor2)
{
	glm::vec2 normalOfPlane = m_normal;
	glm::vec2 relativeVelocity = actor2->getVelocity();

	float elasticity = 1;
	float j = glm::dot(-relativeVelocity - ((1 + elasticity) * normalOfPlane), normalOfPlane);

	glm::vec2 a = actor2->getVelocity() - (1 + elasticity) * glm::dot(relativeVelocity, normalOfPlane) * normalOfPlane ;

	actor2->setVelocity(a);

	//actor2->applyForce(force);
}

void Plane::resolveCollision(RigidBody * actor2, glm::vec2 contact)
{
	// the plane isnt moving, so the relative velocity is just actor2's velocity
	glm::vec2 vRel = actor2->getVelocity();
	float e = actor2->getElasticity();
	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / actor2->getMass());

	glm::vec2 force = m_normal * j;

	actor2->applyForce(force, contact - actor2->getPosition());

}



