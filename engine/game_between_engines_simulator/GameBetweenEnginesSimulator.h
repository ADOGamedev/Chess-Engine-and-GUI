#pragma once

#include <format>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../../chess/game_state/GameState.h"
#include "../../chess/game_over_checker/GameOverChecker.h"
#include "../../chess/fen_loader/FenLoader.h"
#include "../../chess/fen_loader/StateToFenConverter.h"
#include "../../chess/move_executor/MoveExecutor.h"
#include "../uci_engine_communicator/UCIEngineCommunicator.h"

#include "fair_positions/fair_positions.h"

struct SimulationResults {
    std::string engine1_name;
    std::string engine2_name;

    int duration = 0;
    int total_games = 0;
    int wins = 0;
    int draws = 0;
    int loses = 0;
};

struct GameBetweenEngines {
    std::string engine1_name;
    std::string path_to_engine1;

    std::string engine2_name;
    std::string path_to_engine2;

    int games_to_simulate;
};  

class GameBetweenEnginesSimulator {

public:
    static void simulate_games_and_print_results();

private:
    static SimulationResults simulate_multiple_games_between_engines(const GameBetweenEngines& game);
    static Colour simulate_single_game(const GameBetweenEngines& game, const std::string starting_fen);

    static void print_results(const SimulationResults& results);

    static UCIEngineCommunicator uci_communicator1;
    static UCIEngineCommunicator uci_communicator2;

    static GameBetweenEngines game_between_engines;
    static GameState state;
    static MoveGen move_gen;
    static MoveLegalizer* move_legalizer;
};