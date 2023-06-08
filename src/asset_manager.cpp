#include "asset_manager.hpp"
#include <nlohmann/json.hpp>
#include <random>
#include <fstream>


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

    void from_json(const nlohmann::json& j, question& question){
        j.at("text").get_to(question.m_text);
        j.at("answers").get_to(question.m_answers);
        j.at("correct_answer").get_to(question.m_num_correct_answer);
    }

    void asset_manager::parse_quests_from_json(const std::string &filename) {
        std::ifstream f("../text-materials/" + filename);
        nlohmann::json j = nlohmann::json::parse(f);
        int n = j["num"];
        m_all_quests.resize(n);
        for (int i = 0; i < n; i++) {
            m_all_quests[i].m_status = NONE;
            m_all_quests[i].m_header_text = j["all"][i]["header_text"];
            m_all_quests[i].m_details_quest = j["all"][i]["details_quest"];
            m_all_quests[i].m_start_text = j["all"][i]["start_text"];
            m_all_quests[i].m_middle_text = j["all"][i]["middle_text"];
            m_all_quests[i].m_end_text = j["all"][i]["end_text"];
            m_all_quests[i].m_type = j["all"][i]["type"];
            if (m_all_quests[i].m_type == "object_collection") {
                int num_items = j["all"][i]["content"]["num_items"];
                std::string item_type = j["all"][i]["content"]["item_type"];
                object_collection_quest content(num_items, item_type);
                m_all_quests[i].m_content = content;
            } else if (m_all_quests[i].m_type == "quiz") {
                quiz_quest content{};
                for (auto & it : j["all"][i]["content"]){
                    content.add_question(it.get<question>());
                }
                m_all_quests[i].m_content = content;
            }
        }
    }

    quest &asset_manager::get_random_quest() {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> get_random_quest_index(0, (int) m_all_quests.size() - 1);
        int random_quest_index = get_random_quest_index(generator);

        while (m_all_quests[random_quest_index].m_status != NONE) {
            random_quest_index = get_random_quest_index(generator);
        }

        return m_all_quests[random_quest_index];
    }

    int asset_manager::get_num_quests() {
        return m_all_quests.size();
    }
} // game