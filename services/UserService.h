//
// Created by bhavya bansal on 04/02/21.
//

#ifndef USER_UTILITY_H
#define USER_UTILITY_H

#include <iostream>
#include <string>
#include "../dao/PersonDao.h"

class UserService {

private:

    PersonDao personDao;

    Person showSignInScreen() {
        Utility::clearScreen();
        std::string uname, password;
        std::cout << "\t\t\t\t\t\t\tSIGN IN TO MINI FACEBOOK\n\n\n\n";
        std::cout << "\t\t\t\t\t\t\t\t\tUsername: ";
        std::cin >> uname;
        std::cout << "\t\t\t\t\t\t\t\t\tPassword: ";
        std::cin >> password;
        return personDao.findByUsernameAndPassword(uname, password);
    }

public:

    Person signUp() {
        Utility::clearScreen();
        std::cout << "\t\t\t\t\t\t\tSIGN UP TO MINI FACEBOOK\n";
        std::cout << "Enter your Details:\n";
        Person person;
        person.getData(true);
        while (personDao.findByUsername(person.getUname())) {
            Utility::clearScreen();
            std::cout << "Entered username already exists, Enter again: ";
            std::string uname;
            std::cin >> uname;
            person.setUname(uname);
        }
        personDao.insert(person);
        return person;
    }

    Person signIn() {
        Person loggedInUser;
        while (true) {
            if (!(loggedInUser = showSignInScreen())) {
                Utility::clearScreen();
                std::cout << "Either username or password is incorrect";
                std::cout << "\nPress any key to try again(Press b to return)";
                char check = Utility::getch();
                if (check == 'b' || check == 'B') {
                    break;
                }
            } else {
                break;
            }
        }
        return loggedInUser;

    }

    void showProfileMenu(Person &user) {
        Utility::clearScreen();
        std::cout << "Your Profile: \n";
        user.display();
        std::cout << "\nDo you want to edit profile(y/n): ";
        char choice;
        std::cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            std::cout << "\nInvalid choice enter again: ";
            std::cin >> choice;
        }
        if (choice == 'y' || choice == 'Y') {
            user.getData(false);
            personDao.updateByUsername(user.getUname(), user);
        }
        std::cout << "\nTo Return press any Key\n";
        Utility::getch();
    }

};


#endif //USER_UTILITY_H
