#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Spring.h"
#include <list>
#include <glm/ext.hpp>
#include "Box.h"
#include <string>
#include <iomanip>

PhysicsSceneApp::PhysicsSceneApp() {

}

PhysicsSceneApp::~PhysicsSceneApp() {

}

bool PhysicsSceneApp::startup() {
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);


	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = std::unique_ptr<aie::Font>(new aie::Font("../bin/font/consolas.ttf", 32));

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -50));
	m_physicsScene->setTimeStep(0.01f);




	//Sphere* ball = new Sphere(glm::vec2(450, 130), glm::vec2(0, 0), 1.0f, 15, glm::vec4(1, 0, 0, 1));

	//m_physicsScene->addActor(ball);

	//Sphere* ballTwo = new Sphere(glm::vec2(-20, 30), glm::vec2(0, 0), 1.0f, 15, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(ballTwo);

	//Sphere* springBall2 = new Sphere(glm::vec2(35, 50), glm::vec2(0, 0), 1.3f, 15, glm::vec4(1, 1, 1, 1));
	//m_physicsScene->addActor(springBall2);


	Plane* floor = new Plane(glm::vec2(0, 1), 20);
	m_physicsScene->addActor(floor);


	// Testing boxes here. 
	//Box* test = new Box(glm::vec2(10, 10), glm::vec4(1, 1, 1, 1), glm::vec2(200, 200), glm::vec2(0, 0), 1);
	//m_physicsScene->addActor(test);

	// MakeSoftBody(rows,coloums,circleRadius,softbodymass,startingpos,spacing,springstrength)
	//MakeSoftBody(6, 20, 5, 25, glm::vec2(300, 600), 12.5, 0.75, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1));

	//MakeSoftBody(3, 3, 5, 20, glm::vec2(300, 600), 12.5, 5, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1));

	//MakeSoftBody(5, 5, 10, 20, glm::vec2(300, 800), 22.5, 1.25, glm::vec4(1, 0, 0, 1), glm::vec4(1, 0, 0, 1));

	//MakeSoftBody(3, 3, 7, 3, glm::vec2(500, 700), 16, 0.4, glm::vec4(0, 0, 1, 1), glm::vec4(0, 0, 1, 1));

	Sphere* staticBall8 = new Sphere(glm::vec2(350, 200), glm::vec2(0, 0), 1.3f, 25, glm::vec4(1, 1, 1, 1));
	staticBall8->setElasticity(0.9f);
	staticBall8->setKinematic(true);
	m_physicsScene->addActor(staticBall8);

	Sphere* staticBall2 = new Sphere(glm::vec2(410, 300), glm::vec2(0, 0), 1.3f, 25, glm::vec4(1, 1, 1, 1));
	staticBall2->setElasticity(0.9f);
	staticBall2->setKinematic(true);
	m_physicsScene->addActor(staticBall2);



	Sphere* ball1;
	ball1 = new Sphere(glm::vec2(200, 400), glm::vec2(0, 0), 1, 15, glm::vec4(1, 1, 1, 1));
	ball1->setKinematic(true);
	m_physicsScene->addActor(ball1);

	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(240, 400), glm::vec2(0, 0), 6, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(new Spring(ball1, ball2, 40, 0.5, glm::vec4(1, 1, 1, 1)));

	Sphere* ball3;
	ball3 = new Sphere(glm::vec2(280, 400), glm::vec2(0, 0), 6, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(ball3);
	m_physicsScene->addActor(new Spring(ball2, ball3, 40, 0.5, glm::vec4(1, 1, 1, 1)));

	Sphere* ball4;
	ball4 = new Sphere(glm::vec2(320, 400), glm::vec2(0, 0), 50, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(ball4);
	m_physicsScene->addActor(new Spring(ball3, ball4, 40, 0.5, glm::vec4(1, 1, 1, 1)));

	Sphere* ball5 = new Sphere(glm::vec2(10, 20), glm::vec2(0, 0), 10.0f, 5, glm::vec4(1, 0, 0, 1));

	m_physicsScene->addActor(ball5);
	return true;
}

void PhysicsSceneApp::shutdown() {


	delete m_2dRenderer;
}

void PhysicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();


	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	int screenWidth = getWindowWidth();
	int screenHeight = getWindowHeight();

	if (input->wasKeyPressed(aie::INPUT_KEY_0))
	{
		
		// get the point along the x that the mouse pointer hit
		float mouseX = input->getMouseX();
		float mouseY = input->getMouseY();		
		
		m_physicsScene->addActor(new Sphere(glm::vec2((float)mouseX, (float)mouseY), glm::vec2(0, 0), 4, 10, glm::vec4(1, 1, 1, 1)));

		
	}
	// Deletion via right mouse button
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		glm::vec2 tempVec;
		tempVec.x = input->getMouseX();
		tempVec.y = input->getMouseY();

		Sphere* collisionSphere = new Sphere(tempVec, glm::vec2(0, 0), 1, 0.1, glm::vec4(1, 1, 1, 1));
		collisionSphere->setKinematic(true);

		m_physicsScene->checkForCollision(collisionSphere);
		
	}

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		switch (spawnIndex + 1)
		{
		case 1:
			if (PlaneNormal.x > 0.01f && PlaneNormal.y < 0.1f)
			{
				m_physicsScene->addActor(new Plane(PlaneNormal, input->getMouseX()));
			}
			if (PlaneNormal.y > 0.01f && PlaneNormal.x < 0.1f)
			{
				m_physicsScene->addActor(new Plane(PlaneNormal, input->getMouseY()));
			}
			/*if(PlaneNormal.y > 0.01f && PlaneNormal.x > 0.01f)
			{
				m_physicsScene->addActor(new Plane(PlaneNormal, (abs(input->getMouseX() - 1280))));
			}*/
			break;
		case 2:
			m_physicsScene->addActor(new Sphere(glm::vec2(input->getMouseX(), input->getMouseY()), glm::vec2(0, 0), 10, 6, glm::vec4(1, 0, 1, 1)));
			break;
		case 3:
			MakeSoftBody(SoftBodySizeX, SoftBodySizeY, 5, 5, glm::vec2(input->getMouseX(), input->getMouseY()), 10, 0.75, glm::vec4(1, 0, 1, 1), glm::vec4(1, 0, 1, 1));
		default:
			break;
		}
	
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_KP_ADD))
	{
		spawnIndex++;
		if (spawnIndex + 1 > AmountOfShapes)
		{
			spawnIndex = 0;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_KP_SUBTRACT))
	{
		spawnIndex--;

		if (spawnIndex < 0)
		{
			spawnIndex = AmountOfShapes - 1;
		}
	}


	if (input->wasKeyPressed(aie::INPUT_KEY_KP_7))
	{
		switch (spawnIndex)
		{
		case 2:
			SoftBodySizeX += 1;
			break;
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_KP_8))
	{
		switch (spawnIndex)
		{
		case 2:
			SoftBodySizeY += 1;
			break;
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_KP_4))
	{
		switch (spawnIndex)
		{
		case 0:
			PlaneNormal.x = 0.1;
			PlaneNormal.y = 0.0;
			break;
		case 2:
			if (SoftBodySizeX >= 1)
			{
				SoftBodySizeX -= 1;
			}
			break;
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_KP_5))
	{
		switch (spawnIndex)
		{
		case 0:
			PlaneNormal.x = 0.0;
			PlaneNormal.y = 0.1;
			break;
		case 2:
			if (SoftBodySizeY >= 1)
			{
				SoftBodySizeY -= 1;
			}
		default:
			break;
		}
	}

	// Deletion via key
	if (input->wasKeyPressed(aie::INPUT_KEY_DELETE))
	{
		std::vector<PhysicsObject*> tempVec;
		Sphere* tempSphere;
		int sphereCount = 0;
		for (auto it : m_physicsScene->m_actors)
		{
			// loop though the stuff and make a vector of all the stuff we need to delete
			

			// search for a sphere and add it to the temp Vector.
			if (it->getShapeId() == ShapeType::SPHERE && sphereCount == 0)
			{
				tempVec.push_back(it);
				tempSphere = ((Sphere*)it);
				sphereCount++;
			}
		}		
		
			for (auto var : m_physicsScene->m_actors)
			{
					if (var->getShapeId() == ShapeType::JOINT)
					{
						if (((Spring*)var)->m_body1 == tempSphere || ((Spring*)var)->m_body2 == tempSphere)
						{
							tempVec.push_back(var);
						}
					}

				
			}
			
			
		

		for (auto deleteItem : tempVec)
		{
			m_physicsScene->m_actors.erase(std::find(m_physicsScene->m_actors.begin(), m_physicsScene->m_actors.end(), deleteItem));

		}
		


	}

	// Converting the floats to 1dp and outputting this if plane is selected. 
	
	sprintf_s(planex, "%.1f", PlaneNormal.x);
	sprintf_s(planey, "%.1f", PlaneNormal.y);
	


}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;

	//aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	std::string spawnStr = convertIndex(spawnIndex);
	aie::Gizmos::draw2D(glm::ortho<float>(0, this->getWindowWidth(), 0, this->getWindowHeight(), -1.0f, 1.0f));
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font.get(), "Press ESC to quit", 0, 0);


	m_2dRenderer->drawText(m_font.get(), spawnStr.c_str(), 800, 650);

	switch (spawnIndex)
	{
	case 0:
		m_2dRenderer->drawText(m_font.get(), planex, 900, 650);
		m_2dRenderer->drawText(m_font.get(), planey, 1000, 650);
		break;
	case 2:
		m_2dRenderer->drawText(m_font.get(), "Height: ", 700, 550);
		m_2dRenderer->drawText(m_font.get(), to_string(SoftBodySizeX).c_str(), 840, 550);
		m_2dRenderer->drawText(m_font.get(), "Width: ", 700, 500);
		m_2dRenderer->drawText(m_font.get(), to_string(SoftBodySizeY).c_str(), 840, 500);
	}


	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsSceneApp::MakeSoftBody(int amountHigh, int amountWide, int circleRadius, float circleMass, glm::vec2 startPos, float distanceApart, float springStrength, glm::vec4 sphereColour, glm::vec4 lineColour)
{
	// Before making all the new circles. we are going to create a temp list that these objects will get put into.
	// this is important so that we can have all the newly created circles linked with each other, but not anything else.
	// one for the spheres and one for the springs
	std::vector<Sphere*> newSpheres;
	std::vector<Spring*> newSprings;

	// This will create all the spheres
	for (int i = 0; i < amountHigh; i++)
	{
		for (int j = 0; j < amountWide; j++)
		{
			//m_physicsScene->addActor(new Sphere(glm::vec2((startPos.x + (distanceApart * j)), (startPos.y + (distanceApart * i))), glm::vec2(0, 0), softBodyMass, circleRadius, glm::vec4(0, 0, 1, 0)));
			newSpheres.push_back(new Sphere(glm::vec2((startPos.x + (distanceApart * j)), (startPos.y + (distanceApart * i))), glm::vec2(0, 0), circleMass, circleRadius, sphereColour));
		}
	}

	// Create all the new springs.
	for (int i = 0; i < newSpheres.size(); i++)
	{
		for (int j = i + 1; j < newSpheres.size(); j++)
		{
			if (distanceCheck(newSpheres.at(i), glm::sqrt(distanceApart * distanceApart + distanceApart * distanceApart) + 1,newSpheres.at(j)))
			{
				if (distanceCheck(newSpheres.at(i), distanceApart + 1, newSpheres.at(j)))
				{
					newSprings.push_back(new Spring(newSpheres.at(i), newSpheres.at(j), distanceApart, (springStrength *(amountHigh * amountWide)),lineColour));
				}
				else
				{
					newSprings.push_back(new Spring(newSpheres.at(i), newSpheres.at(j), glm::sqrt(distanceApart * distanceApart + distanceApart * distanceApart), ((springStrength *(amountHigh * amountWide))),lineColour));
				}
			}
			
		}
	}

	// then we are going to add all of these actors to the list.
	for (auto var : newSpheres)
	{
		m_physicsScene->addActor(var);
	}
	for (auto var : newSprings)
	{
		m_physicsScene->addActor(var);
	}
}

bool PhysicsSceneApp::distanceCheck(Sphere * sphere1, float distance, Sphere * sphereTwo)
{
	glm::vec2 tempVector;

	tempVector = sphere1->getPosition() - sphereTwo->getPosition();
	float distanceOfObjects = glm::length(tempVector);

	if (distanceOfObjects < distance)
	{

		return true;
	}
	else
	{
		return false;
	}
}

std::string PhysicsSceneApp::convertIndex(int shapeIndex)
{
	switch (shapeIndex + 1)
	{
	case 1:
		return std::string("Plane");
		break;
	case 2:
		return std::string("Sphere");
		break;
	case 3:
		return std::string("Softbody");
		break;
	default:
		return std::string("NULL");
		break;
	}
		
	
}


