#include "Spring.h"





Spring::Spring(RigidBody * body1, RigidBody * body2, float restLength, float springCoefficient, glm::vec4 LineColour, float breakForce, float damping, glm::vec2 contact1, glm::vec2 contact2)
{
	m_body1 = body1;
	m_body2 = body2;
	m_restLength = restLength;
	m_springCoefficent = springCoefficient;
	m_damping = damping;
	m_contact1 = contact1;
	m_contact2 = contact2;
	m_shapeID = ShapeType::JOINT;
	m_colour = LineColour;
	m_breakForce = breakForce;
}

Spring::~Spring()
{
}



void Spring::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	glm::vec2 p1 = m_body1->getPosition() + m_contact1;
	glm::vec2 p2 = m_body2->getPosition() + m_contact2;

	glm::vec2 dist = p2 - p1;

	float length = sqrtf(dist.x*dist.x + dist.y*dist.y);

	// apply damping
	glm::vec2 relativeVelocity = m_body2->getVelocity() - m_body1->getVelocity();

	// F = -kX - bv
	glm::vec2 force = dist * m_springCoefficent * (m_restLength - length) - m_damping * relativeVelocity;


	if (!m_body1->isKinematic())
	{
		m_body1->applyForce(-force * timeStep, p1 - m_body1->getPosition());
	}
	if (!m_body2->isKinematic())
	{
		m_body2->applyForce(force * timeStep, p2 - m_body2->getPosition());
	}


}

void Spring::makeGizmo()
{
	aie::Gizmos::add2DLine(m_body1->getPosition() + m_contact1, m_body2->getPosition() + m_contact2, m_colour);
}


