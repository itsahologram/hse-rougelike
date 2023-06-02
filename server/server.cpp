#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>
#include <thread>

// Словарь для хранения паролей пользователей
std::unordered_map<std::string, std::string> users;

// Функция для сохранения нового пользователя в базу данных
void save_user(const std::string& username, const std::string& password) {
    // Сохраняем имя пользователя и пароль в базе данных
    users[username] = password;
}

// Функция для получения имени пользователя из пакета
std::string get_username(sf::Packet& packet) {
    std::string username;
    packet >> username;
    return username;
}

// Функция для отправки сообщения клиенту
void send_message(sf::TcpSocket* socket, const std::string& message) {
    sf::Packet packet;
    packet << message;
    socket->send(packet);
}

// Функция для обработки запросов от клиентов
void handle_client(sf::TcpSocket* client) {
    // Получаем запрос от клиента
    sf::Packet request;
    if (client->receive(request) != sf::Socket::Done) {
        std::cerr << "Failed to receive request from client" << std::endl;
        return;
    }

    // Обрабатываем запрос
    std::string action, username, password;
    request >> action >> username >> password;

    if (action == "register") {
        // Регистрируем нового пользователя
        if (users.find(username) != users.end()) {
            // Пользователь с таким именем уже зарегистрирован
            send_message(client, "User with this username already exists");
        } else {
            // Регистрируем нового пользователя и отправляем подтверждение
            save_user(username, password);
            send_message(client, "User registered successfully");
        }
    } else if (action == "login") {
        // Проверяем, зарегистрирован ли пользователь с таким именем и паролем
        if (users.find(username) == users.end() || users[username] != password) {
            // Пользователь с таким именем и паролем не зарегистрирован
            send_message(client, "Invalid username or password");
        } else {
            // Отправляем подтверждение входа
            send_message(client, "User logged in successfully");
        }
    }

    // Закрываем соединение с клиентом
    client->disconnect();
    delete client;
}

int main() {
    // Создаем серверный сокет и привязываем его к порту 1234
    sf::TcpListener listener;
    if (listener.listen(1234) != sf::Socket::Done) {
        std::cerr << "Failed to bind to port" << std::endl;
        return 1;
    }

    // Входим в основной цикл
    while (true) {
        // Принимаем новые соединения от клиентов и обрабатываем их запросы в отдельных потоках
        sf::TcpSocket* client = new sf::TcpSocket();
        if (listener.accept(*client) == sf::Socket::Done) {
            std::thread(handle_client, client).detach();
        } else {
            std::cerr << "Failed to accept client" << std::endl;
            delete client;
        }
    }

    return 0;
}
