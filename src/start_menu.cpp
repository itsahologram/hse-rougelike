#include "start_menu.h"

using namespace sf;

menu::Menu::Menu(std::size_t width, std::size_t height) {
    if(!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "No font is here!" << std::endl;
    }
    ///reg
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("Registration");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(300, 200);

    ///render_log_in
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("Log in");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(400, 300);

    ///play
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color::White);
    mainMenu[2].setString("Play");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(430, 400);

    ///exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(sf::Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(430, 500);

    menu_selected = 0;
    mainMenu[menu_selected].setFillColor(sf::Color::Cyan);
}

void menu::Menu::Draw(sf::RenderWindow &window) {
    for(int i = 0; i < MAX_MENU; ++i){
        window.draw(mainMenu[i]);
    }
}

void menu::Menu::Move_up() {
    mainMenu[menu_selected].setFillColor(sf::Color::White);
    menu_selected = (menu_selected + 3) % 4;
    mainMenu[menu_selected].setFillColor(sf::Color::Cyan);
}

void menu::Menu::Move_down() {
    mainMenu[menu_selected].setFillColor(sf::Color::White);
    menu_selected++;
    menu_selected %= MAX_MENU;
    mainMenu[menu_selected].setFillColor(sf::Color::Cyan);
}

menu::Menu::~Menu() {}

int menu::Menu::Menu_pressed() const {
    return menu_selected;
}

log_host::log_host::log_host(std::size_t width, std::size_t height) {
    if(!log_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "No font is here!" << std::endl;
    }
    ///host
    logHost[0].setFont(log_font);
    logHost[0].setFillColor(sf::Color::White);
    logHost[0].setString("HOST");
    logHost[0].setCharacterSize(70);
    logHost[0].setPosition(350, 200);

    ///player
    logHost[1].setFont(log_font);
    logHost[1].setFillColor(sf::Color::White);
    logHost[1].setString("PLAYER");
    logHost[1].setCharacterSize(70);
    logHost[1].setPosition(300, 300);

    log_selected = 0;
    logHost[log_selected].setFillColor(sf::Color::Cyan);
}

void log_host::log_host::Draw_log_or_host(sf::RenderWindow &window) {
    for(int i = 0; i < MAX_BUTTONS; ++i){
        window.draw(logHost[i]);
    }
}

void log_host::log_host::Move_up_log() {
    logHost[log_selected].setFillColor(sf::Color::White);
    log_selected = (log_selected + 1) % 2;
    logHost[log_selected].setFillColor(sf::Color::Cyan);
}

void log_host::log_host::Move_down_log() {
    logHost[log_selected].setFillColor(sf::Color::White);
    log_selected++;
    log_selected %= MAX_BUTTONS;
    logHost[log_selected].setFillColor(sf::Color::Cyan);
}
log_host::log_host::~log_host() {}

int log_host::log_host::Menu_pressed_log() const{
    return log_selected;
}

std::string render_log_in::return_port() {
    sf::RenderWindow text_window(sf::VideoMode(300, 200), "text-input");
    sf::Font text_font;
    if(!text_font.loadFromFile("C:/Windows/Fonts/arial.ttf")){
        std::cout << "No font is here!" << std::endl;
    }

    sf::Text input_text; //для отображения текста в окошке
    input_text.setFont(text_font);
    input_text.setCharacterSize(25);
    input_text.setPosition(10, 10);

    std::string text; //введенный нами текст
    while(text_window.isOpen()){
        sf::Event event;
        while(text_window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                text_window.close();
            }
            else if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    text_window.close();
                }
                else if(event.key.code == sf::Keyboard::Return){
                    input_text.setString(text);
                    text_window.close();
                    return text;
                }
            }
            else if(event.type == sf::Event::TextEntered){
                if(event.text.unicode < 128){ //кажется, проверка на то, что символ ASCII
                    if(event.text.unicode == 8 && !text.empty()){
                        text.pop_back();
                    }
                    else if(event.text.unicode != 8){
                        text += static_cast<char>(event.text.unicode);
                    }
                }
            }
        }
        input_text.setString(text);
        text_window.clear();
        text_window.draw(input_text);
        text_window.display();
    }
    return text;
}

