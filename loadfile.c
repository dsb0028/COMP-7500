/*
 * COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
 * Daniel Benjamin
 * Auburn University
 *
 * This source code implements the functions listed in loadfile.h 
 * See loadfile.h for specifications of the functions.
 *
 * Unit Tests are in loadfiletest.c
 */

#include "pwordcount.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* got from https://stackoverflow.com/questions/5309471/getting-file-extension-in-c */
char *get_filename_ext(char *filename) 
{
   char *dot = strrchr(filename, '.');
   if(!dot || dot == filename) return "";
   return dot + 1;
}

void load_file(FILE *fp, char* file_name,char* msg_buff) 
{
   /* Stores each character into the message buffer. */
   int i = 0;
   while(!feof(fp)) 
   {
      msg_buff[i] = fgetc(fp);
      i++;
   }
   /* Makes sure that the message buffer terminates. */
   if(feof(fp)) 
   {
      msg_buff[i-1] = '\0';
   }
}

bool check_file(FILE *fp, char* file_name) 
{
   bool isValid = true;
   /*gets the file extension of the file*/
   char* ext = get_filename_ext(file_name);
   //  Cases 2 and 3: file doesn't extst and file can't open.
   if( fp==NULL ) 
   {
      fprintf(stderr,"Could not open file: %s.\n", file_name);
      isValid = false;
   }
   // Case 4: file is not a text file
   else if (strcmp(ext,"txt")!=0) 
   {
      fprintf(stderr,"File %s is not a text file. \n",file_name);
      isValid = false;
   }
   return isValid;
}
