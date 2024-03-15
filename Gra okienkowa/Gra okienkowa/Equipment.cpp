#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
//#include "Equipment.ixx";

using namespace sf;

import equipment;
import interface_;

void Equipment::InitGear()
{
	int boxammount = 3;
	std::vector<Slot> bp(boxammount);
	eq = bp;

	filename = "StaffBox.png";
	eq[0].SetTexture(filename);
	filename = "RobeBox.png";
	eq[1].SetTexture(filename);
	filename = "RingBox.png";
	eq[2].SetTexture(filename);

}

void Equipment::InitEq()
{
	filename = "Box.png";
	int boxammount = 6;
	std::vector<Slot> bp(boxammount);
	backpack = bp;
	for (int i = 0; i < backpack.size(); i++)
	{
		backpack[i].SetTexture(filename);
	}
	
	// Wychwytywanie co trzeciego slotu, aby utworzyæ nowy rz¹d slotów
	auto wynik = backpack | std::views::transform([](const Slot& obj) { return obj.id - 3;}) | std::views::stride(3);
	std::ranges::copy(wynik, std::back_inserter(wynik_vector));
	for (int i = 0; i < wynik_vector.size(); i++)
	{
		std::cout << wynik_vector[i];
	}
}

Equipment::Equipment()
{
	this->HideBoxes();
	this->InitGear();
	this->InitEq();
}

void Equipment::UpdateBp(RenderTarget* win, Interface& inter)
{

	eqPos.x = inter.GetWhitebox().getPosition().x; eqPos.y = inter.GetWhitebox().getPosition().y + 115;
	slotPos = eqPos;
	int j = 1;
	slotPos.x = eqPos.x + backpack[0].GetSlot().getGlobalBounds().width * 3 * 0.25 + 3/2;
	backpack[0].SetSlotPosition(slotPos);

	win->draw(backpack[0].GetSprite());

	for (int i = 1; i < backpack.size(); i++)
	{
		slotPos.x = backpack[i-1].GetSlot().getPosition().x + backpack[i - 1].GetSlot().getGlobalBounds().width-1;
		// Nowa linia slotów
		if (i % (wynik_vector[j]-1) == 0)
		{
			slotPos.x = backpack[0].GetSlot().getPosition().x;
			slotPos.y = backpack[i-3].GetSlot().getPosition().y + backpack[0].GetSlot().getGlobalBounds().height - 1 ;
		}
		backpack[i].SetSlotPosition(slotPos);
		win->draw(backpack[i].GetSprite());
	}
}

void Equipment::UpdateGear(RenderTarget* win, Interface& inter)
{
	eqPos.x = inter.GetWhitebox().getPosition().x; eqPos.y = inter.GetWhitebox().getPosition().y + 99;
	slotPos = eqPos;

	slotPos.x = eqPos.x + eq[0].GetSlot().getGlobalBounds().width * 3 * 0.25 - 4.5;
	eq[0].SetSlotPosition(slotPos);
	win->draw(this->eq[0].GetSprite());

	for (int i = 1; i < eq.size(); i++)
	{
		slotPos.x = eq[i - 1].GetSlot().getPosition().x + eq[i - 1].GetSlot().getGlobalBounds().width + 5;
		eq[i].SetSlotPosition(slotPos);
		win->draw(eq[i].GetSprite());
	}
}

void Equipment::Slot::InitSquare()
{
	size = { 10,10 };
	this->square.setSize(size);
	//this->SetTexture(spriteName);
}

Equipment::Slot::Slot()
{
	id = idCounter++;
	this->InitSquare();
}

void Equipment::Slot::SetTexture(std::string& spriteName)
{
	if (!texture.loadFromFile("Sprites/"+spriteName))
	{
		std::cout << "couldnt load " << spriteName << " texture!\n";
	}
	slot_spr.setTexture(texture);
	slot_spr.setPosition(square.getPosition());
}

void Equipment::Slot::SetSlotPosition(Vector2f position)
{
	this->slot_spr.setPosition(position);
	this->square.setPosition(position);
}

Sprite Equipment::Slot::GetSprite()
{
	return slot_spr;
}

void Equipment::DrawInterface(RenderTarget* win)
{
	for (int i = 0; i < eq.size(); i++)
		win->draw(this->eq[i].GetSprite());

	for(int i =0; i < backpack.size(); i++)
		win->draw(this->backpack[i].GetSprite());
}

void Equipment::UpdateInterfacePos(RenderTarget* win, Interface& inter)
{
	this->UpdateBp(win, inter);
	this->UpdateGear(win,  inter);
}

Equipment::~Equipment()
{
	for (int i = 0; i < eq.size(); i++)
	{
		eq.erase(eq.begin() + i);
	}
	eq.clear();
	for (int i = 0; i < backpack.size(); i++)
	{
		backpack.erase(backpack.begin() + i);
	}
	backpack.clear();
}

RectangleShape Equipment::Slot::GetSlot()
{
	return square;
}
