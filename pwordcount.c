/*
* COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
* Daniel Benjamin
* Auburn University
*
* This source code implements the functions listed in the wordcount.h 
* Reference: https://stackoverflow.com/questions/7582619/why-does-fopen-fail-when-given-value-from-main-argv
* Compile: gcc pwordcount.c -o pwordcount
* Usage: ./pwordcount <file_name>
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include "pwordcount.h"
#include "wordcount.h"
#include "loadfile.h"

/**
 * @brief Simulates two cooperating processes where:
 *        Process 1: Read a file containing a list of words.
 *        Process 2: Count the number of words and send the result back to Process 1.
 *        Process 1: Print out the number of words.
 * 
 * @param argc The number of arguments specified on the command line
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
   int file_no = 0;
   char output_file[23];
   char file_buff[23];
   char* file_checker = "file_checker.txt";
   FILE *fp1; //serves as a pointer to <filename>_output.txt
   FILE *fp2; //serves as a pointer to file_checker.txt
   fp2 = fopen(file_checker,"r+");
   /* The process identifier */
   pid_t pid;
   /* Stores the word count */
   int result; 
   /* Declaring the names of the pipes. 
    * The first pipe is used to deliver the input file’s content from the process 1 to process 2. 
    * The second pipe aims to send a wordcount result from process 2 to process 1.
    */
   int fd1[2], fd2[2];
   /* Makes sure enough arguments were inputed */
   checkNumOfArgs(argc,argv);
   /* Sets the name of the file to be the second argument being parsed from the command line. */
   file_name = argv[1];
   
   /* Create the pipes */
   createPipes(fd1,fd2);
   /* now fork a child process */
   pid = fork();
   if (pid < 0) 
   {
      fprintf(stderr, "Fork failed");
      return EXIT_FAILURE;
   }
   if (pid > 0) 
   {  /* parent process */
      /* close the unused ends of the pipes */
      closePipeEnds(fd1[READ_END],fd2[WRITE_END]);
      fp=fopen(file_name,"r"); //opening file
      /* Ensures that the file to be loaded is valid */
      bool isFileValid = check_file(fp,file_name);
      /* Function that loads the file in the write message buffer */
      if (isFileValid == true) {  
         mapInputFileNameToOutput(file_name, output_file);
         fp1 = fopen(output_file,"w+"); //open output_file
         /* Ensures that the name of the new output file is written at the end of file_checker.txt */
         fseek(fp2,-12,SEEK_END);  
         fread(file_buff, sizeof(file_buff),1, fp2);
         /* Writes the name of the output file to file_checker.txt */
         fprintf(fp2,"%s\n",output_file);
         fclose(fp2); //closes file_checker.txt
         fprintf(fp1,"Process 1 is reading file “%s” now ... \n",file_name);   
         printf("Process 1 is reading file “%s” now ... \n",file_name);
         load_file(fp,file_name,write_msg);
      }
      else {
         return EXIT_FAILURE;
      }
      fclose(fp); // closing input file
      fprintf(fp1,"Process 1 starts sending data to Process 2 ...\n");
      fclose(fp1); 
      printf("Process 1 starts sending data to Process 2 ...\n");
      send(fd1,write_msg,strlen(write_msg)+1);
      /* Process 1 receives the result from Process 2 */
      recieve(fd2,&result,sizeof(result));
      mapInputFileNameToOutput(file_name,output_file);
      fp1 = fopen(output_file,"a");
      /* Result is printed out */
      fprintf(fp1,"%s %d%s","Process 1: The total number of words is" ,result,".");
      fclose(fp1);
      printf("Process 1: The total number of words is %d.\n",result);
   }
   else 
   {  /* child process */
      /* close the unused ends of the pipes */
      closePipeEnds(fd1[WRITE_END],fd2[READ_END]);
      mapInputFileNameToOutput(file_name,output_file);
      fp1 = fopen(output_file,"a");
      /* Process 2 is recieving data being sent from Process 1 */
      recieve(fd1, read_msg, BUFFER_SIZE);
      fprintf(fp1,"Process 2 finishes receiving data from Process 1 ...\n");
      printf("Process 2 finishes receiving data from Process 1 ...\n");
      /* performing word count here */
      fprintf(fp1,"Process 2 is counting words now ...\n");
      printf("Process 2 is counting words now ...\n");
	   result = getWordCount(read_msg);   
	   fprintf(fp1,"Process 2 is sending the result back to Process 1 ...\n");
      printf("Process 2 is sending the result back to Process 1 ...\n");
	   send(fd2,&result,sizeof(result));
      fclose(fp1);
   }
   return EXIT_SUCCESS;
}



/**
 * @brief Writes message to the write end of the pipe.
 * 
 * @param fd pipe being written to
 * @param write_msg message being sent
 * @param size size of the message being sent
 */
void send(int fd[2], void* write_msg, size_t size) 
{
   /* write to the pipe */
   write(fd[WRITE_END], write_msg, size);
   /* close the write end of the pipe */
   close(fd[WRITE_END]);
}

/**
 * @brief Receives message from the read end of the pipe and stores it in read_msg. 
 * 
 * @param fd the pipe involved
 * @param read_msg the message being read from the buffer
 * @param size the size of the message being read
 */
void recieve(int fd[2], void* read_msg, size_t size) 
{
   /* read from the pipe */
   read(fd[READ_END], read_msg, size);
   /* close the read end of the pipe */
   close(fd[READ_END]);
}

/**
 * @brief Creates the pipes
 * 
 * @param fd1 The first pipe is used to deliver the input file’s content from the process 1 to process 2. 
 * @param fd2 The second pipe aims to send a wordcount result from process 2 to process 1.
 */
void createPipes(int fd1[2], int fd2[2]) 
{
   if (pipe(fd1) == -1) 
   {
      fprintf(stderr,"Pipe 1 failed");
      exit(EXIT_FAILURE);
   }

   if (pipe(fd2) == -1) 
   {
      fprintf(stderr,"Pipe 2 failed");
      exit(EXIT_FAILURE);
   }
}

/**
 * @brief Closes the specified pipe ends.
 * 
 * @param end1 The end of the first pipe to be closed.
 * @param end2 The end of the second pipe to be closed.
 */
void closePipeEnds(int end1, int end2) 
{
   close(end1);
   close(end2);
}

void checkNumOfArgs(int argc, char *argv[]) 
{
  /* argc must be 2 for correct execution */ 
	if (argc != 2) 
   {
		/* Assume that argv[0] is the program name */
	   printf( "Please enter a file name.\nUsage: %s <file_name> \n", argv[0]);
		exit(EXIT_SUCCESS);		
   }
}

/**
 * @brief This method takes an the name of an input file (without ext) and 
 *        maps it to the name of an output file. 
 *        i.e input.txt gets an output file name of input_output.txt
 * 
 * @param input_file the name of the input file
 * @param output_file the name of the associated output file
 */
void mapInputFileNameToOutput(char* input_file, char* output_file)
{
   char *ext = get_filename_ext(input_file);
   char *res = strstr(input_file, ext);
   int position = res - input_file;
   char file_name_without_ext[position];
   strncpy(file_name_without_ext, input_file, position - 1);
   file_name_without_ext[position - 1] = '\0'; /* null character manually added */
   sprintf(output_file, "%s_output.txt", file_name_without_ext);
}
