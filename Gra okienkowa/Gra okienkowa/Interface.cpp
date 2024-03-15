#include <iostream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

import player;
import interface_;

void Interface::InitVars(float x, float y)
{
	xPos = x;
	yPos = y;
}

void Interface::InitBox()
{
	Vector2f size(46, 146);
	Color outline(0,0,0);
	Color fillw(255, 255, 255, 125);
	this -> whitebox.setSize(size);
	this->whitebox.setOutlineColor(outline);
	this->whitebox.setOutlineThickness(2.f);
	this->whitebox.setFillColor(fillw);
	this -> blackbox.setSize(size);
	this -> blackbox.setOutlineColor(outline);
	this->blackbox.setOutlineThickness(2.f);
	this->blackbox.setFillColor(outline);

	Vector2f nameSize(whitebox.getSize().x, whitebox.getSize().x / 3);
	this->nameHUD.setSize(nameSize);
	this->nameHUD.setFillColor(Color::Red);
	this->nameHUD.setOutlineThickness(2.f);
	this->nameHUD.setOutlineColor(Color::Black);

	this->hpHUD = nameHUD;
	this->hpHUD.setFillColor(Color::Green);
	this->expHUD = nameHUD;
	this->expHUD.setFillColor(Color::Blue);
}

Interface::Interface(float x, float y)
{
	this->InitVars(x,y);
	this->InitBox();
}

RectangleShape Interface::GetWhitebox()
{
	return whitebox;
}

float Interface::GetPosX()
{
	return xPos;
}

float Interface::GetPosY()
{
	return yPos;
}	

void Interface::HideBoxes()
{
	Color invisible(0, 0, 0, 0);
	this->blackbox.setFillColor(invisible);
	this->whitebox.setFillColor(invisible);
	this->blackbox.setOutlineColor(invisible);
}

void Interface::DrawInterface(RenderTarget* target)
{
	target->draw(this->blackbox);
	target->draw(this->whitebox);
	target->draw(this->nameHUD);
	target->draw(this->hpHUD);
	target->draw(this->expHUD);
}

void Interface::UpdateInterfacePos(Player &player)
{
	whitebox.setPosition(player.getPosition().x + xPos, player.getPosition().y - yPos);
	blackbox.setPosition(whitebox.getPosition());

	Vector2f pos(whitebox.getPosition().x, whitebox.getPosition().y + whitebox.getSize().x + whitebox.getOutlineThickness());
	this->nameHUD.setPosition(pos);
	this->hpHUD.setPosition(pos.x, pos.y + whitebox.getSize().x / 3);
	this->expHUD.setPosition(pos.x, pos.y + whitebox.getSize().x / 3 * 2);
}
	
Interface::~Interface()
{

}
