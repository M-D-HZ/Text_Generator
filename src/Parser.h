#ifndef TOG_TXT_GENERATOR_PARSER_H
#define TOG_TXT_GENERATOR_PARSER_H

#include <string>
#include <map>
#include "vector"
using namespace std;

class MarkovState;
typedef map<string, MarkovState*> MarkovStatemap;

class Parser {
public:
    Parser();
    Parser(const string &filename);
    const MarkovStatemap &getStates() const;
    bool isPunctuation(char c) const;

private:
    MarkovStatemap states;
    void test(const string &filename);
    bool wordExists(string &word);
};


#endif //TOG_TXT_GENERATOR_PARSER_H
