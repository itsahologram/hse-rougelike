#include "characters.hpp"

namespace game {
    void players::update(float time, int coffee_timer, sf::Text &text) {
        switch (m_direction) {
            case RIGHT:
                m_acceleration_x = m_speed;
                m_acceleration_y = 0;
                break;
            case LEFT:
                m_acceleration_x = -m_speed;
                m_acceleration_y = 0;
                break;
            case DOWN:
                m_acceleration_x = 0;
                m_acceleration_y = m_speed;
                break;
            case UP:
                m_acceleration_x = 0;
                m_acceleration_y = -m_speed;
                break;
            case STOP:
                m_acceleration_x = 0;
                m_acceleration_y = 0;
        }
        if (coffee_timer - m_last_coffee_time >= 5) {
            m_speed = std::max(m_speed / 1.1, 0.15);
        }
        m_x += m_acceleration_x * time;
        m_y += m_acceleration_y * time;

        interaction_with_map(coffee_timer, text);
        m_sprite.setPosition((float) m_x, (float) m_y);
    }

    void players::interaction_with_map(int coffee_timer, sf::Text &text) {
        for (int i = (int) (m_y / 32); i < (m_y + m_high) / 32; i++) {
            for (int j = (int) (m_x / 32); j < ((m_x + m_width) / 32); j++) {
                if (get_map()[i][j] == '1') {
                    if (m_acceleration_y > 0) {
                        m_y = i * 32 - m_high;
                    }
                    if (m_acceleration_y < 0) {
                        m_y = i * 32 + 32;
                    }
                    if (m_acceleration_x > 0) {
                        m_x = j * 32 - m_width;
                    }
                    if (m_acceleration_x < 0) {
                        m_x = j * 32 + 32;
                    }
                } else if (get_map()[i][j] == 'c') {
                    m_speed *= 1.3;
                    get_map()[i][j] = '0';
                    m_last_coffee_time = coffee_timer;
                } else if (get_map()[i][j] == 'n'){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !is_quest){
                        is_quest = true;
                        text.setString( L"Новый квест");
                        add_quest_obj();

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && is_quest && is_obj){
                        is_complete = true;
                        is_obj = false;
                        is_quest = false;
                        text.setString( L"Квест сдан");
                    }
                } else if (get_map()[i][j] == 'o'){
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                        is_obj = true;
                        get_map()[i][j] = '0';
                        text.setString( L"Объект получен");

                    }
                }
            }
        }
    }
} // namespace game