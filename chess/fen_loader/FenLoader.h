#pragma once

#include <exception>
#include <sstream>

#include "../game_state/GameState.h"
#include "../move_gen/MoveLegalizer.h"

class GameState;


namespace FenElement {

enum FenElement : uint8_t {
    BOARD,
    TURN,
    CASTLING_RIGHTS,
    EN_PASSANT,
    FIFTY_MOVES_RULE_COUNTER,
    FULL_MOVES,

    N_FEN_ELEMENTS
};
};

class FenLoader {

public:
    static void load_fen(GameState* game_state, std::string fen_str);

private:
    static std::array<std::string, FenElement::N_FEN_ELEMENTS> get_split_fen();

    static void load_board();
    static void load_turn();
    static void load_castling_rights();
    static void load_en_passant();
    static void load_fifty_moves_rule_counter();

    static Piece char_to_piece(const char ch);
    static Castling char_to_castling(const char ch);
    static Square fen_en_passant_to_square(const std::string fen_en_passant);
    static bool is_valid_en_passant_position(const int column, const int row);

    static GameState* state;
    static std::string fen;
    static std::array<std::string, FenElement::N_FEN_ELEMENTS> fen_elements;
};


class FenException : public std::exception {

private:
    std::string message;

public:
    FenException(const std::string msg) 
        : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidElementsInFenRowException : public FenException {
public:
    InvalidElementsInFenRowException()
        : FenException("FEN contains an invalid amount of elements in a row!") {};
};

class InvalidFenPieceCharException : public FenException {
    public:
    InvalidFenPieceCharException()
    : FenException("FEN contains an invalid piece char!") {};
};

class InvalidFenCastlingTypeException : public FenException {
public:
    InvalidFenCastlingTypeException()
        : FenException("FEN contains an invalid castling type!") {};
};

class InvalidFenTurnException : public FenException {
public:
    InvalidFenTurnException()
        : FenException("FEN contains an invalid letter in turn field!") {};
};

class InvalidFenEnPassantException : public FenException {
public:
    InvalidFenEnPassantException()
        : FenException("FEN contains an invalid square in en passant field!") {};
};

class InvalidElementsInFenBoardException : public FenException {
public:
    InvalidElementsInFenBoardException()
        : FenException("FEN contains an invalid amount of elements in the board!") {};
};

class BothKingsNotFoundInFenException : public FenException {
public:
    BothKingsNotFoundInFenException()
        : FenException("FEN does not contain both kings!") {};
};

