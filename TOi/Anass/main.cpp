#include <iostream>
#include "DFA.h"
#include "NFA.h"

using namespace std;

int main() {
    DFA dfa("RegexDfa.json");
    dfa.toRE().print();
//    DFA dfa1("Product1.json");
//    DFA dfa2("Product2.json");
//    DFA product(dfa1,dfa2,true); // true betekent doorsnede, false betekent unie
//    product.print();
//    NFA nfa("NFA.json");
//    nfa.toDFA().print();
//    return 0;
//    DFA dfa("DFA.json");
//    dfa.print();
//    return 0;
//    DFA dfa("DFA.json");
//    cout << boolalpha << dfa.accepts("0010110100") << endl << dfa.accepts("0001") << endl;
    return 0;
}
