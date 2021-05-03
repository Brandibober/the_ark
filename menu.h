//
// Created by karina on 02.05.2021.
//

#ifndef THE_ARK_MENU_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using std::string;

class Menu
{
private:
    const static int START = 1;
    const static int EXIT = 2;
    const static int MENU_POSITION_X = 0;
    const static int MENU_POSITION_Y = 0;
    const static int START_BUTTON_POS_X = 325;
    const static int START_BUTTON_POS_Y = 100;
    const static int START_BUTTON_WIDTH = 326;
    const static int START_BUTTON_HEIGHT = 321;
    const static int EXIT_BUTTON_POS_X = 1020;
    const static int EXIT_BUTTON_POS_Y = 525;
    const static int EXIT_BUTTON_WIDTH = 160;
    const static int EXIT_BUTTON_HEIGHT = 127;
    const static int WINDOW_WIDTH = 1200 ;
    const static int WINDOW_HEIGHT = 675;
    const static bool NO = false;
    const static bool YES = true;
    bool IS_FLIGHT_AVAILABLE = NO;
protected:
    Image menu;
    Texture menu_texture;
    Sprite menu_sprite;
    Image start;
    Texture start_texture;
    Sprite start_sprite;
    Image exit;
    Texture exit_texture;
    Sprite exit_sprite;
    int menuNum = 0;
public:

    void create_menu(const string& menu_)
    {
        menu.loadFromFile(menu_);
        menu_texture.loadFromImage(menu);
        menu_sprite.setTexture(menu_texture);
        menu_sprite.setPosition(MENU_POSITION_X, MENU_POSITION_Y);
    }

    void create_start(const string& start_)
    {
        start.loadFromFile(start_);
        start_texture.loadFromImage(start);
        start_sprite.setTexture(start_texture);
        start_sprite.setPosition(START_BUTTON_POS_X, START_BUTTON_POS_Y);
    }
    void create_exit(const string& exit_)
    {
        exit.loadFromFile(exit_);
        exit_texture.loadFromImage(exit);
        exit_sprite.setTexture(exit_texture);
        exit_sprite.setPosition(EXIT_BUTTON_POS_X, EXIT_BUTTON_POS_Y);
    }

    void set_flight()
    { IS_FLIGHT_AVAILABLE = YES; }

    bool get_flight()
    { return IS_FLIGHT_AVAILABLE; }

    void start_pressed(RenderWindow& window)
    {
        set_flight();
        window.close();
    }

    void welcome_page(string menu_, string exit_, string start_)
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

    void exit_pressed(RenderWindow& window)
    { window.close(); }

    void processing_menu(RenderWindow& window)
    {
        while (window.isOpen())
        {
            Event event;

            //while (window.pollEvent(event))
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                exit_pressed(window);

            if (IntRect(START_BUTTON_POS_X, START_BUTTON_POS_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT).contains(Mouse::getPosition(window))) { menuNum = START; }
            if (IntRect(EXIT_BUTTON_POS_X, EXIT_BUTTON_POS_Y, EXIT_BUTTON_WIDTH, EXIT_BUTTON_HEIGHT).contains(Mouse::getPosition(window))) { menuNum = EXIT; }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (menuNum == START)
                    start_pressed(window);
                else if (menuNum == EXIT)
                    exit_pressed(window);
            }
        }
    }
};

#define THE_ARK_MENU_H

#endif //THE_ARK_MENU_H
