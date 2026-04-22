#include "constants/constants.h"
#include "utils/utils.h"
#include "tests/fen_loader_test/fen_loader_test.h"
#include "tests/game_over_check_test/game_over_check_test.h"
#include "tests/move_creation_test/move_creation_test.h"
#include "tests/perft/perft.h"
#include "tests/zobrist_collisions_test/ZobristCollisionsTester.h"

#include "../engine/game_between_engines_simulator/GameBetweenEnginesSimulator.h"
#include "../engine/tests/board_eval_test/BoardEvalTester.h"

int main() {
	Logger::Logger logger = Logger::Logger();
	Logger::set_logger(&logger);

	GameBetweenEnginesSimulator::simulate_games_and_print_results();

	std::cin.get();
}