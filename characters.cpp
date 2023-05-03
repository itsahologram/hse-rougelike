#include "characters.hpp"

namespace game {
void characters::update(float time, int &coffee_time) {
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
        case STOP:
            m_dx = 0;
            m_dy = 0;
    }
    if (coffee_time - m_last_coffee >= 5){
        m_speed = std::max(m_speed / 1.1, 0.15);
    }
    m_x += m_dx * time;
  m_y += m_dy * time;

  iteraction_with_map(coffee_time);
  m_sprite.setPosition(m_x, m_y);
}

void characters::iteraction_with_map(int &coffee_time) {
  for (int i = m_y / 32; i < (m_y + m_high) / 32; i++) {
    for (int j = m_x / 32; j < (m_x + m_width) / 32; j++) {
      if (get_map()[i][j] == '1') {
        if (m_dy > 0) {
          m_y = i * 32 - m_high;
        }
        if (m_dy < 0) {
          m_y = i * 32 + 32;
        }
        if (m_dx > 0) {
          m_x = j * 32 - m_width;
        }
        if (m_dx < 0) {
          m_x = j * 32 + 32;
        }
      } else if (get_map()[i][j] == 'c'){
          m_speed *= 1.5;
          get_map()[i][j] = '0';
          m_last_coffee = coffee_time;
      }
    }
  }
}
} // namespace game