# Containers

The stdlib furnishes several containers.

It is a very important part of an algorithm to choose the right container for the task.

As of C++11, most containers are abstract, that is, only specify which operations it supports.

For example, a `UnorderedMap` could be implemented both as a hash map or a RB tree concrete data structures, but is always supports the same operations: insert, remove, and so on.

The major data structures which you must know about in order of decreasing usefulness are:

- std::vector
- set
- map
- list
- deque
- heap and priority queue
