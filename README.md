# XOR-Linked-List

This project implements a doubly linked list data structure using the XOR (exclusive OR) technique to save memory. A classic doubly linked list stores predecessor and successor addresses directly in each node, while in this project, the list stores the XOR of these addresses, reducing memory usage.

Features

The XOR Linked List project provides the following functionalities:

    ACTUAL: Get the value of the currently pointed element.
    NEXT: Print the value of the successor of the current element, setting it as the current element.
    PREV: Print the value of the predecessor of the current element, setting it as the current element.
    ADD_BEG N: Add an element with value N to the beginning of the list.
    ADD_END N: Add an element with value N to the end of the list.
    ADD_ACT N: Add an element with value N as a predecessor of the currently selected element (ACTUAL).
    DEL_BEG: Remove the first node from the list.
    DEL_END: Remove the last node from the list.
    DEL_VAL N: Remove all nodes with a value equal to N from the list.
    DEL_ACT: Remove the node that ACTUAL points to, setting ACTUAL to PREV. If PREV does not exist (ACTUAL was the first element), ACTUAL points to the last element.
    PRINT_FORWARD: Print the contents of the list from the first to the last element.
    PRINT_BACKWARD: Print the contents of the list from the last to the first element.

Getting Started

    Clone the repository.
    Compile the code using a C++ compiler.
    Enter commands as described in the Features section to interact with the XOR Linked List.
