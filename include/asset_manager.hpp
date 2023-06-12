#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "quest.hpp"

namespace game {

    class asset_manager {
        std::map<std::string, sf::Texture> m_textures;
        std::map<std::string, sf::Font> m_fonts;
        std::vector<quest> m_all_quests;

    public:
        explicit asset_manager() = default;

        sf::Texture &get_texture(std::string const &filename);

        sf::Font &get_font(std::string const &filename);

        void parse_quests_from_json(const std::string &filename);

        quest &get_random_quest();

        int get_num_quests();

    };

} // game

#endif //ASSET_MANAGER_HPP
