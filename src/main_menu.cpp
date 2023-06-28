#include "characters.hpp"
#include "map_generator.hpp"
#include "view.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include "engine.hpp"
#include "asset_manager.hpp"
#include "client.h"
#include "server.h"
#include "packet_status_types.h"


int main() {
    game::engine engine{};
    client client;
    packet_status_types status_type;

    std::string port;
    port = client.get_render().return_port();
    unsigned long long_port = std::stoi(port);

    client.set_client_port(port);
    client.get_render().main_menu();

    client.set_is_client_host(client.get_render().is_host);
    std::vector<std::vector<char>> host_map = client.read_map();
    if(client.get_is_client_host()) {
        sf::Thread host_client_server([&](){
            server Server(static_cast<unsigned short>(long_port));
            Server.start();
        });
        host_client_server.launch();
        std::string line_map;
        for(auto & i : get_map()){
            for(char j : i){
                line_map += j;
            }
            line_map += ' ';
        }
        sf::TcpSocket host_socket;
//        host_socket.setBlocking(true);
        host_socket.connect(sf::IpAddress::getLocalAddress(), static_cast<unsigned short>(long_port));
        std::cout << sf::IpAddress::getLocalAddress().toString() << std::endl;
        sf::Packet host_packet;
//        if(host_socket.receive(host_packet) == sf::Socket::Done){
//            host_socket.send(sf::Packet() << 1 <<  line_map);
//        }
//        host_socket.send(sf::Packet() << 1 << line_map);
        get_map() = host_map;
        engine.run();
        host_client_server.terminate();
    }
    else {
        sf::IpAddress ip(client.get_render().return_port());
        std::cout << ip << std::endl;

        sf::TcpSocket player;
        player.connect(ip, static_cast<unsigned short>(long_port));
        sf::Socket::Status player_status = player.connect(ip, static_cast<unsigned short>(long_port));

        sf::Packet packet;
        int status;
        packet >> status;
        std::cout << status << std::endl;
//        if (status == 1) {
//            std::string map;
//            packet >> map;
//            get_map() = client.parse_map(map);
        get_map() = host_map;
        engine.run();
//        }

    }
    std::cout << client.get_is_client_host() << std::endl;
    std::cout << client.get_client_port() << std::endl;
}