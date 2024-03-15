
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module GoblinMage;

export import Goblin;

export class GoblinMage : public Goblin
{
public:
	GoblinMage();
	void InitVars() override;

	virtual ~GoblinMage() override;

};
