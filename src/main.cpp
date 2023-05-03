#include "characters.hpp"
#include "map_generator.hpp"
#include "view.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

double current_frame = 0;

void keyboard_controller(game::players &player, int time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.animation(game::LEFT, time, current_frame);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.animation(game::RIGHT, time, current_frame);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.animation(game::UP, time, current_frame);

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.animation(game::DOWN, time, current_frame);
    } else {
        player.animation(game::STOP, time, current_frame);
    }
}

void draw_map(sf::RenderWindow &window, sf::Sprite &s_map, sf::Sprite &s_coffee){
    for (int i = 0; i < map_height; i++)
        for (int j = 0; j < map_weight; j++) {
            if (get_map()[i][j] == '0') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
            }
            if (get_map()[i][j] == '1') {
                s_map.setTextureRect(sf::IntRect(
                        384, 0, 32, 32));
            }
            if (get_map()[i][j] == 'c') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_coffee.setTextureRect(sf::IntRect(0, 0, 16, 16));
                s_coffee.setPosition((float) (j * 32), (float) (i * 32));

            }
            s_map.setPosition(
                    (float) (j * 32), (float) (i * 32));
            window.draw(s_map);
            window.draw(s_coffee);
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

    game::players player("hero.png", 64, 64, 32, 48);

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

        int time = (int) clock.getElapsedTime().asMicroseconds();
        coffee_time = (int) bonus_clock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 800;

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        keyboard_controller(player, time);
        game::camera_follow_the_player(player.get_x(), player.get_y());
        player.update(time, coffee_time);

        game::zoom_view();
        window.setView(game::view);
        game::view.reset(sf::FloatRect(0, 0, 640, 480));
        window.clear();

        draw_map(window, s_map, s_coffee);

        window.draw(player.m_sprite);
        window.display();
        Sleep(time / 80);
    }

    return 0;
}
