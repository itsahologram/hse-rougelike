#include "asset_manager.hpp"

namespace game {
    sf::Texture &asset_manager::get_texture(const std::string &filename) {
        auto pair_found = m_textures.find(filename);

        if (pair_found != m_textures.end()) {
            return pair_found->second;
        } else {
            auto &new_texture = m_textures[filename];
            new_texture.loadFromFile("../images/" + filename);
            return new_texture;
        }
    }

    sf::Font &asset_manager::get_font(const std::string &filename) {
        auto pair_found = m_fonts.find(filename);

        if (pair_found != m_fonts.end()) {
            return pair_found->second;
        } else {
            auto &new_font = m_fonts[filename];
            new_font.loadFromFile("../fonts/" + filename);
            return new_font;
        }
    }
} // game