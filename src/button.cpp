#include "button.hpp"

game::button::button(float x, float y, const sf::Texture &normal, const sf::Texture &clicked,
                     sf::RenderWindow *wind, sf::String str, sf::Font &font) {
    this->normal.setTexture(normal);
    this->clicked.setTexture(clicked);

    this->normal.setPosition(x, y);
    this->clicked.setPosition(x, y);
    current_sprite = &this->normal;
    window = wind;


    m_text = sf::Text("", font, 18);
    m_text.setFillColor(sf::Color::Black);
    m_text.setStyle(sf::Text::Bold);
    m_text.setString(str);
    m_text.setPosition(x + 5, y - 5);
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
                     const sf::Texture &normal,
                     const sf::Texture &clicked,
                     sf::Font &font) {
    window = wind;
    m_sprite.setTexture(dialog_window);
    m_sprite.setPosition(x, y);

    m_main_text = sf::Text("", font, 25);
    m_main_text.setFillColor(sf::Color::Black);
    m_main_text.setStyle(sf::Text::Bold);
    m_main_text.setString("");
    m_main_text.setPosition(x + 40, y + 15);


    first_button = new button(x + 10, y + 15, normal, clicked, wind, L"", font);
    second_button = new button(x + 10, y + 57, normal, clicked, wind, L"", font);
    third_button = new button(x + 10, y + 99, normal, clicked, wind, L"", font);

}

void game::dialog::draw() {
    if (is_draw_dialog) {
        window->draw(m_sprite);
        window->draw(m_main_text);

        first_button->draw();
        second_button->draw();
        third_button->draw();

    }

}

int game::dialog::check_click(sf::Vector2f &mousePos) {
    if (first_button->checkClick(mousePos)) {
        return 1;
    };
    if (second_button->checkClick(mousePos)) {
        return 2;
    };
    if (third_button->checkClick(mousePos)) {
        return 3;
    };
    return 0;
}

void game::dialog::reset_button() {
    first_button->set_state(false);
    second_button->set_state(false);
    third_button->set_state(false);
}

void game::dialog::set_posision(float x, float y) {
    m_sprite.setPosition(x, y);
    m_main_text.setPosition(x + 120, y + 20);
    first_button->set_posision(x + 10, y + 15);
    second_button->set_posision(x + 10, y + 57);
    third_button->set_posision(x + 10, y + 99);
}

void
game::dialog::set_text(const std::string &main_text, const std::string &fist_text, const std::string &second_text,
                       const std::string &third_text) {
    m_main_text.setString(sf::String::fromUtf8(main_text.begin(), main_text.end()));
    first_button->set_text(fist_text);
    second_button->set_text(second_text);
    third_button->set_text(third_text);
}

void game::dialog::set_is_draw() {
    is_draw_dialog = true;
}

void game::dialog::set_not_draw() {
    is_draw_dialog = false;
}

bool game::dialog::get_is_draw() {
    return is_draw_dialog;
}

