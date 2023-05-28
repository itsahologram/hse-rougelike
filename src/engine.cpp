#include "engine.hpp"

namespace game {

    void draw_inf_about_quest(game::players &player, sf::Text &text){
        text.setPosition(player.m_x - 210, player.m_y - 240);
    }


    engine::engine() : m_dialog(-100, 140, assets.get_texture("dialog_main.png"), &m_window,
                                assets.get_texture("buttom_1.png"), assets.get_texture("buttom2.png"),
                                assets.get_font("YanoneKaffeesatz-VariableFont_wght.ttf")),
                       m_header_quest("", assets.get_font("YanoneKaffeesatz-VariableFont_wght.ttf"), 30),
                       m_details_quest("", assets.get_font("YanoneKaffeesatz-VariableFont_wght.ttf"), 25),
                       player_1(players(assets.get_texture("hero.png"), 64, 64, 32, 48)),
                       first_nps(assets.get_texture("npc2.png"), 1, 1, 32, 32) {
        init_map();
        create_map();
        m_header_quest.setFillColor(sf::Color::Red);
        m_details_quest.setFillColor(sf::Color::Red);
        m_header_quest.setStyle(sf::Text::Bold);
        m_details_quest.setStyle(sf::Text::Bold);
    };


    void engine::input() {
        sf::Event event{};

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player_1.set_direction(LEFT);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player_1.set_direction(RIGHT);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player_1.set_direction(UP);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player_1.set_direction(DOWN);
        } else {
            player_1.set_direction(STOP);
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
                sf::Vector2f pos = m_window.mapPixelToCoords(pixelPos);
                m_dialog.check_click(pos);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                m_dialog.reset_b();
            }
        }
        zoom_view(view);
    }

    void engine::update(float delta_time, float coffee_time) {
        player_1.update(delta_time, coffee_time, m_header_quest);

        camera_follow_the_player(view, player_1.get_x(), player_1.get_y());
        m_window.setView(view);

        m_dialog.set_posision(player_1.get_x() - 150, player_1.get_y() + 70);
    }

    void engine::draw(sf::Sprite &s_map, sf::Sprite &s_coffee, sf::Sprite &s_quest_obj){
        m_window.clear(m_window_color);
        draw_map(m_window, s_map, s_coffee, first_nps.m_sprite, s_quest_obj);
        m_window.draw(player_1.m_sprite);
        draw_inf_about_quest(player_1, m_header_quest);
        m_window.draw(m_header_quest);

        m_dialog.draw();
        m_window.display();
        view.reset(sf::FloatRect(0, 0, 640, 480));

    }

    void engine::run() {
        sf::Sprite s_map;
        s_map.setTexture(assets.get_texture("new_map.png"));

        sf::Sprite s_coffee;
        s_coffee.setTexture(assets.get_texture("coffee.png"));

        sf::Sprite s_book;
        s_book.setTexture(assets.get_texture("books.png"));

        while (m_window.isOpen()){
            float time = clock.getElapsedTime().asSeconds();
            float coffee_time = coffee_clock.getElapsedTime().asSeconds();
            time = clock.restart().asSeconds();

            input();
            update(time, coffee_time);
            draw(s_map, s_coffee, s_book);
        }
    }
}