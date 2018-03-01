#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	// This is a RigidBody constructor. it takes 5 parameters.
	// ShapeType shapeID -  A shapeID.
	// glm::vec2 position - A position in the window of the simulation.
	// glm::vec2 velocity - A inital velocity.
	// float rotation - A inital rotation.
	// float mass - the mass of the object.
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	
	// This is a Rigidbody constructor. it is the same as the one above with 2 additional parameters.
	// float angularVelocity - Gives the Rigidbody a inital angular velocity.
	// float elasticity - GIves the rigidbody an elasticity value.
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float angularVelocity, float elasticity);
	// This is the rigidbody destructor. 
	~RigidBody();

	//************************************
	// Method:    fixedUpdate
	// FullName:  RigidBody::fixedUpdate
	// Access:    virtual public 
	// Returns:   void
	// Parameter: glm::vec2 gravity - the gravity in PhysicsScene.
	// Parameter: float timeStep - the timeStep in PhysicsScene.
	// Description: This is the fixedUpdate of a RigidBody object.
	//************************************
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	//************************************
	// Method:    applyForce
	// FullName:  RigidBody::applyForce
	// Access:    public 
	// Returns:   void
	// Parameter: glm::vec2 force - the force being applied to a Rigidbody.
	// Parameter: glm::vec2 pos - the position offset of where the force is being applied too.
	// Description: Used to apply forces to RigidBody objects.
	//************************************
	void applyForce(glm::vec2 force, glm::vec2 pos);


	//************************************
	// Method:    checkCollision
	// FullName:  RigidBody::checkCollision
	// Access:    virtual public 
	// Returns:   bool
	// Parameter: PhysicsObject * pOther - the other object a rigidbody is checking for a collision against.
	// Description: This function is used for checking collision's against other objects.
	//************************************
	virtual bool checkCollision(PhysicsObject* pOther) = 0;
	//************************************
	// Method:    resolveCollision
	// FullName:  RigidBody::resolveCollision
	// Access:    public 
	// Returns:   void
	// Parameter: RigidBody * actor2 - the second rigidbody object.
	// Parameter: glm::vec2 contact - the contact point at which the two objects collided.
	// Parameter: glm::vec2 * collisionNormal - the normal at which the two objects collided.
	// Description : used for the resolving of collisions.
	//************************************
	void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal=nullptr);
	//************************************
	// Method:    getPosition
	// FullName:  RigidBody::getPosition
	// Access:    public 
	// Returns:   glm::vec2
	// Description: used to return the position of a RigidBody.
	//************************************
	glm::vec2 getPosition() { return m_position; }
	//************************************
	// Method:    getRotation
	// FullName:  RigidBody::getRotation
	// Access:    public 
	// Returns:   float
	// Description : used to return the rotation of a RigidBody.
	//************************************
	float getRotation();
	//************************************
	// Method:    getVelocity
	// FullName:  RigidBody::getVelocity
	// Access:    public 
	// Returns:   glm::vec2
	// Description : used to return the velocity of a RigidBody.
	//************************************
	glm::vec2 getVelocity() { return m_velocity; }
	//************************************
	// Method:    setVelocity
	// FullName:  RigidBody::setVelocity
	// Access:    public 
	// Returns:   void
	// Parameter: glm::vec2 velocity - a velocity that the object will be set to.
	//************************************
	void setVelocity(glm::vec2 velocity);
	
	//************************************
	// Method:    getMass
	// FullName:  RigidBody::getMass
	// Access:    public 
	// Returns:   float
	// Description : used to return the mass of a RigidBody. will return INT_MAX if the object is kinematic.
	//************************************
	float getMass() { return (m_isKinematic) ? INT_MAX : m_mass; }
	//************************************
	// Method:    setLinearDrag
	// FullName:  RigidBody::setLinearDrag
	// Access:    public 
	// Returns:   void
	// Parameter: float value - the desired linear drag.
	// Description : used to set the linear drag of a RigidBody.
	//************************************
	void setLinearDrag(float value);
	//************************************
	// Method:    setAngularDrag
	// FullName:  RigidBody::setAngularDrag
	// Access:    public 
	// Returns:   void
	// Parameter: float value - the desired angular drag.
	// Description : used to set the angular drag of a RigidBody.
	//************************************
	void setAngularDrag(float value);
	//************************************
	// Method:    setAngularVelocity
	// FullName:  RigidBody::setAngularVelocity
	// Access:    public 
	// Returns:   void
	// Parameter: float value - the desired angular velocity.
	// Description : used to set the angular velocity of a RigidBody.
	//************************************
	void setAngularVelocity(float value);
	//************************************
	// Method:    setElasticity
	// FullName:  RigidBody::setElasticity
	// Access:    public 
	// Returns:   void
	// Parameter: float elasticity - the desired elasticity.
	// Description : used to set the elasticity of a RigidBody.
	//************************************
	void setElasticity(float elasticity);
	//************************************
	// Method:    setKinematic
	// FullName:  RigidBody::setKinematic
	// Access:    public 
	// Returns:   void
	// Parameter: bool state - True/False used to set an object to be or not to be kinematic.
	// Description : used to set m_kinematic of a RigidBody.
	//************************************
	void setKinematic(bool state) { m_isKinematic = state; }
	//************************************
	// Method:    setPosition
	// FullName:  RigidBody::setPosition
	// Access:    public 
	// Returns:   void
	// Parameter: glm::vec2 position - a position in the simulation.
	// Description : used to set the position of a RigidBody.
	//************************************
	void setPosition(glm::vec2 position);
	//************************************
	// Method:    getLinearDrag
	// FullName:  RigidBody::getLinearDrag
	// Access:    public 
	// Returns:   float
	// Description : Used to get the value of m_linearDrag.
	//************************************
	float getLinearDrag() { return m_linearDrag; }
	//************************************
	// Method:    getAngularDrag
	// FullName:  RigidBody::getAngularDrag
	// Access:    public 
	// Returns:   float
	// Description : Used to get the value of m_angularDrag.
	//************************************
	float getAngularDrag() { return m_angularDrag; }
	//************************************
	// Method:    getAngularVelocity
	// FullName:  RigidBody::getAngularVelocity
	// Access:    public 
	// Returns:   float
	// Description : Used to get the value of m_angularVelocity.
	//************************************
	float getAngularVelocity() { return m_angularVelocity; }
	//************************************
	// Method:    getElasticity
	// FullName:  RigidBody::getElasticity
	// Access:    public 
	// Returns:   float
	// Description : Used to get the value of m_elasticity.
	//************************************
	float getElasticity() { return m_elasticity; }
	//************************************
	// Method:    isKinematic
	// FullName:  RigidBody::isKinematic
	// Access:    public 
	// Returns:   bool
	// Description : Used to get the value of m_isKinematic.
	//************************************
	bool isKinematic() { return m_isKinematic; }
	
protected:
	// The position and velocity vectors.
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	// The drags and its thresholds.
	float m_linearDrag = 0.3f;
	float m_angularDrag = 0.3f;
	const float MIN_LINEAR_THRESHOLD = 0.1f;
	const float MIN_ROTATION_THRESHOLD = 0.01f;
	// angular velocity.
	float m_angularVelocity;
	// momentum
	float m_moment;
	//mass
	float m_mass;
	// rotation
	float m_rotation; // 2D so we only need a single float to represent our rotation.
	// elasticity
	float m_elasticity;
	// kinematic (static or dynamic.)
	bool m_isKinematic;

};

