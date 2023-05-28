#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>

namespace game {

    class asset_manager {
        std::map<std::string, sf::Texture> m_textures;
        std::map<std::string, sf::Font> m_fonts;

    public:
        explicit asset_manager() = default;
        sf::Texture& get_texture(std::string const& filename);
        sf::Font& get_font(std::string const& filename);
    };

} // game

#endif //ASSET_MANAGER_HPP
