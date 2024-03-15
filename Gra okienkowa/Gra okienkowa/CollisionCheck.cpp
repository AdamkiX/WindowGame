#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <iostream>;
#include <vector>

using namespace sf;

import CollisionCheck;
import player;
import Enemy;
import map;

Collision::Collision()
{
	this->enemyToKill = -1;
}

void Collision::SetEnemyToKill(int e)
{
	this->enemyToKill = e;
}

void Collision::PlayerHitting(Map& map, Player& player, std::vector<Enemy*>& enemyVector)
{
	for (int i = 0; i < player.bullets.size(); i++)
	{
		player.bullets[i].shape.move(player.bullets[i].currVelocity);

		if (player.bullets[i].shape.getPosition().x < 0 || player.bullets[i].shape.getPosition().x > map.texture.getSize().x
			|| player.bullets[i].shape.getPosition().y < 0 || player.bullets[i].shape.getPosition().y > map.texture.getSize().y)
		{
			player.bullets.erase(player.bullets.begin() + i);
		}
		else
			this->EnemyColCheck(player, enemyVector, i);
	}

}

void Collision::EnemyColCheck(Player& player, std::vector<Enemy*>& enemyVector, int i)
{
	for (int j = 0; j < enemyVector.size(); j++)
	{
		if (enemyVector[j]->GetEnemy().getGlobalBounds().intersects(player.bullets[i].shape.getGlobalBounds()))
		{
			std::cout << "Enemy hit!\n";
			enemyVector[j]->Hit(player);
			if (enemyVector[j]->Dead())
			{
				enemyVector[j]->Reward(player);
				enemyToKill = j;
			}
			player.bullets.erase(player.bullets.begin() + i);
			break;
		}
	}
}

void Collision::EnemyHitting(Map&map, RenderWindow* win, Player& player, std::vector<Enemy*>& enemyVector)
{
	for (int i = 0; i < enemyVector.size(); i++)
	{
		for (int j = 0; j < enemyVector[i]->GetBulletsVecSize(); j++)
		{
			float div = enemyVector.size();
			enemyVector[i]->getBullets()[j].shape.move(enemyVector[i]->getBullets()[j].currVelocity / div);
			enemyVector[i]->getBullets()[j].sprite.setPosition(enemyVector[i]->getBullets()[j].shape.getPosition());
			win->draw(enemyVector[i]->getBullets()[j].sprite);
			//Out of bounds
			if (enemyVector[i]->getBullets()[j].shape.getPosition().x < 0 || enemyVector[i]->getBullets()[j].shape.getPosition().x > map.texture.getSize().x
				|| enemyVector[i]->getBullets()[j].shape.getPosition().y < 0 || enemyVector[i]->getBullets()[j].shape.getPosition().y > map.texture.getSize().y)
			{
				enemyVector[i]->getBullets().erase(enemyVector[i]->getBullets().begin() + j);
			}
			else
			{
				this->PlayerColCheck(win, player, enemyVector, i, j);
				break;
			}
		}

	}
}

void Collision::PlayerColCheck(RenderWindow* win, Player& player, std::vector<Enemy*>& enemyVector, int i, int j)
{
	if (player.rectangle.getGlobalBounds().intersects(enemyVector[i]->getBullets()[j].shape.getGlobalBounds()))
	{
		std::cout << "Player hit!\n";
		player.Hit(enemyVector[i]->GetAttack());
		if (player.Dead())
		{
			win->close();
		}
		enemyVector[i]->getBullets().erase(enemyVector[i]->getBullets().begin() + j);
	}
}
