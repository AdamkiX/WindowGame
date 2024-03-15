
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

import GoblinMage;
import Goblin;
import Enemy;

GoblinMage::GoblinMage()
{
	this->InitVars();
	this->InitSprite();
}

void GoblinMage::InitVars()
{
	Color c(0, 0, 0, 0);
	this->subfolder = "Goblins";
	this->filename = "GoblinMage.png";

	this->attack = 10;
	this->exp = 7000;
	this->hp = 50;
	this->lv = 1;
	this->maxhp = 50;
	this->movSpd = 0.25;
	this->projSpd = 2;
	this->dext = 0.6;

	vision.setSize(Vector2f(150, 150));
	vision.setFillColor(c);
	vision.setOutlineThickness(1.f);
	vision.setOutlineColor(Color::Black);

	rec.setSize({ 6,8 });
	rec.setOutlineThickness(1.f);
	rec.setOutlineColor(Color::Red);
}

GoblinMage::~GoblinMage()
{

}
