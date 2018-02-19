#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class PhysicsSceneApp : public aie::Application {
public:

	PhysicsSceneApp();
	virtual ~PhysicsSceneApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	void MakeSoftBody(int amountHigh, int amountWide, int circleRadius, float softBodyMass, glm::vec2 startPos, float distanceApart, float springStrength, glm::vec4 sphereColour ,glm::vec4 lineColour);
	
	bool distanceCheck(Sphere* sphere1, float distance, Sphere* sphereTwo);

	//void setupConinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
};