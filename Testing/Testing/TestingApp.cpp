#include "TestingApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


TestingApp::TestingApp() {

}

TestingApp::~TestingApp() {

}

bool TestingApp::startup() {
	
	//increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);


	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void TestingApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void TestingApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();





	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();


	// 
}

void TestingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();


	// all of our colours.
	static const glm::vec4 colours[] =
	{
		glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
		glm::vec4(0,0,1,1), glm::vec4(0.8,0,0.5f,1),
		glm::vec4(0,1,1,1)
	};

	
	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	static const glm::vec2 scrExtents(100, 50);
	static const glm::vec2 boxExtents(7, 3);
	static const glm::vec2 startPos(-(coloums >> 1)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f), scrExtents.y - ((boxExtents.y * 2) + hSpace));

	//draw the grid of block
	glm::vec2 pos;
	for (int y = 0; y < rows; y++)
	{
		pos = glm::vec2(startPos.x, startPos.y - (y* ((boxExtents.y * 2) + hSpace)));
		for (int x = 0; x < coloums; x++)
		{
			aie::Gizmos::add2DAABBFilled(pos, boxExtents, colours[y]);
			pos.x += (boxExtents.x * 2) + vSpace;
		}
	}


	//draw the ball
	// aie::GIzmos::add2DCircle(vec2 offset from centre,raidus, segments, vec4 colour rgb) 
	aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));
	


	// draw the player's paddle
	// aie::Gizmos::add2DAABBFilled(vector2 offset from center. , vector 2 widith and height, vector 4 r,g,b,alpha (0 to 1) )
	aie::Gizmos::add2DAABBFilled(glm::vec2(0, -40), glm::vec2(12, 2), glm::vec4(1, 0, 1, 1));

	

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}