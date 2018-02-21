#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include <memory>

class PhysicsSceneApp : public aie::Application {
public:

	PhysicsSceneApp();
	virtual ~PhysicsSceneApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	// This function is for making the softbody.
	void MakeSoftBody(int amountHigh, int amountWide, int circleRadius, float softBodyMass, glm::vec2 startPos, float distanceApart, float springStrength, glm::vec4 sphereColour ,glm::vec4 lineColour);
	
	// this distance check function is important for the setting of springs, as well as the removal of springs.
	bool distanceCheck(Sphere* sphere1, float distance, Sphere* sphereTwo);


	std::string convertIndex(int shapeIndex);
	//void setupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);

	int spawnIndex = 0;
	int AmountOfShapes = 3;
	glm::vec2 PlaneNormal  = glm::vec2(0.0f,0.0f);
	glm::vec2 SoftBodySize = glm::vec2(3, 3);
	float tempSpringCoefficent = 0.75;
	float softBodyMass = 10;
	char planex[255];
	char planey[255];

protected:

	aie::Renderer2D*	m_2dRenderer;
	std::unique_ptr<aie::Font>	m_font;
	PhysicsScene*		m_physicsScene;
};