/*
 * COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
 * Daniel Benjamin
 * Auburn University
 *
 * This source code implements the functions listed in wordcount.h 
 * See wordcount.h for specifications of the functions.
 *
 * Unit Tests are in wordcounttest.c
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isMsgBuffEmpty(char* msg_buff)
{
    bool verdict = false;
    if (strlen(msg_buff) == 0) 
    {
        verdict = true;
    }
    return verdict; 
}

int getWordCount(char* msg) 
{
    // Get total amount of white space. (includes dups)
    int result = getNumOfSpace(msg);
    // Get amount of duplicate white space.
    int number_of_dups = getNumOfDupSpace(msg);
    // Subtracts the total amount of ws from duplicate white space (net white space). 
    result -= number_of_dups;
    // The number of words is the net amount of white space (counting consequtive ws as one) + 1.
    // Assuming there is at least one word in the file. 
    if (!isMsgBuffEmpty(msg)) {
        result += 1;
    }
    return result;
}

int getNumOfDupSpace(char* msg) 
{ 
    // Keeps track of the amount of duplicate white space.
    int number_of_dups = 0;
    /*
     * Handles preceding and trailing whitespace  
     * If there is preceding ws, 1 will be added to the total amount of dup ws otherwise 0.
     * If there is trailing white space, 1 will be added to the total amount of dup ws otherwise 0.
     */
    number_of_dups += (is_prec_ws(msg)+is_trail_ws(msg));
    /* Checks for consecutive spaces within the message and increments the counter 
     * if consecutive places in buffer are white space chars. 
     */
    for(int index = 1; index <= strlen(msg); index++) 
    {
        number_of_dups += isThereConsecWS(msg,index);
    }
    return number_of_dups; 
}

int getNumOfSpace(char* msg) 
{
    int result = 0;
    for(int i = 0; i < strlen(msg) ; i++) 
    {
        if (isspace(msg[i]))  
        {
            result++;
        }
    }
    return result;
}

int is_prec_ws(char* msg) {
    int verdict = 0;
    if (isspace(msg[0])) 
    {
        verdict = 1;
    }
    return verdict;
}

int is_trail_ws(char* msg) {
    int verdict = 0;
    if (isspace(msg[strlen(msg)-1])) 
    {
        verdict = 1;
    } 
    return verdict;
}

int isThereConsecWS(char* msg, int index)
{
    int verdict = 0;
    if (index >= 1 && 
        (isspace(msg[index-1]) && isspace(msg[index])))
    {
        verdict = 1;
    }
    return verdict;    
}  