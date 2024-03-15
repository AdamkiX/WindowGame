
#include <iostream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <random>

using namespace sf;

import Draw;
import CollisionCheck;
import StartMenu;
import Bullet;
import GoblinMage;
import equipment;
import playerStats;
import map;
import player;
import interface_;
import minimap;
import game;


bool isMousePressed = false;
int FRAME = 0;

void Game::InitVars()
{
	this->stop = false;
	this->enemymax = 30;
	this->nameSet = false;
	this->win = nullptr;
	this->InitFont();
	this-> minimap = Minimap(this->inter);
	this->pStats = PlayerStats(this->inter, this->player, this->font);
	this->g.SetSubFolder();
	GoblinMage* goblinMage = new GoblinMage();
	enemyVector.push_back(goblinMage);
	enemyVector[0]->SetSpawnPos(200, 400);
	GoblinMage* goblinMage1 = new GoblinMage();
	enemyVector.push_back(goblinMage1);
	enemyVector[1]->SetSpawnPos(400, 400);
	for (int i = 2; i < 5; i++)
	{
		GoblinMage* goblinMagex = new GoblinMage();
		enemyVector.push_back(goblinMagex);
		enemyVector[i]->SetSpawnPos(i * 50 + 100, i * 50 + 100);
	}
	for (int i = 5; i < 10; i++)
	{
		GoblinMage* goblinMagex = new GoblinMage();
		enemyVector.push_back(goblinMagex);
		enemyVector[i]->SetSpawnPos(i * 25 + 200, 200);
	}
}

void Game::InitWin()
{
	this -> win = new RenderWindow(desktopMode = VideoMode(800, 600), "Island of Forggoten", Style::Default);
	this -> win -> setFramerateLimit(60);
	view.reset(sf::FloatRect(400.f, 300.f, 200.f, 150.f));
}

void Game::InitFont()
{
	if (!font.loadFromFile("Font/LuckiestGuy.ttf"))
	{
		std::cout << "Couldn't load font!\n";
	}
}

Game::Game()
{
	this->InitVars();
	this->InitWin();
	startMenu = StartMenu(this->win, this->font);
}

const bool Game::GetWinIsOpen() const
{
	return this->win->isOpen();
}

void Game::CenterOnPlayer()
{
	Vector2u resolution = win->getSize();
	unsigned int screenWidth = resolution.x;
	unsigned int screenHeight = resolution.y;

	center.x = (screenWidth - screenWidth *0.25)/2;
	center.y = screenHeight/2;
}

void Game::UpdateEnemies()
{
	if (enemyVector.size() != 0)
	{
		for (int i = 0; i < enemyVector.size(); i++)
		{
			this->enemyVector[i]->UpdateEnemy(this->win, this->player);
			drawer.DrawSprite(win,enemyVector[i]->GetSpr());
			// TRYING TO DO
			//collisionCheck.EnemyHitting(this->win,this->player,this->enemyVector);
			int who = collisionCheck.GetEnemyToKill();
			if (who >= 0)
			{
				delete enemyVector[who];
				enemyVector.erase(enemyVector.begin() + who);
				collisionCheck.SetEnemyToKill(-1);
			}
			this->PlayerColCheck();
		}
		for (int i = 0; i < enemyVector.size(); i++)
		{
			for (int j = 0; j < enemyVector[i]->GetBulletsVecSize(); j++)
			{
				drawer.DrawShape(win, enemyVector[i]->getBullets()[j].shape);
			}
		}
	}
}

void Game::PlayerColCheck()
{
	for (int i = 0; i < enemyVector.size(); i++)
	{
		for(int j = 0; j < enemyVector[i]->GetBulletsVecSize(); j++)
		{
			float div = enemyVector.size();
			enemyVector[i]->getBullets()[j].shape.move(enemyVector[i]->getBullets()[j].currVelocity / div);
			enemyVector[i]->getBullets()[j].sprite.setPosition(enemyVector[i]->getBullets()[j].shape.getPosition());
			drawer.DrawSprite(this->win,enemyVector[i]->getBullets()[j].sprite);
			//Out of bounds
			if (enemyVector[i]->getBullets()[j].shape.getPosition().x < 0 || enemyVector[i]->getBullets()[j].shape.getPosition().x > map.texture.getSize().x
				|| enemyVector[i]->getBullets()[j].shape.getPosition().y < 0 || enemyVector[i]->getBullets()[j].shape.getPosition().y > map.texture.getSize().y)
			{
				enemyVector[i]->getBullets().erase(enemyVector[i]->getBullets().begin() + j);
			}
			else
			{
				if (player.rectangle.getGlobalBounds().intersects(enemyVector[i]->getBullets()[j].shape.getGlobalBounds()))
				{
					std::cout << "Player hit!\n";
					player.Hit(enemyVector[i]->GetAttack());
					if (player.Dead())
					{
						this->win->close();
					}
					enemyVector[i]->getBullets().erase(enemyVector[i]->getBullets().begin() + j);
					break;
				}
				
			}
		}

	}
}

