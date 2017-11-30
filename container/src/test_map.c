/* test_map.c
 * Mac Radigan
 */

  #include "map.h"
  #include <stdlib.h>
  #include <stdio.h>

  /*
   * main test driver
   */
  int main(int argc, char *argv[])
  {
    status_t status;

    map_t map;
    size_t size = 100; /* reserve slots */
    status = map_make(&map, size);
      check(status, "Could not create map.");

    object_t k1 = 1010;
    object_t v1 = 1011;
    status = map_insert(&map, &k1, &v1);
      check(status, "Could not insert item into list.");
    object_t v1_stored = *map_get(&map, &k1);
      check(status, "Could not access item from list.");
    fprintf(stdout, "%d : %d\n", k1, v1_stored);

    object_t k2 = 1020;
    object_t v2 = 1021;
    status = map_insert(&map, &k2, &v2);
      check(status, "Could not insert item into list.");
    object_t v2_stored = *map_get(&map, &k2);
      check(status, "Could not access item from list.");
    fprintf(stdout, "%d : %d\n", k2, v2_stored);

    object_t k3 = 1030;
    object_t v3 = 1031;
    status = map_insert(&map, &k3, &v3);
      check(status, "Could not insert item into list.");
    object_t v3_stored = *map_get(&map, &k3);
      check(status, "Could not access item from list.");
    fprintf(stdout, "%d : %d\n", k3, v3_stored);

    return EXIT_SUCCESS;

  } // main

// *EOF*
