#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

// Color definitions (RGB)
#define COLOR_TEXT       0xFFFFFF  // White
#define COLOR_KEYWORD    0xFF6B9D  // Pink
#define COLOR_IDENTIFIER 0xE0E0E0  // Light gray
#define COLOR_STRING     0x98C379  // Green
#define COLOR_NUMBER     0xD19A66  // Orange
#define COLOR_COMMENT    0x5C6C7C  // Gray-blue
#define COLOR_OPERATOR   0x56B6C2  // Cyan

struct TextLine;

class Highlighter {
public:
    Highlighter();
    ~Highlighter() = default;

    void highlight(const std::string& text, std::vector<uint32_t>& colors);

    static uint32_t colorFromRGB(uint8_t r, uint8_t g, uint8_t b);

private:
    std::unordered_set<std::string> keywords_;

    bool isKeyword(const std::string& word) const;
    bool isOperator(char c) const;
};
