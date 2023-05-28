#ifndef TEST_SFML_VIEW_HPP
#define TEST_SFML_VIEW_HPP

#include <SFML/Graphics.hpp>

namespace game {
    void camera_follow_the_player(sf::View &view, float x, float y);

    void zoom_view(sf::View &view);


}

#endif //TEST_SFML_VIEW_HPP
