//
// Created by bhavya bansal on 03/02/21.
//

#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>
#include "../enums/FileMode.h"
#include "../enums/FileType.h"

template<class T>
class File {

private:
    std::fstream fileStream;

public:
    File(const std::string &, FileMode, FileType);

    bool read(T &);

    void write(const T &);

    void begin();

    void end();

    void goTo(std::ios::pos_type);

    std::ios::pos_type getPosition();

    ~File();
};

template<class T>
File<T>::File(const std::string &fileName, FileMode fileMode, FileType fileType) {

    std::ios_base::openmode mode = 0;

    switch (fileMode) {
        case INPUT:
            mode = std::ios::in;
            break;
        case OUTPUT:
            mode = std::ios::out;
            break;
        case INPUT_OUTPUT:
            mode = std::ios::in | std::ios::out;
            break;
        case OUTPUT_APPEND:
            mode = std::ios::out | std::ios::app;
            break;
    }
    switch (fileType) {
        case TEXT:
            break;
        case BINARY:
            mode = mode | std::ios::binary;
            break;
    }
    fileStream.open(fileName, mode);
}

template<class T>
File<T>::~File() {
    fileStream.close();
}

template<class T>
bool File<T>::read(T &object) {
    if (fileStream.read((char *) &object, sizeof(object)))
        return true;
    return false;
}

template<class T>
void File<T>::write(const T &object) {
    fileStream.write((char *) &object, sizeof(object));
}

template<class T>
void File<T>::begin() {
    fileStream.seekg(0);
}

template<class T>
void File<T>::end() {
    fileStream.seekg(0, std::ios::end);
}

template<class T>
void File<T>::goTo(std::ios::pos_type position) {
    fileStream.seekg(position);
}

template<class T>
std::ios::pos_type File<T>::getPosition() {
    return fileStream.tellg();
}


#endif //FILE_H
