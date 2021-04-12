#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	body.setFillColor(color);
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Platform::Move(float dx, float dy)
{
	body.move(dx, dy);
}
