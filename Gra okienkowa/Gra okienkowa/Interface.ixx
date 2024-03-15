
#include <iostream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module interface_;
import player;

export class Interface
{
	View view;
protected:
	RectangleShape nameHUD;
	RectangleShape hpHUD;
	RectangleShape expHUD;
	RectangleShape blackbox;
	RectangleShape whitebox;
	float xPos;
	float yPos;

	void InitVars(float x, float y);
	void InitBox();

public:
	friend class PlayerStats;

	Interface(float x = 77.f, float y = 73.f);

	RectangleShape GetWhitebox();
	float GetPosX();
	float GetPosY();
	void HideBoxes();
	void DrawInterface(RenderTarget *target);
	void UpdateInterfacePos(Player& player);

	virtual ~Interface();

};