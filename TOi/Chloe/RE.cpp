//
// Created by chloeacm on 01.04.22.
//

#include "RE.h"
#include <iostream>
#include <vector>

string RE::createString() {
    string regex;

    bool onlyRS = false;
    if (!R.empty() and !S.empty() and T.empty() and U.empty()) {
        onlyRS = true;
    }

    bool onlySU = false;
    if (R.empty() and T.empty() and !S.empty() and !U.empty()) {
        onlySU = true;
    }

    bool onlyS = false;
    if (R.empty() and U.empty() and T.empty() and !S.empty()) {
        onlyS = true;
    }

    bool noT = false;
    if (T.empty() and !S.empty() and !R.empty() and !U.empty()) {
        noT = true;
    }

    R = haakjes(R);
    S = haakjes(S);
    T = haakjes(T);
    U = haakjes(U);
    if (!R.empty() and R.size()>1) {
        R = "(" + R + ")";
    }
    if (!U.empty() and R.size()>1) {
        U = "(" + U + ")";
    }

    if (onlySU) {
        regex = S + U + "*";
    }
    else if (onlyS) {
        regex = S;
    }
    else if (noT) {
        regex = R + "*" + S + U + "*";
    }

    else if (onlyRS) {
        regex = R + "*" + S;
    }

    else {
        regex = "(" + R + "*" + "+" + S + U + "*" + T + ")" + "*" + S + U + "*";
    }


    return regex;
}

string RE::haakjes(string &s) {
    if (s.empty()) {
        return s;
    }
    else if (s.size() == 1) {
        return s;
    }
    vector<char> tekens;
    for (auto &c:s) {
        if (c == '(' or c == ')' or c == '+') {
            tekens.push_back(c);
        }
    }
    if (tekens.size()>1 and (tekens[0] == '+' or tekens[tekens.size()-1] == '+')) {
        s = "(" + s + ")";
    }


    return s;
}

void RE::print() {
    cout << this->createString() << endl;
}