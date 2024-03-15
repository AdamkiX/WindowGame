#include <iostream>

#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <filesystem>

import player;
import Bullet;

using namespace sf;

bool DEBUG = false;

void Player::InitVars()
{
	name = "Gracz";	

	this->vitality = 30;
	this->hp = 100;
	this->maxhp = 100;
	this->attack = 10;
	this->movSpd = 1;
	this->projSpd = 2;
	this->dexterity = 0.4;

	this->exp = 0;
	this->maxexp = 50;
	this->lv = 1;
}

void Player::InitSprite()
{
	Color color(0, 255, 0, 255);
	if (!DEBUG)
		color.a = 0;

	this -> rectangle.setSize((Vector2f(8, 8)));
	this -> rectangle.setFillColor(color);
	this -> LoadTexture();
}

Player::Player(float x, float y)
{
	this->rectangle.setPosition(Vector2f(x, y));
	this->player_spr.setPosition(rectangle.getPosition());
	this -> InitSprite();
	this -> InitVars();
	position;
}

void Player::SetProjSpd(float value)
{
	projSpd = value;
}

void Player::SetName(String& Pname)
{
	this->name = Pname;
	std::cout << name.toAnsiString();
}

void Player::SetCenter(Vector2f& pcenter)
{
	this->center = pcenter;
}

void Player::SetMovSpd(float value)
{
	movSpd = value;
}

float Player::GetProjSpd()
{
	return projSpd;
}

float Player::GetDext()
{
	return dexterity;
}

float Player::GetAtt()
{
	return attack;
}

float Player::GetEXP()
{
	return exp;
}


int Player::GetLV()
{
	return lv;
}

float Player::GetMaxEXP()
{
	return maxexp;
}

float Player::GetHP()
{
	return hp;
}

float Player::GetMaxHP()
{
	return maxhp;
}

String Player::GetName()
{
	return name;
}

float Player::GetMovSpd()
{
	return movSpd;
}

void Player::AddExp(float Eexp)
{
	this->exp += Eexp;
	if (this->exp >= this->maxexp)
	{
		this->LevelUp();
	}
}

void Player::RegenHP(int& FRAME)
{
	if (FRAME % vitality == 0 && hp < maxhp)
	{
		hp++;
		if (hp > maxhp)
		{
			hp = maxhp;
		}
	}
}

void Player::Hit(float Eatt)
{
	this->hp -= Eatt;
}

bool Player::Dead()
{
	if (this->hp <= 0)
	{
		std::cout << "Player Died! \n";
		return true;
	}
	else
		return false;
}

void Player::Shoot(RenderWindow *win)
{
	if (clock.getElapsedTime().asSeconds() >= this->dexterity)
	{
		this->mousePosWindow = Vector2f(Mouse::getPosition(*win));
		this->aimDir = mousePosWindow - center;
		float div = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		this->aimDirNorm = aimDir / div;
		Bullet b;
		b.shape.setPosition(position);
		b.shape.setOrigin(b.shape.getSize().x, b.shape.getSize().y);
		b.currVelocity = aimDirNorm * b.maxSpeed;
		bullets.push_back(Bullet(b));

		clock.restart();
	}
}

void Player::UpdateInput()
{
	mov.x = 0.0f, mov.y = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mov.y -= movSpd;
//		std::cout << "Player posx:" << player_spr.getPosition().x << std::endl
//			<< "Player posy:" << player_spr.getPosition().y << std::endl << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		mov.y += movSpd;
//		std::cout << "Player posx:" << player_spr.getPosition().x << std::endl
//			<< "Player posy:" << player_spr.getPosition().y << std::endl << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mov.x += movSpd;
//		std::cout << "Player posx:" << player_spr.getPosition().x << std::endl
//			<< "Player posy:" << player_spr.getPosition().y << std::endl << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mov.x -= movSpd;
//		std::cout << "Player posx:" << player_spr.getPosition().x << std::endl
//			<< "Player posy:" << player_spr.getPosition().y << std::endl << std::endl;
	}

	if (mov.x != 0.0f && mov.y != 0.0f)
	{
		mov /= std::sqrt(2.0f); // Dzielimy wektor przez pierwiastek z 2
//		std::cout << "Player posx:" << player_spr.getPosition().x << std::endl
//			<< "Player posy:" << player_spr.getPosition().y << std::endl << std::endl;
	}
	rectangle.move(mov);
	player_spr.setPosition(rectangle.getPosition());

	// Zaktualizuj pozycjê gracza
	position = rectangle.getPosition();
}


void Player::LevelUp()
{
	do
	{
		this->exp -= maxexp;
		this->maxhp = maxhp * 1.25;
		this->maxexp = this->maxexp * 1.5;
		this->attack += 5;
		this->movSpd += 0.05;
		this->dexterity = this->dexterity * 0.9;
		this->lv++;
	}
	while (this->exp >= this->maxexp);
}

void Player::LoadTexture()
{
	std::filesystem::path imagePath = "Sprites/player_mage.png";
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

	player_spr.setTexture(texture);
}

void Player::UpdatePlayer(RenderTarget* target, int& FRAME)
{
	this->UpdateInput();
	this->RegenHP(FRAME);
}