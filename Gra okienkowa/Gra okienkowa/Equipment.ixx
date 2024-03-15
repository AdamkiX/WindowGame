#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module equipment;
export import interface_;

export class Equipment : public Interface
{
	class Slot;

	Vector2f eqPos;
	Vector2f slotPos;

	std::vector<int> wynik_vector;
	std::string filename;
	std::vector<Slot> eq;
	std::vector<Slot> backpack;
	void InitGear();
	void InitEq();

	void UpdateBp(RenderTarget* win, Interface& inter);
	void UpdateGear(RenderTarget* win, Interface& inter);
public:
	Equipment();

	void DrawInterface(RenderTarget* win);

	void UpdateInterfacePos(RenderTarget* win, Interface& inter);
	
	virtual ~Equipment();
	class Slot
	{
		Vector2f size;
		Texture texture;
		Sprite slot_spr;
		RectangleShape square;
		void InitSquare();
	public:
		static int idCounter;
		int id;
		Slot();

		void SetTexture(std::string& spriteName);
		void SetSlotPosition(Vector2f position);

		Sprite GetSprite();

		RectangleShape GetSlot();

	};
};

int Equipment::Slot::idCounter = 1;