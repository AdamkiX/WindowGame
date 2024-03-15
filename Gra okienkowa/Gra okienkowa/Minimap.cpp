#include <iostream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

import map;
import player;
import interface_;
import minimap;

Minimap::Minimap()
{

}

Minimap::Minimap(Interface& inter)
{
	this->InitBox(inter);
}

void Minimap::UpdateMinimap(Interface & inter, RenderWindow* window, Player& player, Map& map)
{
	this->viewmap.setViewport(sf::FloatRect(0.76f, 0.0135f, 0.2305f, 0.307f));
	this->viewmap.setCenter(player.getPosition());
	this->viewmap.setSize(300, 300);
	window->setView(this->viewmap);
	window->draw(map.map_);
	window->draw(player.player_spr);

	window->setView(window->getDefaultView());
}

void Minimap::InitBox(Interface& inter)
{
	this->HideBoxes();
	Vector2f mSize(inter.GetWhitebox().getSize().x, inter.GetWhitebox().getSize().x);

	this->whitebox.setSize(mSize);
}

