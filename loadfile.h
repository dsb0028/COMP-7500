/*
 * COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
 * Daniel Benjamin
 * Auburn University
 *
 * This is the header file for loadfile.c 
 */
#ifndef _LOADFILE_H_
#define _LOADFILE_H_

#include <stdio.h>
#include <stdbool.h>

/* The file descriptor */
FILE *fp;
/* The name of the file */
char* file_name;

/**
 * @brief Loads the text from the file into the message buffer if the file is valid.
 * 
 * @param fp file descriptor
 * @param file_name name of the file 
 * @param msg_buff message buffer being written to
 * 
 */
void load_file(FILE *fp, char* file_name, char* msg_buff);

/**
 * @brief Gets the file extension of any file
 * @cite https://stackoverflow.com/questions/5309471/getting-file-extension-in-c 
 * 
 * @param file_name 
 * @return char* 
 */
char * get_filename_ext(char* file_name);

/**
 * @brief Performs error checking on a file for the following cases:
 *        Case 1: If the file name doesn't exist
 *        Case 2: If the file name doesn't open
 *        Case 3: If the file name is not a txt file
 * 
 * @param fp  file descriptor for the input file
 * @param file_name the name of the input file
 * @return  true if file is valid. 
 * @return  false if file is invalid. 
 */
bool check_file(FILE *fp, char* file_name);
	
#endif
