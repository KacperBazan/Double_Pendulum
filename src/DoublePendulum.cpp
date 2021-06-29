/* Member Functions for the 'DoublePendulum' class */

#include <SFML/Graphics.hpp>
#include "DoublePendulum.hpp"
#include "MyConstants.hpp"
#include <cassert>
#include <cmath>

/* Main Constructor */
DoublePendulum::DoublePendulum(float ang1, float ang2, float l1, float l2)
	: m_ang1{ ang1 }, m_ang2{ ang2 }, m_l1{ l1 }, m_l2{ l2 }
{
	assert(l1 > 0 && l2 > 0 && "Invalid Pendulum Given.");

	m_pos1 = m_l1 * sf::Vector2f{ sin(m_ang1), cos(m_ang1) } + Constants::offset;
	m_pos2 = m_l2 * sf::Vector2f{ sin(m_ang2), cos(m_ang2) } + m_pos1;

	m_bob1.setRadius(m_r1);
	m_bob2.setRadius(m_r2);
	m_bob1.setFillColor(m_c1);
	m_bob2.setFillColor(m_c2);
	m_bob1.setOrigin(sf::Vector2f{ m_r1, m_r1 });
	m_bob2.setOrigin(sf::Vector2f{ m_r2, m_r2 });
	m_bob1.setPosition(m_pos1);
	m_bob2.setPosition(m_pos2);

	m_arm1.setSize(sf::Vector2f((float)Constants::arm_size, m_l1));
	m_arm2.setSize(sf::Vector2f((float)Constants::arm_size, m_l2));
	m_arm1.setOrigin(sf::Vector2f((float)Constants::arm_size / 2.0f, 0.0f));
	m_arm2.setOrigin(sf::Vector2f((float)Constants::arm_size / 2.0f, 0.0f));
	m_arm1.setFillColor(Constants::arm_color);
	m_arm2.setFillColor(Constants::arm_color);
	m_arm1.setPosition(Constants::offset);
	m_arm2.setPosition(m_pos1);
	m_arm1.setRotation(m_ang1* (-180.0f / Constants::pi));
	m_arm2.setRotation(m_ang2* (-180.0f / Constants::pi));
}

/* Delegating Constructor */
DoublePendulum::DoublePendulum(float ang1, float ang2, float l1, float l2, sf::Color c1, sf::Color c2)
	:DoublePendulum{ ang1, ang2, l1, l2 }
{
	m_c1 = c1;
	m_c2 = c2;
	m_bob1.setFillColor(m_c1);
	m_bob2.setFillColor(m_c2);
}

/* Update angle, angular velocity, and angular acceleration of pendulum */
void DoublePendulum::update(float dt)
{
	using Constants::g;

	float drag_1{ Constants::drag_coefficient * m_w1 };
	float drag_2{ Constants::drag_coefficient * m_w2 };

	float num1{ -g * (2.0f * m_m1 + m_m2) * sin(m_ang1) };
	float num2{ -m_m2 * g * sin(m_ang1 - 2.0f * m_ang2) };
	float num3{ -2.0f * sin(m_ang1 - m_ang2) * m_m2 };
	float num4{ m_w2 * m_w2 * m_l2 + m_w1 * m_w1 * m_l1 * cos(m_ang1 - m_ang2) };
	float dec1{ m_l1 * (2.0f * m_m1 + m_m2 - m_m2 * cos(2.0f * (m_ang1 - m_ang2))) };
	m_acc1 = ((num1 + num2 + num3 * num4) / dec1) - drag_1;

	float num5{ 2.0f * sin(m_ang1 - m_ang2) };
	float num6{ m_w1 * m_w1 * m_l1 * (m_m1 + m_m2) };
	float num7{ g * (m_m1 + m_m2) * cos(m_ang1) };
	float num8{ m_w2 * m_w2 * m_l2 * m_m2 * cos(m_ang1 - m_ang2) };
	float dec2{ m_l2 * (2.0f * m_m1 + m_m2 - m_m2 * cos(2.0f * (m_ang1 - m_ang2))) };
	m_acc2 = ((num5 * (num6 + num7 + num8)) / dec2) - drag_2;

	m_w1 += m_acc1 * dt;
	m_w2 += m_acc2 * dt;
	m_ang1 += m_w1 * dt;
	m_ang2 += m_w2 * dt;

	m_arm1.setRotation(m_ang1 * (-180.0f / Constants::pi));
	m_arm2.setRotation(m_ang2 * (-180.0f / Constants::pi));

	m_bob1.setPosition(m_l1 * sf::Vector2f(sin(m_ang1), cos(m_ang1)) + Constants::offset);
	m_pos1 = m_bob1.getPosition();
	m_bob2.setPosition(m_l2 * sf::Vector2f(sin(m_ang2), cos(m_ang2)) + m_pos1);
	m_pos2 = m_bob2.getPosition();

	m_arm2.setPosition(m_pos1);
}

