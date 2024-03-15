#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

export module player;
import Bullet;

using namespace sf;

export class Player
{
	//atrybuty
	String name;

	bool dead = false;

	float hp;
	float maxhp;
	float attack;
	int vitality;
	float movSpd;
	float projSpd;
	float dexterity;

	float exp;
	float maxexp;
	int lv;

	//Prywatne metody
	void InitVars();
	void InitSprite();

	Clock clock;
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;
	Vector2f center;


public:

	std::vector<Bullet> bullets;
	Vector2f position,mov;
	Texture texture;
	Sprite player_spr;
	RectangleShape rectangle;

	//Metody
	//Konstruktor
	Player(float x = 400.f, float y = 300.f);

	// Setters
	void SetMovSpd(float value);
	void SetProjSpd(float value);
	void SetName(String& Pname);
	void SetCenter(Vector2f& pcenter);

	// Getters

	int GetLV();
	float GetMaxEXP();
	float GetEXP();
	float GetHP();
	float GetMaxHP();
	float GetDext();
	float GetAtt();
	String GetName();
	Vector2f getPosition() const { return position; } // Getter dla pozycji gracza
	float GetMovSpd();
	float GetProjSpd();
	const Sprite& GetSpr() const {
		return player_spr;
	}

	//TO DO void Shoot();

	void AddExp(float Eexp);
	void RegenHP(int& FRAME);
	void Hit(float Eatt);
	bool Dead();
	void Shoot(RenderWindow* win);
	void UpdateInput();
	void LevelUp();
	void LoadTexture();
	void UpdatePlayer(RenderTarget* target, int& FRAME);
};