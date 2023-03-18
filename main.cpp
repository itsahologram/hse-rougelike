#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "characters.hpp"
#include "map.hpp"

float current_frame = 0;

void run_animation(game::characters &player, game::directions dir, float time){
    player.m_direction = dir;
    player.m_speed = 0.1;
    current_frame +=0.005*time;
    if (current_frame > 8){
        current_frame = 0;
    }
    if (dir == game::LEFT){
        player.m_sprite.setTextureRect(sf::IntRect(32,48*int(current_frame),-32,48));
    } else if (dir == game::RIGHT){
        player.m_sprite.setTextureRect(sf::IntRect(0,48*int(current_frame),32,48));
    }

}



int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 500), "SFML works!");
    window.setFramerateLimit(120);

    sf::Clock clock;

    game::characters player("hero.png", 64, 64, 32, 48);

    sf::Image map_img;
    map_img.loadFromFile("../images/map.png");
    sf::Texture map;
    map.loadFromImage(map_img);
    sf::Sprite s_map;
    s_map.setTexture(map);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            run_animation(player, game::LEFT, time);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            run_animation(player, game::RIGHT, time);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            run_animation(player, game::UP, time);

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            run_animation(player, game::DOWN, time);

        }

        player.update(time);

        window.clear();
        for (int i = 0; i < H_MAP; i++)
            for (int j = 0; j < W_MAP; j++)
            {
                if (TileMap[i][j] == '0')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
                if (TileMap[i][j] == '1') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


                s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
                window.draw(s_map);//рисуем квадратики на экран
            }
        window.draw(player.m_sprite);
        window.display();
        Sleep(time/80);
    }

    return 0;
}
