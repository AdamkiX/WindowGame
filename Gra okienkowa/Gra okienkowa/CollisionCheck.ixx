#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <iostream>;
#include <vector>

using namespace sf;

export module CollisionCheck;
import player;
import Enemy;
import map;

export class Collision
{
	int enemyToKill;

	void EnemyColCheck(Player& player, std::vector<Enemy*>& enemyVector, int it);
	void PlayerColCheck(RenderWindow* win, Player& player, std::vector<Enemy*>& enemyVector, int it1, int it2);

public:
	Collision();

	int GetEnemyToKill() const { return enemyToKill; }

	void SetEnemyToKill(int e);

	void PlayerHitting(Map& map, Player& player, std::vector<Enemy*>& enemyVector);
	void EnemyHitting(Map& map, RenderWindow* win, Player& player, std::vector<Enemy*>& enemyVector);

};

