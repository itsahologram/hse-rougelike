#ifndef TEST_SFML_QUEST_HPP
#define TEST_SFML_QUEST_HPP

#include <SFML/Graphics.hpp>
#include "map_generator.hpp"
#include <variant>
#include "button.hpp"

namespace game {
    enum quest_status {
        IN_PROGRESS, COMPLETE_BUT_NOT_TELL, COMPLETE, NONE
    };

    struct object_collection_quest {

        int m_num_collected_items = 0;

        int m_num_items = 0;
        std::string m_item_type{};

        object_collection_quest(int num_items, std::string item_type) : m_num_items(num_items),
                                                                        m_item_type(std::move(item_type)) {};

        bool pick_up_item();

    };

    struct question {
        std::string m_text{};
        std::vector<std::string> m_answers{};
        int m_num_correct_answer = 0;

    };

    struct quiz_quest {
        std::vector<question> m_questions;

        int m_answered_correctly = 0;
        int m_answered = -1;

        void add_question(question &&question_);

        void player_answered(game::dialog &dialog, sf::Vector2f &mousePos);

        void set_current_ans(game::dialog &dialog);

    };

    struct quest {
        quest_status m_status = NONE;

        dialog *m_dialog = nullptr;

        std::string m_header_text;
        std::string m_details_quest;
        std::string m_quest_progress;

        std::string m_start_text;
        std::string m_middle_text;
        std::string m_end_text;
        std::string m_type;
        std::variant<object_collection_quest, quiz_quest> m_content{object_collection_quest(0, "none")};

        quest() = default;

        bool middle_update(sf::Vector2f &mousePos);

        void middle_update();


        void quest_was_started(dialog &dial);

    };
}
#endif //TEST_SFML_QUEST_HPP
