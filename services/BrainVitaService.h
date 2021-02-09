//
// Created by bhavya bansal on 07/02/21.
//

#ifndef BRAIN_VITA_SERVICE_H
#define BRAIN_VITA_SERVICE_H


#include "../dao/ScoreDao.h"

class BrainVitaService {

    ScoreDao scoreDao;

    static void showRules() {
        std::cout
                << "\n\t\t\t\t\t\t\tHOW TO PLAY\n\n\n1. Choose a marble according to given code and a direction from the given options.\n\n2. Move a marble over another right next to it (horizontally/vertically) to an empty space.\n\n3. The piece that is jumped over is removed.\n\n4. Your motive is to remove most marbles.\n\n\nSo are you ready to play!!\n\n";
    }

    void play(const Person &user) {
        BrainVita brainVita{};
        while (true) {
            bool quit = false;
            std::cout << "\n\t\t\t\t\t\t\t\t\tPLAY BRAIN VITA\n\n\n";
            brainVita.printBoard();
            int code;
            BrainVitaMoveDirection direction;
            while (true) {
                code = brainVita.getCode();
                direction = brainVita.getDirection();
                if (brainVita.isValidMove(code, direction)) {
                    break;
                }
                std::cout << "\nInvalid Move, Enter Again (b to quit)... ";
                char check = Utility::getch();
                if (check == 'b' || check == 'B') {
                    quit = true;
                    break;
                }
            }
            Utility::clearScreen();
            if (quit) {
                break;
            }
            brainVita.move(code, direction);
            if (brainVita.isGameOver()) {
                break;
            }
        }
        std::cout << "\n\t\t\t\t\t\t\tGAME OVER\n\n";
        brainVita.printBoard(false);
        std::cout << "\n\nYour Score is: " << brainVita.getScore();
        std::cout << "\n\nMarbles Left: " << brainVita.getMarbles();
        std::cout << "\n\nMoves Taken: " << brainVita.getMoves();

        std::cout << "\n\n\nTo view high scores, Press any key!! ";
        Utility::getch();
        scoreDao.insert(Score{user.getUname(), brainVita.getScore(), brainVita.getMarbles(), brainVita.getMoves()});
    }

    std::vector<Score> getScores() {
        struct {
            bool operator()(const Score &score1, const Score &score2) const {
                if (score1.getScore() == score1.getScore()) {
                    if (score1.getMarbles() == score2.getMarbles()) {
                        if (score1.getMoves() == score2.getMoves()) {
                            return score1.getTime() > score2.getTime();
                        }
                        return score1.getMoves() < score2.getMoves();
                    }
                    return score1.getMarbles() < score2.getMarbles();
                }
                return score1.getScore() > score2.getScore();
            }
        } comparator;
        auto scores = scoreDao.findAll();
        std::sort(scores.begin(), scores.end(), comparator);
        return scores;
    }

    void showHighScores() {

        Utility::clearScreen();

        std::cout << "\n\t\t\t\t\t\t\tHIGH SCORES\n\n\n";

        std::cout << "Rank\t\tUser\t\t\t\tScore\t\tMarbles\t\tMoves\t\tDate\n";
        std::cout << "______________________________________________________________________________________\n\n";
        auto scores = getScores();

        int rank = 0;
        for (const auto &score : scores) {
            auto username = score.getUser();
            username.resize(20, ' ');
            auto time = std::chrono::system_clock::to_time_t(score.getTime());
            std::cout << ++rank << "\t\t\t" << username << score.getScore() << "\t\t" << score.getMarbles()
                      << "\t\t\t" << score.getMoves() << "\t\t\t" <<
                      std::put_time(std::localtime(&time), "%F %T") << "\n\n";
        }

        std::cout <<"\n\n";

    }


public:

    void showBrainVitaMenu(const Person &user) {
        while (true) {

            BrainVitaChoice::BrainVitaChoice choice = Choices::getBrainVitaChoice();
            Utility::clearScreen();

            switch (choice) {

                case BrainVitaChoice::RULES:
                    showRules();
                    break;
                case BrainVitaChoice::PLAY:
                    play(user);
                case BrainVitaChoice::SCORES:
                    showHighScores();
                    break;
                case BrainVitaChoice::BACK:
                    return;
            }

            std::cout << "\nPress any key to return\n";
            Utility::getch();
        }
    }

};


#endif //BRAIN_VITA_SERVICE_H
