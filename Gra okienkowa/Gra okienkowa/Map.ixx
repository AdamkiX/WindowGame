#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

export module map;

using namespace sf;

export class Map
{

public:
	Texture texture;
	Sprite map_;
	// Metody
	Map();
	void LoadMap();
	const Sprite& GetSpr() const {
		return map_;
	}

};

