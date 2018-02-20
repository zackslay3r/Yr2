#pragma once
#include "RigidBody.h"
class Box :
	public RigidBody
{
public:
	Box(glm::vec2 extents, glm::vec4 colour, glm::vec2 originOfBox, glm::vec2 velocity, float mass);
	~Box();

	glm::vec2 m_extents;
	glm::vec4 m_colour;
	float width, height;
	void fixedUpdate(glm::vec2 gravity, float timeStep);
	void makeGizmo();
	virtual bool checkCollision(PhysicsObject* pOther);
	// store the local x,y axes of the box based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

