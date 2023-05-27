#include "Button.hpp"
#include "characters.hpp"
#include "map_generator.hpp"
#include "view.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

double current_frame = 0;

void keyboard_controller(game::players &player, float time) {
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

void draw_map(sf::RenderWindow &window, sf::Sprite &s_map, sf::Sprite &s_coffee, sf::Sprite &s_npc,
              sf::Sprite &s_quest_obj){
    for (int i = 0; i < map_height; i++)
        for (int j = 0; j < map_weight; j++) {
            if (get_map()[i][j] == '0') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);
            }
            else if (get_map()[i][j] == '1') {
                s_map.setTextureRect(sf::IntRect(
                        384, 0, 32, 32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);

            }
            else if (get_map()[i][j] == 'c') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                s_coffee.setTextureRect(sf::IntRect(0, 0, 16, 16));
                s_coffee.setPosition((float) (j * 32), (float) (i * 32));
                window.draw(s_map);
                window.draw(s_coffee);

            } else if (get_map()[i][j] == 'o'){
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_quest_obj.setTextureRect(sf::IntRect(1, 1, 32, 32));
                s_quest_obj.setPosition((float) (j * 32), (float) (i * 32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);
                window.draw(s_quest_obj);

            } else if (get_map()[i][j] == 'n'){
                s_npc.setPosition((float) (j * 32), (float) (i * 32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);
                window.draw(s_npc);
            }

        }
}

void draw_inf_about_quest(game::players &player, sf::Text &text){
    text.setPosition(player.m_x - 210, player.m_y - 240);
}


int main() {
    init_map();
    create_map();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");
    game::view.reset(sf::FloatRect(0, 0, 640, 480));

    window.setFramerateLimit(120);

    sf::Clock clock;
    sf::Clock bonus_clock;


    int coffee_time = 0;

    game::players player("hero.png", 64, 64, 32, 48);
    game::npc first_npc("npc2.png", 1, 1, 32, 32);
    first_npc.set_coordinates(set_x_f - 2, 2);


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

    sf::Image book_img;
    book_img.loadFromFile("../images/books.png");
    sf::Texture book;
    book.loadFromImage(book_img);
    sf::Sprite s_book;
    s_book.setTexture(book);

    sf::Font font;
    font.loadFromFile("../fonts/YanoneKaffeesatz-VariableFont_wght.ttf");
    sf::Text text("", font, 30);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setString( L"Квеста нет");


    sf::Image main_d_img;
    main_d_img.loadFromFile("../images/dialog_main.png");
    sf::Texture main_d_text;
    main_d_text.loadFromImage(main_d_img);
//    sf::Sprite main_d_s; // Уберу это после
//    main_d_s.setTexture(main_d_text);


    sf::Image buttom1;
    buttom1.loadFromFile("../images/buttom_1.png");
    sf::Texture buttom1_t;
    buttom1_t.loadFromImage(buttom1);
    sf::Image buttom2;
    buttom2.loadFromFile("../images/buttom2.png");
    sf::Texture buttom2_t;
    buttom2_t.loadFromImage(buttom2);

    game::dialog d(-100, 140, main_d_text, &window, buttom1_t, buttom2_t, font);

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        coffee_time = (int) bonus_clock.getElapsedTime().asSeconds();
        float buttom_time = clock.getElapsedTime().asSeconds();
        //window.setVerticalSyncEnabled(true);
        //window.setFramerateLimit(120);

        clock.restart();
        time = time / 800;

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        keyboard_controller(player, time);
        player.update(time, coffee_time, text);

        game::camera_follow_the_player(player.get_x(), player.get_y());
        game::zoom_view();
        window.setView(game::view);
        game::view.reset(sf::FloatRect(0, 0, 640, 480));


        window.clear();

        draw_map(window, s_map, s_coffee, first_npc.m_sprite, s_book);
        window.draw(player.m_sprite);

        draw_inf_about_quest(player, text);
        window.draw(text);


        d.set_posision(player.get_x() - 150, player.get_y() + 70);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
                d.check_click(pos, buttom_time);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                d.reset_b();
            }
        }

        d.draw();
        window.display();
        //Sleep(time / 80);
    }

    return 0;
}
