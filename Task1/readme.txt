Task 1
==============================================================
To find the local minimum in integer arrray.
The implementation algorithim should have minimal asymptotic complexity.

The local min definition:
    It is a_i that a_ {i-1}> a_i <a_ {i + 1}.
    For the array's borders, the local minimum condition is, respectively: a0 <a1 and a_n <a_ {n-1}.

Solution:
    Assumption: we consider the probability of equality of neighboring elements as extremely low and neglect this possibility.
    (N is significantly smaller than the range of possible values ​​of a_i)

    Then the probability that a_i> a {i + 1) is 1/2
    It turns out that the probability of finding a local minimum at the boundaries of the array 1/2
    The probability a_i> a {i + 1} <a_i + 1 is 1/2 * 1/2 = 1/4

    I.e. the probability that a local minimum is found on the first 3 elements is very close to 1.

Algorithm:
    1. To find the local min at the boundaries of the array.
    2. If no local min found, then to find the local minimum in a1, .... a{n-1}.

The complexity of the algorithm.
    In the worst case, a local minimum is found in the N-1m element.
    Difficulty 2(n-1) -> O (n)
    On average, the local minimum should be found at one of the boundaries, i.e.
    Difficulty O (1)

Running tests:
    Task1 <path to test data file>

Description of the TestSet.json fields:
    "name" - test description, text string
    "data" - an array of integers on which the local minimum is searched
    "result" - the expected test result is the local minimum index in the "data" array or -1 if there is no local minimum.