#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm/ext.hpp>
#include <Gizmos.h>

class TestingApp : public aie::Application {
public:

	TestingApp();
	virtual ~TestingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	// values for rows, columns, horizonal space and vertical space
	static const int rows = 5;
	static const int coloums = 10;
	static const int hSpace = 1;
	static const int vSpace = 1;
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};