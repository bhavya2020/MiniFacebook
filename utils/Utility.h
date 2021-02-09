//
// Created by bhavya bansal on 04/02/21.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

class Utility {

public:

    static char getch() {
        fflush(stdin);
        return std::cin.get();
    }

    static void getline(std::string &input,char delimiter = '\n'){
        fflush(stdin);
        std::getline(std::cin,input,delimiter);
    }

    static void clearScreen() {
        for (int i = 0; i < 30; ++i) {
            std::cout << "\n";
        }
    }
};


#endif //UTILITY_H
