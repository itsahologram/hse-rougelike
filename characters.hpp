#ifndef TEST_SFML_CHARACTERS_HPP
#define TEST_SFML_CHARACTERS_HPP

#include "map_generator.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

namespace game {

enum directions { UP, DOWN, LEFT, RIGHT };

struct characters {
public:
  float m_x = 0, m_y = 0, m_width = 0, m_high = 0, m_dx = 0, m_dy = 0,
        m_speed = 0;
  directions m_direction = RIGHT;
  std::string m_file_name;
  sf::Image m_image;
  sf::Texture m_texture;
  sf::Sprite m_sprite;

  characters(std::string file_name, float x, float y, float w, float h)
      : m_file_name(std::move(file_name)), m_x(x), m_y(y), m_width(w),
        m_high(h) {
    m_image.loadFromFile("../images/" + m_file_name);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, w, h));
  }

  void update(float time);
  void iteraction_with_map();
}; // characters
} // namespace game

#endif // TEST_SFML_CHARACTERS_HPP
