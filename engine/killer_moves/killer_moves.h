#pragma once

#include "../../chess/move_gen/Move.h"
#include "../constants/constants.h"

namespace KillerMoves {
    

inline MovesArray<KILLERS_PER_PLY> moves[PLY_COUNT];

inline void insert_killer(const Move& killer, const int& ply) {
    if (killer == moves[ply].array[0]) {
        return;
    }
    moves[ply].array[1] = moves[ply].array[0];
    moves[ply].array[0] = killer;
}

inline MovesArray<KILLERS_PER_PLY> get_killers(const int& ply) {
    return moves[ply];
}


}
