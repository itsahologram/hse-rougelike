#ifndef TEST_SFML_CLIENT_H
#define TEST_SFML_CLIENT_H
#include "button.hpp"
#include "characters.hpp"
#include "map_generator.hpp"
#include "view.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "engine.hpp"
#include "asset_manager.hpp"
#include "start_menu.h"
#include "SFML/Network.hpp"

class client {
public:
    std::vector<std::vector<char>> parse_map(const std::string& map);
    std::string get_client_port();
    void set_client_port(std::string port);
    render_log_in & get_render();

    void set_is_client_host(bool is_host);
    bool get_is_client_host() const;

    std::vector<std::vector<char>> read_map();


private:
    render_log_in render{};
    bool is_client_host = true;
    std::string client_port;
};




#endif //TEST_SFML_CLIENT_H