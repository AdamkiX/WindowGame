
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module playerStats;
import player;
export import interface_;

export class PlayerStats : public Interface
{
private:

	//Atrybuty
	View StatsHUD;

	Vector2f maxhpBar;
	Vector2f maxexpBar;
	Vector2f actualHP;
	Vector2f actualEXP;

	RectangleShape hpBar;
	RectangleShape dynamicHP;
	RectangleShape expBar;
	RectangleShape dynamicEXP;

	String name_;
	String hp_;
	String inthp_;
	String intmaxhp_;
	String exp_;
	String intexp_;
	String intmaxexp_;

	Text name;
	Text hp;
	Text inthp;
	Text intmaxhp;
	Text exp;
	Text intexp;
	Text intmaxexp;

	//Metody prwyatne
	void InitBars(Interface& inter);
	void InitText(Player& player, Font& font);

public:
	PlayerStats();
	PlayerStats(Interface& inter, Player& player, Font& font);

	void DrawInterface(RenderTarget* target);
	void DrawStats(RenderTarget* target);

	void UpdateInterfacePos(RenderTarget* target, Interface& inter, Player& player, View& view);
	void UpdateStats(RenderTarget* target, Interface& inter, Player& player, View& view);

	String ToString(int integer);
};