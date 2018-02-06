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
		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
				{
					continue;
				}

				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() && std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				{
					continue;
				}

				RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);

				if (pRigid->checkCollision(pOther) == true)
				{
					pRigid->applyForceToActor(dynamic_cast<RigidBody*>(pOther), pRigid->getVelocity() * pRigid->getMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			
			}
		}
		dirty.clear();

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
