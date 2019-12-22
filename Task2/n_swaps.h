/*
 * Task 2 interface
 *
 Created by gsg on 09/12/2019.
*/

#ifndef TASK2_N_SWAPS_H
#define TASK2_N_SWAPS_H

#include <stdlib.h>
#include <stdbool.h>

/***
 * Return operations amount for a0 > a1 > a2 > … > a_{k-1} > a_k < a_{k+1} < a_{k+2} < … a_N, 0 <= k <= N.
 * Strategy:
 * 1. Find max not in order, index i(i != 0 && i != N). If i > N/2 -> shift max to to the right. Else shift max to the left.
 * 2. Exclude max (Decrease array from the left or right size correspondingly)
 * 3. Repeat until no unordered max
 *
 * @param a     - int array
 * @param size  - array size
 * @return      - operations amount or -1 if a == NULL or size < 3
 */
int n_swaps(int *a, size_t size);



#endif /* TASK2_N_SWAPS_H */
