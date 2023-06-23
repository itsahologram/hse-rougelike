#include "quest.hpp"
#include "string"

bool game::object_collection_quest::pick_up_item() {
    m_num_collected_items++;
    if (m_num_collected_items == m_num_items) {
        return true;
    }
    return false;

}

bool game::quest::middle_update(sf::Vector2f mouse_pose) {
    bool is_complete = false;

    if (m_status == COMPLETE){
        int player_choice = m_dialog->check_click(mouse_pose);
        if (player_choice == 3){
            m_dialog->set_not_draw();
        }
        return true;
    }
    if (m_type == "object_collection") {
        auto &current_quest = std::get<object_collection_quest>(m_content);
        is_complete = current_quest.pick_up_item();
        m_quest_progress =
                std::to_string(current_quest.m_num_collected_items) + "/" + std::to_string(current_quest.m_num_items);
    } else if (m_type == "quiz") {
        auto &current_quest = std::get<quiz_quest>(m_content);
        current_quest.player_answered(*m_dialog, mouse_pose);
        if ((int)current_quest.m_answered > (int)current_quest.m_questions.size() && m_status != COMPLETE) {
            finish_window();
        }
    }
    if (is_complete) {
        m_status = COMPLETE_BUT_NOT_TELL;
    }
    return false;
}

void game::quest::quest_was_started() {
    m_status = IN_PROGRESS;
    if (m_type == "object_collection") {
        auto &current_quest = std::get<object_collection_quest>(m_content);
        add_quest_obj(current_quest.m_num_items);
        m_quest_progress = "0/" + std::to_string(current_quest.m_num_items);
        m_dialog->set_not_draw();
    } else if (m_type == "quiz") {
        m_dialog->set_mode(DIALOG);
        m_dialog->set_text(m_middle_text, "", "", "Продолжить");
    }


}

void game::quest::quest_start_window(dialog &dial) {
    m_dialog = &dial;
    m_dialog->set_mode(CONFIRM_WINDOW);
    m_dialog->set_text(m_start_text, "", "Согласиться", "Отказаться");
}

void game::quest::confirm_quest(sf::Vector2f mouse_pose) {
    int player_choice = m_dialog->check_click(mouse_pose);
    if (player_choice == 2){
        quest_was_started();
    } else if (player_choice == 3){
        m_dialog->set_not_draw();
        m_status = NONE;
    }

}

void game::quest::finish_window() {
    m_status = COMPLETE;
    m_dialog->set_mode(DIALOG);
    if (m_type == "quiz") {
        auto &current_quest = std::get<quiz_quest>(m_content);
        m_dialog->set_text(m_end_text + std::to_string(current_quest.m_answered_correctly) + '/' +
                                   std::to_string(current_quest.m_answered - 1));
    } else {
        m_dialog->set_text(m_end_text);
    }
}


void game::quiz_quest::add_question(game::question &&question_) {
    m_questions.emplace_back(std::move(question_));
}

void game::quiz_quest::player_answered(game::dialog &dialog, sf::Vector2f &mousePos) {
    int ans = dialog.check_click(mousePos);
    if (ans == 0){
        return;
    }
    if (m_answered == -1) {
        m_answered++;
        set_current_ans(dialog);
    } else if ((unsigned)m_answered < m_questions.size()) {
        if (ans == 1) {
            if (m_questions[m_answered].m_num_correct_answer == 1) {
                m_answered_correctly++;
            }
        } else if (ans == 2) {
            if (m_questions[m_answered].m_num_correct_answer == 2) {
                m_answered_correctly++;
            }
        } else if (ans == 3) {
            if (m_questions[m_answered].m_num_correct_answer == 3) {
                m_answered_correctly++;
            }
        }
        m_answered++;
        set_current_ans(dialog);


    } else {
        dialog.set_not_draw();
    }
}


void game::quiz_quest::set_current_ans(game::dialog &dialog) {
    if (m_answered == -1){
        return;
    }
    if ((unsigned)m_answered == m_questions.size()) {
        m_answered++;
        return;
    }
    auto current_question = m_questions[m_answered];
    dialog.set_mode(QUIZ);
    dialog.set_text(current_question.m_text, current_question.m_answers[0],
                    current_question.m_answers[1], current_question.m_answers[2]);

}
