#include <SFML/Graphics.hpp>;
#include <SFML/Window.hpp>;
#include <SFML/System.hpp>;
#include <iostream>
#include <regex>

using namespace sf;

import StartMenu;


StartMenu::StartMenu()
    : window(nullptr), inMenu(true), enteringName(false)
{
    // Inicjalizacja tekstu, czcionki i przycisków
}

StartMenu::StartMenu(sf::RenderTarget* window, Font& font)
    : window(window), inMenu(true), enteringName(false)
{
    validName = false;
    startText.setFont(font);
    startText.setString("Start");
    startText.setCharacterSize(20);
    startText.setPosition(200, 200);

    exitText.setFont(font);
    exitText.setString("Wyjdz");
    exitText.setCharacterSize(20);
    exitText.setPosition(200, 250);

    nameText.setFont(font);
    nameText.setPosition(window->getSize().x / 4, window->getSize().y / 4);
    nameText.setFillColor(Color::White);
    nameText.setCharacterSize(30);
}

void StartMenu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (startText.getGlobalBounds().contains(mousePos)) {
            inMenu = false;
            enteringName = true;
        }
        else if (exitText.getGlobalBounds().contains(mousePos)) {
            exit(0);
        }
    }

    if (enteringName && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode != 13) { // 13 - Enter key
            if (event.text.unicode == 8 && playerName.size() > 0) { // 8 - Backspace key
                playerName.pop_back();
            }
            else if (playerName.size() < 6) {
                playerName += event.text.unicode;
                nameText.setString(playerName);
            }

        }
        if (event.text.unicode == 13 && validName)
        {
            enteringName = false;
        }
    }
}

const std::vector<Text>& StartMenu::ExecuteStart()
{
    window->clear();

    if (inMenu) {
        if (once)
        {
            texts.push_back(startText);
            texts.push_back(exitText);
            once = false;
        }

        return texts;
    }
    else if (enteringName) {
        texts.clear();
        std::string displayName = "NIE UZYWAC ZNAKOW SEPCJALNYCH \nLUB LICZB\n\nNazwij postac: " + playerName;

        // Sprawdzanie poprawnoœci imienia
        std::regex nameRegex("^[a-zA-Z]{1,6}$");
        validName = std::regex_match(playerName, nameRegex);

        if (validName) {
            displayName += " \n\n- Poprawne";
        }
        else {
            displayName += " \n\n- Bledne";
        }
        nameText.setString(displayName);
        texts.push_back(nameText);

        return texts;
    }
}


bool StartMenu::isInMenu() const
{
    return inMenu;
}

bool StartMenu::isEnteringName()
{
    return enteringName;
}

StartMenu::~StartMenu()
{
    texts.~vector();
}
