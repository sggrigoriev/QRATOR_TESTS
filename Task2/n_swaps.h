/*
 Created by gsg on 09/12/2019.
*/

#ifndef TASK2_N_SWAPS_H
#define TASK2_N_SWAPS_H

#include <stdlib.h>
#include <stdbool.h>

/***
 * Return operations amount for a0 > a1 > a2 > … > a_{k-1} > a_k < a_{k+1} < a_{k+2} < … a_N, 0 <= k <= N.
 * @param a     - int array
 * @param size  - array size
 * @return      - operations amount or -1 if a == NULL or size < 3
 */
int n_swaps(int *a, size_t size);
int n_swaps_shaker(int *a, size_t size);


#endif /* TASK2_N_SWAPS_H */
