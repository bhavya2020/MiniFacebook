//
// Created by bhavya bansal on 03/02/21.
//

#include "../Person.h"

void Person::getData(bool isSignUp) {
    std::cout << "\n First Name: ";
    std::cin >> fName;
    std::cout << "\n Last Name: ";
    std::cin >> (lName);
    std::cout << "\n Age: ";
    std::cin >> age;
    std::cout << "\n Gender(Male/Female/Other): ";
    std::string genderInput;
    std::cin >> genderInput;
    if (genderInput == "m" || genderInput == "M") {
        gender = MALE;
    } else if (genderInput == "f" || genderInput == "F") {
        gender = FEMALE;
    } else {
        gender = OTHER;
    }
    std::cout << "\n Address: ";
    Utility::getline(address);
    std::cout << "\n Pin Code: ";
    std::cin >> pinCode;
    std::cout << "\n Telephone Number: ";
    Utility::getline(telephone);
    std::cout << "\n mobile number: ";
    Utility::getline(mobile);
    if (isSignUp) {
        std::cout << "\n User Name: ";
        std::cin >> uname;
        std::cout << "\n Password: ";
        std::cin >> password;
        std::cout << "\n Re-Enter Password: ";
        std::string passwordReEntered;
        std::cin >> passwordReEntered;
        while (passwordReEntered != password) {
            std::cout << "\n Your password does not match\n Enter again: ";
            std::cin >> passwordReEntered;
        }
    }
}

void Person::display() {
    std::cout << "\n First Name: " << fName;
    std::cout << "\n Last Name: " << lName;
    std::cout << "\n Age: " << age;
    std::cout << "\n Gender: ";
    switch (gender) {
        case MALE:
            std::cout << "Male";
            break;
        case FEMALE:
            std::cout << "Female";
            break;
        case OTHER:
            std::cout << "Other";
            break;
    }
    std::cout << "\n Address: " << address;
    std::cout << "\n Pin Code: " << pinCode;
    std::cout << "\n Telephone Number: " << telephone;
    std::cout << "\n Mobile Number: " << mobile;
    std::cout << "\n";
}

const std::string &Person::getFName() const {
    return fName;
}

void Person::setFName(const std::string &fName) {
    Person::fName = fName;
}

const std::string &Person::getLName() const {
    return lName;
}

void Person::setLName(const std::string &lName) {
    Person::lName = lName;
}

int Person::getAge() const {
    return age;
}

void Person::setAge(int age) {
    Person::age = age;
}

Gender Person::getGender() const {
    return gender;
}

void Person::setGender(Gender gender) {
    Person::gender = gender;
}

const std::string &Person::getAddress() const {
    return address;
}

void Person::setAddress(const std::string &address) {
    Person::address = address;
}

const std::string &Person::getPinCode() const {
    return pinCode;
}

void Person::setPinCode(const std::string &pinCode) {
    Person::pinCode = pinCode;
}

const std::string &Person::getTelephone() const {
    return telephone;
}

void Person::setTelephone(const std::string &telephone) {
    Person::telephone = telephone;
}

const std::string &Person::getMobile() const {
    return mobile;
}

void Person::setMobile(const std::string &mobile) {
    Person::mobile = mobile;
}

const std::string &Person::getUname() const {
    return uname;
}

void Person::setUname(const std::string &uname) {
    Person::uname = uname;
}

const std::string &Person::getPassword() const {
    return password;
}

void Person::setPassword(const std::string &password) {
    Person::password = password;
}

bool Person::authenticate(const std::string &enteredPassword) const {
    return password == enteredPassword;
}

bool Person::operator==(const Person &person) const {
    return this->getUname() == person.getUname();
}

Person::operator bool() const {
    return !this->getUname().empty();
}

bool Person::operator!=(const Person &person) const {
    return !(*this == person );
}
