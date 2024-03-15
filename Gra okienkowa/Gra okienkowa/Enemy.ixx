
#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module Enemy;
import player;

export class Enemy
{
protected:
	static int idCounter;
	int id;

	bool detected;

	Texture texture;
	Texture bulletTexture;
	Sprite sprite;
	RectangleShape rec;	
	RectangleShape vision;
	Clock clk;

	Vector2f position;
	std::string subfolder;
	std::string filename;

	float hp;
	float maxhp;
	float movSpd;
	float projSpd;
	float attack;
	float exp;
	float dext;

	int lv;

	// Chronione metody

	virtual void InitVars();
	virtual void InitSprite();

	// Chronione pociski

	virtual class Bullet
	{
	public:
		Sprite sprite;
		RectangleShape shape;
		Vector2f size;
		Vector2f currVelocity;
		float maxSpeed;

		Bullet(float width = 4.f, float height = 4.f)
			: currVelocity(0.f, 0.f), maxSpeed(2.f)
		{
			Color a(0, 0, 0, 0);
			this->size.x = width;
			this->size.y = height;
			this->shape.setSize(size);
			this->shape.setFillColor(a);
			//Sprites/Bullets/GoblinBullet.png
			//	std::cout << "Bullet created";
		}

		virtual ~Bullet()
		{
		};
	};

	std::vector<Bullet> bullets;
	Vector2f aimDir;
	Vector2f aimDirNorm;

public:

	virtual float GetExp() const { return exp; };
	virtual void Reward(Player& player);

	virtual void UpdateEnemyPos();
	virtual void SetSpawnPos(float x, float y);
	// Gettery
	virtual RectangleShape GetEnemy();
	virtual int GetBulletsVecSize() const { return bullets.size(); };
	virtual bool Detected() const { return detected; };
	virtual std::vector<Bullet>& getBullets() { return bullets; }
	virtual float GetAttack() const { return attack; };

	virtual bool Dead();	
	virtual void Movement(RenderTarget* target, Player& player);
	virtual bool PlayerTrigger(Player& player);
	virtual void CreateBullet();
	virtual void UpdateEnemy(RenderTarget* target, Player& player);
	virtual void Hit(Player& player);
	virtual void Shoot(Player& player);

	const Sprite& GetSpr() const {
		return sprite;
	}

	virtual ~Enemy();

};