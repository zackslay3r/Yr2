#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float angularVelocity, float elasticity);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force, glm::vec2 pos);
	//void applyForceToActor(RigidBody* actor2, glm::vec2 force);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;
	void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal=nullptr);
	glm::vec2 getPosition() { return m_position; }
	float getRotation();
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec2 velocity);
	
	float getMass() { return (m_isKinematic) ? INT_MAX : m_mass; }
	void setLinearDrag(float value);
	void setAngularDrag(float value);
	void setAngularVelocity(float value);
	void setElasticity(float elasticity);
	void setKinematic(bool state) { m_isKinematic = state; }
	float getLinearDrag() { return m_linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	float getAngularVelocity() { return m_angularVelocity; }
	float getElasticity() { return m_elasticity; }
	bool isKinematic() { return m_isKinematic; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_linearDrag = 0.3f;
	float m_angularDrag = 0.3f;
	const float MIN_LINEAR_THRESHOLD = 0.1f;
	const float MIN_ROTATION_THRESHOLD = 0.01f;
	float m_angularVelocity;
	float m_moment;
	float m_mass;
	float m_rotation; // 2D so we only need a signle float to represent our rotation.
	float m_elasticity;
	bool m_isKinematic;
};

