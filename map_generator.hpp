#ifndef TEST_SFML_MAP_GENERATOR_HPP
#define TEST_SFML_MAP_GENERATOR_HPP

#include "vector"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<std::vector<char>> &get_map();

const int map_height = 45;
const int map_weight = 60;

const int min_room_height = 5;
const int min_room_weight = 8;

const int max_room_height = 20;
const int max_room_weight = 20;

const int count_room = 30;

void init_map();

void create_room(int x, int y, int x_f, int y_f);

void create_map();

#endif // TEST_SFML_MAP_GENERATOR_HPP