/* Reset the pendulum to a position determined by the mouse*/
void DoublePendulum::resetToPoint(sf::RenderWindow& window, sf::Vector2f cursor)
{
	using Constants::offset;

	float delta_x{ cursor.x - offset.x };
	float delta_y{ -cursor.y + offset.y };
	float d{ sqrt(delta_x * delta_x + delta_y * delta_y) };

	/* Don't update pendulum to an impossible position. */
	if (d > (m_l1 + m_l2))
	{
		draw(window);
		return;
	}

	float a{ (m_l1 * m_l1 - m_l2 * m_l2 + d * d) / (2.0f * d) };
	float h{ sqrt(m_l1 * m_l1 - a * a) };
	float x3{ offset.x + a * (delta_x / d) };
	float y3{ -offset.y + a * (delta_y / d) };

	/* Flag is used to determine which intersection point is used. */
	float flag{ 1.0f };
	if (cursor.x < offset.x)
		flag = 1.0f;

	float x4{ x3 + (flag * h) * (delta_y / d) };
	float y4{ -(y3 - (flag * h) * (delta_x / d)) };

	/* Update all pendulum vlues based on intersection (x4, y4). */
	m_pos1 = { x4,y4 };
	m_pos2 = cursor;
	m_ang1 = atan2((x4 - offset.x), (y4 - offset.y));
	m_ang2 = atan2((cursor.x - x4), (cursor.y - y4));

	m_bob1.setPosition(m_pos1);
	m_bob2.setPosition(m_pos2);
	m_arm1.setRotation(m_ang1 * (-180.0f / Constants::pi));
	m_arm2.setPosition(m_pos1);
	m_arm2.setRotation(m_ang2 * (-180.0f / Constants::pi));

	m_w1 = 0.0f;
	m_w2 = 0.0f;
	m_acc1 = 0.0f;
	m_acc2 = 0.0f;

	/* Highlight Circles */
	sf::CircleShape c1{};
	sf::CircleShape c2{};
	c1.setFillColor(Constants::arm_color);
	c2.setFillColor(Constants::arm_color);
	c1.setRadius(m_r1 * 1.33f);
	c2.setRadius(m_r2 * 1.33f);
	c1.setOrigin(sf::Vector2f{ c1.getRadius(),c1.getRadius() });
	c2.setOrigin(sf::Vector2f{ c2.getRadius(),c2.getRadius() });

	c1.setPosition(m_pos1); // Draw highlight circles first.
	c2.setPosition(m_pos2);
	window.draw(c1);
	window.draw(c2);
	draw(window);
}

/* Draw the pendulum to the given window */
void DoublePendulum::draw(sf::RenderWindow& window)
{
	window.draw(m_arm1);
	window.draw(m_arm2);
	window.draw(m_bob1);
	window.draw(m_bob2);
}



