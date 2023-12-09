#include <iostream>
#include <vector>
#include <fstream> // read file
#include <chrono> // time
#include <thread> // sleep


typedef std::vector<std::vector<bool>> Playboard;

// e) - for ball mode
void updateBallRand(Playboard& board) {
    unsigned int boardSize = board.size();
    unsigned int allowedSize = board[0].size() - 2;
    // reparing first and last buffer-symbols in the real lines
    for (unsigned int lineNum = 1; lineNum < boardSize - 1; lineNum ++) {
        board[lineNum][0] = board[lineNum][allowedSize];
        board[lineNum][allowedSize + 1] = board[lineNum][1];
    }
    // copying the first real line to the last buffer-line
    {
        std::vector<bool> firstLine(board[1]);
        board[boardSize - 1] = firstLine;
    }
    // copying the last real line to the first buffer-line
    {
        std::vector<bool> lastLine(board[boardSize - 2]);
        board[0] = lastLine;
    }
    // reparing the corner cells in buffer
    board[0][0] = board[boardSize - 2][allowedSize];
    board[boardSize - 1][allowedSize + 1] = board[1][1];
    board[0][allowedSize + 1] = board[boardSize - 2][1];
    board[boardSize - 1][0] = board[1][allowedSize];
}

// a)
bool addLine(Playboard& board, const std::string& line, const unsigned int allowedSize, const int borderAlive) {
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
Playboard getPlayboard(const std::string& fileName, const int borderAlive = 0) {
    Playboard board;
    std::ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        std::string line;
        unsigned int allowedSize;
        if (std::getline(file, line)) {
            allowedSize = line.size();
            board.push_back(std::vector<bool> (allowedSize + 2, borderAlive)); // first buffer line (alive / dead)
        } else {
            file.close();
            Playboard emptyBoard{std::vector<bool>{0, 0}, std::vector<bool>{0, 0}}; // empty board + buffer
            return emptyBoard;
        }
        addLine(board, line, allowedSize, borderAlive);
        while (std::getline(file, line)) {
            if (!addLine(board, line, allowedSize, borderAlive)) {
                file.close();
                Playboard emptyBoard{std::vector<bool>{0, 0}, std::vector<bool>{0, 0}}; // empty board + buffer
                return emptyBoard;
            }
        }
        board.push_back(std::vector<bool> (allowedSize + 2, borderAlive)); // last buffer line (alive / dead)
        if (borderAlive == 3) { // for ball-mode
            updateBallRand(board);
        }
    }
    file.close();
    return board;
}


// b)
void updateCell(const Playboard& oldBoard, Playboard& board, const unsigned int lineNum, const int rowNum) {
    int counterAliveNeighbors = 
            ((int) oldBoard[lineNum - 1][rowNum - 1]) + ((int) oldBoard[lineNum - 1][rowNum]) + ((int) oldBoard[lineNum - 1][rowNum + 1]) + 
            ((int) oldBoard[lineNum][rowNum - 1])     +              0                        + ((int) oldBoard[lineNum][rowNum + 1])     + 
            ((int) oldBoard[lineNum + 1][rowNum - 1]) + ((int) oldBoard[lineNum + 1][rowNum]) + ((int) oldBoard[lineNum + 1][rowNum + 1]);    
    if (oldBoard[lineNum][rowNum]) {
        board[lineNum][rowNum] = (counterAliveNeighbors == 2) || (counterAliveNeighbors == 3);
    } else {
        board[lineNum][rowNum] = (counterAliveNeighbors == 3);
    }
}

// b)
void updateBoard(Playboard& board, const int mode = 0) {
    unsigned int boardSize = board.size();
    // deeply copying the board
    Playboard oldBoard(boardSize);
    for (unsigned int i = 0; i < boardSize; i ++) {
        std::vector<bool> lineCopy(board[i]);
        oldBoard[i] = lineCopy;
    }
    // updating cells
    for (unsigned int lineNum = 1; lineNum < boardSize - 1; lineNum ++) { // first and last lines - buffer
        for (unsigned int rowNum = 1; rowNum < board[lineNum].size() - 1; rowNum ++) { // first and last rows - buffer
            updateCell(oldBoard, board, lineNum, rowNum);
        }
    }
    // for ball-mode
    if (mode == 3) {
        updateBallRand(board);
    }
}

// c)
void printBoard(const Playboard& board) {
    for (unsigned int lineNum = 1; lineNum < board.size() - 1; lineNum ++) { // first and last lines - buffer
        for (unsigned int rowNum = 1; rowNum < board[lineNum].size() - 1; rowNum ++) { // first and last rows - buffer
// printint with boarders - for debugging
//    for (unsigned int lineNum = 0; lineNum < board.size(); lineNum ++) {
//        for (unsigned int rowNum = 0; rowNum < board[lineNum].size(); rowNum ++) {
            if (board[lineNum][rowNum])
                std::cout << "0";
            else 
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// d)
int main() {
    std::cout << "(The starting board lives in the file \"fileWithBoard.txt\")" << std::endl;
    std::string hint = "(0 - dead border; 1 - alive boarder; 3 - ball boarder)";
    int boardMode = -1; // 0 - dead border; 1 - alive boarder; 3 - ball boarder 
    std::cout << "Enter the game-mode " << std::endl;
    while ((boardMode < 0) || (boardMode == 2) || (boardMode > 3)) {
        std::cout << hint << std::endl;
        std::cin >> boardMode;
    }
    Playboard board = getPlayboard("fileWithBoard.txt", boardMode);
    while (true) {
        std::cout << "\x1B[2J\x1B[H"; // clear the termiinal
        printBoard(board);
        updateBoard(board, boardMode);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}