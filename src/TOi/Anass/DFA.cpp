#include "DFA.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "State.h"
#include "TransitionNFA.h"
#include "unordered_set"

using namespace std;
using json = nlohmann::json;

DFA::DFA(string file) {
    ifstream input(file);
    json j;
    input >> j;

    alphabet = j["alphabet"].get<vector<string>>();
    for (int i = 0; i < j["states"].size(); ++i) {
        State *newstate = new State();
        newstate->setName(j["states"][i]["name"].get<string>());
        newstate->setAccepting(j["states"][i]["accepting"].get<bool>());
        newstate->setStarting(j["states"][i]["starting"].get<bool>());
        States.push_back(newstate);
        if(j["states"][i]["starting"].get<bool>()){
            CurrentState = newstate;
        }
    }
    State* From;
    State* To;
    for (int i = 0; i < j["transitions"].size(); ++i) {
        TransitionDFA* trans = new TransitionDFA();
        string from = j["transitions"][i]["from"].get<string>();
        string to = j["transitions"][i]["to"].get<string>();
        string input = j["transitions"][i]["input"].get<string>();
        for (auto b:States){
            if (from == b->getName()){
                From = b;

            }
            if (b->getName() == to){
                To = b;
            }
        }
        trans->setName(From);
        trans->setTo(To);
        trans->setInput(input);
        Transitions.push_back(trans);
    }
}

bool DFA::checkAlphabet(string k){
    for (int i = 0; i < alphabet.size(); i++) {
        if(k == alphabet[i]){
            return true;
        }
    }
    return false;
}

void DFA::move(string k){
    for (auto b: Transitions) {
        if (b->getName()->getName() == CurrentState->getName() && b->getInput() == k){
            CurrentState = b->getTo();
            return;
        }
    }
}
State* DFA::GetState(string statename){
    for (auto b:States) {
        if (b->getName() == statename){
            return b;
        }
    }
}

bool DFA::accepts(string input) {
    for (char i : input) {
        string k;
        k.push_back(i);
        if (checkAlphabet(k)){
            move(k);
        }
    }
    for (const auto &b: States)
        if (b == CurrentState && b->isAccepting()) {
            return true;
        };
    return false;
}

void DFA::print() {
    json file;
    file["type"] = "DFA";
    for (auto b:States) {
        json j_umap;
        j_umap["name"] = b->getName();
        if (b->isStarting()){
            j_umap["starting"] = true;
        }
        else{
            j_umap["starting"] = false;
        }
        if (b->isAccepting()){
            j_umap["accepting"] = true;
        }
        else{
            j_umap["accepting"] = false;
        }
        file["states"].push_back(j_umap);
    }
    for (auto b:Transitions) {
        map<string,string> trans;
        trans["from"] = b->getName()->getName();
        trans["to"] = b->getTo()->getName();
        trans["input"] = b->getInput();
        file["transitions"].push_back(trans);
    }
    file["alphabet"] = this->alphabet;
    cout << setw(4) << file << endl;
}


const vector<string> &DFA::getAlphabet() const {
    return alphabet;
}

void DFA::setAlphabet(const vector<string> &alphabet) {
    DFA::alphabet = alphabet;
}


DFA::DFA() {}

State *DFA::getCurrentState() const {
    return CurrentState;
}

void DFA::setCurrentState(State *currentState) {
    CurrentState = currentState;
}

void DFA::addState(State* s) {
    States.push_back(s);
}

const vector<State *> &DFA::getStates() const {
    return States;
}

void DFA::addTrans(TransitionDFA *t) {
    Transitions.push_back(t);
}

DFA::DFA(DFA dfa1, DFA dfa2, bool versie) {
    for (int i = dfa2.alphabet.size()-1; i > 0; i--) {
        this->alphabet.push_back(dfa2.alphabet[i]);
    }
    for (auto b:dfa1.alphabet){
        if (!checkAlphabet(b)){
            this->alphabet.push_back(b);
        }
    }
    bool inspect = true;
    pair<State*,State*> Starts;
    for (auto b:dfa1.States) {
        if (b->isStarting()){
            Starts.first = b;
            break;
        }
    }
    for (auto b:dfa2.States) {
        if (b->isStarting()){
            Starts.second = b;
            break;
        }
    }
    NewStates.insert(Starts);
    pair<State*,State*> news;
    vector<State*> from;
    vector<State*> to;
    while (inspect){
        int size = NewStates.size();
        for (auto b:NewStates){
            for (auto a:alphabet) {
                TransitionNFA* Transes = new TransitionNFA();
                Transes->setInput(a);
                from = {b.first,b.second};
                for (auto d: dfa1.Transitions){
                    if (d->getName()->getName() == b.first->getName() && d->getInput() == a){
//                                news.insert(d->getTo());
//                                news.insert(news.end(),d->getTo());
                        news.first = d->getTo();
                        break;
                    }
                }
                for (auto d: dfa2.Transitions){
                    if (d->getName()->getName() == b.second->getName() && d->getInput() == a){
//                                news.insert(d->getTo());
//                                news.insert(news.end(),d->getTo());
                        news.second = d->getTo();
                        break;
                    }
                }
                to = {news.first,news.second};
                if (!from.empty()){
                    Transes->setFrom(from);
                }
                if (!to.empty()){
                    Transes->setTo(to);
                }
                NewStates.insert(news);
                if (!checkExistance(Transes)){
                    NewTrans.insert(Transes);
                }
                news.first = nullptr;
                news.second = nullptr;
                from.clear();
                to.clear();
            }
        }
        inspect = NewStates.size() != size;
    }
    for (auto b:NewStates) {
        State* S = new State();
        string name = "(" + b.first->getName() + "," + b.second->getName() + ")";
        S->setStarting(this->checkStarting(b));
        S->setAccepting(this->checkAccepting(b,versie));
        S->setName(name);
        this->addState(S);
    }
    vector<string> naam;
    for (auto b:NewTrans){
        TransitionDFA* trans = new TransitionDFA();
        trans->setInput(b->getInput());
        string name = "(";
        for (auto c:b->getFrom()){
            naam.push_back(c->getName());
        }
        for (int i = 0; i < naam.size(); i++){
            if (i == naam.size()-1){
                name += naam[i];
            }
            else{
                name += naam[i] + ",";
            }
        }
        name += ")";
        naam.clear();
        for (auto k:this->getStates()) {
            if (k->getName() == name){
                trans->setName(k);
            }
        }
        string to = "(";
        for (auto g:b->getTo()){
            naam.push_back(g->getName());
        }
        for (int i = 0; i < naam.size(); i++) {
            if (i == naam.size()-1){
                to += naam[i];
            }
            else{
                to += naam[i] + ",";
            }
        }
        to += ")";
        naam.clear();
        for (auto b:this->getStates()) {
            if (b->getName() == to){
                trans->setTo(b);
            }
        }
        this->addTrans(trans);
    }

}

bool DFA::checkAccepting(pair<State*,State*> S, bool versie){
    if (!versie){
        if (S.first->isAccepting() || S.second->isAccepting()){
            return true;
        }
        return false;
    }
    else{
        if (S.first->isAccepting() && S.second->isAccepting()){
            return true;
        }
        return false;
    }

}

bool DFA::checkStarting(pair<State*,State*> S){
    if (S.first->isStarting() && S.second->isStarting()){
        return true;
    }
    return false;
}

bool DFA::checkExistance(TransitionNFA* T){
    for (auto k:NewTrans) {
        if (k->getFrom() == T->getFrom() && k->getTo() == T->getTo() && k->getInput() == T->getInput()){
            return true;
        }
    }
    return false;
}