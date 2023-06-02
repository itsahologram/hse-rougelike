#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Network.hpp>

const std::string USER_NOT_FOUND = "User not found. Please check your credentials and try again.";

const std::string SUCCESSFUL_AUTHORIZATION = "You have successfully logged in.";


std::string register_player(const std::string& username) {
    // Создаём запрос на регистрацию
    sf::TcpSocket socket;
    socket.connect("localhost", 1234);
    sf::Packet request_packet;
    request_packet << "register" << username;
    socket.send(request_packet);

    // Получаем пароль от сервера
    sf::Packet response_packet;
    socket.receive(response_packet);
    std::string password;
    response_packet >> password;

    // Возвращаем пароль клиенту
    return password;
}

std::string get_password() {
    // Реализация функции получения пароля из запроса
}

std::string get_username() {
    // Реализация функции получения имени пользователя из запроса
}

void handle_login_response(sf::TcpSocket& server_socket)
{
    sf::Packet packet;
    server_socket.receive(packet);
    std::string response_code;
    packet >> response_code;
    if (response_code == SUCCESSFUL_AUTHORIZATION)
    {
        // Переход на другую страницу, например, на страницу игры
        // ...
    }
    else if (response_code == USER_NOT_FOUND)
    {
        // Если аккаунт пользователя не существует, то выводится сообщение об ошибке
        std::cout << "Пользователь не найден. Пожалуйста, зарегистрируйтесь." << std::endl;
    }
}

void handle_login_button_click()
{
    // Отправка запроса на сервер для проверки наличия аккаунта пользователя в базе данных
    sf::TcpSocket server_socket;
    server_socket.connect("localhost", 1234); // Подключение к серверу
    std::string username = get_username(); // Получение имени пользователя
    std::string password = get_password(); // Получение пароля пользователя
    sf::Packet packet;
    packet << username << password;
    server_socket.send(packet);

    // Обработка ответа от сервера
    handle_login_response(server_socket);
}

void handle_register_button_click()
{
    // Регистрация пользователя

    // После регистрации пользователя можно нажать на кнопку "Вход"
    handle_login_button_click();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Start Menu");
    // Создаем текстуры для кнопок
    sf::Texture regTexture;
    if (!regTexture.loadFromFile("C:/Users/uliya/Downloads/reg.png"))
    {
        // Если текстуру не удалось загрузить, выводим сообщение об ошибке
        return EXIT_FAILURE;
    }
    sf::Texture loginTexture;
    if (!loginTexture.loadFromFile("C:/Users/uliya/Downloads/log.png"))
    {
        // Если текстуру не удалось загрузить, выводим сообщение об ошибке
        return EXIT_FAILURE;
    }

    // Создаем спрайты для кнопок
    sf::Sprite registerButton(regTexture);
    registerButton.setPosition(100, 110);
    sf::Sprite loginButton(loginTexture);
    loginButton.setPosition(100, 300);

    // Создаем шрифт для надписи
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        // Если шрифт не удалось загрузить, выводим сообщение об ошибке и выходим из приложения
        return EXIT_FAILURE;
    }
    // Создаем текст для надписи
    sf::Text hseRougleText("HSE-ROGUELIKE", font, 50);
    hseRougleText.setFillColor(sf::Color::Black);
    hseRougleText.setPosition(190, 40);

    sf::String password;
    sf::Text passwordText("", font, 30);
    passwordText.setFillColor(sf::Color::Black);
    passwordText.setPosition(200, 200);

    // Создаем сокет
    sf::TcpSocket socket;

    // Подключаемся к серверу
    sf::Socket::Status status = socket.connect("localhost", 1234);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    // Входим в основной цикл

    while (window.isOpen())
    {
        // Обрабатываем события
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Если нажата кнопка мыши, проверяем на какую кнопку было нажато
                if (registerButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    // Если нажата кнопка регистрации, отправляем запрос на регистрацию
                    sf::Packet packet;
                    packet << "register" << password.toAnsiString();
                    socket.send(packet);

                    // Получаем ответ от сервера
                    sf::Packet response;
                    socket.receive(response);
                    std::string message;
                    response >> message;
                    std::cout << message << std::endl;
                }
                else if (loginButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    // Если нажата кнопка входа, отправляем запрос на вход
                    sf::Packet packet;
                    packet << "login" << password.toAnsiString();
                    socket.send(packet);

                    // Получаем ответ от сервера
                    sf::Packet response;
                    socket.receive(response);
                    std::string message;
                    response >> message;
                    std::cout << message << std::endl;
                }
            }
            else if (event.type == sf::Event::TextEntered)
            {
                // Если пользователь вводит текст, добавляем его к паролю
                if (event.text.unicode == 'b' && !password.isEmpty())
                {
                    password.erase(password.getSize() - 1, 1);
                }
                else if (event.text.unicode < 128 && password.getSize() < 16)
                {
                    password += event.text.unicode;
                }
                passwordText.setString(password);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                // Если пользователь нажимает Enter, отправляем запрос на регистрацию или вход
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (registerButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                        // Если нажата кнопка регистрации, отправляем запрос на регистрацию
                        sf::Packet packet;
                        packet << "register" << password.toAnsiString();
                        socket.send(packet);

                        // Получаем ответ от сервера
                        sf::Packet response;
                        socket.receive(response);
                        std::string message;
                        response >> message;
                        std::cout << message << std::endl;
                    }
                    else if (loginButton.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                       // Если нажата кнопка входа, отправляем запрос на вход
                        sf::Packet packet;
                        packet << "login" << password.toAnsiString();
                        socket.send(packet);

                        // Получаем ответ от сервера
                        sf::Packet response;
                        socket.receive(response);
                        std::string message;
                        response >> message;
                        std::cout << message << std::endl;
                    }
                }
            }
        }
        // Отрисовываем элементы интерфейса
        window.clear(sf::Color::White);
        window.draw(registerButton);
        window.draw(loginButton);
        window.draw(passwordText);
        window.display();
    }

    return 0;
}
