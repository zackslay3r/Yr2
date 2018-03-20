#pragma once
#include <glm/ext.hpp>
#include <Gizmos.h>

// This is the enum ShapeType, used to identify the shapes within the simulation. 
enum ShapeType {
	JOINT = -1,
	PLANE,
	SPHERE
	


};
// this is the amount shape types defined as a int.
const int SHAPE_COUNT = 2;


class PhysicsObject
{	

public:
	// This is the constructor.
	PhysicsObject();
	// This is the destructor.
	~PhysicsObject();
	// This is the fixedUpdate function as a pure virtual function. 
	// this function takes two parameters.
	// glm::vec2 gravity -  this is the gravity. 
	// float timeStep - the is the physics timeStep.
	// This function returns void.
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	
	// This is the makeGizmo function as a pure virtual function.
	// This is responsible for the making of the objects.
	virtual void makeGizmo() = 0;
	
	// This is the getShapeId function. This is responsible for returning the shapeID.
	// as m_shapeID is a protected value.
	ShapeType getShapeId() { return m_shapeID; }

protected:
	// This is the shapeID value.
	ShapeType m_shapeID;
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {};

};

