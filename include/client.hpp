#ifndef TEST_SFML_CLIENT_HPP
#define TEST_SFML_CLIENT_HPP
#include "button.hpp"
#include "characters.hpp"
#include "map_generator.hpp"
#include "view.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "engine.hpp"
#include "asset_manager.hpp"
#include "start_menu.hpp"
//#include "server.h"
#include "SFML/Network.hpp"

class client {
public:
    std::string get_client_port();
    void set_client_port(std::string port);
//     void set_from_render();
    render_log_in get_render();

    void set_is_client_host(bool is_host);
    bool get_is_client_host() const;

private:
    render_log_in render;
    bool is_client_host = false;
    std::string client_port;
};




#endif //TEST_SFML_CLIENT_HPP