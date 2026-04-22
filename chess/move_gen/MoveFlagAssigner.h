#pragma once

#include "Move.h"
#include "../game_state/GameState.h"

class GameState;

class MoveFlagAssigner {

public:
    static void assign_corresponding_flag_to(Move& move, const GameState* state);

private:
    MoveFlagAssigner(Move& move, const GameState* state) :
        move(&move), state(state) {}

    void assign_moved_piece();
    void assign_prev_en_passant();
    void assign_prev_castling_rights();
    void assign_prev_fifty_moves_rule_counter();

    void check_and_assign_capture_flag();
    void check_and_assign_castling_flag();
    void check_and_assign_pawn_double_push_flag();
    void check_and_assign_en_passant_flag();
    void check_and_assign_promotion_flag();
    bool square_on_promotion_row(const Square square);

    Move* move;
    const GameState* state;
};