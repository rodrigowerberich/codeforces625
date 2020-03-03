#pragma once

#include <iostream>

struct PreviousLetter{
    bool valid;
    char previous;
    constexpr PreviousLetter(char letter):
        valid{(letter != 'a')},
        previous{static_cast<char>(letter-1)}{}
};

std::ostream& operator <<(std::ostream& os, const PreviousLetter& previousLetter);
