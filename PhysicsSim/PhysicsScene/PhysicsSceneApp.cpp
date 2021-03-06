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
	m_screenText = std::unique_ptr<aie::Font>(new aie::Font("../bin/font/consolas.ttf", 16));
	m_uiHelpText = std::unique_ptr<aie::Font>(new aie::Font("../bin/font/consolas.ttf", 12));
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -50));
	m_physicsScene->setTimeStep(0.01f);


	// Spring demo.
	Sphere* staticBall = new Sphere(glm::vec2(300, 400), glm::vec2(0, 0), 1, 6, glm::vec4(1, 1, 1, 1));
	staticBall->setKinematic(true);
	m_physicsScene->addActor(staticBall);

	Sphere* dynamicBall = new Sphere(glm::vec2(350, 400), glm::vec2(0, 0), 10, 6, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(dynamicBall);

	Spring* connector = new Spring(staticBall, dynamicBall, 50, 0.75, glm::vec4(1, 0, 0, 1), 100);
	m_physicsScene->addActor(connector);



	// Joint demo.

	Sphere* staticBall2 = new Sphere(glm::vec2(400, 400), glm::vec2(0, 0), 1, 6, glm::vec4(1, 0, 0, 1));
	staticBall2->setKinematic(true);
	m_physicsScene->addActor(staticBall2);

	Sphere* dynamicBall2 = new Sphere(glm::vec2(450, 400), glm::vec2(0, 0), 10, 6, glm::vec4(1, 0, 0, 1));
	m_physicsScene->addActor(dynamicBall2);

	Spring* joint = new Spring(staticBall2, dynamicBall2, 50, 50, glm::vec4(1, 0, 0, 1), 52);
	m_physicsScene->addActor(joint);


	Plane* floor = new Plane(glm::vec2(0, 0.1), 10);
	m_physicsScene->addActor(floor);

	// Make this the default value for the starting softbody.
	springBreak = 36;
	MakeSoftBody(4, 4, 10, 5, glm::vec2(500, 400), 25, 0.75, glm::vec4(1, 0, 0, 1), glm::vec4(0, 0, 1, 1));
	// Then default it back for creation purposes.
	springBreak = 25;

	Sphere* SoftBodyBreaker = new Sphere(glm::vec2(530, 300), glm::vec2(0, 0), 1, 20, glm::vec4(1, 0, 1, 1));
	SoftBodyBreaker->setKinematic(true);
	m_physicsScene->addActor(SoftBodyBreaker);

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
	breakCheck();

	// For all the actors, we are going to check their positions and if they exceed the screen boundaries
	// delete them. this is for optimizations.
	for (auto var : m_physicsScene->m_actors)
	{
		glm::vec2 position = ((RigidBody*)var)->getPosition();

		if (position.x > this->getWindowWidth() || position.x < 0)
		{
			Sphere* deleteSphere = new Sphere(position, glm::vec2(0, 0), 1, 0.1, glm::vec4(1, 1, 1, 1));
			deleteSphere->setKinematic(true);

			m_physicsScene->checkForCollisionDeletion(deleteSphere);
			delete deleteSphere;
		}

		if (position.y > this->getWindowHeight() || position.y < 0)
		{
			Sphere* deleteSphere = new Sphere(position, glm::vec2(0, 0), 1, 0.1, glm::vec4(1, 1, 1, 1));
			deleteSphere->setKinematic(true);

			m_physicsScene->checkForCollisionDeletion(deleteSphere);
			delete deleteSphere;
		}
	}
	

	//
	// ALL INPUTS
	//

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
	int screenWidth = getWindowWidth();
	int screenHeight = getWindowHeight();

	if (input->wasKeyPressed(aie::INPUT_KEY_0))
	{
		
		// get the point along the x that the mouse pointer hit
		float mouseX = float(input->getMouseX());
		float mouseY = float(input->getMouseY());		
		
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

		m_physicsScene->checkForCollisionDeletion(collisionSphere);
		delete collisionSphere;
	}

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		// create a temporary sphere in case a sphere is created as the target object.
		Sphere* tempSphere = new Sphere(glm::vec2(input->getMouseX(), input->getMouseY()), glm::vec2(0, 0), sphereMass, sphereRadius, glm::vec4(1, 0, 1, 1));
		switch (spawnIndex )
		{
		case 0:
			if (PlaneNormal.x > 0.01f && PlaneNormal.y < 0.1f)
			{
				m_physicsScene->addActor(new Plane(PlaneNormal, input->getMouseX()));
			}
			if (PlaneNormal.y > 0.01f && PlaneNormal.x < 0.1f)
			{
				m_physicsScene->addActor(new Plane(PlaneNormal, input->getMouseY()));
			}
			break;
		case 1:
			
				if (sphereKinematic == true)
				{
					tempSphere->setKinematic(true);
				}
				m_physicsScene->addActor(tempSphere);

			break;
		case 2:
			MakeSoftBody(SoftBodySizeX, SoftBodySizeY, 5, softBodyMass, glm::vec2(input->getMouseX(), input->getMouseY()), 10, tempSpringCoefficent, glm::vec4(1, 0, 1, 1), glm::vec4(1, 0, 1, 1));
		default:
			break;
		}
	
	}
	// a clear all function.
	if (input->wasKeyPressed(aie::INPUT_KEY_F4))
	{
		m_physicsScene->m_actors.clear();
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
		case 1:
			sphereRadius += 1.0f;
			break;
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
		case 1:
			sphereMass += 2.5f;
			break;
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
		case 1:
			if (sphereRadius > 0.0)
			{
				sphereRadius -= 1.0f;
			}
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
		case 1:
			if (sphereMass > 0)
			{
				sphereMass -= 2.5f;
			}
		case 2:
			if (SoftBodySizeY >= 1)
			{
				SoftBodySizeY -= 1;
			}
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_KP_9))
	{
		switch (spawnIndex)
		{
		case 1:
			sphereKinematic = true;
			break;
		case 2:
		
				tempSpringCoefficent += 0.05;
			
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_KP_6))
	{
		switch (spawnIndex)
		{
		case 1:
			sphereKinematic = false;
			break;
		case 2:
			if (tempSpringCoefficent > 0.04)
			{
				tempSpringCoefficent -= 0.05;
			}
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_PAGE_UP))
	{
		switch (spawnIndex)
		{
		case 2:
			if (softBodyMass >= 0.0)
			{
				softBodyMass += 2.5;
			}
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_PAGE_DOWN))
	{
		switch (spawnIndex)
		{
		case 2:
			if (softBodyMass > 0.0)
			{
				softBodyMass -= 2.5;
			}
		default:
			break;
		}
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_HOME))
	{
		switch (spawnIndex)
		{
		case 2:
			springBreak += 1;
		default:
			break;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_END))
	{
		switch (spawnIndex)
		{
		case 2:
			if (springBreak > 0.0)
			{
				springBreak -= 1;
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

	//
	//
	//

	// Converting the floats to 1dp and outputting this if plane is selected. 
	
	sprintf_s(planex, "%.1f", PlaneNormal.x);
	sprintf_s(planey, "%.1f", PlaneNormal.y);
	sprintf_s(springco, "%.02f", tempSpringCoefficent);
	sprintf_s(softbdmass, "%.02f", softBodyMass);
	sprintf_s(spheremass, "%.02f", sphereMass);
}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background color
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;

	

	
	aie::Gizmos::draw2D(glm::ortho<float>(0, this->getWindowWidth(), 0, this->getWindowHeight(), -1.0f, 1.0f));
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font.get(), "Press ESC to quit", 0, 0);
	setVSync(false);
	m_2dRenderer->drawText(m_font.get(), to_string(getFPS()).c_str(), 1200, 30);

	
	

	
	// Show the UI elements and the help.
	ShowUIElements();
	showUIHelp();

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
					newSprings.push_back(new Spring(newSpheres.at(i), newSpheres.at(j), distanceApart, (springStrength *(amountHigh * amountWide)),lineColour,springBreak));
				}
				else
				{
					newSprings.push_back(new Spring(newSpheres.at(i), newSpheres.at(j), glm::sqrt(distanceApart * distanceApart + distanceApart * distanceApart), ((springStrength *(amountHigh * amountWide))),lineColour,springBreak));
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

std::string PhysicsSceneApp::convertBool(bool kinematic)
{
	switch (kinematic)
	{
	case 1:
		return std::string("True");
		break;
	case 0:
		return std::string("False");
		break;

	default:
		return std::string("");
		break;
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

void PhysicsSceneApp::ShowUIElements()
{	
	std::string spawnStr = convertIndex(spawnIndex);
	std::string boolText = convertBool(sphereKinematic);
	switch (spawnIndex)
	{
	case 0:
		m_2dRenderer->drawText(m_screenText.get(), "X Axis: ", 1100, 650);
		m_2dRenderer->drawText(m_screenText.get(), planex, 1200, 650);
		m_2dRenderer->drawText(m_screenText.get(), "Y Axis: ", 1100, 630);
		m_2dRenderer->drawText(m_screenText.get(), planey, 1200, 630);
		break;
	case 1:
		m_2dRenderer->drawText(m_screenText.get(), "Size: ", 1100, 650);
		m_2dRenderer->drawText(m_screenText.get(), to_string(sphereRadius).c_str(), 1200, 650);
		m_2dRenderer->drawText(m_screenText.get(), "Mass: ", 1100, 630);
		m_2dRenderer->drawText(m_screenText.get(), spheremass, 1200, 630);
		m_2dRenderer->drawText(m_screenText.get(), "Is Kinematic?", 1050, 610);
		m_2dRenderer->drawText(m_screenText.get(), boolText.c_str(), 1200, 610);

		break;
	case 2:

		m_2dRenderer->drawText(m_screenText.get(), to_string(SoftBodySizeX).c_str(), 1200, 650);
		m_2dRenderer->drawText(m_screenText.get(), "Height: ", 1100, 650);
		m_2dRenderer->drawText(m_screenText.get(), to_string(SoftBodySizeY).c_str(), 1200, 630);
		m_2dRenderer->drawText(m_screenText.get(), "Width: ", 1109, 630);
		m_2dRenderer->drawText(m_screenText.get(), "Spring Coefficient: ", 996, 610);
		m_2dRenderer->drawText(m_screenText.get(), springco, 1200, 610);
		m_2dRenderer->drawText(m_screenText.get(), "Mass: ", 1100, 590);
		m_2dRenderer->drawText(m_screenText.get(), softbdmass, 1200, 590);
		m_2dRenderer->drawText(m_screenText.get(), "Spring Break Length: ", 1000, 570);
		m_2dRenderer->drawText(m_screenText.get(), to_string(springBreak).c_str(), 1200, 570);
		break;
	}
	
	m_2dRenderer->drawText(m_screenText.get(), spawnStr.c_str(), 1150, 680);
}

void PhysicsSceneApp::showUIHelp()
{
	
	m_2dRenderer->setRenderColour(0.0f, 1.0f, 0.0f);
	m_2dRenderer->drawText(m_uiHelpText.get(), "Press + on the keypad to cycle forward through shapes.", 25, 700);
	m_2dRenderer->drawText(m_uiHelpText.get(), "Press - on the keypad to cycle backward through shapes.", 25, 680);
	m_2dRenderer->drawText(m_uiHelpText.get(), " Left click to place a shape.", 25, 660);
	m_2dRenderer->drawText(m_uiHelpText.get(), " Right click to remove a shape.", 25, 640);
	m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f);
	switch (spawnIndex){
	case 0:
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 4 to make a vertical plane. this will make the X 0.1 and Y 0.0", 25, 620);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 5 to make a horizontal plane. this will make the X 0.0 and Y 0.1", 25, 600);
		
		break;
	case 1:
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 7 to increase the size by 1.", 25, 620);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 4 to decrease the size by 1.", 25, 600);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 8 to increase the mass by 2.5.", 25, 580);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 5 to decrease the mass by 2.5.", 25, 560);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 9 to set the circle to be kinematic.", 25, 540);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 6 to set the circle to not be kinematic.", 25, 520);
		break;
	case 2:
		
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 7 to increase the height by 1.", 25, 620);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 4 to decrease the height by 1.", 25, 600);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 8 to increase the width by 1.", 25, 580);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 5 to decrease the width by 1.", 25, 560);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 9 to increase the spring coeffecient by 0.25.", 25, 540);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press 6 to decrease the spring coeffecient by 0.25.", 25, 520);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press PgUp to increase the mass of each sphere by 2.5.", 25, 500);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press PgDown to decrease the mass of each sphere by 2.5.", 25, 480);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press Home to increase spring break length by 1.", 25, 465);
		m_2dRenderer->drawText(m_uiHelpText.get(), "Press End to decrease spring break length by 1.", 25, 450);
		break;
	default:
		break;

	}
}

