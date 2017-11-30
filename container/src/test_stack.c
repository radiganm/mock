/* test_stack.c
 * Mac Radigan
 */

  #include "stack.h"
  #include <stdlib.h>
  #include <stdio.h>

  /*
   * main test driver
   */
  int main(int argc, char *argv[])
  {
    status_t status;

    stack_t stack;
    status = stack_make(&stack);
      check(status, "Could not create stack.");

    object_t x1 = 101;
    status = stack_insert_front(&stack, &x1);
      check(status, "Could not insert item into stack.");

    object_t x2 = 102;
    status = stack_insert_front(&stack, &x2);
      check(status, "Could not insert item into stack.");

    object_t x3 = 103;
    status = stack_insert_front(&stack, &x3);
      check(status, "Could not insert item into stack.");

    status = stack_remove_front(&stack);
      check(status, "Could not remove item from front of stack.");
   
    status = stack_print(&stack, stdout);
      check(status, "Could not insert print stack.");

    return EXIT_SUCCESS;

  } // main

// *EOF*
