
#ifndef TAI2_TRANSITION_H
#define TAI2_TRANSITION_H
#include "iostream"

//toch geen gebruik van gemaakt.

class Transition {
public:
    const std::string &getFrom() const;

    void setFrom(const std::string &from);

    const std::string &getTo() const;

    void setTo(const std::string &to);

    const std::string &getInput() const;

    void setInput(const std::string &input);

private:
    std::string from;
    std::string to;
    std::string input;
};


#endif //TAI2_TRANSITION_H
