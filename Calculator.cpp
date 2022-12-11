#include "Calculator.h"
#include <iostream>

CalcObj::CalcObj(int val) {
    type = VALUE;
    this->val = val;
}

CalcObj::CalcObj(operation opp) {
    type = OPERATION;
    this->opp = opp;
}

int CalcObj::add(int val) {
    if (type == OPERATION) return -1;
    this->val = 10*(this->val) + val;
    return this->val;
}

void CalcObj::changeTo(operation opp) {
    this->opp = opp;
}

Calculator::Calculator() {
    stack = std::vector<CalcObj>();
}

void Calculator::clear() {
    stack = std::vector<CalcObj>();
}

void Calculator::addToStack(int val) {
    if (stack.empty()) stack.push_back(CalcObj(val));
    else {
        CalcObj & top = stack.back();
        if (top.type == VALUE) top.add(val);
        else stack.push_back(CalcObj(val));
    }
}

void Calculator::addToStack(operation opp) {
    if (stack.empty()) return;
    else {
        CalcObj& top = stack.back();
        if (top.type == OPERATION) top.changeTo(opp);
        else stack.push_back(CalcObj(opp));
    }
}

int Calculator::eval() {
    if (stack.empty()) return 0;
    int total = stack.at(0).val;
    for (int i = 1; i + 1 < stack.size(); i += 2) {
        operation opp = stack.at(i).opp;
        int val = stack.at(i + 1).val;
        switch (opp) {
        case ADD:
            total += val;
            break;
        case SUB:
            total -= val;
            break;
        case MUL:
            total *= val;
            break;
        case DIV:
            total /= val;
            break;
        }
    }
    return total;
}

std::string Calculator::getStack() {
    std::string output = "";
    for (CalcObj& obj : stack) {
        if (obj.type == VALUE) {
            output += std::to_string(obj.val);
        }
        else {
            switch (obj.opp) {
            case ADD:
                output += "+";
                break;
            case SUB:
                output += "-";
                break;
            case DIV:
                output += "/";
                break;
            case MUL:
                output += "x";
                break;
            }
        }
    }
    return output;
}

void Calculator::undo() {
    if (!stack.empty()) stack.pop_back();
}
