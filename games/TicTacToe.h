//
// Created by bhavya bansal on 06/02/21.
//

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H


class TicTacToe {

public:

    enum Result {
        NO_RESULT,
        WINNER,
        LOSER,
        DRAW
    };

private:

    char board[4][4]{};

    struct Position {

        int x;
        int y;

        Position() = default;

        Position(int x, int y) : x{x}, y{y} {}

        static Position getPosition(int code) {
            int count = 1;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (count == code) {
                        return Position{i,j};
                    }
                    ++count;
                }
            }
            return Position{};
        }
    };

    Result result;

    bool verifyCode(int code) {
        if (code < 1 || code > 9) {
            return false;
        }
        Position position = Position::getPosition(code);
        return board[position.x][position.y] == ' ';
    }

public:

    enum Player {
        USER,
        COMPUTER
    };

    TicTacToe() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
        result = NO_RESULT;
    }

    void printBoard(bool withCellNos = true) {

        int count = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << " " << board[i][j];
                if (j < 2) {
                    std::cout << " |";
                }
            }
            if (withCellNos) {
                std::cout << "\t\t\t\t\t\t";
                for (int j = 0; j < 3; ++j) {
                    std::cout << " " << ++count;
                    if (j < 2) {
                        std::cout << " |";
                    }
                }
            }
            if (i < 2) {
                std::cout << "\n---|---|---";
                if (withCellNos) {
                    std::cout << "\t\t\t\t\t\t---|---|---";
                }
            }
            std::cout << "\n";
        }
    }

    bool isGameOver(Player player) {

        Result possibleResult = player == USER ? WINNER : LOSER;

        char ch = player == USER ? 'X' : 'O';

        for (int i = 0; i < 3; ++i) {
            int count = 0;
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ch) {
                    ++count;
                }
            }
            if (count == 3) {
                result = possibleResult;
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            int count = 0;
            for (int j = 0; j < 3; ++j)
                if (board[j][i] == ch)
                    ++count;
            if (count == 3) {
                result = possibleResult;
                return true;
            }
        }
        int count = 0;
        for (int i = 0; i < 3; ++i) {
            if (board[i][i] == ch)
                ++count;
            if (count == 3) {
                result = possibleResult;
                return true;
            }
        }
        count = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                if (i + j == 2) {
                    if (board[i][j] == ch)
                        ++count;
                }
            if (count == 3) {
                result = possibleResult;
                return true;
            }
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        result = DRAW;
        return true;

    }

    void usersTurn() {
        std::cout << "\nYOUR TURN\n\n";
        std::cout << "Enter the position where you want to put cross(X) according to the code:\n\n";
        printBoard();
        std::cout << "\nEnter code: ";
        int code;
        std::cin >> code;
        while (!verifyCode(code)) {
            std::cout << "\nInvalid Code, Enter Again: ";
            std::cin >> code;
        }
        Position position = Position::getPosition(code);
        board[position.x][position.y] = 'X';
    }

    void computersTurn() {

        int code;
        do {
            code = rand() % 9 + 1;
        } while (!verifyCode(code));
        Position position = Position::getPosition(code);
        board[position.x][position.y] = 'O';

    }

    const Result &getResult() {
        return result;
    }
};


#endif //TIC_TAC_TOE_H
