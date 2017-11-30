/* map.h
 * Mac Radigan
 */

  #pragma once

  #include "common.h"
  #include <sys/types.h>

  typedef struct map_s
  {
    methods_t    methods;
    object_t   **table;
    size_t       size;
  } map_t;

#ifdef __cplusplus
extern "C" {
#endif

  typedef unsigned long hashcode_t;

  status_t map_make(map_t *map, const size_t size);

  status_t map_free(map_t *map);

  status_t map_insert(map_t *map, object_t *key, object_t *value);

  status_t map_remove(map_t *map, object_t *key);

  object_t *map_get(map_t *map, object_t *key);

#ifdef __cplusplus
}
#endif

/* EOF */
