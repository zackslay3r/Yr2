#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Spring.h"
#include <list>
#include <glm/ext.hpp>

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
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -50));
	m_physicsScene->setTimeStep(0.01f);




	Sphere* ball = new Sphere(glm::vec2(450, 130), glm::vec2(0, 0), 1.0f, 15, glm::vec4(1, 0, 0, 1));
	
	m_physicsScene->addActor(ball);
	
	Sphere* ballTwo = new Sphere(glm::vec2(-20, 30), glm::vec2(0, 0), 1.0f, 15, glm::vec4(0, 1, 0, 1));
	m_physicsScene->addActor(ballTwo);
	
	Sphere* springBall2 = new Sphere(glm::vec2(35, 50), glm::vec2(0, 0), 1.3f, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(springBall2);
	

	Plane* floor = new Plane(glm::vec2(0, 1),20);
	m_physicsScene->addActor(floor);


	//// This creates the 2x2 softbody
	//Sphere* softBody1 = new Sphere(glm::vec2(400, 500), glm::vec2(0, 0), 1.0f, 12, glm::vec4(1, 0, 0, 1));
	//m_physicsScene->addActor(softBody1);
	//Sphere* softBody2 = new Sphere(glm::vec2(430, 500), glm::vec2(0, 0), 1.0f, 12, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(softBody2);
	//Sphere* softBody3 = new Sphere(glm::vec2(430, 470), glm::vec2(0, 0), 1.0f, 12, glm::vec4(0, 0, 1, 1));
	//m_physicsScene->addActor(softBody3);
	//Sphere* softBody4 = new Sphere(glm::vec2(400, 470), glm::vec2(0, 0), 1.0f, 12, glm::vec4(1, 1, 1, 1));
	//m_physicsScene->addActor(softBody4);

	//m_physicsScene->addActor(new Spring(softBody1, softBody2, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody2, softBody3, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody3, softBody4, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody4, softBody1, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody2, softBody4, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody1, softBody3, 37.74, 15, .1f));


	MakeSoftBody(2, 2, 12, 4.1, glm::vec2(400, 500), 30, 1);

	// This will create a 3x3 softbody
	//Sphere* softBody11 = new Sphere(glm::vec2(600, 500), glm::vec2(0, 0), 1.0f, 10, glm::vec4(1, 0, 0, 1));
	//m_physicsScene->addActor(softBody11);
	//Sphere* softBody22 = new Sphere(glm::vec2(630, 500), glm::vec2(0, 0), 1.0f, 10, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(softBody22);
	//Sphere* softBody33 = new Sphere(glm::vec2(660, 500), glm::vec2(0, 0), 1.0f, 10, glm::vec4(0, 0, 1, 1));
	//m_physicsScene->addActor(softBody33);
	//Sphere* softBody44 = new Sphere(glm::vec2(600, 470), glm::vec2(0, 0), 1.0f, 10, glm::vec4(1, 1, 1, 1));
	//m_physicsScene->addActor(softBody44);
	//Sphere* softBody55 = new Sphere(glm::vec2(630, 470), glm::vec2(0, 0), 1.0f, 10, glm::vec4(1, 0, 0, 1));
	//m_physicsScene->addActor(softBody55);
	//Sphere* softBody66 = new Sphere(glm::vec2(660, 470), glm::vec2(0, 0), 1.0f, 10, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(softBody66);
	//Sphere* softBody77 = new Sphere(glm::vec2(600, 440), glm::vec2(0, 0), 1.0f, 10, glm::vec4(0, 0, 1, 1));
	//m_physicsScene->addActor(softBody77);
	//Sphere* softBody88 = new Sphere(glm::vec2(630, 440), glm::vec2(0, 0), 1.0f, 10, glm::vec4(1, 1, 1, 1));
	//m_physicsScene->addActor(softBody88);
	//Sphere* softBody99 = new Sphere(glm::vec2(660, 440), glm::vec2(0, 0), 1.0f, 10, glm::vec4(1, 1, 1, 1));
	//m_physicsScene->addActor(softBody99);

	//m_physicsScene->addActor(new Spring(softBody11, softBody22, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody11, softBody44, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody11, softBody55, 37.74, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody22, softBody33, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody22, softBody55, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody22, softBody66, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody33, softBody66, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody44, softBody55, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody44, softBody77, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody44, softBody88, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody55, softBody66, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody55, softBody88, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody55, softBody99, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody77, softBody88, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody88, softBody66, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody99, softBody66, 30, 7, .1f));
	//m_physicsScene->addActor(new Spring(softBody44, softBody22, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody55, softBody33, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody77, softBody55, 37.74, 15, .1f));
	//m_physicsScene->addActor(new Spring(softBody88, softBody99, 30, 7, .1f));
	//

	MakeSoftBody(6, 3, 10, 5, glm::vec2(500, 300), 30, 1);

	Sphere* staticBall8 = new Sphere(glm::vec2(580, 200), glm::vec2(0, 0), 1.3f, 25, glm::vec4(1, 1, 1, 1));
	staticBall8->setElasticity(0.9f);
	staticBall8->setKinematic(true);
	m_physicsScene->addActor(staticBall8);

	Sphere* staticBall2 = new Sphere(glm::vec2(410, 300), glm::vec2(0, 0), 1.3f, 25, glm::vec4(1, 1, 1, 1));
	staticBall2->setElasticity(0.9f);
	staticBall2->setKinematic(true);
	m_physicsScene->addActor(staticBall2);
	


	Sphere* ball1;
	ball1 = new Sphere(glm::vec2(200, 400), glm::vec2(0, 0), 1, 15, glm::vec4(1, 1, 1, 1));
	ball1->setElasticity(0.9f);
	ball1->setKinematic(true);
	m_physicsScene->addActor(ball1);
	
	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(240, 400), glm::vec2(0, 0), 6, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(new Spring(ball1, ball2, 40, 1, 0));

	Sphere* ball3;
	ball3 = new Sphere(glm::vec2(280, 400), glm::vec2(0, 0), 6, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(ball3);
	m_physicsScene->addActor(new Spring(ball2, ball3, 40, 1, 0));

	Sphere* ball4;
	ball4 = new Sphere(glm::vec2(320, 400), glm::vec2(0, 0), 50, 15, glm::vec4(1, 1, 1, 1));
	m_physicsScene->addActor(ball4);
	m_physicsScene->addActor(new Spring(ball3, ball4, 40, 1, 0));

	Sphere* ball5 = new Sphere(glm::vec2(10, 20), glm::vec2(0, 0), 10.0f, 5, glm::vec4(1, 0, 0, 1));

	m_physicsScene->addActor(ball5);
	return true;
}

void PhysicsSceneApp::shutdown() {

	delete m_font;
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
		

		/*mouseX /= screenWidth;
*/
		// if this point is less than half of the screen width, we are going to make in negative for later.
		//if (mouseX < screenWidth / 2)
		//{
		//	mouseX = -mouseX;
		//}





		//mouseX /= screenHeight;
		//if (mouseX < (getWindowWidth() * 0.5))
		//{
		//	mouseX = 0 - mouseX;
		//}


		
	
		/*
		mouseX /= 2;
		mouseX = mouseX * 100;*/
		//float mouseY = (input->getMouseY() / screenHeight) * 100;
		float mouseY = input->getMouseY();
	/*	mouseY /= screenHeight;
		
		
		if (mouseY < (getWindowHeight() * 0.5))
		{
			mouseY = 0 - mouseY;
		}
		
		mouseY /= 2;
		mouseY *= 100;*/
		m_physicsScene->addActor(new Sphere(glm::vec2((float)mouseX, (float)mouseY), glm::vec2(0, 0), 1, 5, glm::vec4(1, 1, 1, 1)));

		//m_physicsScene->addActor(new Sphere(glm::vec2(((float)input->getMouseX() - (((float)screenWidth) * 0.5f) / 100),((float)input->getMouseY() - (((float)screenHeight) * 0.5f)) / 100), glm::vec2(0, 0), 1, 1, glm::vec4(1, 1, 1, 1)));
	}
}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;

	//aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	
	aie::Gizmos::draw2D(glm::ortho<float>(0, this->getWindowWidth(), 0, this->getWindowHeight(), -1.0f, 1.0f));
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);


	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsSceneApp::MakeSoftBody(int amountHigh, int amountWide, int circleRadius, float softBodyMass, glm::vec2 startPos, float distanceApart, float springStrength)
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
			newSpheres.push_back(new Sphere(glm::vec2((startPos.x + (distanceApart * j)), (startPos.y + (distanceApart * i))), glm::vec2(0, 0), softBodyMass / (amountHigh * amountWide), circleRadius, glm::vec4(0, 0, 1, 0)));
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
					newSprings.push_back(new Spring(newSpheres.at(i), newSpheres.at(j), distanceApart, springStrength * 2));
				}
				else
				{
					newSprings.push_back(new Spring(newSpheres.at(i), newSpheres.at(j), glm::sqrt(distanceApart * distanceApart + distanceApart * distanceApart), springStrength));
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

//void PhysicsSceneApp::setupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
//{
//	float t = 0;
//	float tStep = 0.5f;
//	float radius = 1.0f;
//	int segments = 12;
//	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
//
//	while (t <= 5)
//	{
//		// calculate the x,y position of the projectile at time t
//		float x = 0;
//		float y	= 0;
//		glm::vec2 velocity = glm::vec2(cos(inclination) * speed, sin(inclination) * speed);
//		//velocity.x = velocity.x * tStep;
//		//velocity.y = velocity.y * tStep;
//
//		//float tempVar = (gravity * (tStep * tStep)) * 0.5;
//
//		//velocity.y = velocity.y + tempVar;
//
//		//y = velocity.y;
//
//		x = startPos.x + velocity.x * t;
//		y = startPos.y + velocity.y * t - 0.5f * gravity * (t*t);
//
//		
//
//		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
//		t += tStep;
//	}
//
//
//}
