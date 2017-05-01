// =========
// display.h
// =========

#ifndef DISPLAY_H
#define DISPLAY_H

#include "../utils/utils.h"

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace render
{
	class Display
	{
	public:
		Display();
		Display(unsigned int width, unsigned int height, const std::string& title);
		~Display();

		void printGLInfo();
		void clear(float r, float g, float b, float a);
		void handleUserInput();
		void drawFPS();
		void run();

		bool isRunning()
		{
			return _window.isOpen();
		}

		void setMousePosition(int x, int y)
		{
			_mousePos.x = x;
			_mousePos.y = y;
		}

		utils::Vec2i32 getMousePosition()
		{
			return utils::Vec2i32(_mousePos.x, _mousePos.y);
		}

		void enableBlending()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}

	private:
		sf::RenderWindow _window;
		sf::Event _event;
		sf::Clock _clock;
		sf::Time _time;
		sf::Font _font;
		sf::Text _text;

		sf::Vector2i _mousePos;
	};
}

#endif
