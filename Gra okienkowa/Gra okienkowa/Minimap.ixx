
#include <iostream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module minimap;
import map;
import player;
export import interface_;

export class Minimap : public Interface
{
protected:

	View viewmap;

	void InitBox(Interface &inter);

public:
	Minimap();
	Minimap(Interface& inter);

	void UpdateMinimap(Interface& inter, RenderWindow* window, Player& player, Map& map);
};