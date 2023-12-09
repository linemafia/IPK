#include <iostream>
#include <vector>
#include <fstream> // read file
#include <chrono> // time
#include <thread> // sleep


typedef std::vector<std::vector<bool>> Playboard;

// a)
bool addLine(Playboard& board, const std::string& line, const unsigned int allowedSize, const bool borderAlive) {
    if (line.size() != allowedSize) {
        return false;
    }
    std::vector<bool> boardLine;
    boardLine.push_back(borderAlive); // first cell in line - buffer (alive / dead)
    for (const char i : line) {
        if (i == '0') {
            boardLine.push_back(true);
        } else if (i == ' ') {
            boardLine.push_back(false);
        } else {
            return false;
        }
    }
    boardLine.push_back(borderAlive); // last cell in line - buffer (alive / dead)
    board.push_back(boardLine);
    return true;
}

// a)
Playboard getPlayboard(const std::string& fileName, const bool borderAlive = false) {
    Playboard board;
    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        std::string line;
        unsigned int allowedSize;
        if (std::getline(file, line)) {
            allowedSize = line.size();
            board.push_back(std::vector<bool> (allowedSize, borderAlive)); // first buffer line (alive / dead)
        } else {
            file.close();
            Playboard emptyBoard;
            return emptyBoard;
        }
        addLine(board, line, allowedSize, borderAlive);
        while (std::getline(file, line)) {
            if (!addLine(board, line, allowedSize, borderAlive)) {
                file.close();
                Playboard emptyBoard;
                return emptyBoard;
            }
        }
        board.push_back(std::vector<bool> (allowedSize, borderAlive)); // last buffer line (alive / dead)
    }
    file.close();
    return board;
}


// b)
void updateCell(Playboard& newBoard, const Playboard& board, const unsigned int lineNum, const int rowNum) {
    int counterAliveNeighbors = 
            board[lineNum - 1][rowNum - 1] + board[lineNum - 1][rowNum] + board[lineNum - 1][rowNum + 1] + 
            board[lineNum][rowNum - 1]     +              0             + board[lineNum][rowNum + 1]     + 
            board[lineNum + 1][rowNum - 1] + board[lineNum + 1][rowNum] + board[lineNum + 1][rowNum + 1];
    if (board[lineNum][rowNum]) {
        newBoard[lineNum][rowNum] = (counterAliveNeighbors == 2) || (counterAliveNeighbors == 3);
    } else {
        newBoard[lineNum][rowNum] = (counterAliveNeighbors == 3);
    }
}

// b)
void updateBoard(Playboard& board) {
    Playboard newBoard(board);
    for (unsigned int lineNum = 1; lineNum < board.size() - 1; lineNum ++) { // first and last lines - buffer
        for (unsigned int rowNum = 1; rowNum < board[lineNum].size() - 1; rowNum ++) { // first and last rows - buffer
            updateCell(newBoard, board, lineNum, rowNum);
        }
    }
}

// c)
void printBoard(const Playboard& board) {
    if (board.size() == 0) {
        std::cout << std::endl;
        return;
    }
    for (unsigned int lineNum = 1; lineNum < board.size() - 1; lineNum ++) { // first and last lines - buffer
        for (unsigned int rowNum = 1; rowNum < board[lineNum].size() - 1; rowNum ++) { // first and last rows - buffer
            if (board[lineNum][rowNum])
                std::cout << "0";
            else 
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}


// d)
int main() {
    Playboard board = getPlayboard("fileWithBoard.txt");
    while (true) {
        // std::cout << "x1B[2J\x1B[H"; // clear the termiinal
        printBoard(board);
        updateBoard(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}