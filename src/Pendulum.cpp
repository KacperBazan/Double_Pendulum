/* Member function definitions for Pendulum.hpp */

#include <SFML/Graphics.hpp>
#include "Pendulum.hpp"
#include "MyConstants.hpp"
#include <cassert>
#include <iostream>

/* Main Constructor */
Pendulum::Pendulum(float ang, float l)
	: m_ang{ ang }, m_l{ l }
{
	assert(l > 0 && "Invalid Pendulum Given.");

	m_pos = m_l * sf::Vector2f{ sin(m_ang), cos(m_ang) } + Constants::offset;

	m_bob.setRadius(m_r);
	m_bob.setFillColor(m_c);
	m_bob.setOrigin(sf::Vector2f{ m_r, m_r });
	m_bob.setPosition(m_pos);

	m_arm.setSize(sf::Vector2f((float)Constants::arm_size, m_l));
	m_arm.setOrigin(sf::Vector2f((float)Constants::arm_size / 2.0f, 0.0f));
	m_arm.setFillColor(Constants::arm_color);
	m_arm.setPosition(Constants::offset);
	m_arm.setRotation(m_ang* (-180.0f / Constants::pi));
}

/* Delegating Constructor */
Pendulum::Pendulum(float ang, float l, sf::Color c)
	:Pendulum{ ang, l }
{
	m_c = c;
	m_bob.setFillColor(m_c);
}

/* Update angle, angular velocity, and angular acceleration of pendulum */
void Pendulum::update(float dt)
{
	using Constants::g;

	float drag{ Constants::drag_coefficient * m_w };
	float force{ -1.0f * g * (1 / m_l) * sin(m_ang) };

	m_acc = force - drag;
	m_w += m_acc * dt;
	m_ang += m_w * dt;

	m_arm.setRotation(m_ang * (-180.0f / Constants::pi));
	m_bob.setPosition(m_l * sf::Vector2f(sin(m_ang), cos(m_ang)) + Constants::offset);
}

/* Reset the pendulum to a position determined by the mouse*/
void Pendulum::resetToPoint(sf::RenderWindow& window, sf::Vector2f cursor)
{
	using Constants::offset;

	float delta_x{ cursor.x - offset.x };
	float delta_y{ -cursor.y + offset.y };
	float d{ sqrt(delta_x * delta_x + delta_y * delta_y) };

	/* Don't update pendulum to an impossible position. */
	if (d > m_l)
	{
		draw(window);
		return;
	}

	/* Update all pendulum vlues based on cursor. */
	m_pos = cursor;
	m_ang = atan2((cursor.x - offset.x), (cursor.y - offset.y));

	m_bob.setPosition(m_pos);
	m_arm.setRotation(m_ang * (-180.0f / Constants::pi));

	m_w = 0.0f;
	m_acc = 0.0f;

	/* Highlight Circle */
	sf::CircleShape c1{};
	c1.setFillColor(Constants::arm_color);
	c1.setRadius(m_r * 1.33f);
	c1.setOrigin(sf::Vector2f{ c1.getRadius(),c1.getRadius() });

	c1.setPosition(m_pos); // Draw highlight circle first.
	window.draw(c1);
	draw(window);
}

/* Draw the pendulum to the given window */
void Pendulum::draw(sf::RenderWindow& window)
{
	window.draw(m_arm);
	window.draw(m_bob);
}