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

    struct characters {
        double m_x = 0, m_y = 0;
        directions m_direction = RIGHT;

        int m_width = 0, m_high = 0;
        std::string m_file_name;
        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        double get_x() const { return m_x; }
        double get_y() const { return m_y; }
        directions get_direction() const { return m_direction; };

        characters(std::string file_name, double x, double y,
                   int width, int high): m_file_name(std::move(file_name)), m_x(x), m_y(y),
                   m_width(width), m_high(high){
            m_image.loadFromFile("../images/" + m_file_name);
            m_texture.loadFromImage(m_image);
            m_sprite.setTexture(m_texture);
            m_sprite.setTextureRect(sf::IntRect(0, 0, width, high));
        };

        virtual void animation(game::directions dir, int time, double &current_frame){};
    };

    class players : public characters {

        double m_acceleration_x = 0, m_acceleration_y = 0;

        double m_speed = 0.15;
        int m_last_coffee_time = -5;

    public:
        void update(int time, int coffee_timer);
        void interaction_with_map(int coffee_timer);

        players(std::string file_name, float x, float y,
                int width, int high): characters(std::move(file_name), x, y, width, high){};

        void animation(game::directions dir, int time, double &current_frame) override;
    };
}

#endif // TEST_SFML_CHARACTERS_HPP
