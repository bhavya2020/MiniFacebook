//
// Created by bhavya bansal on 06/02/21.
//

#ifndef GAMES_SERVICE_H
#define GAMES_SERVICE_H


#include "../games/TicTacToe.h"
#include "../games/Bollywood.h"
#include "../games/BrainVita.h"
#include "BrainVitaService.h"

class GamesService {

    BrainVitaService brainVitaService;

    static void showBollywood() {

        std::cout << "\n\t\t\t\tBOLLYWOOD\n\n";

        Bollywood bollywood{};

        while (!bollywood.isGameOver()){
            bollywood.showCurrentGuess();
            bollywood.takeTurn();
            Utility::clearScreen();
        }

        Utility::clearScreen();
        switch (bollywood.getResult()) {
            case Bollywood::NO_RESULT:
                break;
            case Bollywood::WON:
                std::cout << "\n\n\n\n\t\t\t\tYOU WON\n\n";
                std::cout << "You guessed correct it was: ";
                break;
            case Bollywood::LOST:
                std::cout << "\n\n\n\n\t\t\t\tYOU LOST\n\n";
                std::cout << "The movie was: ";
                break;
        }
        std::cout << bollywood.getMovie() << "\n\n";

    }

    static void showTicTacToe() {



        TicTacToe ticTacToe{};

        while (true) {
            Utility::clearScreen();
            std::cout << "\n\t\t\t\tTIC-TAC-TOE\n\n";
            ticTacToe.usersTurn();
            if (ticTacToe.isGameOver(TicTacToe::USER)) {
                break;
            }
            ticTacToe.computersTurn();
            if (ticTacToe.isGameOver(TicTacToe::COMPUTER)) {
                break;
            }
        }

        Utility::clearScreen();

        std::cout << "\n\n\n\n\n\t\t\t\t";
        switch (ticTacToe.getResult()) {

            case TicTacToe::NO_RESULT:
                break;
            case TicTacToe::WINNER:
                std::cout << "YOU WIN\n\n\n\n";
                break;
            case TicTacToe::LOSER:
                std::cout << "YOU LOST\n\n\n\n";
                break;
            case TicTacToe::DRAW:
                std::cout << "MATCH DRAWN\n\n\n\n";
                break;
        }

        ticTacToe.printBoard(false);

    }

public:

    void showGamesMenu(const Person &user) {
        while (true) {
            GamesChoice::GamesChoice choice = Choices::getGamesChoice();
            Utility::clearScreen();

            switch (choice) {

                case GamesChoice::BRAIN_VITA:
                    brainVitaService.showBrainVitaMenu(user);
                    break;
                case GamesChoice::BOLLYWOOD:
                    showBollywood();
                    std::cout << "\nPress any key to return\n";
                    Utility::getch();
                    break;
                case GamesChoice::TIC_TAC_TOE:
                    showTicTacToe();
                    std::cout << "\nPress any key to return\n";
                    Utility::getch();
                    break;
                case GamesChoice::BACK:
                    return;
            }

        }
    }

};

#endif //GAMES_SERVICE_H
