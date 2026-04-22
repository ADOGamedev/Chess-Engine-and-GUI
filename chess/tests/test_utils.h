#pragma once

#include <bitset>
#include "../utils/utils.h"
#include "../logger/Logger.h"

template <typename T, std::size_t N>
bool assert_and_print(const std::string& name, const std::array<T, N>& value, const std::array<T, N>& expected) {
    if (value != expected) {
        Logger::log(name + ": " + arr_to_str(value) + " expected " + arr_to_str(expected));
        return false;
    }

    return true;
}

template <typename T>
bool assert_and_print(const std::string& name, const T& value, const T& expected) {
    if (value != expected) {
        Logger::log(name + ": " + std::to_string(value) + " expected " + std::to_string(expected));
        return false;
    }

    return true;
}

inline bool assert_and_print(const std::string& name, const int value, const int expected) {
    if (value != expected) {
        Logger::log(name + ": " + std::to_string(static_cast<int>(value)) + " expected " + std::to_string(static_cast<int>(expected)));
        return false;
    }

    return true;
}

template <std::size_t N>
inline bool assert_and_print(const std::string& name, const std::bitset<N> value, const std::bitset<N> expected) {
    if (value != expected) {
        Logger::log(name + ": " + value.to_string() + " expected " + expected.to_string());
        return false;
    }

    return true;
}