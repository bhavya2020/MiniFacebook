//
// Created by bhavya bansal on 07/02/21.
//

#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <chrono>

class Score {

    std::string user;
    int score;
    int marbles;
    int moves;
    std::chrono::time_point<std::chrono::system_clock> time;

public:

    Score(std::string user, int score, int marbles, int moves);

    Score();

    const std::string &getUser() const;

    void setUser(const std::string &user);

    int getScore() const;

    void setScore(int score);

    int getMarbles() const;

    void setMarbles(int marbles);

    int getMoves() const;

    void setMoves(int moves);

    const std::chrono::time_point<std::chrono::system_clock> &getTime() const;

    void setTime(const std::chrono::time_point<std::chrono::system_clock> &time);

    bool operator==(const Score &) const;

    bool operator!=(const Score &) const;

};


#endif //SCORE_H
