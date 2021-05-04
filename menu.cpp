//
// Created by karina on 04.05.2021.
//

#include "menu.h"

void Menu::create_menu(const string& menu_)
{
    menu.loadFromFile(menu_);
    menu_texture.loadFromImage(menu);
    menu_sprite.setTexture(menu_texture);
    menu_sprite.setPosition(MENU_POSITION_X, MENU_POSITION_Y);
}

void Menu::create_start(const string& start_)
{
    start.loadFromFile(start_);
    start_texture.loadFromImage(start);
    start_sprite.setTexture(start_texture);
    start_sprite.setPosition(START_BUTTON_POS_X, START_BUTTON_POS_Y);
}
void Menu::create_exit(const string& exit_)
{
    exit.loadFromFile(exit_);
    exit_texture.loadFromImage(exit);
    exit_sprite.setTexture(exit_texture);
    exit_sprite.setPosition(EXIT_BUTTON_POS_X, EXIT_BUTTON_POS_Y);
}

void Menu::set_flight()
{ IS_FLIGHT_AVAILABLE = YES; }

bool Menu::get_flight() const
{ return IS_FLIGHT_AVAILABLE; }

void Menu::start_pressed(RenderWindow& window)
{
    set_flight();
    window.close();
}

void Menu::welcome_page(const string& menu_, const string& exit_, const string& start_)
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "THE ARK");
    create_menu(menu_);
    create_exit(exit_);
    create_start(start_);
    window.clear();
    window.draw(menu_sprite);
    window.draw(exit_sprite);
    window.draw(start_sprite);
    window.display();
    processing_menu(window);
}

void Menu::exit_pressed(RenderWindow& window)
{ window.close(); }

void Menu::processing_menu(RenderWindow& window)
{
    while (window.isOpen())
    {
        Event event;

        if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
            exit_pressed(window);

        if (IntRect(START_BUTTON_POS_X, START_BUTTON_POS_Y,
                    START_BUTTON_WIDTH, START_BUTTON_HEIGHT).contains(Mouse::getPosition(window)))
            menuNum = START;
        if (IntRect(EXIT_BUTTON_POS_X, EXIT_BUTTON_POS_Y,
                    EXIT_BUTTON_WIDTH, EXIT_BUTTON_HEIGHT).contains(Mouse::getPosition(window)))
            menuNum = EXIT;

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == START)
                start_pressed(window);
            else if (menuNum == EXIT)
                exit_pressed(window);
        }
    }
}