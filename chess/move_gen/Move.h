#pragma once

#include <cstdint>
#include "../constants/constants.h"


enum MoveFlag : uint8_t {
    NORMAL, 
    DOUBLE_PAWN_PUSH,
    
    CAPTURE,
    EN_PASSANT,
    
    SHORT_CASTLE,
    LONG_CASTLE,
    
    PROMOTION,
    PROMOTION_CAPTURE,
};

class Move {
    
public:
    Move() = default;
    Move(Square from, Square to, MoveFlag flag = MoveFlag::NORMAL) :
        from(from), to(to), flag(flag) {}
    
    void set_flag(const MoveFlag move_flag) {flag = move_flag;}
    
    bool is_promotion() const;
    bool is_capture() const;
    bool is_en_passant() const;
    bool is_double_pawn_push() const;

    bool is_castle() const;
    bool is_short_castle() const;
    bool is_long_castle() const;
    
    bool is_valid() const;
    
    bool operator==(const Move& move) const {
        return from == move.from && to == move.to;
    }
    
    Square from = SQ_0;
    Square to = SQ_0;
    MoveFlag flag = MoveFlag::NORMAL;

    Square prev_en_passant = SQ_NONE;
    Square prev_en_passant_capture = SQ_NONE;
    std::array<bool, N_CASTLINGS> prev_castling_rights;
    int prev_fifty_moves_rule_counter = 0;
    
    Piece moved_piece = PIECE_NONE;
    PieceType promotion_piece_type = PIECE_TYPE_NONE;
    Piece captured_piece = PIECE_NONE;
};

const Move castling_moves_for_rook[N_CASTLINGS] = {
    Move( SQ_7,  SQ_5),
    Move( SQ_0,  SQ_3),
    Move(SQ_63, SQ_61),
    Move(SQ_56, SQ_59)
};
