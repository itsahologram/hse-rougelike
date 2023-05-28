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
        button(float x, float y, const sf::Texture& normal,
               const sf::Texture& clicked, sf::RenderWindow *wind,
               sf::String str, sf::Font& font);
        bool checkClick(sf::Vector2f mouse_pos = sf::Vector2f(-1, -1));
        sf::Sprite* get_sprite();

        void draw(){
            window->draw(*current_sprite);
            window->draw(m_text);
        }

        void set_text(sf::String str){
            m_text.setString(str);
        }

        void set_posision(float x, float y){
            current_sprite->setPosition(x, y);
            m_text.setPosition(x, y);
        }

    private:
        sf::Sprite normal;
        sf::Sprite clicked;
        sf::Sprite* current_sprite;
        bool current = false;

        sf::RenderWindow *window;
        sf::Text m_text;

        void set_state(bool state);
    };

    class dialog {
    public:
        dialog(float x, float y, sf::Texture& dialog_window, sf::RenderWindow *wind,
               const sf::Texture& normal,
               const sf::Texture& clicked, sf::Font& font);

        void draw(){
            if (is_draw){
                window->draw(dial);
                f_button->draw();
                s_button->draw();
                th_button->draw();
            }
        }
        void check_click(sf::Vector2f& mousePos){
            if (f_button->checkClick(mousePos) && f <= 2){
                f_button->set_text(but_1[f++]);
            };
            if (s_button->checkClick(mousePos) && s <= 2){
                s_button->set_text(but_2[s++]);
            };
            if (th_button->checkClick(mousePos) && th <= 2){
                th_button->set_text(but_3[th++]);
            };
        }
        void reset_b(){
            f_button->set_state(false);
            s_button->set_state(false);
            th_button->set_state(false);
        }

        void set_posision(float x, float y){
            dial.setPosition(x, y);
            f_button->set_posision(x+10, y+15);
            s_button->set_posision(x+10, y+57);
            th_button->set_posision(x+10, y+99);

        }
    private:
        button* f_button;
        button* s_button;
        button* th_button;

        int f = 0;
        int s = 0;
        int th = 0;

        sf::RenderWindow *window;

        bool is_draw = true;
        sf::Sprite dial;
        std::vector<sf::String> main_text = {L"text1", L"text2", L"text3"};
        std::vector<sf::String> but_1 = {L"but11", L"but12", L"but13"};
        std::vector<sf::String> but_2 = {L"but21", L"but22", L"but23"};;
        std::vector<sf::String> but_3 = {L"but31", L"but32", L"but33"};;



    };
}


#endif //TEST_SFML_BUTTON_HPP
