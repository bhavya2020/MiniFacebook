//
// Created by bhavya bansal on 07/02/21.
//

#ifndef BRAIN_VITA_H
#define BRAIN_VITA_H


#include "../enums/BrainVitaMoveDirection.h"

class BrainVita {

    char board[10][10];

    struct Position {

        int x;
        int y;

        Position() = default;

        Position(int x, int y) : x{x}, y{y} {}

    };

    int marbles;

    int moves;

    static void printGridLines(int x, bool withCellNos){
        if(x < 8) {
            if (x < 2 || x >= 6) {
                std::cout << "\t\t\t---|---|---\t\t\t";
                if(withCellNos){
                    std::cout <<"\t\t\t\t\t\t\t   ----|----|----\t\t\t";
                }
            } else {
                std::cout << "---|---|---|---|---|---|---|---|---";
                if(withCellNos){
                    std::cout << "\t\t\t\t----|----|----|----|----|----|----|----|----";
                }
            }
        }
        std::cout<<"\n";
    }

    static bool isValidBoardPosition(int x, int y) {
        if (x < 0 || x >= 9 || y < 0 || y >= 9)
            return false;
        if (x < 3 && y < 3)
            return false;
        if (x < 3 && y >= 6)
            return false;
        if (x >= 6 && y < 3)
            return false;
        if (x >= 6 && y >= 6)
            return false;
        return true;
    }

    static bool isValidBoardPosition(const Position &position) {
        return isValidBoardPosition(position.x, position.y);
    }

    static bool isLastColumn(int x,int y){
        if(x < 3 || x>=6){
            return y>=5;
        }
        return y>=8;
    }

    static const std::map<int, Position> positionCodeMap;

    static std::map<int, Position> createPositionCodeMap() {
        std::map<int, Position> map;
        int code = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (isValidBoardPosition(i, j)) {
                    map[++code] = Position{i, j};
                }
            }
        }
        return map;
    }

    bool isMarblePresent(int code) const {
        if (positionCodeMap.find(code) == positionCodeMap.end())
            return false;
        Position position = positionCodeMap.at(code);
        return board[position.x][position.y] == 'O';
    }

    static std::pair<Position, Position>
    getJumpedAndDestinationPosition(Position source, BrainVitaMoveDirection direction) {
        Position jumped;
        Position destination;
        switch (direction) {
            case UP:
                jumped = Position{source.x - 1, source.y};
                destination = Position{source.x - 2, source.y};
                break;
            case DOWN:
                jumped = Position{source.x + 1, source.y};
                destination = Position{source.x + 2, source.y};
                break;
            case RIGHT:
                jumped = Position{source.x, source.y + 1};
                destination = Position{source.x, source.y + 2};
                break;
            case LEFT:
                jumped = Position{source.x, source.y - 1};
                destination = Position{source.x, source.y - 2};
                break;
        }
        return std::make_pair(jumped, destination);
    }

    bool isValidMove(Position source, BrainVitaMoveDirection direction) const {
        auto positions = getJumpedAndDestinationPosition(source, direction);
        Position jumped = positions.first;
        Position destination = positions.second;
        if (isValidBoardPosition(jumped) && isValidBoardPosition(destination)) {
            if (board[jumped.x][jumped.y] == 'O' && board[destination.x][destination.y] == ' ') {
                return true;
            }
        }
        return false;
    }

public:

    bool isValidMove(int code, BrainVitaMoveDirection direction) const {
        return isValidMove(Position{positionCodeMap.at(code)}, direction);
    }

    BrainVita() : marbles{44}, moves{0} {

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (isValidBoardPosition(i, j)) {
                    board[i][j] = 'O';
                } else {
                    board[i][j] = ' ';
                }
            }
        }

        board[4][4] = ' ';

    }

    void printBoard(bool withCellNos = true) const {
        int code = 1;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (isValidBoardPosition(i, j)) {
                    std::cout << " " << board[i][j] << " ";
                    if(!isLastColumn(i,j)) {
                        std::cout << "|";
                    }
                } else {
                    std::cout << "    ";
                }
            }
            if (withCellNos) {
                std::cout << "\t\t\t\t";
                for (int j = 0; j < 9; ++j) {
                    if (isValidBoardPosition(i, j)) {
                        if (code < 10) {
                            std::cout << " ";
                        }
                        std::cout << " " << code << " ";
                        if(!isLastColumn(i,j)) {
                            std::cout << "|";
                        }
                        ++code;
                    } else {
                        std::cout << "     ";
                    }
                }
            }
            std::cout << "\n";
            printGridLines(i,withCellNos);
        }
    }

    int getCode() const {
        std::cout << "\nWhich marble to move according to the code? ";
        int code;
        while (true) {
            std::cin >> code;
            if (isMarblePresent(code))
                break;
            std::cout << "\nInvalid Code, Enter Again: ";
        }
        return code;
    }

    BrainVitaMoveDirection getDirection() const {
        std::cout << "\nEnter the direction according to code\n1. Up\t 2. Down\t 3. Right\t 4. Left \nEnter code: ";
        return static_cast<BrainVitaMoveDirection>(Choices::getChoice(1, 4));
    };

    void move(int code, BrainVitaMoveDirection direction) {
        Position source = positionCodeMap.at(code);
        auto positions = getJumpedAndDestinationPosition(source, direction);
        Position jumped = positions.first;
        Position destination = positions.second;
        board[source.x][source.y] = ' ';
        board[jumped.x][jumped.y] = ' ';
        board[destination.x][destination.y] = 'O';
        ++moves;
        --marbles;
    }

    bool isGameOver() const {

        if (marbles == 1) {
            return true;
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == 'O') {
                    Position position{i, j};
                    if (isValidMove(position, UP) || isValidMove(position, DOWN) || isValidMove(position, RIGHT) ||
                        isValidMove(position, LEFT)) {
                        return false;
                    }
                }
            }
        }

        return true;

    }

    int getMarbles() const {
        return marbles;
    };

    int getMoves() const {
        return moves;
    };

    int getScore() const {
        int score;
        switch (marbles) {
            case 1:
            case 2:
                score = moves <= 50 ? 10000 : 8000;
                break;
            case 3:
            case 4:
                score = moves <= 50 ? 8000 : 6000;
                break;
            case 5:
            case 6:
                score = moves <= 50 ? 6000 : 4000;
                break;
            case 7:
            case 8:
                score = moves <= 50 ? 4000 : 2000;
                break;
            default:
                score = 1000;
        }
        return score;
    }
};

const std::map<int, BrainVita::Position> BrainVita::positionCodeMap = createPositionCodeMap();


#endif //BRAIN_VITA_H
