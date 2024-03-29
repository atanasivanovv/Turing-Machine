#ifndef TAPE_H
#define TAPE_H

#include <iostream>
#include "list/dll.h"

class Tape {
public:
    Tape();
    Tape(const std::string& input);
    Tape(const DLL<char> list);
    Tape& operator=(const Tape&);
    void print() const;
    void printWithCurr() const;
    const char operator[](size_t i);
    std::string getTapeString() const;

    void write(char);
    char read() const;
    int readIndex() const;
    void moveRight();
    void moveLeft();
    void moveNot();
    void addSpace();
private:
    DLL<char> list;
    const char SPACE = ' ';
    char curr;
    int currIndex;
};

#endif