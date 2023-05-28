#!/bin/bash
    wget -q -O- https://www.ynetnews.com/article/h1vqp2mq5 >file.txt
    Benn_appear=$(grep -c Bennett file.txt)
    Net_appear=$(grep -c Netanyahu file.txt) 
    if [[ Benn_appear == 0 && Net_appear == 0 ]];
    then echo ',-'
    else
    echo -n "Bennett,"$Benn_appear | tr '\n' ' '
    echo -n ",Netanyahu,"$Net_appear
    fi
    echo

    (while read line; do echo -n $line && (word_counter $line); done < list_of_links.txt) >>results.csv

