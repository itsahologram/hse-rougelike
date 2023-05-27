#include "Button.hpp"

game::button::button(float x, float y, const sf::Texture &normal, const sf::Texture &clicked,
                     sf::RenderWindow *wind, sf::String str, sf::Font& font) {
    this->normal.setTexture(normal);
    this->clicked.setTexture(clicked);

    this->normal.setPosition(x, y);
    this->clicked.setPosition(x, y);
    current_sprite = &this->normal;
    window = wind;


    m_text = sf::Text("", font, 25);
    m_text.setFillColor(sf::Color::Black);
    m_text.setStyle(sf::Text::Bold);
    m_text.setString(str);
    m_text.setPosition(x+5, y-5);
}

bool game::button::checkClick(sf::Vector2f mousePos) {
        if ((static_cast<float>(mousePos.x) > current_sprite->getPosition().x &&
             static_cast<float>(mousePos.x) < (current_sprite->getPosition().x +
                                               current_sprite->getGlobalBounds().width))
            && (static_cast<float>(mousePos.y) > current_sprite->getPosition().y &&
                static_cast<float>(mousePos.y) < (current_sprite->getPosition().y +
                                                  current_sprite->getGlobalBounds().height))) {
            set_state(!current);
            return true;
        }
    return false;
}

void game::button::set_state(bool which) {
    current = which;
    if (current) {
        current_sprite = &clicked;
        return;
    }
    current_sprite = &normal;
}

sf::Sprite *game::button::get_sprite() {
    return current_sprite;
}

game::dialog::dialog(float x, float y, sf::Texture &dialog_window, sf::RenderWindow *wind,
                     const sf::Texture& normal,
                     const sf::Texture& clicked,
                     sf::Font& font) {
    window = wind;
    dial.setTexture(dialog_window);
    dial.setPosition(x, y);
    f_button = new button(x+10, y+15, normal, clicked, wind, L"кнопка1", font);
    s_button = new button(x+10, y+57, normal, clicked, wind, L"кнопка2", font);
    th_button = new button(x+10, y+99, normal, clicked, wind, L"кнопка3", font);

}