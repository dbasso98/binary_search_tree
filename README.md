# Advanced programming exam 2020/2021
### Group: Romina Doz [SM3500441], Davide Basso [SM3500450], Imola Fodor [SM3500474]

## Problem statement

Implement a templated binary search tree, a data structure with the following properties:

- The left subtree of a node contains only nodes with keys smaller than the node’s key
- The right subtree of a node contains only nodes with keys greater than the node’s key
- Left and right subtree each must also be a binary search tree

Each node of the tree has to store a key and a value and the tree has to be traversed from the smaller key to the biggest. This is the so called in-order traversal and is only one among the different options that we have to actually traverse the tree.

## Command Line Arguments

The command line arguments are specified in the Makefile, so the program can be executed with the *make* command. However, these are the main commands:

    -I include -g -std=c++17 -Wall -Wextra

- The folder *include* contains the following files: *include/bst.hpp  include/node.hpp  include/iterator.hpp* 
- *-std=c++17* specifies the version of C++ to be used
- *-Wall -Wextra* asks for almost all warnings

## Output

In *main()* all the functions that were implemented for the binary search tree are tested. 

First, *insert()* and *emplace()* are used to create a bst. 
Then, with the *find()* function, it is possible to see whether a node is present and, in that case, show his value. 
*erase()* can delete a node and repopulate the subtree without the erased node.
Once all these steps have been done, it is probable that the bst is not balanced (it means that it has not the minimum possible height). To solve this problem, *balance()* is used and the tree can be printed as an ordered sequence (using the operator *<<*) or in its 2D shape (using *print2D()*).
Another tree with the same nodes of the previous one can be obtained using the *deep copy constructor*. A change in the second tree (made with *subscripting operator[]*) will not modify the original tree, as shown in the output. *Move assignment* is tested too and works properly. Finally all the trees generated are deleted, using the *clear()* function.

##### Note
For all the calls to the above functions, the microseconds taken by the execution are printed, in order to have a performance index.


## Design Decisions & Issues

The methods of bts described in the previous section are public but use private fuctions for the implementation. Iterators are often constructed inside these functions and can be used to traverse the tree. 

The most important design decisions concern the following operations:

- *insert()* -> This function returns a pair of an iterator (pointing to the node) and a bool (true if the new node is added, false otherwise). When a new node has to be added to a bst object, it is inserted as a leaf node (without children). For this reason the tree is traversed from the top to the bottom (and not from left to right). This decision is made to avoid a self-balancing binary search tree and improve the performance of the program. If the node is already present in the bts, the original one will not be substituted. 

- *emplace()* -> Inserts a new element into the container constructed in-place with the given args if there is no element with the key in the container. By in-place, we mean the element object is built in-place from the passed arguments.

- *erase()* -> Removes the node (if one exists) with a corresponding key. Once the node is found, its link with the parent is removed and the node is deleted. All the nodes of the subtree over the erased node are re-inserted recursively in the bst to keep the right ordered stucture of the binary search tree.

- *balance()* -> Can be used to change an existing tree in order to have the minimum possible height. To achieve this purpose, the nodes are stored in an ordered (by key) vector and the current tree is cleared. Then, the node in the center of the vector becomes the head of the tree and the vector is splitted in left and right part. The nodes placed in middle position of these new vectors are inserted then. Following this execution path, all the nodes are inserted recursively in the new tree.
