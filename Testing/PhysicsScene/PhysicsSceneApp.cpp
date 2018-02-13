#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Spring.h"

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
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.01f);


	//float radius = 1.0f;
	//float speed = 30;
	//glm::vec2 startPos(-40, 0);
	//float inclination = 3.14159265358979323846 / 4.0f;

	//m_physicsScene->addActor(new Sphere(startPos,))

	//Sphere* ball = new Sphere(glm::vec2(20, 30), glm::vec2(0, 0), 1.0f, 5, glm::vec4(1, 0, 0, 1));
	//
	//m_physicsScene->addActor(ball);
	//
	//Sphere* ball2 = new Sphere(glm::vec2(-20, 30), glm::vec2(0, 0), 1.0f, 5, glm::vec4(0, 1, 0, 1));
	//m_physicsScene->addActor(ball2);
	//
	//Sphere* springBall2 = new Sphere(glm::vec2(35, 50), glm::vec2(0, 0), 1.3f, 5, glm::vec4(1, 1, 1, 1));
	//m_physicsScene->addActor(springBall2);
	//
	//Plane* plane1 = new Plane(glm::vec2(0, 1), 0);
	//m_physicsScene->addActor(plane1);

	//Sphere* staticBall = new Sphere(glm::vec2(0, 30), glm::vec2(0, 0), 1.3f, 5, glm::vec4(1, 1, 1, 1));
	//staticBall->setElasticity(0.9f);
	//staticBall->setKinematic(true);
	//m_physicsScene->addActor(staticBall);
	//

	//Sphere* staticBall2 = new Sphere(glm::vec2(30, 0), glm::vec2(0, 0), 1.3f, 5, glm::vec4(1, 1, 1, 1));
	//staticBall2->setElasticity(0.9f);
	//staticBall2->setKinematic(true);
	//m_physicsScene->addActor(staticBall2);



	//Sphere* springBall = new Sphere(glm::vec2(25, 50), glm::vec2(0, 0), 1.3f, 5, glm::vec4(1, 1, 1, 1));
	//springBall->setElasticity(0.9f);
	//springBall->setKinematic(true);
	//m_physicsScene->addActor(springBall);




	//ball->applyForce(glm::vec2(-40, 0),glm::vec2(0,0));
	//ball2->applyForce(glm::vec2(40, 0), glm::vec2(0,0));
	//
	//setupConinuousDemo(glm::vec2(-40,0),45,40,10);

	int startX = -50;
	Sphere* ball1; 
	Sphere* ball2;
	float ballRadius = 2;
	float mass = 1;
	ball1 = new Sphere(glm::vec2(startX, 40), glm::vec2(0, 0), mass, ballRadius, glm::vec4(1, 1, 1, 1));
	ball1->setElasticity(0.9f);
	ball1->setKinematic(true);
	m_physicsScene->addActor(ball1);

	int numberOfBalls = 10;

	for (int i = 1; i < numberOfBalls; i++)
	{
		ball2 = new Sphere(glm::vec2(startX + i * 6.0f, 40), glm::vec2(0, 0), mass, ballRadius, glm::vec4(1, 1, 1, 1));
		ball2->setElasticity(0.9f);
		m_physicsScene->addActor(ball2);
		m_physicsScene->addActor(new Spring(ball1, ball2, 5, 10, .1f,ball1->getPosition(),ball2->getPosition()));
		ball1 = ball2;
	}

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
}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
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
