#ifndef QUEUE_H
#define QUEUE_H

#include "linkedList.h"
#include <iostream>
using namespace std;

template <class T>
class queue {
    private:
    int top;

    public:
    queue();
    ~queue();
    void enqueue(linkedList<T> &list, T data);
    T dequeue(linkedList<T> &list);
    void display(linkedList<T> &list);
    bool isEmpty(linkedList<T> &list);
    bool isNotEmpty(linkedList<T> &list);
    T peekFront(linkedList<T> &list);
};

template <class T>
queue<T>::queue(){
    //create linked list to use
}

template <class T>
queue<T>::~queue(){
    //delete linked list
}

template <class T>
void queue<T>::enqueue(linkedList<T> &list, T data) {
    list.insertBack(data);
}

template <class T>
T queue<T>::dequeue(linkedList<T> &list) {
    return list.removeFront();
}

template <class T>
void queue<T>::display(linkedList<T> &list) {
    list.displayList();
}

template <class T>
bool queue<T>::isEmpty(linkedList<T> &list) {
    if (list.isEmpty())
        return true;
    else
        return false;    
}

template <class T>
bool queue<T>::isNotEmpty(linkedList<T> &list) {
    if (list.isEmpty())
        return false;
    else
        return true;    
}

template <class T>
T queue<T>::peekFront(linkedList<T> &list) {
    return list.peekHead();
}

#endif