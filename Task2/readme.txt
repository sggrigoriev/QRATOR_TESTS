Task 2
==========================================================================
Sort integer array as follows: a0> a1> a2> ...> a_ {k-1}> a_k <a_ {k + 1} <a_ {k + 2} <... a_N, 0 <= k <= N.
The only valid operation: swap two adjacent elements.

To write a function int n_swaps (int * a, size_t size), which returns the minimum required number of operations that lead the array to this form.
Please note that the index k can be on the edge (that is, the sorted list already has the desired order of elements), and also that k
It is not a parameter of the function, but should be obtained as a result of the algorithm.

Decision:
    1. Find the minimum element in the array.
    2. Rearrange it with the border adjacent to it. If the distance to the borders is the same, then to the right. Calculate the number of pairwise permutations.
    3. Reduce the size of the array by 1. If there was a left shift, then reduce the address of the beginning of the array by 1.
    4. Perform 1-3 until the elements in the array run out.
    5. Issue the index of the minimum element at which the number of element operations is minimal.

Running tests:
    Task2 <path to the file with test data>

Description of the TestSet.json fields:

    "name" - test description, text string
    "data" - an array of integers, sorted data

