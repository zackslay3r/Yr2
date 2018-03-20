#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

class Plane :
	public PhysicsObject
{
public:
	// This is the default constructor.
	Plane();
	// This is a constructor for a plane object, it takes 2 parameters.
	// glm::vec2 normal - the normal for which the plane will be drawn.
	// float distance - the offset from the center.
	Plane(glm::vec2 normal, float distance);
	// This is the destructor.
	~Plane();

	//************************************
	// Method:    fixedUpdate
	// FullName:  Plane::fixedUpdate
	// Access:    virtual public 
	// Returns:   void
	// Parameter: glm::vec2 gravity - the gravity value from PhysicsScene.
	// Parameter: float timeStep - the timeStep value from PhysicsScene.
	// Description: This is responsible for doing the fixedUpdate of the Plane object.
	//************************************
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	//************************************
	// Method:    makeGizmo
	// FullName:  Plane::makeGizmo
	// Access:    virtual public 
	// Returns:   void
	// Description: This is responsible for doing the makeGizmo function of the Plane object.
	//************************************
	virtual void makeGizmo();

	//************************************
	// Method:    resolveCollision
	// FullName:  Plane::resolveCollision
	// Access:    public 
	// Returns:   void
	// Parameter: RigidBody * actor2 - a rigidbody object.
	// Description: This is used for collision resolution of a particular rigidbody.
	//************************************
	void resolveCollision(RigidBody* actor2);
	//************************************
	// Method:    resolveCollision
	// FullName:  Plane::resolveCollision
	// Access:    public 
	// Returns:   void
	// Parameter: RigidBody * actor2 - a rigidbody object.
	// Parameter: glm::vec2 contact - the contact point where the collision happened.
	// Description: This is used for collision resolution of a particular rigidbody at a contact point.
	//************************************
	void resolveCollision(RigidBody* actor2, glm::vec2 contact);

	//************************************
	// Method:    getNormal
	// FullName:  Plane::getNormal
	// Access:    public 
	// Returns:   glm::vec2
	// Description: returns the value of m_normal.
	//************************************
	glm::vec2 getNormal() { return m_normal; }
	//************************************
	// Method:    getDistance
	// FullName:  Plane::getDistance
	// Access:    public 
	// Returns:   float
	// Description: returns the value of m_distanceToOrigin.
	//************************************
	float getDistance() { return m_distanceToOrigin; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
};

