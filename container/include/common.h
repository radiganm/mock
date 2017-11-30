/* common.h
 * Mac Radigan
 */

  #pragma once

  #include <stdio.h>

  /* define application-appropriate type here */
  typedef int element_t; 

  typedef enum status_e
  {
    SUCCESS = 0,
    FAILURE
  } status_t;

  typedef enum boolean_e
  {
    FALSE = 0,
    TRUE  = 1
  } boolean_t;

  typedef struct cell_s
  {
    void   *car;
    struct cell_s *cdr;
  } cell_t;

  typedef element_t object_t;
  typedef int (*compare_fn_t)(const object_t *object1, const object_t *object2);
  typedef status_t (*print_fn_t)(const object_t *object, FILE *stream);
  typedef object_t* (*copy_fn_t)(const object_t *object);
  typedef void (*free_fn_t)(object_t *object);

  typedef struct methods_s
  {
    compare_fn_t compare;
    print_fn_t   print;
    copy_fn_t    copy;
    free_fn_t    free;
  } methods_t;

#ifdef __cplusplus
extern "C" {
#endif

  void check(status_t status, const char *messsage);
  status_t object_print(const object_t *object, FILE *stream);
  int object_compare(const object_t *object1, const object_t *object2);
  object_t *object_copy(const object_t *object);
  void object_free(object_t *object);

#ifdef __cplusplus
}
#endif

/* EOF */
