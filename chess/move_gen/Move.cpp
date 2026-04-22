#include "Move.h"

bool Move::is_promotion() const {
    return flag == MoveFlag::PROMOTION || flag == MoveFlag::PROMOTION_CAPTURE;
}

bool Move::is_capture() const {
    return flag == MoveFlag::CAPTURE || flag == MoveFlag::PROMOTION_CAPTURE;
}

bool Move::is_en_passant() const {
    return flag == MoveFlag::EN_PASSANT;
}

bool Move::is_double_pawn_push() const {
    return flag == MoveFlag::DOUBLE_PAWN_PUSH;
}

bool Move::is_castle() const {
    return flag == MoveFlag::SHORT_CASTLE || flag == MoveFlag::LONG_CASTLE;
}  

bool Move::is_long_castle() const {
    return flag == MoveFlag::LONG_CASTLE;
}  

bool Move::is_short_castle() const {
    return flag == MoveFlag::SHORT_CASTLE;
}   

bool Move::is_valid() const {
    return from != to;
}