/*
* COMP 7500/01: Project 2 pWordCount: A Pipe-based WordCount Tool
* Daniel Benjamin
* Auburn University
*
* A test suite called Load tests all functions implmented in loadfile.c using CUnit libraries. 
* Reference: https://cunit.sourceforge.net/example.html
* Compile: gcc -Wall -o test1 loadfiletest.c -lcunit
* Usage: ./test1
*/

#include "loadfile.c"
#include "pwordcount.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "CUnit/Basic.h"


/* Pointer to the file used by the tests. */
FILE* temp_file = NULL;
FILE* temp_file1 = NULL;
FILE* temp_file2 = NULL;

char* file_name = "input.txt";
char* file_name1 = "input1.txt";
char* file_name2 = "wordcount.c";

char msg_buffer[BUFFER_SIZE];
char msg_buffer1[BUFFER_SIZE];
char msg_buffer2[BUFFER_SIZE];
char msg_buffer3[BUFFER_SIZE];
char msg_buffer4[BUFFER_SIZE];

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int 
init_load(void)
{
   if ((NULL == (temp_file = fopen(file_name, "r"))) ||
      (NULL == (temp_file1 = fopen(file_name1, "r"))) ||
      (NULL == (temp_file2 = fopen(file_name2, "r")))) {
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
int 
clean_load(void)
{
   if ((0 != fclose(temp_file)) ||
      (0 != fclose(temp_file1)) ||
      (0 != fclose(temp_file2))) 
   {
      return -1;
   }
   else 
   {
      temp_file = NULL;
      temp_file1 = NULL;
      temp_file2 = NULL;
      return 0;
   }
}

void 
test_getFileExtension(void) 
{
   char* ext = get_filename_ext(file_name);
   char* ext1 = get_filename_ext(file_name1);
   char* ext2 = get_filename_ext(file_name2);
   CU_ASSERT_STRING_EQUAL(ext, "txt");
   CU_ASSERT_STRING_EQUAL(ext1, "txt");
   CU_ASSERT_STRING_EQUAL(ext2, "c");
}

void 
test_check_file(void) 
{
   CU_ASSERT(check_file(temp_file,file_name) == true);
   CU_ASSERT(check_file(temp_file1,file_name1) == true);
   CU_ASSERT(check_file(temp_file2,file_name2) == false);
}

void 
test_load_file(void) 
{
   char* expected_msg = "This is the second project of COMP7500 class.";
   char* expected_msg1 = "\nWhat the heck is going on here?";
   load_file(temp_file, file_name, msg_buffer);
   load_file(temp_file1, file_name1, msg_buffer1);
   CU_ASSERT_STRING_EQUAL(msg_buffer, expected_msg);
   CU_ASSERT_STRING_EQUAL(msg_buffer1, expected_msg1);
}

int main() 
{
   CU_pSuite loadSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   loadSuite = CU_add_suite("Load", init_load, clean_load);
   if (NULL == loadSuite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(loadSuite, "test of getFileExtension()", test_getFileExtension))||
      (NULL == CU_add_test(loadSuite, "test of checkFile()", test_check_file))||
      (NULL == CU_add_test(loadSuite, "test of loadFile()", test_load_file)))
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