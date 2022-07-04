#pragma once

#include <unordered_map>
#include <sstream>
#include <string>
#include <cctype>
#include <stdio.h>

#include "tag.hpp"
#include "word.hpp"
#include "num.hpp"
#include "token.hpp"

class Lexer {
    char peek = ' ';
    bool isComment = false;
    bool isMultilineComment = false;
    std::unordered_map<std::string, Word> words;

    void reserve(Word t) {
        words.emplace(t.lexeme, t);
    }
public:
    int line = 1;

    Lexer() {
        reserve(Word(Tag::TRUE, "true"));
        reserve(Word(Tag::FALSE, "false"));
    }

    Token scan() {
        for(; ; peek = getchar()) {
            if(isMultilineComment || isComment || peek == ' ' || peek == '\t') continue;
            else if(peek == '\n') {
                isComment = false;
                line = line + 1;
            }
            else break;
        }

        if(std::isdigit(peek)) {
            int v = 0;
            do {
                v = 10 * v + (peek - '0');
                peek = getchar();
            } while (std::isdigit(peek)) ;
            return Num(v);
        }
        else if(std::isalpha(peek)) {
            std::ostringstream buffer;
            do {
                buffer << peek;
                peek = getchar();
            } while (std::isalnum(peek)) ;

            std::string s = buffer.str();
            auto [w, inserted] = words.emplace(s, Word(Tag::ID, s));
            if(inserted == false) {
                return w->second;
            }
        }
        else if(peek == '/') {
            char nextCharacter = getchar();
            if(nextCharacter == '/') {
                isComment = true;
            } else if(nextCharacter == '*') {
                isMultilineComment = true;
            }
        }
        else if(peek == '*') {
            char nextCharacter = getchar();
            if(nextCharacter == '/') {
                isMultilineComment = false;
            }
        } else if(peek == '<') {
            char nextCharacter = getchar();
            if(nextCharacter == '=') {
                return Token(Tag::LESS_OR_EQUAL);
            }
            return Token(Tag::LESS);
        } else if(peek == '=') {
            char nextCharacter = getchar();
            if(nextCharacter == '=') {
                return Token(Tag::EQUAL);
            }
        } else if(peek == '!') {
            char nextCharacter = getchar();
            if(nextCharacter == '=') {
                return Token(Tag::NOT_EQUAL);
            }
        } else if(peek == '>') {
            char nextCharacter = getchar();
            if(nextCharacter == '=') {
                return Token(Tag::GREATER_OR_EQUAL);
            }
            return Token(Tag::GREATER);
        }


        Token t = Token(peek);
        peek = ' ';
        return t;
    }
};