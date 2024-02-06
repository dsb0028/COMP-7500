/*
* COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
* Daniel Benjamin
* Auburn University
*
* A test suite called Word_Count tests all functions implmented in wordcount.c using CUnit libraries. 
* Reference: https://cunit.sourceforge.net/example.html
* Compile: gcc -Wall -o test wordcounttest.c -lcunit
* Usage: ./test
*/

#include "wordcount.c"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_wordcount(void)
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
int clean_wordcount(void)
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
char* msg15 = "";
char* msg16 = "1";

void test_getWordCount(void) 
{
   /* Case 1: No preceding or trailing white space, one unit of white space between words. */
   CU_ASSERT(getWordCount(msg) == 8);
   /* Case 2: One '\t' of preceding white space, one unit of white space between words. */
   CU_ASSERT(getWordCount(msg1) == 8);
   /* Case 3: One '\n' of preceding white space, one unit of white space between words. */
   CU_ASSERT(getWordCount(msg2) == 8);
   /* Case 4: One '\n' of preceding white space and one '\n' of trailing white space. */
   CU_ASSERT(getWordCount(msg3) == 8);
   /* Case 5: Two consecutive tabs of prec. ws. */
   CU_ASSERT(getWordCount(msg4) == 8);
   /* Case 6: Three consecutive tabs of prec. ws. */
   CU_ASSERT(getWordCount(msg5) == 8);
   /* Case 7: Three consecutive tabs of prec. ws, two words are seperated by a blank space and two tabs. */
   CU_ASSERT(getWordCount(msg6) == 8);
   /* Case 8: New line character inserted in the middle of the messsage. */
   CU_ASSERT(getWordCount(msg7) == 8);
   /* Case 9: Tab and new line characters seperate two words. */
   CU_ASSERT(getWordCount(msg8) == 8);
   /* Case 10: Three multiple new line characters exists in the message. */
   CU_ASSERT(getWordCount(msg9) == 8);
   /* Case 11: More than three white space types exist in the message. (' ', '\t','\r', '\n') */
   CU_ASSERT(getWordCount(msg10) == 8);
   /* Case 12: One '\n' of trailing of white space. */
   CU_ASSERT(getWordCount(msg11) == 8);
   /* Case 13: Two consecutive '\n' of trailing white space. */
   CU_ASSERT(getWordCount(msg12) == 8);
   /* Case 14: Two consecutive '\n' of trailing white space and a number is included in the message. */
   CU_ASSERT(getWordCount(msg13) == 8);
   /* Case 15: Mix of numbers and special characters. */
   CU_ASSERT(getWordCount(msg14) == 9);
   /* Case 16: Message is completely empty */
   CU_ASSERT(getWordCount(msg15) == 0);
   /* Case 17: Message has only one word. */
   CU_ASSERT(getWordCount(msg16) == 1);
}

void test_getNumOfSpace(void) 
{
   /* Case 1: No preceding or trailing white space, one unit of white space between words. */
   CU_ASSERT(getNumOfSpace(msg) == 7);
   /* Case 2: One '\t' of preceding white space, one unit of white space between words. */
   CU_ASSERT(getNumOfSpace(msg1) == 8);
   /* Case 3: One '\n' of preceding white space, one unit of white space between words. */
   CU_ASSERT(getNumOfSpace(msg2) == 8);
   /* Case 4: One '\n' of preceding white space and one '\n' of trailing white space. */
   CU_ASSERT(getNumOfSpace(msg3) == 9);
   /* Case 5: Two consecutive tabs of prec. ws. */
   CU_ASSERT(getNumOfSpace(msg4) == 9);
   /* Case 6: Three consecutive tabs of prec. ws. */
   CU_ASSERT(getNumOfSpace(msg5) == 10);
   /* Case 7: Three consecutive tabs of prec. ws, two words are seperated by a blank space and two tabs. */
   CU_ASSERT(getNumOfSpace(msg6) == 12);
   /* Case 8: New line character inserted in the middle of the messsage. */
   CU_ASSERT(getNumOfSpace(msg7) == 7);
   /* Case 9: Tab and new line characters seperate two words. */
   CU_ASSERT(getNumOfSpace(msg8) == 8);
   /* Case 10: Three multiple new line characters exists in the message. */
   CU_ASSERT(getNumOfSpace(msg9) == 8);
   /* Case 11: More than three white space types exist in the message. (' ', '\t','\r', '\n') */
   CU_ASSERT(getNumOfSpace(msg10) == 7);
   /* Case 12: One '\n' of trailing of white space. */
   CU_ASSERT(getNumOfSpace(msg11) == 8);
   /* Case 13: Two consecutive '\n' of trailing white space. */
   CU_ASSERT(getNumOfSpace(msg12) == 9);
   /* Case 14: Two consecutive '\n' of trailing white space and a number is included in the message. */
   CU_ASSERT(getNumOfSpace(msg13) == 9);
   /* Case 15: Mix of numbers and special characters. */
   CU_ASSERT(getNumOfSpace(msg14) == 8);
   /* Case 16: Message is completely empty */     
}

