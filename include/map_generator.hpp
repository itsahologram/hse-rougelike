#ifndef TEST_SFML_MAP_GENERATOR_HPP
#define TEST_SFML_MAP_GENERATOR_HPP

#include "vector"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<std::vector<char>> &get_map();

const int map_height = 60;
const int map_weight = 100;

const int min_room_height = 5;
const int min_room_weight = 8;

const int max_room_height = 30;
const int max_room_weight = 30;

const int count_room = 60;
const int count_coffee = 25;

static int set_x_f = 0;
static int set_y_f = 0;

void init_map();

void create_room(int x, int y, int x_f, int y_f);

void create_map();
void add_quest_obj(int count);

void draw_map(sf::RenderWindow &window, sf::Sprite &s_map, sf::Sprite &s_coffee, sf::Sprite &s_npc,
              sf::Sprite &s_quest_obj);

#endif // TEST_SFML_MAP_GENERATOR_HPP
