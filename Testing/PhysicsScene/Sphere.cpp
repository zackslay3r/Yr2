#include "Sphere.h"




Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_moment = 0.5f * m_mass * m_radius * m_radius;
	m_moment = 0.0f;
	m_rotation = 0.0f;
	m_angularVelocity = 0.0f;
	m_shapeID = ShapeType::SPHERE;
	m_elasticity = 1.0f;

}





Sphere::~Sphere()
{
}

void Sphere::makeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;
	aie::Gizmos::add2DCircle(m_position, m_radius, 30, m_colour);

	// This is to be used to show rotation when it is impelmented in a later version.
	//aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(0, 0, 0, 0));


}

bool Sphere::checkCollision(PhysicsObject* pOther)
{
	//Sphere* testCast = dynamic_cast<Sphere*>(pOther);

	//if (testCast != NULL)
	//{
	//	glm::vec2 SphereDistanceAway =  testCast->m_position - this->m_position ;
	//	if (this->m_radius + testCast->m_radius > abs(SphereDistanceAway.x))
	//	{
	//		if (this->m_radius + testCast->m_radius > abs(SphereDistanceAway.y))
	//		{
	//			return true;
	//		}
	//		else
	//		{
	//			return false;
	//		}
	//	}
	//	

	//	
	//}
	//else
	//{
	//	return false;
	//}
	//cast the objects to sphere and sphere
	Sphere* sphere2 = dynamic_cast<Sphere*>(pOther);

	// if we suceed, test for a collision.

	if (pOther != nullptr)
	{
		float distanceAway = glm::distance(this->getPosition(), sphere2->getPosition());
		if (distanceAway < this->getRadius() + sphere2->getRadius())
		{
			return true;
		}
		else
		{
			return false;
		}

	}
}
