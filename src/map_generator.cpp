#include "map_generator.hpp"

std::random_device random_device;
std::mt19937 generator(random_device());
std::uniform_int_distribution<> rand_h(min_room_height, max_room_height);
std::uniform_int_distribution<> rand_w(min_room_weight, max_room_weight);
std::uniform_int_distribution<> rand_x(1, map_weight - 5);
std::uniform_int_distribution<> rand_y(1, map_height - 5);

std::vector<std::vector<char>> &get_map() {
    static std::vector<std::vector<char>> tile_map;
    return tile_map;
}

struct room {
public:
    int x_1, y_1;
    int x_2, y_2;

    int center_x, center_y;

    room(int x, int y, int x2, int y2) : x_1(x), y_1(y), x_2(x2), y_2(y2) {
        center_x = x_1 + (x_2 - x_1) / 2;
        center_y = y_1 + (y_2 - y_1) / 2;
    };

    bool is_collisions(room &other) {
        if ((x_1 >= other.x_1 && x_1 <= other.x_2) &&
            (y_1 >= other.y_1 && y_1 <= other.y_2)) {
            return true;
        }
        if ((x_1 <= other.x_1 && x_1 >= other.x_2) &&
            (y_1 <= other.y_1 && y_1 >= other.y_2)) {
            return true;
        }
        if ((x_2 >= other.x_1 && x_2 <= other.x_2) &&
            (y_2 >= other.y_1 && y_2 <= other.y_2)) {
            return true;
        }
        if ((x_2 <= other.x_1 && x_2 >= other.x_2) &&
            (y_1 <= other.y_2 && y_2 >= other.y_2)) {
            return true;
        }
        return false;
    };

    void create_tunnel(room &other) const {
        int x_start = 0;
        int x_finish = 0;
        int y_start = 0;
        int y_finish = 0;

        if (center_x > other.center_x) {
            x_start = other.center_x;
            y_start = other.center_y;
            x_finish = center_x;
            y_finish = center_y;
        } else {
            x_start = center_x;
            y_start = center_y;
            x_finish = other.center_x;
            y_finish = other.center_y;
        }

        for (int i = x_start; i <= x_finish; i++) {
            get_map()[y_start][i] = '0';
            get_map()[y_start + 1][i] = '0';
        }

        for (int i = std::min(y_start, y_finish); i <= std::max(y_start, y_finish);
             i++) {
            get_map()[i][x_finish] = '0';
            get_map()[i][x_finish + 1] = '0';
        }
    }
};

void init_map() {
    get_map() =
            std::vector<std::vector<char>>(map_height, std::vector<char>(map_weight, '1'));
}

void create_room(int x, int y, int x_f, int y_f) {
    for (int i = x + 1; i < x_f - 1; i++) {
        for (int j = y + 1; j < y_f - 1; j++) {
            get_map()[j][i] = '0';
        }
    }
}

void create_coffee() {
    int coffee_complete = 0;
    while (coffee_complete < count_coffee) {
        int set_x = rand_x(generator);
        int set_y = rand_y(generator);
        if (get_map()[set_y][set_x] == '0') {
            get_map()[set_y][set_x] = 'c';
            coffee_complete++;
        }
    }
}

void create_map() {
    set_x_f = 1 + rand_w(generator);
    set_y_f = 1 + rand_h(generator);

    create_room(1, 1, set_x_f, set_y_f);

    std::vector<room> all_room;
    room last_room = room(1, 1, set_x_f, set_y_f);

    for (int i = 0; i < count_room; i++) {
        int set_x = rand_x(generator);
        int set_y = rand_y(generator);

        int set_x_f = std::min(set_x + rand_w(generator), map_weight - 1);
        int set_y_f = std::min(set_y + rand_h(generator), map_height - 1);

        room new_room = room(set_x, set_y, set_x_f, set_y_f);
        bool is_col = false;

        for (auto old_room: all_room) {
            if (new_room.is_collisions(old_room)) {
                is_col = true;
            }
        }

        if (is_col) {
            continue;
        }

        all_room.emplace_back(new_room);
        create_room(set_x, set_y, set_x_f, set_y_f);
        last_room.create_tunnel(new_room);
        last_room = new_room;
    }
    get_map()[2][set_x_f - 2] = 'n';
    create_coffee();
}

void game::npc::set_coordinates(int new_x, int new_y) {
    m_x = new_x;
    m_y = new_y;
}

void add_quest_obj(int count) {
    int count_obj = 0;
    while (count_obj < count) {
        auto new_x = rand_x(generator);
        auto new_y = rand_y(generator);
        if (get_map()[new_y][new_x] == '0') {
            get_map()[new_y][new_x] = 'o';
            count_obj++;
        }
    }
}

void draw_map(sf::RenderWindow &window, sf::Sprite &s_map, sf::Sprite &s_coffee, sf::Sprite &s_npc,
              sf::Sprite &s_quest_obj) {
    for (int i = 0; i < map_height; i++)
        for (int j = 0; j < map_weight; j++) {
            if (get_map()[i][j] == '0') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);
            } else if (get_map()[i][j] == '1') {
                s_map.setTextureRect(sf::IntRect(
                        384, 0, 32, 32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);

            } else if (get_map()[i][j] == 'c') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                s_coffee.setTextureRect(sf::IntRect(0, 0, 16, 16));
                s_coffee.setPosition((float) (j * 32), (float) (i * 32));
                window.draw(s_map);
                window.draw(s_coffee);

            } else if (get_map()[i][j] == 'o') {
                s_map.setTextureRect(sf::IntRect(
                        461, 320, 32,
                        32));
                s_quest_obj.setTextureRect(sf::IntRect(1, 1, 32, 32));
                s_quest_obj.setPosition((float) (j * 32), (float) (i * 32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);
                window.draw(s_quest_obj);

            } else if (get_map()[i][j] == 'n') {
                s_npc.setPosition((float) (j * 32), (float) (i * 32));
                s_map.setPosition(
                        (float) (j * 32), (float) (i * 32));
                window.draw(s_map);
                window.draw(s_npc);
            }

        }
}