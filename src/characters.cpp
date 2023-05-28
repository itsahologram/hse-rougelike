#include "characters.hpp"

namespace game {
    void players::update(float time, float coffee_timer, sf::Text &text) {
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
        if (coffee_timer - m_last_coffee_time >= 15) {
            m_speed = std::max(m_speed / 2, 200.0);
        }
        m_x += m_acceleration_x * time;
        m_y += m_acceleration_y * time;

        interaction_with_map(coffee_timer, text);
        text.setString(m_current_quest->m_name_of_quest);
        m_sprite.setPosition((float) m_x, (float) m_y);
    }

    void players::interaction_with_map(float coffee_timer, sf::Text &text) {
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
                    m_speed = std::min(m_speed * 2, 500.0);
                    get_map()[i][j] = '0';
                    m_last_coffee_time = coffee_timer;
                } else if (get_map()[i][j] == 'n') {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
                            (m_current_quest->m_status == NONE || m_current_quest->m_status == COMPLETE)) {
                        m_current_quest = new quest_find_some_obj(L"Новый квест", 1);
                        m_current_quest->update_status(true, false);
                        add_quest_obj(1);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && m_current_quest->m_status == IN_PROGRESS) {
                        m_current_quest->update_status(false, true);
                        m_current_quest->m_name_of_quest = L"Квест сдан";

                    }
                } else if (get_map()[i][j] == 'o') {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && m_current_quest->m_status == START) {
                        if (auto *q = dynamic_cast<quest_find_some_obj *>(m_current_quest)) {
                            q->m_current_count_of_obj++;
                        }
                        m_current_quest->update_status(false, false);
                        get_map()[i][j] = '0';
                    }
                }
            }
        }
    }

    void characters::set_direction(directions dir) {
        m_direction = dir;
    }
} // namespace game