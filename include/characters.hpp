#ifndef TEST_SFML_CHARACTERS_HPP
#define TEST_SFML_CHARACTERS_HPP

#include "map_generator.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

namespace game {

    enum directions {
        UP, DOWN, LEFT, RIGHT, STOP
    };

    enum quest_status {
        START, IN_PROGRESS, COMPLETE, NONE
    };

    struct abstract_quest {
        game::quest_status m_status = NONE;

        virtual void update_status(bool is_start, bool is_passed) = 0;
    };

    struct quest_find_some_obj: public abstract_quest {
        sf::Text m_name_of_quest{};

        int m_count_of_obj = 0;
        int m_current_count_of_obj = 0;
        // char type_of_obj;

        quest_find_some_obj(sf::Text name_of_quest, int count_of_obj): m_name_of_quest(name_of_quest),
                                                                       m_count_of_obj(count_of_obj){};
        void update_status(bool is_start, bool is_passed) override {
            if (is_start){
                m_status = START;
            } else if (is_passed){
                m_status = COMPLETE;
            } else if (m_current_count_of_obj == m_count_of_obj) {
                m_status = IN_PROGRESS;
            }
        }


    };

    struct characters {
        float m_x = 0, m_y = 0;
        directions m_direction = RIGHT;

        int m_width = 0, m_high = 0;
        std::string m_file_name;
        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        double get_x() const { return m_x; }

        double get_y() const { return m_y; }

        directions get_direction() const { return m_direction; };

        characters(std::string file_name, float x, float y,
                   int width, int high) : m_file_name(std::move(file_name)), m_x(x), m_y(y),
                                          m_width(width), m_high(high) {
            m_image.loadFromFile("../images/" + m_file_name);
            m_texture.loadFromImage(m_image);
            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(sf::IntRect(0, 0, width, high));
        };

        virtual void animation(game::directions dir, int time, double &current_frame) {};
    };

    class players : public characters {

        float m_acceleration_x = 0, m_acceleration_y = 0;

        double m_speed = 0.15;
        int m_last_coffee_time = -5;

        bool is_quest = false;
        bool is_obj = false;
        bool is_complete = false;



    public:
        bool get_inf_about_current_quest() const{
            return is_quest;
        }
        bool get_about_complete() const {
            return is_complete;
        }
        bool get_about_obj() const {
            return is_obj;
        }

        void update(float time, int coffee_timer, sf::Text &text);

        void interaction_with_map(int coffee_timer, sf::Text &text);

        players(std::string file_name, float x, float y,
                int width, int high) : characters(std::move(file_name), x, y, width, high) {};

        void animation(game::directions dir, float time, double &current_frame);
    };

    class npc: public characters {
    public:
        npc(std::string file_name, float x, float y,
            int width, int high): characters(std::move(file_name), x, y, width, high) {};

        void set_coordinates(int new_x, int new_y);
    };
}

#endif // TEST_SFML_CHARACTERS_HPP