void PhysicsSceneApp::breakCheck()
{
	std::vector<PhysicsObject*> springsToDelete;
	for (auto spring : m_physicsScene->m_actors)
	{
		if (spring->getShapeId() == ShapeType::JOINT)
		{
			glm::vec2 p1 = ((Spring*)(spring))->m_body1->getPosition() + ((Spring*)(spring))->m_contact1;
			glm::vec2 p2 = ((Spring*)(spring))->m_body2->getPosition() + ((Spring*)(spring))->m_contact2;
			// calculate the distance away
			glm::vec2 dist = p2 - p1;
			float length = sqrtf(dist.x*dist.x + dist.y*dist.y);
			// if the spring exceeds the distance limit, then add it to the delete list to break.
			if (length > ((Spring*)spring)->m_breakForce)
			{
				springsToDelete.push_back(spring);
			}
		
		}
	}
	// Then after all the springs are checked. delete from m_actors.
	for (auto deleteItem :springsToDelete)
	{

		if (deleteItem != nullptr && springsToDelete.size() > 0)
		{
			auto p = std::find(m_physicsScene->m_actors.begin(), m_physicsScene->m_actors.end(), deleteItem);
			if (p == m_physicsScene->m_actors.end())
			{
				continue;
			}
			//if (p != m_actors.end())
			else
			{
				m_physicsScene->m_actors.erase(std::find(m_physicsScene->m_actors.begin(), m_physicsScene->m_actors.end(), deleteItem));
			}
		}
	}
}


