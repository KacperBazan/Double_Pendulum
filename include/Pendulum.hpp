#pragma once
#include <SFML/Graphics.hpp>

class Pendulum
{
private:
	float m_ang{};	// Angle of the Pendulum.
	float m_l{};	// Length of the Pendulum.

	sf::Color m_c{ sf::Color::White };	// Color of the Pendulum.
	float m_m{ 50.0f };					// Mass of the Pendulum.
	float m_r{ 15.0f };					// Radius of the Pendulum.

	float m_w{ 0.0f };			// Angular Velocity of the Pendulum.
	float m_acc{ 0.0f };		// Angular Acceleration of the Pendulum.
	sf::Vector2f m_pos{};		// Position of the Pendulum.
	sf::CircleShape m_bob{};	// Bob of the Pendulum.
	sf::RectangleShape m_arm{};	// Arm of the Pendulum.

public:
	Pendulum(float ang, float l1);
	Pendulum(float ang, float l1, sf::Color c);

	void resetToPoint(sf::RenderWindow& window, sf::Vector2f cursor);

	void update(float dt);
	void draw(sf::RenderWindow& window);
};

