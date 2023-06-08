#ifndef TEST_SFML_ENGINE_HPP
#define TEST_SFML_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "asset_manager.hpp"
#include "characters.hpp"
#include "button.hpp"
#include "view.hpp"

namespace game {
    class engine {

        asset_manager assets{};

        sf::RenderWindow m_window{sf::VideoMode(1280, 720), "Game"};
        sf::Color m_window_color{55, 55, 79, 1};
        sf::View view;
        sf::Clock clock;
        sf::Clock coffee_clock;

        dialog m_dialog;
        sf::Text m_header_quest;
        sf::Text m_details_quest;


        players player_1;
        npc first_nps;

        void input(sf::Event &event);
        void update(float delta_time, float coffee_time, sf::Event &event);
        void draw(sf::Sprite &s_map, sf::Sprite &s_coffee, sf::Sprite &s_quest_obj);

    public:

        engine();
        void run();

    };

    void draw_inf_about_quest(game::players &player, sf::Text &headet_text);

}

#endif //TEST_SFML_ENGINE_HPP
