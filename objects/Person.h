//
// Created by bhavya bansal on 03/02/21.
//

#ifndef PERSON_H
#define PERSON_H


#include <string>
#include <iostream>
#include "../enums/Gender.h"
#include "../utils/Utility.h"

class Person {

private:
    std::string fName;
    std::string lName;
    int age;
    Gender gender;
    std::string address;
    std::string pinCode;
    std::string telephone;
    std::string mobile;
    std::string uname;
    std::string password;

public:
    void getData(bool);

    void display();

    const std::string &getFName() const;

    void setFName(const std::string &fName);

    const std::string &getLName() const;

    void setLName(const std::string &lName);

    int getAge() const;

    void setAge(int age);

    Gender getGender() const;

    void setGender(Gender gender);

    const std::string &getAddress() const;

    void setAddress(const std::string &address);

    const std::string &getPinCode() const;

    void setPinCode(const std::string &pinCode);

    const std::string &getTelephone() const;

    void setTelephone(const std::string &telephone);

    const std::string &getMobile() const;

    void setMobile(const std::string &mobile);

    const std::string &getUname() const;

    void setUname(const std::string &uname);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    bool authenticate(const std::string &enteredPassword) const;

    bool operator==(const Person&) const;

    bool operator!=(const Person&) const;

    operator bool () const;

};


#endif //PERSON_H
