//
// Created by bhavya bansal on 05/02/21.
//

#ifndef PERSON_DAO_H
#define PERSON_DAO_H

#include <vector>
#include "../dao/Dao.h"
#include "../objects/Person.h"

class PersonDao : public Dao<Person> {

public:

    PersonDao() : Dao{"users.dat"} {}

    Person findByUsername(const std::string &username) {
        Person user;
        File<Person> file{FILE_NAME, INPUT, BINARY};
        while (file.read(user)) {
            if (user.getUname() == username) {
                return user;
            }
        }
        Person userNotFound;
        return userNotFound;
    }

    Person findByUsernameAndPassword(const std::string &username, const std::string &password) {
        Person user;
        File<Person> file{FILE_NAME, INPUT, BINARY};
        while (file.read(user)) {
            if (user.getUname() == username && user.getPassword() == password) {
                return user;
            }
        }
        Person userNotFound;
        return userNotFound;
    }

    void updateByUsername(const std::string &username, const Person &person) {
        File<Person> file{FILE_NAME, INPUT_OUTPUT, BINARY};
        std::ios::pos_type userLocation = file.getPosition();
        Person temporary;
        while (file.read(temporary)) {
            if (temporary.getUname() == username) {
                break;
            }
            userLocation = file.getPosition();
        }
        file.goTo(userLocation);
        file.write(person);
    }
};

#endif //PERSON_DAO_H
