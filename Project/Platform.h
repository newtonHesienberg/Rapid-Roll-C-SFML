#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Color color);

	void Draw(sf::RenderWindow& window);
	void Move(float dx, float dy);

	Collider GetCollider()
	{
		return Collider(body);
	}

private:
	sf::RectangleShape body;
};

