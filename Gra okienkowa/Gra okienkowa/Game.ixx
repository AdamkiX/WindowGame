#include <random>
#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

using namespace sf;

export module game;

import Draw;
import CollisionCheck;
import StartMenu;
import Bullet;
import GoblinMage;
import equipment;
import playerStats;	
import map;
import minimap;
import player;
import interface_;

int FRAME;

export class Game
{
	// Atrybuty
	Drawer drawer;
	Clock clock;
	RenderWindow *win;
	VideoMode desktopMode;
	View view;
	Event ev;
	Map map;
	Player player;
	Interface inter;
	Minimap minimap;
	Font font;	
	PlayerStats pStats;
	Equipment equipment;
	Goblin g;
	std::vector<Enemy*> enemyVector;
	StartMenu startMenu;
	Collision collisionCheck;

	//std::vector<int> enemyShooting;
	bool nameSet;
	bool stop;
	int enemymax;

	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;
	Vector2f center;


	// Metody prywatne
	void InitVars();
	void InitWin();
	void InitFont();

public:
	Game();

	const bool GetWinIsOpen() const;
	void CenterOnPlayer();
	void UpdateEnemies();
	void DrawBullets();
	void PlayerColCheck();
	void UpdateInterface();
	void CreateInterface();
	void UpdateEvents();
	void RenderGame();
	void UpdateGame();
};
