#ifndef POLAND_H

#define POLAND_H

#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include "math.h"

using namespace std;
struct Stack {
    double num;
    char zn;
    Stack* next;
};

Stack* top1;
Stack* top2;

void push(Stack*& t, double number, char ch) {
    Stack* ptr;
    ptr = (Stack*)malloc(sizeof(Stack));
    (*ptr).num = number;
    (*ptr).zn = ch;
    (*ptr).next = t;
    t = ptr;
}

Stack pop(Stack*& t) {
    Stack temp = *t;
    t = (*t).next;
    return temp;
}

int prior(char ch) {
    if (ch == '(') {
        return 0;
    }
    if (ch == '+' || ch == '-') {
        return 1;
    }
    if (ch == '*' || ch == '/') {
        return 2;
    }
    if (ch == '^') {
        return 3;
    }
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'l' || ch == 'q' || ch == 'a') {
        return 4;
    }
    return 0;
}

bool apply(Stack*& t, char znak) {
    double b = pop((t)).num;
    if (znak == 's' || znak == 'c' || znak == 't' || znak == 'q' || znak == 'l' || znak == 'a') {
        if (znak == 's') {
            push(t, sin(b), '@');
        }
        if (znak == 'c') {
            push(t, cos(b), '@');
        }
        if (znak == 't') {
            if (b == M_PI / 2) {
                return false;
            }
            push(t, tan(b), '@');
        }
        if (znak == 'q') {
            if (b < 0) {
                return false;
            }
            push(t, sqrt(b), '@');
        }
        if (znak == 'l') {
            if (b <= 0) {
                return false;
            }
            push(t, log(b), '@');
        }
        if (znak == 'a'){
            push(t, abs(b), '@');
        }
    }
    else {
        double a = pop((t)).num;
        if (znak == '+') {
            push(t, a + b, '@');
        }
        if (znak == '-') {
            push(t, a - b, '@');
        }
        if (znak == '*') {
            push(t, a * b, '@');
        }
        if (znak == '/') {
            if (b == 0) {
                return false;
            }
            push(t, a / b, '@');
        }
        if (znak == '^') {
            if (a == 0.0 && b == 0.0) {
                return false;
            }
            push(t, pow(a, b), '@');
        }
    }
    return true;
}

bool debug(string s) {
    int sl = 0;
    int sr = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            sl += 1;
        }
        if (s[i] == ')') {
            sr += 1;
        }
        if (sr > sl) {
            return false;
        }
        if (i != 0) {
            if (s[i] == '+' || s[i] == '/' || s[i] == '*' || s[i] == '-' || s[i] == ')' ||
                s[i] == '^') {
                if (s[i - 1] == '+' || s[i - 1] == '/' || s[i - 1] == '*' || s[i - 1] == '-' ||
                    s[i - 1] == '^' || s[i - 1] == '(') {
                    return false;
                }
            }
        }
        if ((s[i] == '+' || s[i] == '/' || s[i] == '*' || s[i] == '^') && i == 0) {
            return false;
        }
        if (i == (s.size() - 1) && (s[i] == '+' || s[i] == '/' || s[i] == '*' || s[i] == '-'
                                    || s[i] == '^')) {
            return false;
        }
        if (i != 0 && s[i - 1] == '(' && s[i] == ')') {
            return false;
        }
        if (i != 0 && ('0' <= s[i - 1] && s[i - 1] <= '9') && (s[i] == 's' || s[i] == 'c' || s[i] == 't' ||
                                                               s[i] == 'q' || s[i] == 'l' || s[i] == '(' || s[i] == 'a')) {
            return false;
        }
        if (i != 0 && s[i - 1] == ')' && (('0' <= s[i] && s[i] <= '9') || s[i] == 's' || s[i] == 'c' ||
                                          s[i] == 't' || s[i] == 'q' || s[i] == 'l' || s[i] == 'a')) {
            return false;
        }
    }
    if (sr != sl) {
        return false;
    }
    return true;
}


bool reduction(string& s) {
    string new_str, imp;
    new_str = "";
    for (int j = 0; j < s.size(); j++) {
        if (s[j] == '-' && (j == 0 || s[j - 1] == '(')) {
            new_str += "0-";
        }
        if ('a' <= s[j] && s[j] <= 'z') {
            imp = "";
            while ('a' <= s[j] && s[j] <= 'z') {
                imp += s[j];
                j++;
            }
            if (s[j] != '(') {
                return false;
            }
            else {
                if (imp == "sin") {
                    new_str += 's';
                }
                if (imp == "cos") {
                    new_str += 'c';
                }
                if (imp == "tg") {
                    new_str += 't';
                }
                if (imp == "sqrt") {
                    new_str += 'q';
                }
                if (imp == "ln") {
                    new_str += 'l';
                }
                if (imp == "abs") {
                    new_str += 'a';
                }
                if (imp != "sin" && imp != "cos" && imp != "tg" && imp != "sqrt" && imp != "ln" && imp != "abs") {
                    return false;
                }
            }
        }
        if (s[j] != ' ' && not('a' <= s[j] && s[j] <= 'z') &&
            not(s[j] == '-' && (j == 0 || s[j - 1] == '('))) {
            new_str += s[j];
        }
    }
    s = new_str;
    return true;
}

bool calculate(string&str, double & ans) {

    string some_num;
    string new_str;

    int i = 0;

    if (!reduction(str)) return false;
    if (!debug(str)) return false;
    while (i < str.size()) {
        if ('0' <= str[i] && str[i] <= '9') {
            while ('0' <= str[i] && str[i] <= '9' or str[i] == '.') {
                some_num += str[i];
                i += 1;
            }

            push(top1, stod(some_num), '@');
            some_num = "";
            i -= 1;
        }
        if (str[i] == '(') {
            push(top2, 0.0, str[i]);
        }
        if (str[i] == ')') {
            while ((*top2).zn != '(')
                if (!apply(top1, (pop(top2)).zn)) return false;
            pop(top2);
            if (top2 != nullptr && (top2->zn == 's' || top2->zn == 'c' || top2->zn == 't'
                                    || top2->zn == 'q' || top2->zn == 'l' || top2->zn == 'a')) {
                if (!apply(top1, pop(top2).zn)) return false;
            }
        }
        if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-' || str[i] == '^' || str[i] == 's'
            || str[i] == 'c' || str[i] == 't' || str[i] == 'q' || str[i] == 'l' || str[i] == 'a') {
            while (top2 != nullptr && prior((*top2).zn) >= prior(str[i])) {
                if (!apply(top1, (pop(top2)).zn)) return 0;
            }
            push(top2, 0.0, str[i]);
        }
        i += 1;
    }
    while (top2 != nullptr) {
        if (!apply(top1, pop(top2).zn)) return false;
    }
    ans = pop(top1).num;
    return true;
}

#endif // POLAND_H
