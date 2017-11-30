/* map.c
 * Mac Radigan
 */

  #include "map.h"
  #include <stddef.h>
  #include <stdlib.h>
  #include <string.h>

  static hashcode_t hash_djb2(const object_t *object, size_t size)
  {
     const unsigned char *buf = (const unsigned char *)object;
     unsigned long hash = 5381;
     int c;
     for(size_t k=0; k<size;  ++k)
     {
       hash = ((hash << 5) + hash) + buf[k]; /* hash * 33 + buf[k] */
     }
     return hash;
  }

  status_t map_make(map_t *map, const size_t size)
  {
    map->methods.compare = &object_compare;
    map->methods.copy    = &object_copy;
    map->methods.free    = &object_free;
    map->size            = size;
    /* NB:  architecture-specific NULL equivalence */
    map->table = calloc(sizeof(object_t *), size);
    return SUCCESS;
  }

  status_t map_free(map_t *map)
  {
    for(int k=0; k<map->size;  ++k)
    {
      /* NB:  architecture-specific NULL equivalence */
      if(NULL != map->table[k])
      {
        map->methods.free( *(object_t *)(map->table[k]) );
      }
    }
    return SUCCESS;
  }

  status_t map_insert(map_t *map, object_t *key, object_t *value)
  {
    hashcode_t hashcode = hash_djb2(key, sizeof(object_t));
    const int index = hashcode % map->size;
    if(NULL != map->table[index])
    {
      perror("Object already in map.");
      return FAILURE;
    }
  //map->table[index] = map->methods.copy(value);
    object_t *object_new = (object_t *)malloc(sizeof(object_t));
    memcpy(object_new, value, sizeof(object_t));
    map->table[index] = object_new;
    return SUCCESS;
  }

  status_t map_remove(map_t *map, object_t *key)
  {
    hashcode_t hashcode = hash_djb2(key, sizeof(object_t));
    const int index = hashcode % map->size;
    object_t *candidate = map->table[index];
    /* NB:  architecture-specific NULL equivalence */
    if(NULL == candidate)
    {
      perror("Object not in map.");
      return FAILURE;
    }
    map->methods.free(candidate);
    return SUCCESS;
  }

  object_t *map_get(map_t *map, object_t *key)
  {
    hashcode_t hashcode = hash_djb2(key, sizeof(object_t));
    const int index = hashcode % map->size;
    object_t *candidate = map->table[index];
    /* NB:  architecture-specific NULL equivalence */
    return candidate;
  }

/* EOF */
