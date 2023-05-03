#include "characters.hpp"
#include "map_generator.hpp"
#include "view.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

float current_frame = 0;

void run_animation(game::characters &player, game::directions dir, float time) {
  player.m_direction = dir;
  current_frame += 0.005 * time;
  if (current_frame > 8) {
    current_frame = 0;
  }
  if (dir == game::LEFT) {
    player.m_sprite.setTextureRect(
        sf::IntRect(32, 48 * int(current_frame), -32, 48));
  } else if (dir == game::RIGHT) {
    player.m_sprite.setTextureRect(
        sf::IntRect(0, 48 * int(current_frame), 32, 48));
  }
}

int main() {
  init_map();
  create_map();

  sf::RenderWindow window(sf::VideoMode(1920, 1440), "Game");
  game::view.reset(sf::FloatRect(0, 0, 640, 480));

  window.setFramerateLimit(120);

  sf::Clock clock;
  sf::Clock bonus_clock;

  int coffee_time = 0;

  game::characters player("hero.png", 64, 64, 32, 48);

  sf::Image map_img;
  map_img.loadFromFile("../images/new_map.png");
  sf::Texture map;
  map.loadFromImage(map_img);
  sf::Sprite s_map;
  s_map.setTexture(map);

  sf::Image coffee_img;
  coffee_img.loadFromFile("../images/coffee.png");
  sf::Texture coffee;
  coffee.loadFromImage(coffee_img);
  sf::Sprite s_coffee;
  s_coffee.setTexture(coffee);

  while (window.isOpen()) {
    float time = clock.getElapsedTime().asMicroseconds();
    coffee_time = bonus_clock.getElapsedTime().asSeconds();
    clock.restart();
    time = time / 800;

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      run_animation(player, game::LEFT, time);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      run_animation(player, game::RIGHT, time);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      run_animation(player, game::UP, time);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      run_animation(player, game::DOWN, time);
    } else {
        run_animation(player, game::STOP, time);
    }
    game::camera_follow_the_player(player.get_x(), player.get_y());
    player.update(time, coffee_time);

    game::zoom_view();
    window.setView(game::view);
    game::view.reset(sf::FloatRect(0, 0, 640, 480));
      window.clear();
    for (int i = 0; i < map_height; i++)
      for (int j = 0; j < map_weight; j++) {
        if (get_map()[i][j] == '0') {
            s_map.setTextureRect(sf::IntRect(
                    461, 320, 32,
                    32)); //если встретили символ пробел, то рисуем 1й квадратик
        }
        if (get_map()[i][j] == '1') {
            s_map.setTextureRect(sf::IntRect(
                    384, 0, 32, 32)); //если встретили символ 0, то рисуем 3й квадратик
        }
        if (get_map()[i][j] == 'c'){
            s_map.setTextureRect(sf::IntRect(
                    461, 320, 32,
                    32));
            s_coffee.setTextureRect(sf::IntRect(0, 0, 16, 16));
            s_coffee.setPosition(j*32, i * 32);

        }
        s_map.setPosition(
            j * 32, i * 32); //по сути раскидывает квадратики, превращая в
                             //карту. то есть задает каждому из них позицию.
                             //если убрать, то вся карта нарисуется в одном
                             //квадрате 32*32 и мы увидим один квадрат
        window.draw(s_map);
        window.draw(s_coffee);
      }
    window.draw(player.m_sprite);
    window.display();
    Sleep(time / 80);
  }

  return 0;
}
