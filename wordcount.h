/*
 * COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
 * Daniel Benjamin
 * Auburn University
 *
 * This is the header file for wordcount.c.
 */

#ifndef _WORDCOUNT_H_
#define _WORDCOUNT_H_

/**
 * @brief Calculates the number of words given a message buffer.
 * 
 * @param msg message buffer of type char* 
 * @return int - the number of words 
 */
int getWordCount(char* msg);

/**
 * @brief Calculates the amount of spaces that appear consecutively in the message
 * 
 * @param msg A message buffer of type char*.
 * @return int - the amount of duplicate spaces
 */
int getNumOfDupSpace(char* msg);

/**
 * @brief Gets the total number of spaces that are in the message buffer. (including duplicates)
 * 
 * @param msg A message buffer of type char*.
 * @return int - the total amount of spaces that appear in the message buffer
 */
int getNumOfSpace(char* msg);

/**
 * @brief Determines if input msg has preceding whitespace.
 * 
 * @param msg A mesaage buffer of type char*. 
 * @returns 0 - there is not preceding white space
 *          1 - there is preceding white space
 */
int is_prec_ws(char* msg);

/**
 * @brief Determines if input msg has trailing whitespace. 
 * 
 * @param msg A message buffer of type char*.
 * @returns 0 - there is not trailing white space 
 *          1 - there is trailing white space
 */
int is_trail_ws(char* msg);

/**
 * @brief Checks the char at index in buffer and the char at index-1
 *        in buffer to see if they are both white spaces. 
 * 
 * @param msg message buffer
 * @param index index of the second char being compared
 * @returns 0 - if there is not consecutive white space
 *          1 - if there is consecutive white space
 */
int isThereConsecWS(char* msg, int index);

bool isMsgBuffEmpty(char* msg_buff);

#endif



