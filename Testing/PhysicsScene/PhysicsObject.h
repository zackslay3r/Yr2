#pragma once
#include <glm/ext.hpp>
#include <Gizmos.h>

// this enum will be used for shapeType
enum ShapeType {
	JOINT = -1,
	PLANE,
	SPHERE
	


};

const int SHAPE_COUNT = 2;


class PhysicsObject
{	
protected:	
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {};
public:
	PhysicsObject();
	~PhysicsObject();
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	ShapeType getShapeId() { return m_shapeID; }

protected:
	ShapeType m_shapeID;


};

