/*
 * COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
 * Daniel Benjamin
 * Auburn University
 *
 * This is the header file for pwordcount.c.
 */

#ifndef _PWORDCOUNT_H_
#define _PWORDCOUNT_H_

#define BUFFER_SIZE     10000
#define READ_END        0
#define WRITE_END       1

#include <stddef.h>

/* The buffer used to write messages */
char write_msg[BUFFER_SIZE];
/* The buffer used to read messages */
char read_msg[BUFFER_SIZE];
 
/**
 * @brief Writes message to the write end of the pipe.
 * 
 * @param fd pipe being written to
 * @param write_msg message being sent
 * @param size size of the message being sent
 */
void send(int fd[2], void* write_msg, size_t size); 

/**
 * @brief Retrieves message from read end of the pipe.
 * 
 * @param fd the pipe involved
 * @param read_msg the message being read from the buffer
 * @param size the size of the message being read
 */
void recieve(int fd[2], void* read_msg, size_t size);

/**
 * @brief Creates the pipes
 * 
 * @param fd1 The first pipe is used to deliver the input file’s content from the process 1 to process 2. 
 * @param fd2 The second pipe aims to send a wordcount result from process 2 to process 1.
 */
void createPipes(int fd1[2], int fd2[2]);

/**
 * @brief Closes the specified pipe ends.
 * 
 * @param end1 The end of the first pipe to be closed.
 * @param end2 The end of the second pipe to be closed.
 */
void closePipeEnds(int end1, int end2);

/**
 * @brief Prints out the argument missing and the expected program usage.
 * 
 * @param argc The number of arguments.
 * @param argv The arguments passed to the command line.
 */
void checkNumOfArgs(int argc, char *argv[]);

//void mapInputFileNameToOutput(char* file_name_without_ext, int position, char output_file[23]);
void mapInputFileNameToOutput(char* input_file, char* output_file);
#endif