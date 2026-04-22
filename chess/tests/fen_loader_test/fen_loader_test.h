#pragma once

#include <array>
#include <vector>
#include <string>

#include "../../utils/utils.h"
#include "../test_utils.h"
#include "../../game_state/GameState.h"
#include "../../fen_loader/FenLoader.h"


struct FenTestCase {
    std::string fen;
    Colour turn;
    std::array<bool, N_CASTLINGS> castling_rights;
    Square en_passant;
    int fifty_moves_rule_counter;
    bool expect_exception;
};

class FenLoaderTester {

public:
    static void test_fen_loader();

private:
    static bool validate_case(const FenTestCase& test_case);

    static std::vector<FenTestCase> fen_test_cases;
};


