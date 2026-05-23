#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

class Highlighter;

struct TextLine {
    std::string text;
    std::vector<uint32_t> colors;  // Color for each character
};

class Editor {
public:
    Editor();
    ~Editor();

    // File operations
    bool loadFile(const std::string& filename);
    bool saveFile(const std::string& filename);
    const std::string& getFilename() const { return filename_; }
    bool isDirty() const { return dirty_; }
    void setDirty(bool dirty) { dirty_ = dirty; }

    // Text operations
    void insertChar(int line, int col, char c);
    void deleteChar(int line, int col);
    void insertLine(int line, const std::string& text);
    void deleteLine(int line);
    void insertText(int line, int col, const std::string& text);
    std::string getLine(int line) const;
    std::string getSelection() const;

    // Navigation
    int getLineCount() const { return lines_.size(); }
    int getLineLength(int line) const;
    void setCursorPos(int line, int col);
    void getCursorPos(int& line, int& col) const;
    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorHome();
    void moveCursorEnd();
    void moveCursorPageUp();
    void moveCursorPageDown();

    // Selection
    void selectAll();
    void clearSelection();
    bool hasSelection() const { return sel_start_ != sel_end_; }
    void getSelection(int& sline, int& scol, int& eline, int& ecol) const;

    // Undo/Redo
    void undo();
    void redo();
    bool canUndo() const;
    bool canRedo() const;

    // Syntax highlighting
    uint32_t getCharColor(int line, int col) const;
    void updateHighlight();

    // Viewport
    void setViewport(int width, int height) { view_width_ = width; view_height_ = height; }
    void getViewport(int& width, int& height) const { width = view_width_; height = view_height_; }
    int getScrollLine() const { return scroll_line_; }
    int getScrollCol() const { return scroll_col_; }
    void setScrollLine(int line);
    void setScrollCol(int col);

    // Get rendered lines for display
    const TextLine& getDisplayLine(int line) const;

private:
    std::vector<TextLine> lines_;
    std::string filename_;
    bool dirty_;
    int cursor_line_, cursor_col_;
    int sel_start_, sel_end_;
    int scroll_line_, scroll_col_;
    int view_width_, view_height_;
    std::unique_ptr<Highlighter> highlighter_;
    std::vector<std::vector<TextLine>> undo_stack_;
    std::vector<std::vector<TextLine>> redo_stack_;

    void recordUndo();
};
