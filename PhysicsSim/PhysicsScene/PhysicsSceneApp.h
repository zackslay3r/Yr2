#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include <memory>

class PhysicsSceneApp : public aie::Application {
public:

	// This is the constructor.
	PhysicsSceneApp();
	// This is the destructor.
	~PhysicsSceneApp();
	// This is the startup function which is a virtual function.
	// This is responsible for all the startup functions of physicsSceneApp.
	// This will return a bool that is true once startup is complete.
	virtual bool startup();
	// This is the startup function which is a virtual function.
	// This is responsible for all the startup functions of physicsSceneApp.
	// This returns void.
	virtual void shutdown();
	// This is the update function which is a virtual function.
	// This is responsible for all the startup functions of physicsSceneApp.
	//This takes a parameter which is deltaTime and returns void.
	virtual void update(float deltaTime);
	// This is the draw function which is a virtual function.
	// This is responsible for all the draw functions of physicsSceneApp.
	//This returns void.
	virtual void draw();
	
	// This function is for making the a softbody during the game.
	// This function takes 9 parameters.
	// int amountHigh - amount of circles high.
	// int amountWide - amount of circles wide.
	// int circleRadius - the radius of each circle.
	// float softBodyMass - the mass of each object in the softbody.
	// glm::vec2 startPos - the starting position of the very first sphere in the softbody.
	// float distanceApart - the distance apart for each of the spheres.
	// float springStrength - the strength of the springs (spring coefficent).
	// glm::vec4 sphereColour - the colour of each sphere.
	// glm::vec4 lineColour - the colour of each line.
	// This function returns void.
	void MakeSoftBody(int amountHigh, int amountWide, int circleRadius, float softBodyMass, glm::vec2 startPos, float distanceApart, float springStrength, glm::vec4 sphereColour ,glm::vec4 lineColour);
	
	// This is the distanceCheck function.
	// this distance check function is important for the setting of springs, as well as the removal of springs.
	// This takes 3 parameters.
	// Sphere* sphere1 - the first sphere that is being checked against.
	// float distance - this is the distance that we wish to check if two spheres are within this number.
	// Sphere* sphere2 - the second sphere that is being checked against.
	// This function returns a boolean.
	bool distanceCheck(Sphere* sphere1, float distance, Sphere* sphereTwo);

	//This is the convertBool function. it is responsible for taking boolean value and converting it into a string.
	// This takes one parameter.
	// bool kinematic - this is the boolean value.
	// this returns a std::string.
	std::string convertBool(bool kinematic);

	//This is the convertIndex function. it is responsible for taking a shapeIndex and converting it into a string.
	// This takes one parameter.
	// int shapeIndex - this is a shapeIndex.
	// this returns a std::string.
	std::string convertIndex(int shapeIndex);

	//This is the ShowUIElements function. This function is responsible for showing all the UI elements in the simulation. 
	// and returns type void.
	void ShowUIElements();
	
	//This is the showUIHelp function. it is responsible for displaying the help for the user.
	// and returns type void.
	void showUIHelp();

	// This is the breakCheck function. it is responsible for checking the spring length and if its greater then what is permitted.
	// then break the spring.
	// this returns type void.
	void breakCheck();



	int spawnIndex = 0;
	int AmountOfShapes = 3;
	glm::vec2 PlaneNormal  = glm::vec2(0.0f,0.0f);
	int SoftBodySizeX = 3;
	int SoftBodySizeY = 3;
	float tempSpringCoefficent = 0.75;
	float softBodyMass = 10;
	int sphereRadius = 5;
	float sphereMass = 5;
	int springBreak = 25;
	bool sphereKinematic;
	
	// These char arrays are for the conversion from floats to floats with 2 decimal place or 1 decimal place.
	// These two are for plane x and y coordinates
	char planex[255];
	char planey[255];
	// These are for softbody size x,y's.
	char sbsizex[255];
	char sbsizey[255];
	// THis is for the spring coefficent.
	char springco[255];
	// THis is for the softbody mass.
	char softbdmass[255];
	char spheremass[255];


protected:
	// This is the renderer pointer.
	aie::Renderer2D*	m_2dRenderer;
	// THese 3 pointers are used for the different text's in the game.
	std::unique_ptr<aie::Font>	m_font,m_screenText,m_uiHelpText;
	// THis is the physics scene itself.
	PhysicsScene*		m_physicsScene;
};