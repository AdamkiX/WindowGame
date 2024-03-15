#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

import Draw;
import Bullet;

Drawer::Drawer()
{

}

void Drawer::DrawSprite(RenderWindow* window, const Sprite& sprite)
{
	window->draw(sprite);
}

void Drawer::DrawShape(RenderWindow* window, const Shape& shape)
{
	window->draw(shape);
}

void Drawer::Drawtext(RenderWindow* window, const Text& text)
{
	window->draw(text);
}

void Drawer::Drawtext(RenderWindow* window, const std::vector<Text>& text)
{
	for (int i = 0; i < text.size(); i++)
	{
		window->draw(text[i]);
	}
}

void Drawer::DrawBullets(RenderWindow* window, const std::vector<Bullet>& bullets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		window->draw(bullets[i].shape);
	}
}
