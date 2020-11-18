#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "listNode.h"
#include <iostream>
using namespace std;

template <class T>
class linkedList {
private:
    listNode<T>* head;
    listNode<T>* rear;
    int size;
public:
    linkedList();
    ~linkedList();
    void insertBack(T data);
    T removeFront();
    bool isEmpty();
    void displayList();
    T peekHead();
    int getSize();
};

template <class T>
linkedList<T>::linkedList() {
    head = NULL;
    rear = NULL;
    size = 0;
}

template <class T>
linkedList<T>::~linkedList() {
    //cout << "List Deleted!"<<endl;
}

template <class T>
void linkedList<T>::insertBack(T dataN) {
    listNode<T>* newNode = new listNode<T>;
    newNode->data = dataN;
    if (isEmpty()) {
        head = newNode;
        rear = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
        ++size;
    }
    else {
        rear->next = newNode;
        newNode->prev = rear;
        newNode->next = NULL;
        rear = newNode;
        ++size;
    }
}

template <class T>
T linkedList<T>::removeFront() {
    if (isEmpty()) {
        cout << "List empty can not remove!"<<endl;
        return 99;                                       //MUST FIX LATER NEED TO FIND SOLUTION
    }
    listNode<T>* temp;
    temp = head;
    if (head->next == NULL) {
        head = NULL;
        rear = NULL;
        return temp->data;
    }
    head = head->next;
    head->prev = NULL;
    return temp->data;
}

template <class T>
bool linkedList<T>::isEmpty() {
    if (head == NULL) {
        return true;
    }
    else {
        return false;
    }
}

template <class T>
void linkedList<T>::displayList() {
    listNode<T>* temp = new listNode<T>;
    temp = head;
    while (temp != NULL){
        cout << temp->data <<endl;
        temp = temp->next;
    }
    delete temp;
}

template <class T>
T linkedList<T>::peekHead() {
    return head->data;
}

template <class T>
int linkedList<T>::getSize() {
    return size;
}

#endif