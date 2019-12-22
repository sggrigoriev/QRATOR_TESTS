Task 3
==========================================================================
To implement ThreadPool:
- when creating, one parameter is indicated - the number of workers who will perform the tasks.
- the Enqueue method has two parameters - an object (a reference to an object) that describes the task that will need to be completed
(for example, an abstract type with the .do () method) and priority (let there be three priorities in all - low, normal, high).
- Stop () method - waits for the completion of the tasks currently being performed, after which it kills the workers and returns control.

Enqueue adds tasks to the execution queue and returns true (if Stop had not been called before - in this case, Enqueue returns false).

Priorities are processed as follows:
a) low-tasks are never performed while there is at least one task with a different priority in the queue.
b) for 3 high-tasks, 1 normal-task is performed.
This logic applies only to the selection of tasks from the queue; already running tasks do not need to be prioritized.

NB! Using C++11, C++17, Boost is prohibited!
===========================================================================

Changes in the statement of the Task 3:
    the '.do ()' method has been renamed to '_do ()'

Additions:
    1. Processing priority tasks occurs in the order of high, normal, low
    2. If there are free workers and there are no tasks with high priority in the queue, then tasks with normal priority are taken into work
    3. ThreadPool may terminate with TP_exception in the following cases
        - error when calling system functions (pthread _ *, ...)
    4. ThreadPool does not catch exceptions that occur when calling C++ std libraries
    5. ThreadPool in the debug build may crash on assert in case of implementation errors

Description:
    Main classes:
        ThreadPool - implements the logic requested in the task
        Manager - sends tasks for execution. Waits for a new task or release of the worker.
        ThreadPool - queue of pending tasks. Adds new tasks, issues tasks according to the rules and priorities
        Workers - Serves outstanding tasks.

Running tests:
    Task3 <path to test data file>

Description of the TestSet.json fields:

    "name" - test description, text string
    "expected" - description of the expected result
    "tasks" - an array of started tasks
        "priority" - priority ("hi" | "norm" | "lo")
        "workTimeSec" - task run time
    "workersAmount" - number of workers
    "delaySecBeforeStop" - delay after starting the last task before calling Stop ()
    Expected Result:
        "resultSet" - many completed tasks
            or
        "result" - an array of completed tasks - the execution sequence is taken into account
    "stop_after" - call Stop () after starting the task with the given serial number
