#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
//#include "PlayerStats.ixx";

using namespace sf;

import player;
import interface_;
import playerStats;

PlayerStats::PlayerStats()
{

}

PlayerStats::PlayerStats(Interface& inter, Player& player, Font& font)
{
	this->HideBoxes();
	this->InitBars(inter);
	this->InitText(player, font);
}

void PlayerStats::DrawInterface(RenderTarget* target)
{
	this->DrawStats(target);
}

void PlayerStats::DrawStats(RenderTarget* target)
{

}

void PlayerStats::InitBars(Interface & inter)
{
	Vector2f barSize(inter.nameHUD.getSize().x * 2.5 , inter.nameHUD.getSize().x/2);
	Color r(75, 0, 0);
	Color y(100,100,0);
	this->hpBar.setSize(barSize);
	this->hpBar.setFillColor(r);
	this->hpBar.setOutlineThickness(4.f);
	this->hpBar.setOutlineColor(Color::Black);
	
	this->expBar = this->hpBar;
	this->dynamicHP = this->hpBar;
	this->dynamicEXP = this->hpBar;

	this->expBar.setFillColor(y);
	this->dynamicHP.setOutlineThickness(0.f);
	this->dynamicEXP.setOutlineThickness(0.f);
	this->dynamicHP.setFillColor(Color::Red);
	this->dynamicEXP.setFillColor(Color::Yellow);

	maxhpBar = hpBar.getSize();
	maxexpBar = expBar.getSize();
}

void PlayerStats::InitText(Player& player, Font& font)
{
	// Inicjowanie Sta³ych wartoœci (Nazwy pasków)
	this->name_ = player.GetName() + "  LV: " + ToString(player.GetLV());
	this->hp_ = "HP  ";
	this->exp_ = "XP ";

	this->hp.setFont(font);
	this->hp.setCharacterSize(25);
	this->hp.setFillColor(Color::Black);

	this->name = this->hp;
	this->exp = this->hp;

	this->hp.setString(hp_);
	this->name.setString(name_);
	this->exp.setString(exp_);

	// Inicjowanie zmiennych hp, exp'a gracza do interfejsu 
	this->inthp_ = ToString(player.GetHP());
	this->intmaxhp_ = " / " + ToString(player.GetMaxHP());
	this->intexp_ = ToString(player.GetEXP());
	this->intmaxexp_ = " / " + ToString(player.GetMaxEXP());

	this->inthp.setFont(font);
	this->inthp.setCharacterSize(15);
	this->inthp.setFillColor(Color::Black);

	this->intexp = this->inthp;
	this->intmaxexp = this->inthp;
	this->intmaxhp = this->inthp;

	this->inthp.setString(inthp_);
	this->intmaxhp.setString(intmaxhp_);
	this->intexp.setString(intexp_);
	this->intmaxexp.setString(intmaxexp_);
}

void PlayerStats::UpdateInterfacePos(RenderTarget* target, Interface& inter, Player& player, View& view)
{
	this->UpdateStats(target, inter, player, view);
}

void PlayerStats::UpdateStats(RenderTarget* target, Interface& inter, Player& player, View& view)
{
	this->name_ = player.GetName() + "  LV:" + ToString(player.GetLV());
	this->name.setString(name_);

	// Ustawienie view portu, aby paski i czczionka mia³y lepsz¹ rozdzielczoœæ
	this->StatsHUD.setViewport(sf::FloatRect(0.55f, 0.23f, 0.5f, 0.5f));
	this->StatsHUD.setCenter(player.getPosition());
	this->StatsHUD.setSize(400, 400);

	// Aktualizowanie pozycji statycznego tekstu
	this->name.setPosition(inter.nameHUD.getPosition().x - 100, inter.nameHUD.getPosition().y-75);
	this->hp.setPosition(inter.hpHUD.getPosition().x - 100, inter.hpHUD.getPosition().y-12);
	this->exp.setPosition(inter.expHUD.getPosition().x -100, inter.expHUD.getPosition().y+60);

	// Warunek przesuwania siê dynamicznego paska zdrowia i expa
	inthp_ = ToString(player.GetHP());
	inthp.setString(inthp_);
	intmaxhp_ = ToString(player.GetMaxHP());
	intmaxhp.setString(" / " + intmaxhp_);
	intexp_ = ToString(player.GetEXP());
	intexp.setString(intexp_);
	intmaxexp_ = ToString(player.GetMaxEXP());
	intmaxexp.setString(" / " + intmaxexp_);
	actualHP.x = player.GetHP() / player.GetMaxHP() * maxhpBar.x; actualHP.y = maxhpBar.y;
	actualEXP.x = player.GetEXP() / player.GetMaxEXP() * maxexpBar.x; actualEXP.y = maxexpBar.y;

	this->dynamicHP.setSize(actualHP);
	this->dynamicEXP.setSize(actualEXP);

	// Ustawienie pozycji pasków
	this->hpBar.setPosition(this->hp.getPosition().x + this->hp.getGlobalBounds().width, this->hp.getPosition().y + this->hp.getGlobalBounds().height*0.5);
	this->expBar.setPosition(this->exp.getPosition().x + this->hp.getGlobalBounds().width, this->exp.getPosition().y + this->exp.getGlobalBounds().height*0.5);
	this->dynamicHP.setPosition(hpBar.getPosition());
	this->dynamicEXP.setPosition(expBar.getPosition());

	// Ustawienie pozycji tekstu zawieraj¹cych aktualne dane gracza
	this->intexp.setPosition(this->expBar.getPosition().x + (this->expBar.getLocalBounds().width - this->intexp.getLocalBounds().width - this->intmaxexp.getLocalBounds().width)*0.5, this->expBar.getPosition().y);
	this->intmaxexp.setPosition(this->intexp.getPosition().x + this->intexp.getLocalBounds().width, this->intexp.getPosition().y);
	this->inthp.setPosition(this->hpBar.getPosition().x + (this->hpBar.getLocalBounds().width - this->inthp.getLocalBounds().width - this->intmaxhp.getLocalBounds().width) * 0.5, this->hpBar.getPosition().y);
	this->intmaxhp.setPosition(this->inthp.getPosition().x + this->inthp.getLocalBounds().width, this->inthp.getPosition().y);

	// Rysowanie na ekranie

	target->setView(this->StatsHUD);
	target->draw(this->hp);
	target->draw(this->exp);
	target->draw(this->name);

	target->draw(this->hpBar);
	target->draw(this->expBar);
	target->draw(this->dynamicHP);
	target->draw(this->dynamicEXP);

	target->draw(this->inthp);
	target->draw(this->intexp);
	target->draw(this->intmaxhp);
	target->draw(this->intmaxexp);

	target->setView(view);
}

String PlayerStats::ToString(int integer)
{
	std::ostringstream os;
	os << integer;
	return os.str();
}