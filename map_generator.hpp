#ifndef TEST_SFML_MAP_GENERATOR_HPP
#define TEST_SFML_MAP_GENERATOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include "vector"

//28x38
std::vector<std::vector<char>> &get_map();

const int H_MAP = 45; //38
const int W_MAP = 59; // 28

const int min_h = 5;
const int min_w = 8;

const int max_h = 20;
const int max_w = 20;

const int count_room = 30;


void init_map();

void create_room(int x, int y, int x_f, int y_f);

void create_map();





#endif //TEST_SFML_MAP_GENERATOR_HPP
