
#include <iostream>;

#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <vector>

using namespace sf;

export module StartMenu;
import player;

export class StartMenu
{
public:
    StartMenu();
    StartMenu(RenderTarget* window, Font& font);
    void handleEvent(const Event& event);
    const std::vector<Text>& ExecuteStart();
    bool isInMenu() const;
    bool isEnteringName();
    std::string GetPlayerName() { return playerName; };
    virtual ~StartMenu();

private:

    RenderTarget* window;
    Font font;
    Text startText;
    Text exitText;

    bool once = true;
    bool validName;
    bool inMenu;
    bool enteringName;
    std::string playerName;
    Text nameText;

    std::vector<Text> texts;
};