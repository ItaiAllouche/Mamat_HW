#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "port.h"
#include "ip.h"
#include "input.h"

const int VALID = 0;

using namespace std;


int main(int argc, char **argv){

    if(check_args(argc,argv)){// arc מספר ארגומנטים
        return -1;
    }
    // e.g src-ip  =122.0.0.0/8
    //String full_rule = "src-ip=210.53.65.133/8";
    String full_rule  = argv[1];
    String *sub_strings;
    size_t total = 0;
    const char *delimitors = "=";
    //split to src-ip ,122.0.0.0/8 untrimmed***
    full_rule.split(delimitors, &sub_strings, &total);
    String trimmed_field = sub_strings[0].trim();

    String ip_src = "src-ip";
    String ip_dst = "dst-ip";
    
    //check whether field is ip or port 
    if(trimmed_field.equals(ip_src) || trimmed_field.equals(ip_dst)){
        Ip rule(trimmed_field);
        rule.set_value(full_rule.trim());
        parse_input(rule);
    }
    else{
        Port rule(trimmed_field);
        rule.set_value(full_rule.trim()); 
        parse_input(rule);  
    }
    delete[] sub_strings;

    return 0;
    
};
    
   