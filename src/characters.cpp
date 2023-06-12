#include "characters.hpp"

void update_text(sf::Text &header_quest, sf::Text &details_quest, game::quest &current_quest, int complete_quest,
                 int all_quest) {
    if (complete_quest == all_quest) {
        header_quest.setString(L"Ты выполнил все квесты!");
        details_quest.setString("");
        return;
    }
    if (current_quest.m_status == game::NONE) {
        header_quest.setString(L"Нет активного квеста");
        details_quest.setString("");
    }
    if (current_quest.m_status == game::IN_PROGRESS) {
        header_quest.setString(
                sf::String::fromUtf8(current_quest.m_header_text.begin(), current_quest.m_header_text.end()));
        details_quest.setString(
                sf::String::fromUtf8(current_quest.m_details_quest.begin(), current_quest.m_details_quest.end()) +
                current_quest.m_quest_progress);
    }
    if (current_quest.m_status == game::COMPLETE_BUT_NOT_TELL) {
        details_quest.setString(L"Вернись и расскажи о своём успехе");

    }
    if (current_quest.m_status == game::COMPLETE) {
        header_quest.setString(L"Ты выполнил квест!");
        details_quest.setString("");

    }
}


namespace game {
    void players::update(float time, float coffee_timer, asset_manager &assets,
                         sf::Text &header_quest, sf::Text &details_quest, sf::Event &event,
                         dialog &dial) {
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

        interaction_with_map(coffee_timer, assets, event, dial);
        update_text(header_quest, details_quest, *m_current_quest, m_num_complete_quests, assets.get_num_quests());
        m_sprite.setPosition((float) m_x, (float) m_y);
    }

    void players::interaction_with_map(float coffee_timer, asset_manager &assets, sf::Event &event,
                                       dialog &dial) {
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
                }
            }
        }
    }

    void characters::set_direction(directions dir) {
        m_direction = dir;
    }
} // namespace game
