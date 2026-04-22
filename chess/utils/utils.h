#pragma once

#include <cstdint>
#include <string>
#include <random>
#include <vector>
#include <iostream>
#include <type_traits>

#include "../game_state/GameState.h"
#include "../constants/constants.h"
#include "../move_gen/Move.h"
#include "../logger/Logger.h"

#ifdef _MSC_VER
    #define count_trailing_zeros std::_Countr_zero
#else
    #define count_trailing_zeros std::countr_zero
#endif

#ifdef _MSC_VER
    #define count_bits_in std::_Popcount
#else
    #define count_bits_in std::popcount
#endif

class GameState;

void set_bit_to_1(uint64_t& num, const int bit);
void set_bit_to_0(uint64_t& num, const  int bit);
bool is_bit_1(const uint64_t num, const int bit);
bool is_bit_0(const uint64_t num, const int bit);

bool is_square_out_of_bounds(const Square& square);
bool is_square_out_of_bounds(const int& square);


bool is_white(const Piece& piece);

int char_to_int(const char ch);
int string_to_int(const std::string str);


std::string move_to_lan_notation(const Move& move);
Move lan_notation_to_move(const std::string& lan_str);

std::string square_to_chess_coords(const Square square);
Square chess_coords_to_square(const std::string chess_coords);

Square get_flipped_square(const Square square);

template <typename T, size_t N>
std::string arr_to_str(const std::array<T, N>& arr) {
    std::string str = "{";

    for (int i = 0; i < arr.size(); i++) {
        str += std::to_string(arr[i]);

        if (i < arr.size() - 1) {
            str += ", ";
        }

        if ((i + 1) % 8 == 0) {
            str += "\n";
        }
    }

    return str + "}";
}

template <typename T>
std::string arr_to_str(const std::vector<T>& vec) {
    std::string str = "{";

    for (int i = 0; i < vec.size(); i++) {
        str += vec[i];

        if (i < vec.size() - 1) {
            str += ", ";
        }

        if ((i + 1) % 8 == 0) {
            str += "\n";
        }
    }

    return str + "}";
}

std::string board_to_string(const GameState& state);
void print_bitboard(const uint64_t& state);

uint64_t rand_uint64(uint64_t seed);
double randf();
int randi_range(int min, int max);