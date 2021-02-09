//
// Created by bhavya bansal on 07/02/21.
//

#ifndef BOLLYWOOD_H
#define BOLLYWOOD_H

#include <set>

class Bollywood {

public:

    enum Result {
        NO_RESULT,
        WON,
        LOST
    };


private:

    static const std::vector<std::string> MOVIES;

    const std::string MOVIE;

    std::string bollywood;

    std::string currentGuess;

    std::set<char> guesses{};

    int chances;

    Result result;

    bool verify(char &guess) {

        if (!isalpha(guess)) {
            return false;
        }
        guess = tolower(guess);
        if (guess == 'a' || guess == 'e' || guess == 'i' || guess == 'o' || guess == 'u') {
            return false;
        }

        return guesses.find(guess) == guesses.end();

    }

    bool matchGuess(const char &guess){
        bool isMatched = false;
        for(int i = 0; i< currentGuess.size(); ++i){
            if(MOVIE[i] == guess){
                isMatched = true;
                currentGuess[i] = guess;
            }
        }
        return isMatched;
    }

    void reduceChances(const char &guess){
        int curPosition = -1;
        while (bollywood[++curPosition] == 'X');
        if(toupper(guess) != bollywood[curPosition]) {
            --chances;
            bollywood[curPosition] = 'X';
        }
    }

public:

    Bollywood() : MOVIE{MOVIES[rand() % MOVIES.size()]}, bollywood{"BOLLYWOOD"}, result{NO_RESULT} {
        chances = bollywood.size();
        currentGuess = MOVIE;
        for (int i = 0; i < MOVIE.size(); ++i) {
            switch (MOVIE[i]) {
                case 'a':
                    break;
                case 'e':
                    break;
                case 'i':
                    break;
                case 'o':
                    break;
                case 'u':
                    break;
                case ' ':
                    break;
                default :
                    currentGuess[i] = '_';
            }
        }
    }

    void showCurrentGuess() {
        std::cout << "Guess the movie\n\nYou have only " << chances << " chances left\n\n";
        std::cout << bollywood;
        std::cout << "\n\n";
        std::cout << currentGuess;
    }

    bool isGameOver()  {
        if(MOVIE == currentGuess){
            result = WON;
            return true;
        }
        if(chances == 0){
            result = LOST;
            return true;
        }
        return false;
    }

    void takeTurn() {

        std::cout << "\n\nEnter any alphabet: ";
        char guess;
        while (true) {
            std::cin >> guess;
            if (verify(guess)) {
                guesses.insert(guess);
                break;
            }
            std::cout << "\nInvalid Input, Enter again: ";
        }

        if(!matchGuess(guess)){
            reduceChances(guess);
        }

    }

    const std::string &getMovie() const {
        return MOVIE;
    }

    const Result &getResult() const {
        return result;
    }


};

const std::vector<std::string> Bollywood::MOVIES{"ek tha tiger",
                                                 "dil dhadkne do",
                                                 "bajrangi bhaijaan",
                                                 "happy new year",
                                                 "sooryavansham",
                                                 "hum saath saath hai",
                                                 "dilwale dulhania le jayenge",
                                                 "saat khoon maaf",
                                                 "holiday",
                                                 "yamla pagla diwana",
                                                 "ek vivah aisa bhi",
                                                 "hawrah bridge pe lataki lash",
                                                 "alone",
                                                 "tanu weds manu returns",
                                                 "yamraj ek faulad",
                                                 "meri jung one man army",
                                                 "meri taquat mera faisla",
                                                 "ragada the multipower",
                                                 "anybody can dance",
                                                 "rowdy badshah",
                                                 "kartik calling kartik",
                                                 "humshakals",
                                                 "jodha akbar",
                                                 "chalte chalte",
                                                 "karan arjun",
                                                 "kismat konnection",
                                                 "mr india",
                                                 "baghban",
                                                 "om shanti om",
                                                 "destiny"
};


#endif //BOLLYWOOD_H
