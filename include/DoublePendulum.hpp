#pragma once
#include <SFML/Graphics.hpp>

class DoublePendulum
{
private:
	float m_ang1{};	// Angle of 1st Pendulum.
	float m_ang2{};	// Angle of 2nd Pendulum.
	float m_l1{};	// Length of 1st Pendulum.
	float m_l2{};	// Length of 2nd Pendulum.

	sf::Color m_c1{ sf::Color::White };	// Color of 1st Pendulum.
	sf::Color m_c2{ sf::Color::White };	// Color of 2nd Pendulum.
	float m_m1{ 50.0f };				// Mass of 1st Pendulum.
	float m_m2{ 50.0f };				// Mass of 2nd Pendulum.
	float m_r1{ 15.0f };				// Radius of 1st Pendulum.
	float m_r2{ 15.0f };				// Radius of 2nd Pendulum.

	float m_w1{ 0.0f };				// Angular Velocity of 1st Pendulum.
	float m_w2{ 0.0f };				// Angular Velocity of 2nd Pendulum.
	float m_acc1{ 0.0f };			// Angular Acceleration of 1st Pendulum.
	float m_acc2{ 0.0f };			// Angular Acceleration of 2nd Pendulum.
	sf::Vector2f m_pos1{};			// Position of 1st Pendulum.
	sf::Vector2f m_pos2{};			// Position of 2nd Pendulum.
	sf::CircleShape m_bob1{};		// Bob of 1st Pendulum.
	sf::CircleShape m_bob2{};		// Bob of 2nd Pendulum.
	sf::RectangleShape m_arm1{};	// Arm of 1st Pendulum.
	sf::RectangleShape m_arm2{};	// Arm of 2nd Pendulum.

public:
	DoublePendulum(float ang1, float ang2, float l1, float l2);
	DoublePendulum(float ang1, float ang2, float l1, float l2, sf::Color c1, sf::Color c2);

	void resetToPoint(sf::RenderWindow& window, sf::Vector2f cursor);

	void update(float dt);
	void draw(sf::RenderWindow& window);
};

