Modified AVL Tree for List Operations

Overview

This project implements a Modified AVL Tree to maintain a list of integers (L) and support efficient execution of several operations on the list. The AVL Tree structure is used to ensure that all operations are performed in logarithmic time, making it optimal for handling large datasets. The implementation is written in C++, utilizing advanced data structure techniques for fast and efficient operations.

The solution extends the functionality of a traditional list by supporting the following operations:

Insert(k, x): Insert an integer x into the list L at position k.

Remove(k): Remove the integer at position k from the list L.

FindKth(k): Find the element at position k in the list L.

Index(x): Find the position of the integer x in the list L.

Sum(k1, k2): Calculate the sum of elements in positions from k1 to k2 (inclusive).

Max(k1, k2): Find the maximum element among elements in positions from k1 to k2 (inclusive).

Features

The key features of this solution include:

Self-Balancing Tree Structure: The AVL tree ensures that the list remains balanced, with a time complexity of O(log n) for all operations.

Augmented Nodes: Each node in the AVL tree is augmented with additional data to efficiently calculate sums and maximum values for given ranges.

Dynamic Updates: The tree dynamically updates its structure and augmented data during insertions and deletions.

Operations

1. Insert(k, x)
Description: Inserts the integer x into the list L at position k.

Implementation: Uses the AVL tree structure to ensure that the element is placed at the correct position, balancing the tree after insertion.

Time Complexity: O(log n).

3. Remove(k)
Description: Removes the element at position k from the list L.

Implementation: Deletes the node at the specified position, rebalances the tree, and updates augmented data.

Time Complexity: O(log n).

5. FindKth(k)
Description: Retrieves the element at position k in the list L.

Implementation: Traverses the AVL tree to locate the k-th element.

Time Complexity: O(log n).

7. Index(x)
Description: Finds the position of the integer x in the list L.

Implementation: Traverses the AVL tree, using parent-child relationships to compute the index of the node.

Time Complexity: O(log n).

9. Sum(k1, k2)
Description: Calculates the sum of elements in the range [k1, k2].

Implementation: Uses the augmented sum data in the tree nodes to compute the sum efficiently.

Time Complexity: O(log n).

11. Max(k1, k2)
Description: Finds the maximum element in the range [k1, k2].

Implementation: Uses the augmented max data in the tree nodes to identify the maximum value efficiently.

Time Complexity: O(log n).
