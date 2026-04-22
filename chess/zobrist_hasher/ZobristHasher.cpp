#include "ZobristHasher.h"

uint64_t ZobristHasher::piece_square_zobrist_values[N_PIECES][N_SQUARES] = {};
uint64_t ZobristHasher::black_to_move_zobrist_value = 0ULL;
uint64_t ZobristHasher::castling_rights_zobrist_values[N_CASTLINGS] = {};
uint64_t ZobristHasher::en_passant_zobrist_values[N_COLUMNS] = {};
RandUint64Gen ZobristHasher::rand_uint64_gen(ZobristHasher::ZOBRIST_SEED);

void ZobristHasher::initialize_zobrist_values() {
    initialize_pieces_squares_zobrist_values();
    initialize_black_to_move_zobrist_value();
    initialize_castling_rights_zobrist_values();
    initialize_en_passants_zobrist_values();
}

void ZobristHasher::initialize_pieces_squares_zobrist_values() {
    for (Piece piece = WHITE_PAWN; piece < N_PIECES; piece++) {
        for (Square square = SQ_0; square < N_SQUARES; square++) {
            piece_square_zobrist_values[piece][square] = rand_uint64_gen.get_next_random_number();
        }
    }
}

void ZobristHasher::initialize_black_to_move_zobrist_value() {
    black_to_move_zobrist_value = rand_uint64_gen.get_next_random_number();
}

void ZobristHasher::initialize_castling_rights_zobrist_values() {
    for (Castling castling = WHITE_SHORT_CASTLING; castling < N_CASTLINGS; castling++) {
        castling_rights_zobrist_values[castling] = rand_uint64_gen.get_next_random_number();
    }
}

void ZobristHasher::initialize_en_passants_zobrist_values() {
    for (Column column = COLUMN_1; column < N_COLUMNS; column++) {
        en_passant_zobrist_values[column] = rand_uint64_gen.get_next_random_number();
    }
}


void ZobristHasher::set_zobrist_key_of_state(GameState& state) {
    state.key = get_pieces_square_zobrist_key(state) ^
                get_turn_zobrist_key(state.turn) ^
                get_castlings_zobrist_key(state.castling_rights) ^
                get_en_passant_zobrist_key(state.en_passant);
}

uint64_t ZobristHasher::get_pieces_square_zobrist_key(GameState& state) {
    uint64_t key = 0ULL;

    for (Square square = SQ_0; square < N_SQUARES; square++) {
        Piece piece = state.get_piece_at(square);

        if (piece != PIECE_NONE) {
            key ^= piece_square_zobrist_values[piece][square];
        }
    }

    return key;
}

uint64_t ZobristHasher::get_turn_zobrist_key(const Colour turn) {
    return turn == WHITE ? 0ULL : black_to_move_zobrist_value;
}

uint64_t ZobristHasher::get_castlings_zobrist_key(const std::array<bool, N_CASTLINGS>& castling_rights) {
    uint64_t key = 0ULL;

    for (Castling castling = WHITE_SHORT_CASTLING; castling < N_CASTLINGS; castling++) {
        if (castling_rights[castling]) {
            key ^= castling_rights_zobrist_values[castling];
        }
    }

    return key;
}

uint64_t ZobristHasher::get_en_passant_zobrist_key(const Square en_passant_square) {
    if (en_passant_square == SQ_NONE) {
        return 0ULL;
    }

    Column en_passant_column = square_to_column[en_passant_square];
    return en_passant_zobrist_values[en_passant_column];
}