void render_log_in::main_menu() {
    sf::RenderWindow window_menu(VideoMode(960, 720), "my_class_menu", Style::Default);
    menu::Menu my_class_menu(window_menu.getSize().x, window_menu.getSize().y);

    while (window_menu.isOpen()) {
        Event event;
        while (window_menu.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window_menu.close();
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    my_class_menu.Move_up();
                    continue;
                }
                if (event.key.code == Keyboard::Down) {
                    my_class_menu.Move_down();
                    continue;
                }
                if (event.key.code == sf::Keyboard::Return) {

                    int flag = my_class_menu.Menu_pressed();
                    if (flag == 0) {
                        sf::RenderWindow Registration(VideoMode(960, 720), "reg");
                        while (Registration.isOpen()) {
                            Event reg_event{};
                            while (Registration.pollEvent(reg_event)) {
                                if (reg_event.type == sf::Event::Closed) {
                                    Registration.close();
                                }
                                if (reg_event.type == sf::Event::KeyPressed) {
                                    if (reg_event.key.code == sf::Keyboard::Escape) {
                                        Registration.close();
                                    }
                                }
                            }
                            Registration.clear();
                            Registration.display();
                        }
                    }
                    if (flag == 1) {
                        host_or_not();


                    }
                    if (flag == 2) {
                        game::engine engine{};
                        engine.run();
                    }
                    if (flag == 3)
                        window_menu.close();
                    break;
                }
            }
        }
        window_menu.clear();
        my_class_menu.Draw(window_menu);
        window_menu.display();
    }
}
void render_log_in::host_or_not() {
    sf::RenderWindow log_or_host(VideoMode(960, 720), "my_log_or_host_window", Style::Default);
    log_host::log_host my_log_or_host_window(log_or_host.getSize().x, log_or_host.getSize().y);
    while (log_or_host.isOpen()) {
        Event event2;
        if(event2.key.code == Keyboard::Escape){
            log_or_host.close();
        }
         while (log_or_host.pollEvent(event2)) {
            if (event2.type == Event::Closed) {
                log_or_host.close();
            }
            if (event2.type == Event::KeyReleased) {
                if (event2.key.code == Keyboard::Up) {
                    my_log_or_host_window.Move_up_log();
                    continue;
                }
                if (event2.key.code == Keyboard::Down) {
                    my_log_or_host_window.Move_down_log();
                    continue;
                }
                if (event2.key.code == sf::Keyboard::Return) {

                    int log_flag = my_log_or_host_window.Menu_pressed_log();
                    if (log_flag == 0) {
                        is_host = true;
                        sf::RenderWindow HOST(VideoMode(960, 720), "host");
                        while (HOST.isOpen()) {
                            Event host_event{};
                            while (HOST.pollEvent(host_event)) {
                                if (host_event.type == sf::Event::Closed) {
                                    HOST.close();
                                }
                                if (host_event.type == sf::Event::KeyPressed) {
                                    if (host_event.key.code == sf::Keyboard::Escape) {
                                        HOST.close();
                                    }
                                }

                            }
                            HOST.clear();
                            HOST.display();
                        }
                    }
                    else {
                        is_host = false;
                        sf::RenderWindow ONLY_PLAYER(VideoMode(960, 720), "only_player");
                        while (ONLY_PLAYER.isOpen()) {
                            Event only_player_event{};
                            while (ONLY_PLAYER.pollEvent(only_player_event)) {
                                if (only_player_event.type == sf::Event::Closed) {
                                    ONLY_PLAYER.close();
                                }
                                if (only_player_event.type == sf::Event::KeyPressed) {
                                    if (only_player_event.key.code == sf::Keyboard::Escape) {
                                        ONLY_PLAYER.close();
                                    }
                                }
                            }
                            ONLY_PLAYER.clear();
                            ONLY_PLAYER.display();
                        }
                    }
                }
            }
        }
        log_or_host.clear();
        my_log_or_host_window.Draw_log_or_host(log_or_host);
        log_or_host.display();
    }
}
