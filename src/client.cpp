#include "client.h"
#include <utility>
#include <sstream>
#include <fstream>

std::string client::get_client_port() {
    return client_port;
}

void client::set_client_port(std::string port) {
    client_port = std::move(port);
}

render_log_in & client::get_render() {
    return render;
}

bool client::get_is_client_host() const {
    return is_client_host;
}

void client::set_is_client_host(bool is_host) {
    is_client_host = is_host;
}

std::vector<std::vector<char>> client::parse_map(const std::string &map) {
    std::vector<std::vector<char>> my_client_map;
    std::stringstream ss(map);
    std::string row;
    while(ss >> row){
        my_client_map.push_back(std::vector<char>(row.size()));
        for(int i = 0; i < row.size(); i++){
            my_client_map[my_client_map.size() - 1][i] = row[i];
        }
    }
}

std::vector<std::vector<char>> client::read_map() {
    std::vector<std::vector<char>> my_map;
    std::ifstream inputfile("../fonts/smth");
    if(inputfile.is_open()){
        std::string line;
        while(std::getline(inputfile, line)){
            my_map.resize(my_map.size()+1);
            for(auto i : line){
                my_map[my_map.size() - 1].push_back(i);
            }
        }
        inputfile.close();
    }
    return my_map;
}



