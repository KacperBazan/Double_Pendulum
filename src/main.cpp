#include <SFML/Graphics.hpp>
#include "MyConstants.hpp"
#include "DoublePendulum.hpp"	
#include "Pendulum.hpp"	
#include <iostream>
#include <array>

int main()
{
	/* Make the window and set the Anti Aliasing level. */
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(Constants::screen_width, Constants::screen_height), "Pendulum", sf::Style::Close, settings);

	DoublePendulum p1{ 2.87979f,  2.879793f, 200.0f, 200.0f, sf::Color::Red,sf::Color::Red };
	DoublePendulum p2{ 2.87979f,  2.879794f, 200.0f, 200.0f, sf::Color::Green,sf::Color::Green };
	DoublePendulum p3{ 2.87979f,  2.879795f, 200.0f, 200.0f, sf::Color::Yellow,sf::Color::Yellow };

	/* Entry for main loop */
	while (window.isOpen())
	{
		/* Checks if window is ever closed */
		sf::Event window_event{};
		while (window.pollEvent(window_event))
		{
			if (window_event.type == sf::Event::Closed)
				window.close();
		}

		/* Clears screen buffer to Black */
		window.clear(sf::Color::Black);

		/* Moves Pendulum to mouse cursor when left-clicked */
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			p2.resetToPoint(window, static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			p1.update(Constants::dt);
			p1.draw(window);
			p2.update(Constants::dt);
			p2.draw(window);
			p3.update(Constants::dt);
			p3.draw(window);
		}

		/* Render objects to screen */
		window.display();
	}
	return 0;
}