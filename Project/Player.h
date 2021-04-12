#pragma once
#include <SFML/Graphics.hpp>
//#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);

	void Update(float deltaTime);
	void Jump();
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition();
	Collider GetCollider()
	{
		return Collider(body);
	}
	bool GetCanJump();

private:
	sf::RectangleShape body;
	//Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	//Jumping
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

};

