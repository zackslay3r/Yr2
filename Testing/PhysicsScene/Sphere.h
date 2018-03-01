#pragma once
#include "RigidBody.h"
class Sphere :
	public RigidBody
{
public:
	// This is the Sphere constructor. it takes 5 parameters.
	// glm::vec2 position - The intial position of the sphere object.
	// glm::vec2 velocity - The intial velocity of the sphere object.
	// float mass - The mass of the sphere object.
	// float radius - The radius of the sphere.
	// glm::vec4 colour - The colour of the sphere.
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	// This is the destructor.
	~Sphere();


	//************************************
	// Method:    makeGizmo
	// FullName:  Sphere::makeGizmo
	// Access:    virtual public 
	// Returns:   void
	// Description: This is responsible for doing the makeGizmo function of the Sphere object.
	//************************************
	virtual void makeGizmo();

	//************************************
	// Method:    checkCollision
	// FullName:  Sphere::checkCollision
	// Access:    virtual public 
	// Returns:   bool
	// Parameter: PhysicsObject * pOther - the object its checking the collision against.
	// Description: Used for checking if a sphere object has collided with something else.
	//************************************
	virtual bool checkCollision(PhysicsObject* pOther);

	//************************************
	// Method:    getRadius
	// FullName:  Sphere::getRadius
	// Access:    public 
	// Returns:   float
	// Description: Used to get the value of m_radius.
	//************************************
	float getRadius() { return m_radius; }
	
	//************************************
	// Method:    getColour
	// FullName:  Sphere::getColour
	// Access:    public 
	// Returns:   glm::vec4
	// Description: Used to get the value of m_colour.
	//************************************
	glm::vec4 getColour() { return m_colour; }

protected:
	// The radius of the circle.
	float m_radius;
	// the colour of the circle.
	glm::vec4 m_colour;

};

