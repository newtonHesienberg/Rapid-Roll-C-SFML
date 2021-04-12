#include "Player.h"
#include<iostream>

static const sf::Color playerColor(255, 0, 0);

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
	//animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->canJump = true;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(20.0f, 20.0f));
	body.setFillColor(playerColor);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(sf::Vector2f(200.0f, 400.0f));
	body.setTexture(texture);
}

void Player::Update(float deltaTime)
{
	velocity.x *= 0.25f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;*/
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		Jump();
	}*/

	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 0;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	//animation.Update(row, deltaTime, faceRight);
	//body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	
}

void Player::Jump()
{
	canJump = false;
	velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision On Left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision On RIght
		velocity.x = 0.0f;
	}

	if (direction.y < 0.0f)
	{
		//Collision On Bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision On Top
		velocity.y = 0.0f;
	}
}

sf::Vector2f Player::GetPosition()
{
	return	body.getPosition();
}

bool Player::GetCanJump()
{
	return canJump;
}
