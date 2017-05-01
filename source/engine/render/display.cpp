// ===========
// display.cpp
// ===========

#include "display.h"

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace render;

Display::Display()
{

}

Display::Display(unsigned int width, unsigned int height, const std::string& title)
{
	if (!_font.loadFromFile("resources/FreeMono.ttf"))
		std::cout << "[r] font loading failed." << std::endl;

	_text.setFont(_font);
	_text.setCharacterSize(15);
	_text.setFillColor(sf::Color::White);
	_text.setOutlineColor(sf::Color::White);
	_text.setPosition(5.0f, 5.0f);
	_text.setString("");

	_window.create(sf::VideoMode(width, height), title, sf::Style::Default);

//	_window.setFramerateLimit(60);
	_window.setVerticalSyncEnabled(true);

	GLenum res = glewInit();

    if (res != GLEW_OK)
		std::cerr << "[r] Glew failed to initialize!" << std::endl;
}

Display::~Display()
{
	
}

void Display::printGLInfo()
{
	char *glVersion=(char*)glGetString(GL_VERSION);
	char *glVendor=(char*)glGetString(GL_VENDOR);
	char *glRenderer=(char*)glGetString(GL_RENDERER);

	std::cout << "[r] OpenGL version: " << glVersion << std::endl;
	std::cout << "[r] OpenGL vendor: " << glVendor << std::endl;
	std::cout << "[r] OpenGL renderer: " << glRenderer << std::endl;
}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::handleUserInput()
{
	if (_window.isOpen())
	{
		// SFML Events
		while (_window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				_window.close();
		}

		// SFML Keyboard Input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window.close();

		// SFML Mouse Input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			_mousePos = sf::Mouse::getPosition(_window);
	}
}

void Display::drawFPS()
{
	_time = _clock.getElapsedTime();
	_clock.restart().asSeconds();

	float fps = 1.0f / _time.asSeconds();

	std::stringstream ssFPS;
	ssFPS << std::fixed << std::setprecision(2) << fps;
	std::string stringFPS = ssFPS.str();

//	std::string vtx_string = std::to_string(_num_vertices);

	_text.setString(stringFPS + " FPS\n"/* + vtx_string + " vertices"*/);

	_window.pushGLStates();
	_window.draw(_text);
	_window.popGLStates();
}

void Display::run()
{
	_window.display();
	glFinish();
}
