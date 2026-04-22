#pragma once

#include <vector>
#include "../test_utils.h"
#include "../../move_gen/move.h"
#include "../../game_state/GameState.h"
#include "../../move_gen/MoveGen.h"

struct MoveCreationTestCase {
    Square from;
    Square to;
    Move expected_move;
};

class MoveCreationTester {

public:
    static void test_move_creation();

private:
    static bool validate_case(const MoveCreationTestCase& test_case);

    static std::vector<MoveCreationTestCase> move_creation_test_cases;

    static GameState state;
    static MoveGen move_gen;
    static const std::string FEN;
};