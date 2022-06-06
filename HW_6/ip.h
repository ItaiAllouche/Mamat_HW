#ifndef IP_H
#define IP_H

#include <stddef.h>
#include <iostream>
#include "field.h"
#include "string.h"

class Ip : public Field{
    public:
    int ip;
    size_t mask;
    bool set_value(String val);
    bool match_value(String value)const;
    Ip(String pattern);
};
/*
נשמור את מספר הביטים משמאל שצריך להתחייס אליהם שבאים אחרי הסלאש.
נשמור את הכתובת ip .
נבצע and bit bye bit
ונבדוק האם התנאי מתקיים.
*/
#endif