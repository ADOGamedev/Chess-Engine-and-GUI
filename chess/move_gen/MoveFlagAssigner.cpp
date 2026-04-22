#include "MoveFlagAssigner.h"

void MoveFlagAssigner::assign_corresponding_flag_to(Move& move, const GameState* state) {
    MoveFlagAssigner assigner = MoveFlagAssigner(move, state);

    assigner.assign_moved_piece();
    assigner.assign_prev_en_passant();
    assigner.assign_prev_castling_rights();
    assigner.assign_prev_fifty_moves_rule_counter();
    
    PieceType moved_piece_type = piece_to_piece_type[move.moved_piece];
    
    assigner.check_and_assign_capture_flag();

    if (moved_piece_type == KING) {
        assigner.check_and_assign_castling_flag();
    }
    if (moved_piece_type == PAWN) {
        assigner.check_and_assign_pawn_double_push_flag();
        assigner.check_and_assign_en_passant_flag();
        assigner.check_and_assign_promotion_flag();
    }
}

void MoveFlagAssigner::assign_moved_piece() {
    Piece moved_piece = state->get_piece_at(move->from);
    PieceType moved_piece_type = piece_to_piece_type[moved_piece];

    move->moved_piece = moved_piece;
}

void MoveFlagAssigner::assign_prev_en_passant() {
    if (state->en_passant != SQ_NONE) {
        move->prev_en_passant = state->en_passant;
        move->prev_en_passant_capture = state->en_passant_capture;
        move->captured_piece = state->get_piece_at(state->en_passant_capture);
    }
}

void MoveFlagAssigner::assign_prev_castling_rights() {
    move->prev_castling_rights = state->castling_rights;
}

void MoveFlagAssigner::assign_prev_fifty_moves_rule_counter() {
    move->prev_fifty_moves_rule_counter = state->fifty_moves_rule_counter;
}

void MoveFlagAssigner::check_and_assign_capture_flag() {
    if (state->is_enemy(move->to)) {
        move->set_flag(MoveFlag::CAPTURE);
        move->captured_piece = state->get_piece_at(move->to);
    }
}

void MoveFlagAssigner::check_and_assign_castling_flag() {
    int squares_difference = move->to - move->from;

    bool is_short_castle = squares_difference == 2;
    bool is_long_castle = squares_difference == -2;

    if (is_short_castle) {
        move->set_flag(MoveFlag::SHORT_CASTLE);
    }
    else if (is_long_castle) {
        move->set_flag(MoveFlag::LONG_CASTLE);
    }
}

void MoveFlagAssigner::check_and_assign_pawn_double_push_flag() {
    int pawn_offset = abs(move->to - move->from);
    bool is_double_push = pawn_offset == PawnOffset::DOUBLE_FRONT;

    if (is_double_push) {
        move->set_flag(MoveFlag::DOUBLE_PAWN_PUSH);
    }
}

void MoveFlagAssigner::check_and_assign_en_passant_flag() {
    bool is_en_passant = move->to == state->en_passant;
    
    if (is_en_passant) {
        move->set_flag(MoveFlag::EN_PASSANT);
    }
}

void MoveFlagAssigner::check_and_assign_promotion_flag() {
    if (square_on_promotion_row(move->to)) {
        if (move->is_capture()) {
            move->set_flag(MoveFlag::PROMOTION_CAPTURE);
        }
        else {
            move->set_flag(MoveFlag::PROMOTION);
        }
    }
}

bool MoveFlagAssigner::square_on_promotion_row(const Square square) {
    return  (state->is_white_turn() && square_to_row[square] == ROW_8) ||
            (!state->is_white_turn() && square_to_row[square] == ROW_1);
}
