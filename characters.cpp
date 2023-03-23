#include "characters.hpp"

namespace game{
    void characters::update(float time) {
        switch (m_direction) {
            case RIGHT:
                m_dx = m_speed;
                m_dy = 0;
                break;
            case LEFT:
                m_dx = -m_speed;
                m_dy = 0;
                break;
            case DOWN:
                m_dx = 0;
                m_dy = m_speed;
                break;
            case UP:
                m_dx = 0;
                m_dy = -m_speed;
                break;
        }

        m_x += m_dx*time;
        m_y += m_dy*time;

        m_speed = 0;
        iteraction_with_map();
        m_sprite.setPosition(m_x, m_y);

    }
}