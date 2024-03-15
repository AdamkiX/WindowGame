#include <iostream> 

#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;

import game;

using namespace sf;

int main()
{
    Game myGame;

    while (myGame.GetWinIsOpen())
    {
        myGame.UpdateGame();

        myGame.RenderGame();
    }

    return 0;
}
