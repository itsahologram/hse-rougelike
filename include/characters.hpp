#ifndef TEST_SFML_CHARACTERS_HPP
#define TEST_SFML_CHARACTERS_HPP

#include "map_generator.hpp"
#include "quest.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>


namespace game {

    enum directions {
        UP, DOWN, LEFT, RIGHT, STOP
    };


    struct characters {
        float m_x = 0, m_y = 0;
        directions m_direction = RIGHT;

        int m_width = 0, m_high = 0;

        sf::Sprite m_sprite;

        float get_x() const { return m_x; }

        float get_y() const { return m_y; }

        directions get_direction() const { return m_direction; };

        void set_direction(game::directions new_dir);

        characters(sf::Texture& texture, float x, float y,
                   int width, int high) : m_x(x), m_y(y),
                                          m_width(width), m_high(high) {

            m_sprite.setTexture(texture);
            m_sprite.setTextureRect(sf::IntRect(0, 0, width, high));
        };

        virtual void animation(game::directions dir, int time, double &current_frame) {};

    };

    class players : public characters {

        float m_acceleration_x = 0, m_acceleration_y = 0;

        double m_speed = 200;
        float m_last_coffee_time = -5;

        bool is_quest = false;
        bool is_obj = false;
        bool is_complete = false;

        abstract_quest* m_current_quest = new quest_find_some_obj();



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


        void update(float time, float coffee_timer, sf::Text &text);

        void interaction_with_map(float coffee_timer, sf::Text &text);

        players(sf::Texture& texture, float x, float y,
                int width, int high) : characters(texture, x, y, width, high) {
            m_current_quest = new quest_find_some_obj();
        };

        void animation(game::directions dir, float time, double &current_frame);
    };

    class npc: public characters {
    public:
        npc(sf::Texture& texture, float x, float y,
            int width, int high): characters(texture, x, y, width, high) {};

        void set_coordinates(int new_x, int new_y);
    };
}

#endif // TEST_SFML_CHARACTERS_HPP
