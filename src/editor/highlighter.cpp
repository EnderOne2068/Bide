#include "highlighter.hpp"
#include <cctype>
#include <algorithm>

Highlighter::Highlighter() {
    keywords_ = {
        "let", "be", "and", "or", "not",
        "if", "then", "else", "for", "to", "by",
        "while", "do", "until", "repeat", "break",
        "return", "switchon", "case", "default",
        "manifest", "global", "static", "extern",
        "true", "false", "nil", "void"
    };
}

bool Highlighter::isKeyword(const std::string& word) const {
    return keywords_.find(word) != keywords_.end();
}

bool Highlighter::isOperator(char c) const {
    static const std::string ops = "+-*/%()[]{}.,;:=<>!&|~^?";
    return ops.find(c) != std::string::npos;
}

void Highlighter::highlight(const std::string& text, std::vector<uint32_t>& colors) {
    colors.clear();
    colors.resize(text.size(), COLOR_TEXT);

    size_t i = 0;
    while (i < text.size()) {
        if (std::isspace(text[i])) {
            colors[i] = COLOR_TEXT;
            i++;
            continue;
        }

        if (i + 1 < text.size() && text[i] == '/' && text[i + 1] == '/') {
            while (i < text.size()) {
                colors[i] = COLOR_COMMENT;
                i++;
            }
            break;
        }

        if (i + 1 < text.size() && text[i] == '/' && text[i + 1] == '*') {
            colors[i] = COLOR_COMMENT;
            i++;
            continue;
        }

        if (text[i] == '"') {
            colors[i] = COLOR_STRING;
            i++;
            while (i < text.size() && text[i] != '"') {
                if (text[i] == '\\' && i + 1 < text.size()) {
                    colors[i] = COLOR_STRING;
                    i++;
                }
                colors[i] = COLOR_STRING;
                i++;
            }
            if (i < text.size()) {
                colors[i] = COLOR_STRING;
                i++;
            }
            continue;
        }

        if (text[i] == '\'') {
            colors[i] = COLOR_STRING;
            i++;
            if (i < text.size()) {
                colors[i] = COLOR_STRING;
                i++;
            }
            if (i < text.size() && text[i] == '\'') {
                colors[i] = COLOR_STRING;
                i++;
            }
            continue;
        }

        if (std::isdigit(text[i]) || (text[i] == '#' && i + 1 < text.size() && std::isxdigit(text[i + 1]))) {
            while (i < text.size() && (std::isdigit(text[i]) || std::tolower(text[i]) == 'x' || std::isxdigit(text[i]))) {
                colors[i] = COLOR_NUMBER;
                i++;
            }
            continue;
        }

        if (std::isalpha(text[i]) || text[i] == '_') {
            size_t start = i;
            while (i < text.size() && (std::isalnum(text[i]) || text[i] == '_')) {
                i++;
            }
            std::string word = text.substr(start, i - start);
            uint32_t color = isKeyword(word) ? COLOR_KEYWORD : COLOR_IDENTIFIER;
            for (size_t j = start; j < i; j++) {
                colors[j] = color;
            }
            continue;
        }

        if (isOperator(text[i])) {
            colors[i] = COLOR_OPERATOR;
            i++;
            continue;
        }

        i++;
    }
}

uint32_t Highlighter::colorFromRGB(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | b;
}
