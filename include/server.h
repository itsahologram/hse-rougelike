#ifndef TEST_SFML_SERVER_H
#define TEST_SFML_SERVER_H

#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
#include "packet_status_types.h"

class server {
public:
    void parse_map(const std::string& map);
    explicit server(unsigned short port);
    void start();
    int generate_id();
    int return_id();
    void wait_players();


private:

    sf::TcpSocket host_player;
    sf::TcpSocket player;
    std::vector<std::vector<char>> my_map;
    std::map<int, sf::TcpSocket*> players;
    sf::TcpListener listener;
    std::pair<double, double> current_condition_of_the_player; //мб для хранения позиции
    int id = 0;


};


#endif //TEST_SFML_SERVER_H