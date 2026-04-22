#include "fen_loader_test.h"


std::vector<FenTestCase> FenLoaderTester::fen_test_cases = {
    {
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        WHITE,
        { true, true, true, true },
        SQ_NONE,
        0,
        false
    },
    {
        "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
        WHITE,
        { true, true, true, true },
        SQ_NONE,
        0,
        false
    },
    {
        "r1bq1rk1/pppp1ppp/2n2n2/4p3/2B1P3/2NP1N2/PPP2PPP/R1BQ1RK1 w - - 6 7",
        WHITE,
        { false, false, false, false },
        SQ_NONE,
        6,
        false
    },
    {
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR/8 w KQkq - 0 1",
        WHITE,
        { false, false, false, false },
        SQ_NONE,
        0,
        true
    },
    {
        "rnbqkbnr/ppppxppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        WHITE,
        { false, false, false, false },
        SQ_NONE,
        0,
        true
    },
    {
        "8/8/8/8/8/8/8/8 w - - 50 99",
        WHITE,
        { false, false, false, false },
        SQ_NONE,
        50,
        true
    },
    {
        "r3k2r/8/8/8/8/8/8/R3K2R w KQ - 0 1",
        WHITE,
        { true, true, false, false },
        SQ_NONE,
        0,
        false
    },
    {
        "r3k2r/8/8/8/8/8/8/R3K2R b kq - 0 1",
        BLACK,
        { false, false, true, true },
        SQ_NONE,
        0,
        false
    },
    {
        "r3k2r/8/8/8/8/8/8/R3K2R b kq m1 0 1",
        BLACK,
        { false, false, true, true },
        SQ_NONE,
        0,
        true
    },
    {
        "r3k3r/8/8/8/8/8/8/R3K2R b kq - 0 1",
        BLACK,
        { false, false, true, true },
        SQ_NONE,
        0,
        true
    },
    {
        "r3k2r/8/8/8/8/8/8/R3K2R b hg - 0 1",
        BLACK,
        { false, false, false, false },
        SQ_NONE,
        0,
        true
    },
    {
        "r3k2r/8/8/8/8/8/8/R3K2R l kq - 0 1",
        BLACK,
        { false, false, false, false },
        SQ_NONE,
        0,
        true
    },
    {
        "r3k2r/8/8/8/8/8/8/R3K2R w kq c3 0 1",
        WHITE,
        { false, false, true, true },
        SQ_18,
        0,
        false
    },
    {
        "r3k2r/6P1/8/4Pp2/8/1p6/P7/R3K2R w KQkq f6 0 1",
        WHITE,
        { true, true, true, true },
        SQ_45,
        0,
        false
    },
    {
        "r3k2r/6P1/8/4Pp2/8/1p6/P7/R3K2R w KQkq k f6a 0 1",
        WHITE,
        { true, true, true, true },
        SQ_NONE,
        0,
        true
    }
};

void FenLoaderTester::test_fen_loader() {
    int test_cases_count = fen_test_cases.size();
    int passed_tests_count = 0;

    for (FenTestCase test_case : fen_test_cases) {
        bool test_passed = validate_case(test_case);

        if (test_passed) {
            passed_tests_count++;

            std::string message = "Passed test! " + std::to_string(passed_tests_count) + "/" + std::to_string(test_cases_count);
            Logger::log(message);
        }

        Logger::log("-------------------------------------");
    }
}

bool FenLoaderTester::validate_case(const FenTestCase& test_case) {
    GameState state = GameState();

    bool test_passed = true;

    Logger::log("Fen: " + test_case.fen);

    try {
        FenLoader::load_fen(&state, test_case.fen);
    }
    catch (const FenException& e) {
        if (!test_case.expect_exception) {
            Logger::log("Unexpected exception");
            
            test_passed = false;
        }
        return test_passed;
    }
        
    if (!assert_and_print("Turn", state.turn, test_case.turn) ||
        !assert_and_print("Castling rights", state.castling_rights, test_case.castling_rights) ||
        !assert_and_print("En passant", state.en_passant, test_case.en_passant) ||
        !assert_and_print("Fifty moves rule counter", state.fifty_moves_rule_counter, test_case.fifty_moves_rule_counter)) {
            test_passed = false;
    }
        
    if (test_case.expect_exception) {
        Logger::log("Expected exception but no excepition");

        test_passed = false;
    }

    return test_passed;

}

