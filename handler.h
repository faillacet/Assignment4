#ifndef HANDLER_H
#define HANDELR_H
#include "linkedList.h"
#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct info {           //struct that stores all collected data
    int time;           //clock tick
    int numStudents;
    int* timeAtWindow;
};

class handler {
    private:
    string* allData;
    info* allInfo;
    int totalWindows;
    int openWindows;
    int usedWindows;
    int globalLineCount;
    int globalCounter;
    int itemsQCurr;
    int itemsQTotal;
    int* window;
    int* waitTime;
    int* newArr;
    int* idle;
    bool continueRun;

    public:
    //getting information from file
    handler();
    ~handler();
    void getFile(string fileName);
    void dataSorter();                  //function sorts the data retreived from the list
    void simulation();
    void displayMetrics();
};

#endif