#pragma once

#include "token.hpp"
#include "tag.hpp"

struct Num: Token {
    const int value;
    Num(int value): Token(Tag::NUM), value(value) {}
};
