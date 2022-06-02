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

private:
    MarkovStatemap states;

    bool isPunctuation(char c) const;
    bool wordExists(string &word);
};


#endif //TOG_TXT_GENERATOR_PARSER_H
