#include "GameBetweenEnginesSimulator.h"
#include <format>

UCIEngineCommunicator GameBetweenEnginesSimulator::uci_communicator1 = UCIEngineCommunicator();
UCIEngineCommunicator GameBetweenEnginesSimulator::uci_communicator2 = UCIEngineCommunicator();

GameState GameBetweenEnginesSimulator::state = GameState();
MoveGen GameBetweenEnginesSimulator::move_gen = MoveGen(&state);
MoveLegalizer* GameBetweenEnginesSimulator::move_legalizer;

GameBetweenEngines GameBetweenEnginesSimulator::game_between_engines = {
    "ADOCE V3.1", "D:\\My Projects\\Chess Engine and GUI\\engine\\engine_versions\\engine_v3.1.exe",
    "ADOCE V3.2", "D:\\My Projects\\Chess Engine and GUI\\engine\\engine_versions\\engine_v3.2.exe",
    100
};


void GameBetweenEnginesSimulator::simulate_games_and_print_results() {
    state = GameState();
    move_gen = MoveGen(&state);
    move_legalizer = new MoveLegalizer(&state, move_gen);

    SimulationResults results = simulate_multiple_games_between_engines(game_between_engines);
    print_results(results);

    uci_communicator1.end_process();
    uci_communicator2.end_process();
}

SimulationResults GameBetweenEnginesSimulator::simulate_multiple_games_between_engines(
        const GameBetweenEngines& game)
{
    uci_communicator1.end_process();
    uci_communicator2.end_process();

    try {
        uci_communicator1.start_uci_engine(game.path_to_engine1);
        uci_communicator2.start_uci_engine(game.path_to_engine2);
    } catch (const UCIEngineException& e) {
        Logger::log(e.what());
        return SimulationResults();
    }

    SimulationResults results = SimulationResults();
    results.engine1_name = game.engine1_name;
    results.engine2_name = game.engine2_name;
    
    auto start_time = std::chrono::high_resolution_clock::now();

    
    for (int i = 0; i < game.games_to_simulate; i++) {
        int fair_position_index = randi_range(0, fair_positions.size() - 1);
        
        uci_communicator1.send_command("ucinewgame");
        uci_communicator2.send_command("ucinewgame");
        
        std::string fen = fair_positions[fair_position_index % fair_positions.size()];
        Logger::log("New game with fen " + fen);
        
        FenLoader::load_fen(&state, fen);
        ZobristHasher::set_zobrist_key_of_state(state);
        
        Colour winner = simulate_single_game(game, fen);
        results.total_games++;
        
        switch (winner) {
            case WHITE: 
                Logger::log(std::format("Game {}/{} ended. Winner: WHITE.", i + 1, game.games_to_simulate));
                results.wins++;
                break;
            case BLACK: 
                Logger::log(std::format("Game {}/{} ended. Winner: BLACK.", i + 1, game.games_to_simulate));
                results.loses++;
                break;
            case COLOUR_NONE: 
                Logger::log(std::format("Game {}/{} ended. Winner: DRAW.", i + 1, game.games_to_simulate));
                results.draws++;
                break;
            default:
                break;
        }
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    results.duration = duration;

    return results;
}

Colour GameBetweenEnginesSimulator::simulate_single_game(const GameBetweenEngines& game, const std::string starting_fen) {
    while (true) {
        move_legalizer->calculate_pins_and_checks();

        GameOverType game_over = GameOverChecker::check_game_over(state);

        if (game_over != GAME_OVER_NONE) {
            Colour winner = game_over_type_to_winner_colour[game_over];
            Logger::log("GAME OVER: " + game_over_messages[game_over]);
            Logger::log("TURN: " + std::to_string(!state.turn));
            return winner;
        }
        
        UCIEngineCommunicator& curr_uci_communicator = state.is_white_turn() ? uci_communicator1 : uci_communicator2;

        if (true) {
            curr_uci_communicator.send_command("position fen " + StateToFenConverter::game_state_to_fen(&state));
        }
        else {
            std::string str_moves_history = state.convert_moves_history_to_str();
            std::string uci_command = "position fen " + starting_fen;

            if (!str_moves_history.empty()) {
                uci_command += " moves " + str_moves_history;
            }
        
            curr_uci_communicator.send_command(uci_command);
        }

        // TODO: duplicated code from gui/src/move_manager
        /*std::string best_lan_move = curr_uci_communicator.find_best_move(100);

        Move best_move = lan_notation_to_move(best_lan_move);
        PieceType promotion_piece_type = best_move.promotion_piece_type;
        
        best_move = move_gen.create_move(best_move.from, best_move.to);
        best_move.promotion_piece_type = promotion_piece_type;
        
        MoveExecutor::do_move(best_move, &state);*/
    }
}


void GameBetweenEnginesSimulator::print_results(const SimulationResults& results) {
    Logger::log(std::format("Games finished in {}ms", results.duration));
    Logger::log(std::format("Engines: {} vs. {}", results.engine1_name, results.engine2_name));
    Logger::log(std::format("Total games: {}", results.total_games));

    if (results.total_games == 0) {
        return;
    }

    Logger::log(std::format("Wins: {} - {}%", results.wins, 100 * results.wins / results.total_games));
    Logger::log(std::format("Draws: {} - {}%", results.draws, 100 * results.draws / results.total_games));
    Logger::log(std::format("Loses: {} - {}%", results.loses, 100 * results.loses / results.total_games));
}

