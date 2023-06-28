#include <sstream>
#include "server.h"


void server::start() {
    listener.listen(12345);
    sf::TcpSocket socket;
    packet_status_types status_type;
    int status;
    wait_players();
    while (true) {
        sf::Packet packet;
        packet >> status;
        if (status == 1) {
            socket.send(sf::Packet() << 1);

            std::string map;
            packet >> map;
            parse_map(map);
            packet.clear();

            socket.send(sf::Packet() << map);

        }
    }
}

server::server(unsigned short port) {
//    listener.listen(port);
}

int server::generate_id() {
    id++;
    return id;
}

int server::return_id() {
    return id;
}

void server::wait_players() {
    while(true){
        sf::TcpSocket::Status status1 = listener.accept(host_player);
        sf::TcpSocket::Status status2 = listener.accept(player);
        if(status1 == sf::Socket::Done && status2 == sf::Socket::Done){
            break;
        }
    }
}

void server::parse_map(const std::string& map) {
    std::stringstream ss(map);
    std::string row;
    while(ss >> row){
        my_map.push_back(std::vector<char>(row.size()));
        for(int i = 0; i < row.size(); i++){
            my_map[my_map.size() - 1][i] = row[i];
        }
    }
}
