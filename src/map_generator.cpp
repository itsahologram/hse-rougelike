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
    int set_x_f = 1 + rand_w(generator);
    int set_y_f = 1 + rand_h(generator);
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
    create_coffee();
}