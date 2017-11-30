/* stack.c
 * Mac Radigan
 */

  #include "stack.h"
  #include <stddef.h>
  #include <stdlib.h>
  #include <string.h>

  status_t stack_make(stack_t *stack)
  {
    stack->methods.compare = &object_compare;
    stack->methods.copy    = &object_copy;
    stack->methods.free    = &object_free;
    stack->methods.print   = &object_print;
    stack->head.cdr = NULL;
    return SUCCESS;
  }

  status_t stack_free(stack_t *stack)
  {
    cell_t *cursor = &stack->head;
    while(NULL != (cursor = cursor->cdr))
    {
      stack->methods.free( ((object_t *)cursor->car) );
    }
    return SUCCESS;
  }

  status_t stack_insert_front(stack_t *stack, object_t *object)
  {
    cell_t *cell = (cell_t *)malloc(sizeof(cell_t));
    cell->car = stack->methods.copy(object);
    cell->cdr = stack->head.cdr;
    stack->head.cdr = cell;
    return SUCCESS;
  }

  status_t stack_remove_front(stack_t *stack)
  {
    cell_t *candidate = stack->head.cdr;
    if(NULL != candidate)
    {
      stack->head.cdr = candidate->cdr;
      free(candidate);
    }
    return SUCCESS;
  }

  status_t stack_print(stack_t *stack, FILE *stream)
  {
    cell_t *cursor = &stack->head;
    fprintf(stream, "( ");
    while(NULL != (cursor = cursor->cdr))
    {
      fprintf(stream, "%d ", *((object_t *)cursor->car));
      //stack->methods.print( ((object_t *)cursor->car), stream );
    }
    fprintf(stream, ")");
    fprintf(stream, "\n");
    fflush(stream);
    return SUCCESS;
  }

/* EOF */
