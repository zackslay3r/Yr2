#pragma once
#include "PhysicsObject.h"
class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force);
	void applyForceToActor(RigidBody* actor2, glm::vec2 force);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;

	glm::vec2 getPosition() { return m_position; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec2 velocity);
	void resolveCollision(RigidBody* actor2);
	float getMass() { return m_mass; }
	void setLinearDrag(float value);
	void setAngularDrag(float value);
	void setAngularVelocity(float value);
	float getLinearDrag() { return m_linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	float getAngularVelocity() { return m_angularVelocity; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_linearDrag = 0.3f;
	float m_angularDrag = 0.3f;
	float m_angularVelocity;
	float m_mass;
	float m_rotation; // 2D so we only need a signle float to represent our rotation.
};

