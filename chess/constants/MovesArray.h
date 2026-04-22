#pragma once

#include <cstring>

#include "../move_gen/Move.h"

template <int N>
struct MovesArray {
    static constexpr int MAX_SIZE = N;
    int count = 0;
    Move array[N];

    void push(const Move& new_move) {
        array[count] = new_move;
        count++;
    }

    MovesArray() = default;
    MovesArray(const MovesArray& other) {
        count = other.count;
        if (count > 0) {
            std::memcpy(array, other.array, count * sizeof(Move));
        }
    }

    MovesArray& operator=(const MovesArray& other) {
        if (this != &other) {
            count = other.count;
            if (count > 0) {
                std::memcpy(array, other.array, count * sizeof(Move));
            }
        }
        return *this;
    }

    void insert_back(const Move* from, const Move* to) {
        int added = to - from;
        std::memcpy(array + count, from, added * sizeof(Move));
        count += added;
    }

    const Move* begin() const { return array; }
    const Move* end() const { return array + count; }

    Move* begin() { return array; }
    Move* end() { return array + count; }

};