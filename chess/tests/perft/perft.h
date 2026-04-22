#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <unordered_set>

#include "../test_utils.h"
#include "../../utils/utils.h"

#include "../../game_state/GameState.h"
#include "../../move_gen/MoveGen.h"
#include "../../move_executor/MoveExecutor.h"

struct PerftTestCase {
    std::string starting_fen;
    int depth;
    int expected_positions_count;
};

class PerftTester {

public:
    static void test_perft();

private:
    static bool validate_case(const PerftTestCase& test_case);
    static int perft(GameState& state, const int depth, const int initial_depth);

    static std::vector<PerftTestCase> perft_test_cases;
    
    static int collisions_count;
    static int positions_searched;
    static std::unordered_set<uint64_t> zobrist_keys;
};