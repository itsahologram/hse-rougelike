#include "engine.hpp"

namespace game {

    void draw_inf_about_quest(game::players &player, sf::Text &headet_text, sf::Text &details_quest) {
        headet_text.setPosition(player.m_x - 210, player.m_y - 240);
        details_quest.setPosition(player.m_x - 210, player.m_y - 200);
    }


    engine::engine() : m_dialog(-100, 140, assets.get_texture("dialog_main.png"), &m_window,
                                assets.get_texture("buttom_1.png"), assets.get_texture("buttom2.png"),
                                assets.get_font("YanoneKaffeesatz-VariableFont_wght.ttf")),
                       m_header_quest("", assets.get_font("YanoneKaffeesatz-VariableFont_wght.ttf"), 30),
                       m_details_quest("", assets.get_font("YanoneKaffeesatz-VariableFont_wght.ttf"), 25),
                       player_1(players(assets.get_texture("player.png"), 64, 64, 50, 40)),
                       first_nps(assets.get_texture("npc2.png"), 1, 1, 32, 32) {
        init_map();
        create_map();
        m_header_quest.setFillColor(sf::Color::Red);
        m_details_quest.setFillColor(sf::Color::Red);
        m_header_quest.setStyle(sf::Text::Bold);
        m_details_quest.setStyle(sf::Text::Bold);


        assets.parse_quests_from_json("quests.json");
    };


    void engine::input(sf::Event &event) {

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }

            if (m_dialog.get_mode() == QUIZ || m_dialog.get_mode() == DIALOG) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
                        sf::Vector2f pos = m_window.mapPixelToCoords(pixelPos);
                        if (player_1.get_quest().middle_update(pos)) {
                            player_1.m_num_complete_quests += 1;
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        m_dialog.reset_button();
                    }
                }
            }

            if (m_dialog.get_mode() == CONFIRM_WINDOW){
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i pixel_pos = sf::Mouse::getPosition(m_window);
                        sf::Vector2f pos = m_window.mapPixelToCoords(pixel_pos);
                        player_1.get_quest().confirm_quest(pos);
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        m_dialog.reset_button();
                    }
                }
            }


            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                for (int i = (int) (player_1.m_y / 32); i < (player_1.m_y + player_1.m_high) / 32; i++) {
                    for (int j = (int) (player_1.m_x / 32); j < ((player_1.m_x + player_1.m_width) / 32); j++) {
                        if (get_map()[i][j] == 'n') {
                            if ((player_1.get_quest().m_status == NONE || player_1.get_quest().m_status == COMPLETE) &&
                                player_1.m_num_complete_quests < assets.get_num_quests()) {
                                auto* quest = &assets.get_random_quest();
                                player_1.m_current_quest = quest;
                                player_1.get_quest().quest_start_window(m_dialog);
                            } else if (player_1.get_quest().m_status == COMPLETE_BUT_NOT_TELL) {
                                player_1.get_quest().finish_window();
                            }
                        } else if (get_map()[i][j] == 'o' && player_1.get_quest().m_status == IN_PROGRESS) {
                            player_1.get_quest().middle_update(sf::Vector2f(16.5f, 24.f));
                            get_map()[i][j] = '0';
                        }
                    }
                }
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


        zoom_view(view);
    }

    void engine::update(float delta_time, float coffee_time) {
        player_1.update(delta_time, coffee_time, assets,
                        m_header_quest, m_details_quest);

        camera_follow_the_player(view, player_1.get_x(), player_1.get_y());
        m_window.setView(view);

        m_dialog.set_posision(player_1.get_x() - 150, player_1.get_y() + 70);
    }

    void engine::draw(sf::Sprite &s_map, sf::Sprite &s_coffee, sf::Sprite &s_quest_obj) {
        m_window.clear(m_window_color);
        draw_map(m_window, s_map, s_coffee, first_nps.m_sprite, s_quest_obj);
        player_1.draw_direction();
        m_window.draw(player_1.m_sprite);
        draw_inf_about_quest(player_1, m_header_quest, m_details_quest);
        m_window.draw(m_header_quest);
        m_window.draw(m_details_quest);

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
        float time = clock.getElapsedTime().asSeconds();

        while (m_window.isOpen()) {
            sf::Event event{};
            float coffee_time = coffee_clock.getElapsedTime().asSeconds();
            time = clock.restart().asSeconds();


            input(event);
            update(time, coffee_time);
            draw(s_map, s_coffee, s_book);
        }
    }
}
