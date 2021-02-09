//
// Created by bhavya bansal on 05/02/21.
//

#ifndef DAO_H
#define DAO_H

#include "File.h"

template<class T>
class Dao {

protected:

    std::string FILE_NAME;

    Dao(std::string fileName): FILE_NAME{fileName}{}

public:

    virtual T findOne(const T &object) {
        T objectFromFile;
        File<T> file{FILE_NAME, INPUT, BINARY};
        while (file.read(objectFromFile)) {
            if (objectFromFile == object) {
                return objectFromFile;
            }
        }
        return objectFromFile;
    }

    virtual std::vector<T> findAll() {
        File<T> file{FILE_NAME, INPUT, BINARY};
        std::vector<T> objects;
        T objectFromFile;
        while (file.read(objectFromFile)) {
            objects.push_back(objectFromFile);
        }
        return objects;
    }

    virtual void insert(const T &object) {
        File<T> file{FILE_NAME, OUTPUT_APPEND, BINARY};
        file.write(object);
    }
};

#endif //DAO_H
