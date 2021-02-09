//
// Created by bhavya bansal on 04/02/21.
//

#ifndef CHOICES_H
#define CHOICES_H

#include "../enums/LandingChoice.h"
#include "../enums/DashboardChoice.h"
#include "Utility.h"
#include "../enums/PostsChoice.h"
#include "../enums/FriendRequestChoice.h"
#include "../enums/MailChoice.h"
#include "../enums/GamesChoice.h"
#include "../enums/BrainVitaChoice.h"
#include <iostream>

class Choices {

public:

    static int getChoice(int min, int max) {
        int choice;
        std::cin >> choice;
        while (choice < min || choice > max) {
            std::cout << "\n Invalid Option \n";
            std::cout << "Enter Again: ";
            std::cin >> choice;
        }
        return choice;
    }

    static LandingChoice getLandingChoice() {
        Utility::clearScreen();
        std::cout << " \n\n\n\n\t\t\t\t\t\t\tMINI FACEBOOK\n";
        std::cout << "\n\n\n";
        std::cout << " \t\t\t\t\tChoose any of the following options:";
        std::cout << "\n\t\t\t\t\t\t\t1. Sign up ";
        std::cout << "\n\t\t\t\t\t\t\t2. Sign in \n";
        std::cout << "\n\t\t\t\t\tEnter your choice: ";
        return static_cast<LandingChoice>(getChoice(1, 2));
    }

    static DashboardChoice getDashboardChoice() {
        Utility::clearScreen();
        std::cout << "\n\n\t\t\t\t\t\t\tWELCOME TO MINI FACEBOOK\n\n";
        std::cout << "\nChoose any option:\n";
        std::cout << "1. Profile \n2. Post \n3. Friend Requests\n4. Mails \n5. Games \n6. Sign Out\n\nYour Choice: ";
        return static_cast<DashboardChoice >(getChoice(1, 6));
    }

    static PostsChoice::PostsChoice getPostsChoice() {
        Utility::clearScreen();
        std::cout << "\n\n\t\t\t\t\t\t\tTHE POST MENU\n\n";
        std::cout << "\nChoose any option:\n";
        std::cout << "1. View posts \n2. Post something \n3. Back\n\nYour Choice: ";
        return static_cast<PostsChoice::PostsChoice >(getChoice(1, 3));
    }

    static FriendRequestChoice::FriendRequestChoice getFriendRequestsChoice(){
        Utility::clearScreen();
        std::cout << "\n\n\t\t\t\t\t\t\tFRIEND REQUESTS\n\n";
        std::cout << "\nChoose any option:\n";
        std::cout << "1. Notifications \n2. Friends \n3. Send friend requests";
        std::cout << "\n4. Accept/Reject friend requests \n5. Back\n\nYour Choice: ";
        return static_cast<FriendRequestChoice::FriendRequestChoice >(getChoice(1,5));
    }

    static MailChoice::MailChoice getMailChoice(){
        Utility::clearScreen();
        std::cout<< "\n\n\t\t\t\t\t\t\tMAIL MENU\n\n";
        std::cout<<"\nChoose any options:\n";
        std::cout<<"1. Compose\n2. Inbox\n3. Sent Mail\n4. Trash Mail\n5. Back\n\nYour Choice: ";
        return static_cast<MailChoice::MailChoice>(getChoice(1, 5));
    }

    static GamesChoice::GamesChoice getGamesChoice(){
        Utility::clearScreen();
        std::cout<< "\n\n\t\t\t\t\t\t\tGAMES MENU\n\n";
        std::cout<<"\nChoose any options:\n";
        std::cout<<"\n1. Brain Vita \n2. Bollywood \n3. Tic-Tac-Toe \n4. Back\n\nYour Choice: ";
        return static_cast<GamesChoice::GamesChoice>(getChoice(1, 4));
    }

    static BrainVitaChoice::BrainVitaChoice getBrainVitaChoice(){
        Utility::clearScreen();
        std::cout<< "\n\n\t\t\t\t\t\t\tBRAIN VITA\n\n";
        std::cout<<"\nChoose any options:\n";
        std::cout<<"\n1. How to Play?\n2. Play the Game\n3. High Scores\n4. Back\n\nYour Choice: ";
        return static_cast<BrainVitaChoice::BrainVitaChoice>(getChoice(1, 4));
    }
};


#endif //CHOICES_H
