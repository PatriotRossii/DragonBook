#pragma once

#include "tag.hpp"

struct Token {
     const int tag;
     Token(int t): tag(t) { }
};