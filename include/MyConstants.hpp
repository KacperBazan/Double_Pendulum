#pragma once
#include <SFML/Graphics.hpp>

namespace Constants
{
	/* Screen Variables */
	const int screen_height{ 800 };
	const int screen_width{ 1000 };
	const sf::Vector2f offset{ (float)screen_width / 2.0f, (float)screen_height / 2.0f };

	/* Math Variables */
	const float pi{ 3.14159265f };
	const float g{ 9.81f };
	const float drag_coefficient{ 0.000f }; // 0 = No Drag, 0.001 = Comfortable Drag.
	const float dt{ 0.005f }; // Incremental time step for the simulation.

	/* Cosmetic Variables */
	const int arm_size{ 4 };
	const sf::Color arm_color{ sf::Color::White };
}