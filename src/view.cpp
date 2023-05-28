#include "view.hpp"

namespace game {
    void camera_follow_the_player(sf::View& view, float x, float y){
        view.setCenter(x + 100, y);
    }

    void zoom_view(sf::View& view){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            view.setCenter(0, 0);
            view.setSize(3200, 1920);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            view.zoom(1.0100f);
            view.reset(sf::FloatRect(0, 0, 640, 480));
        }

    }
}