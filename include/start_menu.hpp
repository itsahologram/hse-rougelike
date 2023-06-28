#ifndef TEST_SFML_START_MENU_HPP
#define TEST_SFML_START_MENU_HPP
#pragma once
#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "engine.hpp"

namespace menu {
#define MAX_MENU 4

    class Menu {
    public:
        Menu(std::size_t width, std::size_t height);
        void Draw(sf::RenderWindow &window);
        void Move_up();
        void Move_down();
        int Menu_pressed() const;
        ~Menu();

    private:
        int menu_selected;
        sf::Font font;
        sf::Text mainMenu[MAX_MENU];
    };
}

namespace log_host {
#define MAX_BUTTONS 2
    class log_host{
    public:
        log_host(std::size_t width, std::size_t height);
        void Draw_log_or_host(sf::RenderWindow &window);
        void Move_up_log();
        void Move_down_log();
        int Menu_pressed_log() const;
        ~log_host();

    private:
        int log_selected;
        sf::Font log_font;
        sf::Text logHost[MAX_BUTTONS];
    };
}

class render_log_in{
public:
    void main_menu();
    bool host_or_not();
    std::string return_port();
    bool is_host = false;
};

#endif //TEST_SFML_START_MENU_HPP