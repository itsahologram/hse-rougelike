#ifndef TEST_SFML_BUTTON_HPP
#define TEST_SFML_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace game {
    class dialog;

    class button {
        friend dialog;
    public:
        button(float x, float y, const sf::Texture &normal,
               const sf::Texture &clicked, sf::RenderWindow *wind,
               sf::String str, sf::Font &font);

        bool checkClick(sf::Vector2f mouse_pos = sf::Vector2f(-1, -1));

        sf::Sprite *get_sprite();

        void draw() {
            window->draw(*current_sprite);
            window->draw(m_text);
        }

        void set_text(sf::String str) {
            m_text.setString(sf::String::fromUtf8(str.begin(), str.end()));
        }

        void set_posision(float x, float y) {
            current_sprite->setPosition(x, y);
            m_text.setPosition(x+5, y+5);
        }

    private:
        sf::Sprite normal;
        sf::Sprite clicked;
        sf::Sprite *current_sprite;
        bool current = false;

        sf::RenderWindow *window;
        sf::Text m_text;

        void set_state(bool state);
    };

    enum dialog_mode {DIALOG, CONFIRM_WINDOW, QUIZ, NOT_DRAW};

    class dialog {
    public:
        dialog(float x, float y, sf::Texture &dialog_window, sf::RenderWindow *wind,
               const sf::Texture &normal,
               const sf::Texture &clicked, sf::Font &font);

        void draw();

        int check_click(sf::Vector2f &mousePos);

        void reset_button();

        void set_posision(float x, float y);

        void set_text(const std::string &main_text, const std::string &fist_text = "",
                      const std::string &second_text = "", const std::string &third_text = "Продолжить");

        void set_mode(dialog_mode mode);

        void set_not_draw();

        bool get_is_draw();

        dialog_mode get_mode();

    private:
        button *first_button;
        button *second_button;
        button *third_button;

        sf::Text m_main_text;

        sf::RenderWindow *window;

        sf::Sprite m_sprite;

        dialog_mode m_mode = NOT_DRAW;

    };
}


#endif //TEST_SFML_BUTTON_HPP
