#include "PhysicsScene.h"
#include <list>
#include <Input.h>


PhysicsScene::PhysicsScene()
{
}


PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}

}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject * actor)
{
}

void PhysicsScene::update(float dt)
{
	// input example
	aie::Input* input = aie::Input::getInstance();
	static std::list<PhysicsObject*> dirty;
	//update physics at a fixed time step


	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
			

		}

		accumulatedTime -= m_timeStep;


		//check for collisions
		//for (auto pActor : m_actors)
		//{
		//	for (auto pOther : m_actors)
		//	{
		//		if (pActor == pOther)
		//		{
		//			continue;
		//		}

		//		if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() && std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
		//		{
		//			continue;
		//		}

		//		RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);

		//		if (pRigid->checkCollision(pOther) == true)
		//		{
		//			pRigid->applyForceToActor(dynamic_cast<RigidBody*>(pOther), pRigid->getVelocity() * pRigid->getMass());
		//			dirty.push_back(pRigid);
		//			dirty.push_back(pOther);
		//		}
		//	
		//	}
		//}
		/*dirty.clear();*/
		checkForCollision();

	}
	
	if (input->isKeyDown(aie::INPUT_KEY_F))
	{

		for (auto pActor : m_actors)
		{
			RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);

			pRigid->applyForce(glm::vec2(2, 0));
		}
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}

}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->debug();
		count++;

	}
}

//function pointer array for the collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
PhysicsScene::plane2Plane,
PhysicsScene::plane2Sphere,
PhysicsScene::sphere2Plane,
PhysicsScene::sphere2Sphere
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	//need to check for collisions against all objects except this one.
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			int shapeId1 = object1->getShapeId();
			int shapeId2 = object2->getShapeId();

			// using function pointers
			int functionIdx = ( shapeId1 * SHAPE_COUNT - 1 ) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				//did a collision occur?
				collisionFunctionPtr(object1, object2);
			}

		}

	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	if (sphere2Plane(obj2, obj1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	// if we are sucessful then test for a collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

		// if we are behind the plane flip the normal
		if(sphereToPlane < 0) 
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;

		if (intersection > 0)
		{
			sphere->setVelocity(glm::vec2(0,0));
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//cast the objects to sphere and sphere
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	// if we suceed, test for a collision.

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float distanceAway = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		if (distanceAway < sphere1->getRadius() + sphere2->getRadius())
		{
			
			sphere1->resolveCollision(sphere2);
			return true;
		}
		else
		{
			return false;
		}

	}

}
