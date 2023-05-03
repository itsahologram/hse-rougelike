#ifndef TEST_SFML_VIEW_HPP
#define TEST_SFML_VIEW_HPP

#include <SFML/Graphics.hpp>

namespace game {
    sf::View view;
    void camera_follow_the_player(float x, float y){
        view.setCenter(x + 100, y);
    }

    void zoom_view(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            view.setCenter(1600, 940);
            view.setSize(3200, 1920);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            view.zoom(1.0100f);
            game::view.reset(sf::FloatRect(0, 0, 640, 480));
        }

    }
}

#endif //TEST_SFML_VIEW_HPP
