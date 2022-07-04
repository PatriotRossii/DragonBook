#pragma once

#include <string>

#include "token.hpp"
#include "tag.hpp"

struct Word: Token {
    const std::string lexeme;
    Word(int t, std::string s): Token(t), lexeme(s) {}
};
