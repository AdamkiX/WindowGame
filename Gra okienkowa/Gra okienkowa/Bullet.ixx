
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <iostream>;

export module Bullet;

using namespace sf;

export class Bullet
{
public:
	RectangleShape shape;
	Vector2f size;
	Vector2f currVelocity;
	float maxSpeed;

	Bullet(float width = 5.f, float height = 5.f)
		: currVelocity(0.f, 0.f), maxSpeed(4.f)
	{
		this->size.x = width;
		this->size.y = height;
		this->shape.setSize(size);
		this->shape.setFillColor(Color::Red);
	//	std::cout << "Bullet created";
	}

	virtual ~Bullet()
	{
	};
};