void test_getNumOfDupSpace(void) 
{
   /* Case 1: No preceding or trailing white space, one unit of white space between words. */
   CU_ASSERT(getNumOfDupSpace(msg) == 0);
   /* Case 2: One '\t' of preceding white space, one unit of white space between words. */
   CU_ASSERT(getNumOfDupSpace(msg1) == 1);
   /* Case 3: One '\n' of preceding white space, one unit of white space between words. */
   CU_ASSERT(getNumOfDupSpace(msg2) == 1);
   /* Case 4: One '\n' of preceding white space and one '\n' of trailing white space. */
   CU_ASSERT(getNumOfDupSpace(msg3) == 2);
   /* Case 5: Two consecutive tabs of prec. ws. */
   CU_ASSERT(getNumOfDupSpace(msg4) == 2);
   /* Case 6: Three consecutive tabs of prec. ws. */
   CU_ASSERT(getNumOfDupSpace(msg5) == 3);
   /* Case 7: Three consecutive tabs of prec. ws, two words are seperated by a blank space and two tabs. */
   CU_ASSERT(getNumOfDupSpace(msg6) == 5);
   /* Case 8: New line character inserted in the middle of the messsage. */
   CU_ASSERT(getNumOfDupSpace(msg7) == 0);
   /* Case 9: Tab and new line characters seperate two words. */
   CU_ASSERT(getNumOfDupSpace(msg8) == 1);
   /* Case 10: Three multiple new line characters exists in the message. */
   CU_ASSERT(getNumOfDupSpace(msg9) == 1);
   /* Case 11: More than three white space types exist in the message. (' ', '\t','\r', '\n') */
   CU_ASSERT(getNumOfDupSpace(msg10) == 0);
   /* Case 12: One '\n' of trailing of white space. */
   CU_ASSERT(getNumOfDupSpace(msg11) == 1);
   /* Case 13: Two consecutive '\n' of trailing white space. */
   CU_ASSERT(getNumOfDupSpace(msg12) == 2);
   /* Case 14: Two consecutive '\n' of trailing white space and a number is included in the message. */
   CU_ASSERT(getNumOfDupSpace(msg13) == 2);
   /* Case 15: Mix of numbers and special characters. */
   CU_ASSERT(getNumOfDupSpace(msg14) == 0);
   /* Case 16: Message is completely empty */
}

void test_is_prec_ws(void) {
   /* Case 1: Returns 0 if there is not preceding ws */
   CU_ASSERT(is_prec_ws(msg) == 0);
   /* Case 2: Returns 1 if there is preceding white space */
   CU_ASSERT(is_prec_ws(msg1) == 1);
} 

void test_is_trail_ws(void) {
   /* Case 1: Returns 0 if there is not trailing whitespace. */
   CU_ASSERT(is_trail_ws(msg) == 0);
   /* Case 2: Returns 1 if there is trailing whitespace. */
   CU_ASSERT(is_trail_ws(msg3) == 1);
}

/**
 * @brief test_is_there_consec_ws() uses boundary testing given the following test cases:
 * 
 */
void test_is_there_consec_ws(void) {
   /* Case 1: Returns 0 if there is not trailing whitespace. */
   CU_ASSERT(isThereConsecWS(msg,index) == 0);
   /* Case 2: Returns 1 if there is trailing whitespace. */
   CU_ASSERT(is_trail_ws(msg3) == 1);
}

int main() 
{
   CU_pSuite wordcount = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   wordcount = CU_add_suite("Word_Count", init_wordcount, clean_wordcount);
   if (NULL == wordcount) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(wordcount, "test of getWordCount()", test_getWordCount))||
      (NULL == CU_add_test(wordcount, "test of getNumOfSpace()", test_getNumOfSpace))||
      (NULL == CU_add_test(wordcount, "test of getNumOfDupSpace()", test_getNumOfDupSpace))||
      (NULL == CU_add_test(wordcount, "test of is_prec_ws()", test_is_prec_ws))||
      (NULL == CU_add_test(wordcount, "test of is_trail_ws()", test_is_trail_ws)))
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