#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
using namespace std;

template <class T>
struct listNode {
    T data;
    listNode* next = NULL;
    listNode* prev = NULL;
};

#endif