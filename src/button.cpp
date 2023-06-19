#include "button.hpp"

game::button::button(float x, float y, const sf::Texture &normal, const sf::Texture &clicked,
                     sf::RenderWindow *wind, sf::String str, sf::Font &font) {
    this->normal.setTexture(normal);
    this->clicked.setTexture(clicked);

    this->normal.setPosition(x, y);
    this->clicked.setPosition(x, y);
    current_sprite = &this->normal;
    window = wind;


    m_text = sf::Text("", font, 15);
    m_text.setFillColor(sf::Color::Black);
    m_text.setStyle(sf::Text::Bold);
    m_text.setString(str);
    m_text.setPosition(x + 10, y - 100);
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
    m_main_text.setPosition(x + 15, y + 15);


    first_button = new button(x + 10, y + 15, normal, clicked, wind, L"", font);
    second_button = new button(x + 10, y + 57, normal, clicked, wind, L"", font);
    third_button = new button(x + 10, y + 99, normal, clicked, wind, L"", font);

}

void game::dialog::draw() {
    if (get_is_draw()) {
        window->draw(m_sprite);
        window->draw(m_main_text);

        third_button->draw();
        if (m_mode == DIALOG) return;

        second_button->draw();
        if (m_mode == CONFIRM_WINDOW) return;

        first_button->draw();
    }

}

int game::dialog::check_click(sf::Vector2f &mousePos) {
    if (third_button->checkClick(mousePos)) {
        return 3;
    };
    if (m_mode == DIALOG){
        return 0;
    }
    if (second_button->checkClick(mousePos)) {
        return 2;
    };

    if (m_mode == CONFIRM_WINDOW){
        return 0;
    }
    if (first_button->checkClick(mousePos)) {
        return 1;
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


void game::dialog::set_not_draw() {
    m_mode = NOT_DRAW;
    reset_button();
}

bool game::dialog::get_is_draw() {
    return (m_mode != NOT_DRAW);
}

void game::dialog::set_mode(game::dialog_mode mode) {
    m_mode = mode;
}

game::dialog_mode game::dialog::get_mode() {
    return m_mode;
}

