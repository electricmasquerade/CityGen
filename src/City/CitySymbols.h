#pragma once

namespace City {
    constexpr char kForward = 'F'; // Move forward
    constexpr char kRight = '+'; // Turn Right
    constexpr char kLeft = '-'; // Turn Left
    constexpr char kPush = '['; // Push current state
    constexpr char kPop = ']'; // Pop current state

    inline bool isCommandSymbol(const char symbol) {
        // Check if the symbol is a command symbol
        return symbol == kForward || symbol == kRight || symbol == kLeft || symbol == kPush || symbol == kPop;
    }
}