void Game::UpdateInterface()
{
	this->inter.DrawInterface(this->win);
	this->inter.UpdateInterfacePos(this->player);
	this->minimap.UpdateInterfacePos(this->player);
	this->minimap.UpdateMinimap(this->inter, this->win, this->player, this->map);
	this->pStats.UpdateInterfacePos(this->win, this->inter, this->player, this->view);
	this->equipment.UpdateInterfacePos(this->win, this->inter);

	this->win->display();
}

void Game::CreateInterface()
{
	this->inter.DrawInterface(this->win);
	this->minimap.DrawInterface(this->win);
	this->pStats.DrawInterface(this->win);
	this->equipment.DrawInterface(this->win);
}

void Game::UpdateEvents()
{
	while (this->win->pollEvent(this->ev))
	{
		if (this->ev.type == Event::Closed)
		{
			for (int i = 0; i < enemyVector.size(); i++)
			{
				for (int j = 0; j < enemyVector[i]->getBullets().size(); j++)
				{
					enemyVector[i]->getBullets().erase(enemyVector[i]->getBullets().begin());
				}
				enemyVector[i]->getBullets().clear();
				enemyVector.erase(enemyVector.begin());
			}
			enemyVector.clear();
			this->win->close();
		}
		if (this->ev.type == Event::KeyPressed && ev.KeyPressed == Keyboard::Escape)
			this->win->close();
		if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
		{
			isMousePressed = true;
			this->CenterOnPlayer();
			this->player.SetCenter(center);
		}
		if (ev.type == sf::Event::MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Left)
		{
			isMousePressed = false;
		}
		startMenu.handleEvent(ev);
		if (!startMenu.isInMenu() and !startMenu.isEnteringName())
		{
			nameSet = true;
		}
		if (nameSet && !stop)
		{
			std::string pname = startMenu.GetPlayerName();
			String sfmlname(pname);
			player.SetName(sfmlname);
			stop = true;
		}
	}

	if (!startMenu.isInMenu() and !startMenu.isEnteringName())
	{
		if (isMousePressed and Mouse::getPosition(*win).x < center.x * 2)
		{
			this->player.Shoot(win);
		}
		else
		{
			// Wejœcie w interfejs
		}
	}
}

void Game::RenderGame()
{
	this->win->clear();
	this->drawer.DrawSprite(this->win, map.GetSpr());
	this->CreateInterface();
	this->drawer.DrawSprite(this->win, this->player.GetSpr());
	//this->player.DrawPlayer(this->win);

}

void Game::UpdateGame()
{	
	if (!startMenu.isInMenu() and !startMenu.isEnteringName())
	{
		this->player.UpdatePlayer(this->win, FRAME);
		this->view.setCenter(this->player.getPosition().x + 25, this->player.getPosition().y);
		drawer.DrawBullets(this->win, this->player.bullets);
		//this->DrawBullets();
		//this->EnemyColCheck();
		this->collisionCheck.PlayerHitting(this->map, this->player, this->enemyVector);
		this->UpdateEnemies();
		if (this->enemyVector.size() < enemymax)
		{
			int lastenemy = enemyVector.size();
			for (int i = 0; i < enemymax - enemyVector.size(); i++)
			{
				std::random_device rx;
				std::random_device ry;
				std::default_random_engine e1(rx());
				std::uniform_int_distribution<int> uniform_dist1(200, 800);
				std::default_random_engine e2(ry());
				std::uniform_int_distribution<int> uniform_dist2(100, 600);

				int x = uniform_dist1(rx);
				int y = uniform_dist2(ry);

				GoblinMage* goblinMagex = new GoblinMage();
				enemyVector.push_back(goblinMagex);
				enemyVector[i+lastenemy]->SetSpawnPos(x, y);
			}
		}
		this->UpdateInterface();
		this->win->setView(view);
	}
	else if(startMenu.isInMenu() or startMenu.isEnteringName())
	{
		drawer.Drawtext(win, startMenu.ExecuteStart());
		
		//this->startMenu.draw();
		this->win->display();
	}

	this->UpdateEvents();

	FRAME++;
}