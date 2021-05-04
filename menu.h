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

    //---------------------------------------creating sprites for menu:
    void create_menu(const string& menu_);
    void create_start(const string& start_);
    void create_exit(const string& exit_);
    //------------------------------------------------------------------


    //-----------------------------changing and getting flight condition:
    void set_flight();                                              //makes the flight available
    bool get_flight();                                              //gets flight condition
    //------------------------------------------------------------------


    //------------------------------------------------processing bottons:
    void start_pressed(RenderWindow& window);                       //start booton
    void welcome_page(string menu_, string exit_, string start_);   //menu
    void exit_pressed(RenderWindow& window);                        //exit botton
    void processing_menu(RenderWindow& window);                     //processing the previos
    //------------------------------------------------------------------
};

#define THE_ARK_MENU_H

#endif //THE_ARK_MENU_H
