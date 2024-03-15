
#include <iostream>;
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <filesystem>

import map;

using namespace sf;

Map::Map()
{
	this->LoadMap();
}

void Map::LoadMap()
{
	std::filesystem::path imagePath = "Sprites/MapAlpha.png";
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

	map_.setTexture(texture);

}