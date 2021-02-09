//
// Created by bhavya bansal on 07/02/21.
//

#include "../Score.h"

#include <utility>

Score::Score(std::string user, int score, int marbles, int moves) : user{std::move(user)}, score{score},
                                                                               marbles{marbles}, moves{moves}{
    time = std::chrono::system_clock::now();
}

const std::string &Score::getUser() const {
    return user;
}

void Score::setUser(const std::string &user) {
    Score::user = user;
}

int Score::getScore() const {
    return score;
}

void Score::setScore(int score) {
    Score::score = score;
}

int Score::getMarbles() const {
    return marbles;
}

void Score::setMarbles(int marbles) {
    Score::marbles = marbles;
}

int Score::getMoves() const {
    return moves;
}

void Score::setMoves(int moves) {
    Score::moves = moves;
}

const std::chrono::time_point<std::chrono::system_clock> &Score::getTime() const {
    return time;
}

void Score::setTime(const std::chrono::time_point<std::chrono::system_clock> &time) {
    Score::time = time;
}

bool Score::operator==(const Score &score) const {
    return this->getTime() == score.getTime() && this->getMoves() == score.getMoves() && this->getMarbles() == score.getMarbles() &&
            this->getScore() == score.getScore() && this->getUser() == score.getUser();
}

bool Score::operator!=(const Score &score) const {
    return !(score == *this);
}

Score::Score() = default;
