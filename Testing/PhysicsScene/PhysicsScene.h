#pragma once
#include "PhysicsObject.h"
#include <vector>
#include "RigidBody.h"
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "Spring.h"

using namespace std;

class PhysicsScene
{
public:
	// This is the PhysicsScene constructor.
	PhysicsScene();
	// This is the PhysicsScene destructor.
	~PhysicsScene();


	//************************************
	// Method:    addActor
	// FullName:  PhysicsScene::addActor
	// Access:    public 
	// Returns:   void
	// Parameter: PhysicsObject * actor - a physicsObject.
	// Description : This function is responsible for adding a PhysicsObject to the vector m_actors.
	//************************************
	void addActor(PhysicsObject* actor);
	//************************************
	// Method:    removeActor
	// FullName:  PhysicsScene::removeActor
	// Access:    public 
	// Returns:   void
	// Parameter: PhysicsObject * actor - a physicsObject.
	// Description : This function is responsible for removing a PhysicsObject from the vector m_actors.
	//************************************
	void removeActor(PhysicsObject* actor);
	//************************************
	// Method:    update
	// FullName:  PhysicsScene::update
	// Access:    public 
	// Returns:   void
	// Parameter: float dt
	// Description : This is responsible for the updating the physicsScene.
	//************************************
	void update(float dt);
	//************************************
	// Method:    updateGizmos
	// FullName:  PhysicsScene::updateGizmos
	// Access:    public 
	// Returns:   void
	// Description: This is responsible for updating the gizmo's in the PhysicsScene.
	//************************************
	void updateGizmos();


	

	//************************************
	// Method:    setGravity
	// FullName:  PhysicsScene::setGravity
	// Access:    public 
	// Returns:   void
	// Parameter: const glm::vec2 gravity - desired gravity.
	// Description : Responsible for setting the gravity of the scene.
	//************************************
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	//************************************
	// Method:    getGravity
	// FullName:  PhysicsScene::getGravity
	// Access:    public 
	// Returns:   glm::vec2
	// Description: responsible for returning the m_gravity value.
	//************************************
	glm::vec2 getGravity() const { return m_gravity; }

	//************************************
	// Method:    setTimeStep
	// FullName:  PhysicsScene::setTimeStep
	// Access:    public 
	// Returns:   void
	// Parameter: const float timeStep -  the desired timestep.
	// Description : Responsible for setting the timestep.
	//************************************
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	//************************************
	// Method:    getTimeStep
	// FullName:  PhysicsScene::getTimeStep
	// Access:    public 
	// Returns:   float
	// Description: Responsible for returning the value of m_timeStep.
	//************************************
	float getTimeStep() const { return m_timeStep; }

	//************************************
	// Method:    checkForCollision
	// FullName:  PhysicsScene::checkForCollision
	// Access:    public 
	// Returns:   void
	// Description: Responsible for checking to see if a collision has happened.
	//************************************
	void checkForCollision();
	//************************************
	// Method:    checkForCollisionDeletion
	// FullName:  PhysicsScene::checkForCollisionDeletion
	// Access:    public 
	// Returns:   void
	// Parameter: Sphere * collisionCheckSphere
	// Description: Responsible for doing a collision detection against an invisible
	// circle and an object to see if they are colliding, used for deletion purposes.
	//************************************
	void checkForCollisionDeletion(Sphere* collisionCheckSphere);

	//************************************
	// Method:    plane2Plane
	// FullName:  PhysicsScene::plane2Plane
	// Access:    public static 
	// Returns:   bool
	// Parameter: PhysicsObject *
	// Parameter: PhysicsObject *
	// Description: Is responsible for the collision detection between a plane and a plane.
	//************************************
	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	//************************************
	// Method:    plane2Sphere
	// FullName:  PhysicsScene::plane2Sphere
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: PhysicsObject *
	// Parameter: PhysicsObject *
	// Description: 	// Description: Is responsible for the collision detection between a plane and a sphere.
	//************************************
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	//************************************
	// Method:    sphere2Plane
	// FullName:  PhysicsScene::sphere2Plane
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: PhysicsObject *
	// Parameter: PhysicsObject *
	// Description: Is responsible for the collision detection between a sphere and a plane.
	//************************************
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	//************************************
	// Method:    sphere2Sphere
	// FullName:  PhysicsScene::sphere2Sphere
	// Access:    public static 
	// Returns:   bool
	// Qualifier:
	// Parameter: PhysicsObject *
	// Parameter: PhysicsObject *
	// Description: Is responsible for the collision detection between a sphere and a sphere.
	//************************************
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	
	// We are making the list of PhysicsObjects.
	std::vector<PhysicsObject*> m_actors;
protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	
};

