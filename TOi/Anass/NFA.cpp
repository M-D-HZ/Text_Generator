//#include "NFA.h"
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include "json.hpp"
//#include "set"
//#include "iterator"
//
//using namespace std;
//using json = nlohmann::json;
//set<string>::iterator itr;
//NFA::NFA(string file) {
//    ifstream input(file);
//    json j;
//    input >> j;
//
//    alphabet = j["alphabet"].get<vector<string>>();
//    for (int i = 0; i < j["states"].size(); ++i) {
//        State *newstate = new State();
//        newstate->setName(j["states"][i]["name"].get<string>());
//        newstate->setAccepting(j["states"][i]["accepting"].get<bool>());
//        newstate->setStarting(j["states"][i]["starting"].get<bool>());
//        States.push_back(newstate);
//        if(j["states"][i]["starting"].get<bool>()){
//            CurrentState.insert(newstate);
//        }
//    }
//    vector<TransitionDFA*> Temptrans;
//    State* From;
//    State* To;
//    for (int i = 0; i < j["transitions"].size(); ++i) {
//        TransitionDFA* trans = new TransitionDFA();
//        string from = j["transitions"][i]["from"].get<string>();
//        string to = j["transitions"][i]["to"].get<string>();
//        string input = j["transitions"][i]["input"].get<string>();
//        for (auto b:States){
//            if (from == b->getName()){
//                From = b;
//
//            }
//            if (b->getName() == to){
//                To = b;
//            }
//        }
//        trans->setName(From);
//        trans->setTo(To);
//        trans->setInput(input);
//        Transitions.insert(trans);
//    }
//}
//
//bool NFA::checkAlphabet(string k){
//    for (int i = 0; i < alphabet.size(); ++i) {
//        if(k == alphabet[i]){
//            return true;
//        }
//    }
//    return false;
//}
//
//
//State* NFA::GetState(string statename){
////    for (auto b:d.getStates()) {
////        if (b->getName() == statename){
////            return b;
////        }
////    }
//}
//
//set<State*> NFA::move(set<State*> S, string A){
//    set<State*> newstates;
//    set<State*> from;
//    set<State*> to;
//    TransitionNFA* Transes = new TransitionNFA();
//    Transes->setInput(A);
//    for (auto b:S) {
//        from.insert(b);
//    }
//    for (auto a:Transitions) {
//        for (auto b:S) {
//            if (a->getName()->getName() == b->getName() && a->getInput() == A){
//                newstates.insert(a->getTo());
//            }
//        }
//    }
//    for (auto b:newstates){
//        to.insert(b);
//    }
//    if (!from.empty() && !to.empty()){
//        Transes->setFrom(from);
//        Transes->setTo(to);
//        if (!checkExistance(Transes)){
//            NewTrans.insert(Transes);
//        }
//    }
//    return newstates;
//}
//
//DFA NFA::toDFA() {
//    DFA d;
//    d.setAlphabet(this->alphabet);
//    NewStates.insert(CurrentState);
//    vector<TransitionNFA*> transes;
//    set<State*> from;
//    set<State*> to;
//    bool inspect = true;
//    while(inspect) {
//        int size = NewStates.size();
//        for (auto b:NewStates){
//            for (auto a:alphabet){
//                set<State*> k = move(b,a);
//                if (!k.empty()){
//                    NewStates.insert(k);
//                }
//            }
//        }
//        inspect = NewStates.size() != size;
//    }
//    vector<string> naam;
//    for (auto b:NewStates) {
//        State* S = new State();
//        string name = "{";
//        for (auto c:b) {
//            naam.push_back(c->getName());
//        }
//        std::sort(naam.begin(), naam.end());
//        for (int i = 0; i < naam.size(); i++) {
//            if (naam[i] == naam.back()){
//                name += naam[i];
//            }
//            else{
//                name += naam[i] + ",";
//            }
//        }
//        name+= "}";
//        naam.clear();
//        S->setStarting(this->checkStarting(b));
//        S->setAccepting(this->checkAccepting(b));
//        S->setName(name);
//        d.addState(S);
//    }
//    vector<string> FROM;
//    vector<string> TO;
//    for (auto b:NewTrans){
//        TransitionDFA* trans = new TransitionDFA();
//        trans->setInput(b->getInput());
//        string name = "{";
//        for (auto c:b->getFrom()){
//            FROM.push_back(c->getName());
//        }
//        std::sort(FROM.begin(), FROM.end());
//        for (int i = 0; i < FROM.size(); i++) {
//            if (FROM[i] == FROM.back()){
//                name += FROM[i];
//            }
//            else{
//                name += FROM[i] + ",";
//            }
//        }
//        name += "}";
//        FROM.clear();
//        for (auto k:d.getStates()) {
//            if (k->getName() == name){
//                trans->setName(k);
//            }
//        }
//        string to = "{";
//        for (auto g:b->getTo()){
//            TO.push_back(g->getName());
//        }
//        std::sort(TO.begin(), TO.end());
//        for (int i = 0; i < TO.size(); i++) {
//            if (TO[i] == TO.back()){
//                to += TO[i];
//            }
//            else{
//                to += TO[i] + ",";
//            }
//        }
//        to += "}";
//        TO.clear();
//        for (auto l:d.getStates()) {
//            if (l->getName() == to){
//                trans->setTo(l);
//            }
//        }
//        d.addTrans(trans);
//    }
//    return d;
//}
//
//bool NFA::checkExistance(TransitionNFA* T){
//    for (auto k:NewTrans) {
//        if (k->getFrom() == T->getFrom() && k->getTo() == T->getTo() && k->getInput() == T->getInput()){
//            return true;
//        }
//    }
//    return false;
//}
//
//
//bool NFA::checkAccepting(set<State*> S){
//    for (auto k:S) {
//        if (k->isAccepting()){
//            return true;
//        }
//    }
//    return false;
//}
//
//bool NFA::checkStarting(set<State*> S){
//    for (auto k:S) {
//        if (!k->isStarting()){
//            return false;
//        }
//    }
//    return true;
//}
//
