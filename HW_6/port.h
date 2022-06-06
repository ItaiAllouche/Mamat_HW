#ifndef PORT_H
#define PORT_H

#include <stddef.h>
#include <iostream>
#include "field.h"
#include "string.h" 

class Port : public Field{
    int max;
    int min;
    public:
    bool set_value(String val);
    bool match_value(String value)const;
    Port(String pattern);
};

#endif