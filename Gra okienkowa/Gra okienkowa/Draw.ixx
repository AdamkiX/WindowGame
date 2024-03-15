#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <iostream>
#include <vector>

using namespace sf;

export module Draw;
import Bullet;

export class Drawer
{

public:
	Drawer();

	void DrawSprite(RenderWindow* window, const Sprite& sprite);
	void DrawShape(RenderWindow* window, const Shape& shape);
	void DrawBullets(RenderWindow* window, const std::vector<Bullet>& bullets);
	void Drawtext(RenderWindow* window, const Text& text);
	void Drawtext(RenderWindow* window, const std::vector<Text>& text);
};

