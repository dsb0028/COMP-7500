/*
 * COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
 * Daniel Benjamin
 * Auburn University
 *
 * A test suite called Word_Count tests all functions implmented in wordcountp.c using CUnit libraries. 
 * Reference: https://cunit.sourceforge.net/example.html
 * Compile: gcc -Wall -o test pwordcounttest.c -lcunit
 * Usage: ./test2
 */

#include "pwordcount.h"
#include "loadfile.h"
#include "wordcount.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "CUnit/Basic.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_pwordcount(void)
{
   if (NULL == (temp_file = fopen("input.txt", "r"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_pwordcount(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

char* msg = "This is the second project of COMP7500 class.";
char* msg1 = "\tThis is the second project of COMP7500 class.";
char* msg2 = "\nThis is the second project of COMP7500 class.";
char* msg3 = "\nThis is the second project of COMP7500 class.\n";
char* msg4 = "\t\tThis is the second project of COMP7500 class.";
char* msg5 = "\t\t\tThis is the second project of COMP7500 class.";
char* msg6 = "\t\t\tThis is the second \t\tproject of COMP7500 class.";
char* msg7 = "This is\nthe second project of COMP7500 class.";
char* msg8 = "This is\t\nthe second project of COMP7500 class.";
char* msg9 = "This\tis\t\nthe\nsecond project of COMP7500\nclass.";
char* msg10 = "This\tis\tthe\nsecond\tproject\rof\tCOMP7500\nclass.";
char* msg11 = "This is the second project of COMP7500 class.\n";
char* msg12 = "This is the second project of COMP7500 class.\n\n";
char* msg13 = "This is the 2 project of COMP7500 class.\n\n";
char* msg14 = "/ / / 11 && 88 () 00 15";

int fd1[2], fd2[2];


void test_main(void) {
   
}





int main() {
   CU_pSuite wordcount = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   wordcount = CU_add_suite("Word_Count", init_pwordcount, clean_pwordcount);
   if (NULL == wordcount) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(wordcount, "test of getWordCount()", test_getWordCount))||
      (NULL == CU_add_test(wordcount, "test of getNumOfSpace()", test_getNumOfSpace))||
      (NULL == CU_add_test(wordcount, "test of getNumOfDupSpace()", test_getNumOfDupSpace)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();

}

