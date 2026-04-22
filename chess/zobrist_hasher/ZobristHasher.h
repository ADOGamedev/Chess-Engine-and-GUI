#pragma once

#include <random>

#include "../game_state/GameState.h"
#include "../move_gen/MoveGen.h"
#include "../utils/utils.h"

class GameState;

class RandUint64Gen {
    public:
    RandUint64Gen(uint64_t seed) :
    gen(seed), distribution(0, UINT64_MAX) {}
    
    uint64_t get_next_random_number() {
        return distribution(gen);
    }
    
    private:
    std::mt19937_64 gen;
    std::uniform_int_distribution<uint64_t> distribution;
};


class ZobristHasher {

public:
    static void initialize_zobrist_values();
    static void set_zobrist_key_of_state(GameState& state);

private:
    static void initialize_pieces_squares_zobrist_values();
    static void initialize_black_to_move_zobrist_value();
    static void initialize_castling_rights_zobrist_values();
    static void initialize_en_passants_zobrist_values();

    static uint64_t get_pieces_square_zobrist_key(GameState& state);
    static uint64_t get_turn_zobrist_key(const Colour turn);
    static uint64_t get_castlings_zobrist_key(const std::array<bool, N_CASTLINGS>& castling_rights);
    static uint64_t get_en_passant_zobrist_key(const Square en_passant_square);

    static uint64_t piece_square_zobrist_values[N_PIECES][N_SQUARES];
    static uint64_t black_to_move_zobrist_value;
    static uint64_t castling_rights_zobrist_values[N_CASTLINGS];
    static uint64_t en_passant_zobrist_values[N_COLUMNS];

    static RandUint64Gen rand_uint64_gen;

    static const uint64_t ZOBRIST_SEED = 3682;
};