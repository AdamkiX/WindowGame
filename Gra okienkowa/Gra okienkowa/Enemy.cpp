
#include <iostream>
#include <math.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <filesystem>

//#include "Enemy.ixx";

using namespace sf;

import Enemy;

//bool DEBUG = false;

void Enemy::InitVars()
{
	this->detected = false;

	this->hp = 100;
	this->maxhp = 100;
	this->movSpd = 0.5;
	this->projSpd = 1;
	this->attack = 5;
	this->exp = 5;
	this->dext = 0.7;
	
	this->lv = 1;

	this->subfolder = "Goblins";
	this->filename = "GoblinWarior.png";

	vision.setOrigin(rec.getPosition());
	vision.setSize(Vector2f(100, 80));
}

RectangleShape Enemy::GetEnemy()
{
	return rec;
}

bool Enemy::Dead()
{
	if (hp <= 0)
		return true;
	else
		return false;
}

void Enemy::InitSprite()
{
	std::filesystem::path imagePath = "Sprites/" + subfolder + "/" + filename;
	if (!std::filesystem::exists(imagePath))
	{
		std::cout << "Could not find image file: " << imagePath << std::endl;
		return;
	}

	if (!texture.loadFromFile(imagePath.string()))
	{
		std::cout << "Could not load player texture from file: " << imagePath << std::endl;
		return;
	}

	sprite.setTexture(texture);
}

bool Enemy::PlayerTrigger(Player& player)
{
	if (player.rectangle.getGlobalBounds().intersects(vision.getGlobalBounds()))
	{
		this->detected = true;
		return true;
	}
	else
	{
		this->detected = false;
		return false;
	}


}

void Enemy::UpdateEnemy(RenderTarget* target, Player& player)
{
	this->Movement(target,player);
	this->Shoot(player);
	//target->draw(vision);
	//target->draw(rec);
}

void Enemy::Hit(Player& player)
{
	this->hp -= player.GetAtt();
	std::cout << "Goblin mage HP: " << this->hp << "\n";
}

void Enemy::Movement(RenderTarget* target, Player& player)
{	
	if (PlayerTrigger(player))
	{
		Vector2f direction = player.getPosition() - rec.getPosition();
		direction = sf::Vector2f(direction.x / std::sqrt(direction.x * direction.x + direction.y * direction.y),
			direction.y / std::sqrt(direction.x * direction.x + direction.y * direction.y));
			rec.move(movSpd * direction);
		UpdateEnemyPos();
	}
}

void Enemy::UpdateEnemyPos()
{
	FloatRect rectBounds = rec.getGlobalBounds();
	float visionPosX = rectBounds.left + (rectBounds.width - vision.getSize().x) / 2.0f;
	float visionPosY = rectBounds.top + (rectBounds.height - vision.getSize().y) / 2.0f;

	vision.setPosition(visionPosX,visionPosY);
	sprite.setPosition(rec.getPosition());
}

void Enemy::SetSpawnPos(float x, float y)
{
	rec.setPosition(x, y);
	rec.setSize({ 8,8 });

	vision.setPosition(rec.getPosition().x - vision.getGlobalBounds().width/2, rec.getPosition().y - vision.getGlobalBounds().height/2);
	sprite.setPosition(rec.getPosition());
}

void Enemy::Reward(Player& player)
{
	player.AddExp(exp);
}

Enemy::~Enemy()
{
	
}

void Enemy::CreateBullet()
{
	float div = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	this->aimDirNorm = aimDir / div;

	Bullet b;
	b.shape.setPosition(rec.getPosition());
	b.sprite.setPosition(b.shape.getPosition());
	std::filesystem::path imagePath = "Sprites/Bullets/GoblinBullet.png";
	if (!std::filesystem::exists(imagePath))
	{
		std::cout << "Could not find image file: " << imagePath << std::endl;
		return;
	}

	if (!bulletTexture.loadFromFile(imagePath.string()))
	{
		std::cout << "Could not load player texture from file: " << imagePath << std::endl;
		return;
	}
	b.sprite.setTexture(bulletTexture);
	b.shape.setOrigin(b.shape.getSize().x, b.shape.getSize().y);
	b.currVelocity = aimDirNorm * b.maxSpeed;
	bullets.push_back(Bullet(b));

	clk.restart();
}

void Enemy::Shoot(Player& player)
{
	if (PlayerTrigger(player)&& clk.getElapsedTime().asSeconds() >= this->dext)
	{
		this->aimDir = player.getPosition() - rec.getPosition();
		this->CreateBullet();
		// Przesuwaj pocisk w stronê gracza
	}
}



