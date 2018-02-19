#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
class Spring :
	public PhysicsObject
{
public:
	Spring(RigidBody* body1, RigidBody* body2,float restLength, float springCoefficient, glm::vec4 LineColour, float damping = 0.1f, glm::vec2 contact1=glm::vec2(0,0), glm::vec2 contact2=glm::vec2(0,0));
	~Spring();
	
	void fixedUpdate(glm::vec2 gravity, float timeStep);
	void makeGizmo();
	RigidBody* m_body1;
	RigidBody* m_body2;
	void debug();
	glm::vec2 m_contact1;
	glm::vec2 m_contact2;
	glm::vec4 m_colour;
	float m_damping;
	float m_restLength;
	float m_springCoefficent; // the restoring force;
};

