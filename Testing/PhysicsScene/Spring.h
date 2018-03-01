#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
class Spring :
	public PhysicsObject
{
public:
	// This is the constructor of a Spring object. it has 9 parameters.
	// RigidBody* body1 - the first rigidbody the spring is attached to.
	// RigidBody* body2 - the second rigidbody the spring is attached to.
	// float restLength - the resting length of the spring.
	// float springCoefficient - the strength of the spring.
	// glm::vec4 LineColour - the colour of the spring.
	// float breakforce - the amount of force required to break the spring.
	// float damping - the time required for the spring to return to resting length.
	// glm::vec2 contact1 - the offset of where to spring is attached to the first object.
	// glm::vec2 contact2 - the offset of where to spring is attached to the second object.
	Spring(RigidBody* body1, RigidBody* body2,float restLength, float springCoefficient, glm::vec4 LineColour, float breakforce, float damping = 0.1f, glm::vec2 contact1=glm::vec2(0,0), glm::vec2 contact2=glm::vec2(0,0));
	// This is the destructor.
	~Spring();
	
	//************************************
	// Method:    fixedUpdate
	// FullName:  Spring::fixedUpdate
	// Access:    public 
	// Returns:   void
	// Parameter: glm::vec2 gravity - the gravity value from PhysicsScene.
	// Parameter: float timeStep - the timeStep value from PhysicsScene.
	// Description: This is responsible for doing the fixedUpdate of the Spring object.
	//************************************
	void fixedUpdate(glm::vec2 gravity, float timeStep);
	
	//************************************
	// Method:    makeGizmo
	// FullName:  Spring::makeGizmo
	// Access:    public 
	// Returns:   void
	// Description: This is responsible for doing the makeGizmo function of the Plane object.
	//************************************
	void makeGizmo();
	// The two rigidbodies the spring is attached to.
	RigidBody* m_body1;
	RigidBody* m_body2;
	// the contact points of the two springs.
	glm::vec2 m_contact1;
	glm::vec2 m_contact2;
	// color of the spring.
	glm::vec4 m_colour;
	// breakforce.
	float m_breakForce;
	// damping
	float m_damping;
	// rest length.
	float m_restLength;
	// spring strength. 
	float m_springCoefficent; // the restoring force;
};

