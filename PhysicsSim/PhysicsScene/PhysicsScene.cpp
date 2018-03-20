#include "PhysicsScene.h"
#include <list>
#include <Input.h>


PhysicsScene::PhysicsScene()
{
}


PhysicsScene::~PhysicsScene()
{
	// delete all the actors from the vector so we dont get memory leaks.
	for (auto pActor : m_actors)
	{
		delete pActor;
	}

}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	// adding to the actors vector.
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject * actor)
{
	// set a variable to be actor that we wish to delete. and if we can find it, then delete it.
	auto a = std::find(m_actors.begin(), m_actors.end(), actor);
	// .end() function is a invisible object after the end of the vector.
	if (a != m_actors.end())
	{
		m_actors.erase(std::find(m_actors.begin(), m_actors.end(), actor));
	}
}

void PhysicsScene::update(float dt)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	//update physics at a fixed time step
	// this will ensure that the physics will slow if the frame rate is lower then warranted to prevent lockup.
	if (dt > m_timeStep)
	{
		dt = m_timeStep;
	}
	
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	// while accumlated is greater then the timestep.
	while (accumulatedTime >= m_timeStep)
	{
		// for each opf the actors, do a fixed update.
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
			

		}
		// then minus the timestep for the accumlated time.
		accumulatedTime -= m_timeStep;

		// now checks for collisions.
		checkForCollision();

	}
	
	
}

void PhysicsScene::updateGizmos()
{
	// for each of the actors. draw each of the objects.
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
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

			// if they are joints, we dont want to do a collision check.
			if (shapeId1 < 0 || shapeId2 < 0)
			{
				continue;
			}
			// using function pointers with a function index.
			int functionIdx = ( shapeId1 * SHAPE_COUNT ) + shapeId2;
			// function pointer assignment.
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			// if it is not null, then do the collision function based on the index.
			if (collisionFunctionPtr != nullptr)
			{
				//did a collision occur?
				collisionFunctionPtr(object1, object2);
			}

		}

	}
}

void PhysicsScene::checkForCollisionDeletion(Sphere *collisionCheckSphere)
{
	//count all the actors.
	int actorCount = m_actors.size();
	// convert the sphere to a physics object.
	PhysicsObject* object1 = ((PhysicsObject*)collisionCheckSphere);
	// create a vector that will be used to store the items that need to be deleted.
	std::vector<PhysicsObject*> toDelete;

	// if the conversion was sucesful, get the shape id of the two objects, and then setting the function index.
	if (object1 != nullptr)
	{
		for (int actors = 0; actors < actorCount; actors++)
		{
			PhysicsObject* object2 = m_actors[actors];

			int shapeId1 = object1->getShapeId();
			int shapeId2 = object2->getShapeId();


			if (shapeId1 < 0 || shapeId2 < 0)
			{
				continue;
			}
			// using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				//did a collision occur?
				if (collisionFunctionPtr(object1, object2) == true)
				{

					// For all the actors.
					for (auto var : m_actors)
					{
						// if the shape is a joint.
						if (var->getShapeId() == ShapeType::JOINT)
						{
							//get rid of the springs attached to that body.
							if (((Spring*)var)->m_body1 == object2 || ((Spring*)var)->m_body2 == object2)
							{
								toDelete.push_back(var);
							}
						}


					}
					// to get rid of the main object.
					toDelete.push_back(object2);

				

					//m_actors.erase(std::find(m_actors.begin(), m_actors.end(), object2));
				}

			}

		}
		// for each item in the delete items vector, delete them from the actors vector.
		for (auto deleteItem : toDelete)
		{
			
			if (deleteItem != nullptr && toDelete.size() > 0)
			{	
				auto p = std::find(m_actors.begin(), m_actors.end(), deleteItem);
				if (p == m_actors.end())
				{
					continue;
				}
				//if (p != m_actors.end())
				else
				{
					m_actors.erase(std::find(m_actors.begin(), m_actors.end(), deleteItem));
				}
			}
		}
	}
}


// plane to plane will never happen.
bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

// plane to sphere is sphere to plane.
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
		// this gets the contact point of where the two objects hit
		glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
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
			plane->resolveCollision(dynamic_cast<RigidBody*>(sphere),contact);
			sphere->setPosition(sphere->getPosition() + collisionNormal * intersection);
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

	// if we succeed, test for a collision.

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float distanceAway = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		//glm::vec2 direction = glm::normalize(sphere2->getPosition() - sphere1->getPosition());
		glm::vec2 direction = glm::normalize(sphere1->getPosition() - sphere2->getPosition());
		if (distanceAway < sphere1->getRadius() + sphere2->getRadius())
		{
			
			glm::vec2 touchpos;	
			touchpos = (glm::normalize(sphere2->getPosition() - sphere1->getPosition()) * sphere1->getRadius());
			
			float radiusSum = sphere1->getRadius() + sphere2->getRadius();
			if (sphere2->isKinematic())
			{
				sphere1->setPosition(sphere1->getPosition() + direction * (radiusSum - distanceAway));
			}
			if (sphere1->isKinematic())
			{
				sphere2->setPosition(sphere2->getPosition() - direction * (radiusSum - distanceAway));
			}
			sphere1->resolveCollision(sphere2,touchpos);
			
		
			// if both of the spheres can move...
			if (!sphere1->isKinematic() && !sphere2->isKinematic())
			{
				// get the mass of both objects.
				float combinedMass =  1 / sphere1->getMass() + 1 / sphere2->getMass();
				// then get the ratio of how much each object weights.
				float ratioA = (1 / sphere1->getMass()) / combinedMass;
				float ratioB = (1 / sphere2->getMass()) / combinedMass;
				// then set the positions based on this ratio * position vector
				sphere1->setPosition(sphere1->getPosition() + (direction * ratioA));
				sphere2->setPosition(sphere2->getPosition() + (direction * -ratioB));
			}
			return true;
		}
		else
		{
			return false;
		}

	}

}
