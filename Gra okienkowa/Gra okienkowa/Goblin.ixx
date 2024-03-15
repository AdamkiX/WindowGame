
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module Goblin;

export import Enemy;

export class Goblin : public Enemy
{

public:
	virtual void SetSubFolder();
};



