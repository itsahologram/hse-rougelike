#ifndef TEST_SFML_CHARACTERS_HPP
#define TEST_SFML_CHARACTERS_HPP

#include "map_generator.hpp"
#include "quest.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <asset_manager.hpp>
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

        characters(sf::Texture &texture, float x, float y,
                   int width, int high) : m_x(x), m_y(y),
                                          m_width(width), m_high(high) {

            m_sprite.setTexture(texture);
            m_sprite.setTextureRect(sf::IntRect(0, 0, width, high));
        };

    };

    class players : public characters {

        float m_acceleration_x = 0, m_acceleration_y = 0;

        double m_speed = 240;
        float m_last_coffee_time = -5;




    public:
        int m_num_complete_quests = 0;
        quest *m_current_quest = new quest();


        quest &get_quest() const {
            return *m_current_quest;
        }



        void update(float time, float coffee_timer, asset_manager &assets, sf::Text &header_quest,
                    sf::Text &details_quest);

        void interaction_with_map(float coffee_timer);

        players(sf::Texture &texture, float x, float y,
                int width, int high) : characters(texture, x, y, width, high) {};

        void draw_direction();
    };

    class npc : public characters {
    public:
        npc(sf::Texture &texture, float x, float y,
            int width, int high) : characters(texture, x, y, width, high) {};

        void set_coordinates(int new_x, int new_y);
    };
}

#endif // TEST_SFML_CHARACTERS_HPP
