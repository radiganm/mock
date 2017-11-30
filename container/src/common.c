/* common.c
 * Mac Radigan
 */

  #include "common.h"
  #include <assert.h>
  #include <errno.h>
  #include <stdlib.h>
  #include <string.h>

  void check(status_t status, const char *message)
  {
    if(SUCCESS != status)
    {
      perror(message);
      assert(-1);
    }
  }

  /* define application-appropriate serialization here */
  status_t object_print(const object_t *object, FILE *stream)
  {
    fprintf(stream, "%d", *object);
    return SUCCESS;
  }

  /* define application-appropriate comparator here */
  int object_compare(const object_t *object1, const object_t *object2)
  {
    if(*object1 == *object2)
    {
      return 0;
    }
    else if(*object1 < *object2)
    {
      return -1;
    }
    else if(*object1 > *object2)
    {
      return +1;
    }
    assert(-1); /* unreachable line */
  }

  /* define application-appropriate copy constructor here */
  object_t *object_copy(const object_t *object)
  {
    object_t *new_object = (object_t *)malloc(sizeof(object_t));
    memcpy(new_object, object, sizeof(object_t));
    return new_object;
  }

  /* define application-appropriate cleanup here */
  void object_free(object_t *object)
  {
    free(object);
  }

/* EOF */
