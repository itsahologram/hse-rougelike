#include "characters.hpp"

namespace game {

    void players::animation(game::directions dir, int time, double &current_frame) {
        m_direction = dir;
        current_frame += 0.005 * time;
        if (current_frame > 8) {
            current_frame = 0;
        }
        if (dir == game::LEFT) {
            m_sprite.setTextureRect(
                    sf::IntRect(32, 48 * int(current_frame), -32, 48));
        } else if (dir == game::RIGHT) {
            m_sprite.setTextureRect(
                    sf::IntRect(0, 48 * int(current_frame), 32, 48));
        }
    }
}