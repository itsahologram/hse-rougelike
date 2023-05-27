#ifndef TEST_SFML_QUEST_HPP
#define TEST_SFML_QUEST_HPP

#include <SFML/Graphics.hpp>

namespace game {
    enum quest_status {
        START, IN_PROGRESS, COMPLETE, NONE
    };

    struct abstract_quest {
        game::quest_status m_status = NONE;
        sf::String m_name_of_quest = L"Нет квеста";


        virtual void update_status(bool is_start, bool is_passed) = 0;
    };

    struct quest_find_some_obj : public abstract_quest {

        int m_count_of_obj = 0;
        int m_current_count_of_obj = 0;
        // char type_of_obj;

        quest_find_some_obj(sf::String name_of_quest, int count_of_obj) : m_count_of_obj(count_of_obj) {
            m_name_of_quest = name_of_quest;
        };

        quest_find_some_obj() = default;

        void update_status(bool is_start, bool is_passed) override {
            if (is_start) {
                m_status = START;
            } else if (is_passed) {
                m_status = COMPLETE;
            } else if (m_current_count_of_obj == m_count_of_obj) {
                m_status = IN_PROGRESS;
                m_name_of_quest = L"Ты собрал";
            }
        }

    };

    struct quest_second : public abstract_quest {
        void update_status(bool is_start, bool is_passed) override {
            int a = 5;
        }

        void foo() {
            int a = 10;
        }
    };
}
#endif //TEST_SFML_QUEST_HPP
