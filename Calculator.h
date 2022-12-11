#pragma once

#include <vector>
#include <string>

static const enum operation {
    ADD,
    SUB,
    DIV,
    MUL,
};

static const enum calcObjType {
    VALUE,
    OPERATION,
};

class CalcObj {
public:
    CalcObj(int val);
    CalcObj(operation opp);
    int add(int val);
    void changeTo(operation opp);
    calcObjType type; // 0=val, 1=obj
    int val;
    operation opp;
};

class Calculator {
public:
    Calculator();
    void addToStack(int val);
    void addToStack(operation opp);
    std::string getStack();
    int eval();
    void undo();
    void clear();
private:
    std::vector<CalcObj> stack;
};

