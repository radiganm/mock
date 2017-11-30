/* stack.h
 * Mac Radigan
 */

  #pragma once

  #include "common.h"
  #include <sys/types.h>

  typedef union stack_u
  {
    cell_t    head;
    methods_t methods;
  } stack_t;

#ifdef __cplusplus
extern "C" {
#endif

  status_t stack_make(stack_t *stack);

  status_t stack_free(stack_t *stack);

  status_t stack_insert_front(stack_t *stack, object_t *object);

  status_t stack_remove_front(stack_t *stack);

  status_t stack_print(stack_t *stack, FILE *stream);

#ifdef __cplusplus
}
#endif

/* EOF */
