#include "move_creation_test.h"

std::vector<MoveCreationTestCase> MoveCreationTester::move_creation_test_cases = {
    { SQ_8, SQ_16, Move( SQ_8, SQ_16, MoveFlag::NORMAL)},
    { SQ_8, SQ_24, Move( SQ_8, SQ_24, MoveFlag::DOUBLE_PAWN_PUSH)},
    { SQ_8, SQ_17, Move( SQ_8, SQ_17, MoveFlag::CAPTURE)},
    {SQ_36, SQ_45, Move(SQ_36, SQ_45, MoveFlag::EN_PASSANT)},
    { SQ_4,  SQ_6, Move( SQ_4,  SQ_6, MoveFlag::SHORT_CASTLE)},
    {SQ_60, SQ_62, Move(SQ_60, SQ_62, MoveFlag::SHORT_CASTLE)},
    { SQ_4,  SQ_2, Move( SQ_4,  SQ_2, MoveFlag::LONG_CASTLE)},
    {SQ_60, SQ_58, Move(SQ_60, SQ_58, MoveFlag::LONG_CASTLE)},
    {SQ_54, SQ_62, Move(SQ_54, SQ_62, MoveFlag::PROMOTION)},
    {SQ_54, SQ_63, Move(SQ_54, SQ_63, MoveFlag::PROMOTION_CAPTURE)}
};

const std::string MoveCreationTester::FEN = "r3k2r/6P1/8/4Pp2/8/1p6/P7/R3K2R w KQkq f6 0 1";

GameState MoveCreationTester::state;
MoveGen MoveCreationTester::move_gen(&MoveCreationTester::state);

void MoveCreationTester::test_move_creation() {
    try {
        FenLoader::load_fen(&state, FEN);
    }
    catch (const FenException& e) {}

    int test_cases_count = move_creation_test_cases.size();
    int passed_tests_count = 0;

    for (MoveCreationTestCase test_case : move_creation_test_cases) {
        bool test_passed = validate_case(test_case);

        if (test_passed) {
            passed_tests_count++;

            std::string message = "Passed test! " + std::to_string(passed_tests_count) + "/" + std::to_string(test_cases_count);
            Logger::log(message);
        }

        Logger::log("-------------------------------------");
    }
}

bool MoveCreationTester::validate_case(const MoveCreationTestCase& test_case) {
    Move move = move_gen.create_move(test_case.from, test_case.to);
    bool test_passed = true;

    Logger::log("Move: " + std::to_string(test_case.from) + ", " + std::to_string(test_case.to));

    if (!assert_and_print("From", move.from, test_case.expected_move.from) ||
        !assert_and_print("To",   move.to,   test_case.expected_move.to  ) ||
        !assert_and_print("Flag", move.flag, test_case.expected_move.flag)) {
            test_passed = false;
    }

    return test_passed;
}