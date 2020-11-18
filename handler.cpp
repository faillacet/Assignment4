#include "handler.h"

handler::handler() {
    globalCounter = 0;
    openWindows = 0;
    usedWindows = 0;
    itemsQCurr = 0;
    itemsQTotal = 0;
}

handler::~handler() {
    cout << "Thank You!" <<endl;
}

void handler::getFile(string fileName) {
    ifstream myFile(fileName);
    int lineCount = 0;
    string x;
    if(myFile.is_open()) {
        while (getline(myFile, x)) {
           lineCount++;
        }
        myFile.close();
    }
    allData = new string[lineCount];
    globalLineCount = lineCount-1;
    ifstream myFile2(fileName);
    lineCount = 0;
    if (myFile2.is_open()) {
        while (getline(myFile2, x)) {
            allData[lineCount] = x;
            lineCount++;
        }
        myFile2.close();
    }
    else {
        cout << "Could not open file, program terminating." <<endl;
    }
}

void handler::dataSorter() {
    totalWindows = stoi(allData[0]);
    allInfo = new info[globalLineCount/3];                          //allocates max case just in case
    int counter = 1;
    int i = 0;
    while (counter<globalLineCount) {                                     //need to find a better way to implement this loop might b ok
        allInfo[i].time=stoi(allData[counter]);
        counter++;
        allInfo[i].numStudents=stoi(allData[counter]);
        counter++;
        allInfo[i].timeAtWindow = new int[allInfo[i].numStudents];
        for (int j = 0; j < allInfo[i].numStudents; ++j) {
            allInfo[i].timeAtWindow[j]=stoi(allData[j+counter]);
        }
        counter+=allInfo[i].numStudents;
        i++;
        globalCounter++;
    }
    delete[] allData;
}

void handler::simulation() {
    linkedList<int> list;
    linkedList<int> idleTime;
    queue<int> Q;
    unsigned int time = 0;   //time is in minutes -- clock
    int counter =0;
    bool arryEmpty = false;
    bool flag = false;
    continueRun = true;
    window = new int[totalWindows];
    for (int i = 0; i <totalWindows;++i){
        window[i] =0;
    }
    waitTime =  new int[globalLineCount-2];
    for (int i = 0; i < globalLineCount-2; ++i) {
        waitTime[i]=0;
    }
    idle = new int[globalLineCount-2];
	for (int i = 0; i < globalLineCount-2; ++i) {
		idle[i]=0;
	}


    //This is kinda complicated lets cut it into chunks


    while (continueRun) {
        //cout << "TIME:" << time << endl;

        //pushes the times (students) to the queue when needed -- top priority
        for (int i =0; i < globalCounter; ++i) {         
            if (allInfo[i].time==time) {
                for (int j = 0; j < allInfo[i].numStudents; ++j) {
                    Q.enqueue(list, allInfo[i].timeAtWindow[j]);
                    itemsQTotal++;
                }
            }
        }
    
        //prefroms window operations --- students sit at windows until their time is complete
        usedWindows = 0;
        for (int i=0;i<totalWindows;++i){                   // check if any windows opened and incrament if they have not
            if(window[i]!=0) {
                usedWindows++;
                window[i]--;
            }
        }
        //cout << usedWindows <<endl;                    --debugging purposes
        openWindows = totalWindows - usedWindows;       //updates amount of windows available
        for (int i = 0; i < totalWindows; ++i){
            if (window[i] == 0 && Q.isNotEmpty(list)) {
                window[i]=Q.dequeue(list);
                //cout << window[i] << " added to window" <<endl;
                itemsQCurr++;
            }
        }

        //timeing operations --- updates counters for amount of time sitting in line
        //calc wait times...
        for (int i = itemsQCurr; i <= itemsQTotal; ++i) {
            waitTime[i]++;
        }                 

        //WINDOW IDLE TIME CHECKER, PUSHES ALL THE IDLE TIMES TO A LINKED LIST THEN TO AN ARRAY
        for (int i =0; i < totalWindows; ++i) {
            if (window[i]==0) {
                idle[i]++;
            }
            else if (window[i]!=0 && idle[i]>0) {
                idleTime.insertBack(idle[i]);
                idle[i]=0;
            }
        }
        
        time++; //while loop runs every tick and checks for conditions
        if (itemsQTotal >= globalLineCount/2) {
            arryEmpty = true;
        }
        if (arryEmpty && Q.isEmpty(list) && openWindows == totalWindows) {
            continueRun = false;
        }
        if (time > 1000 && Q.isEmpty(list) && openWindows == totalWindows) {    //safety
            continueRun = false;
        }
    }
    //transfer from local to global
    for (int i = 0; i < globalLineCount-2; ++i) {
		idle[i]=0;
	}
    int x = idleTime.getSize();
    if (x>0) {
        for (int i =0; i <x;++i) {
            idle[i]=idleTime.removeFront();
        }
    }
   

    
    //clean up
    delete[] window;
    delete[] allInfo;
}

void handler::displayMetrics() {
    double temp = 0;
    int temp2 = 0;

    for (int i =1; i < itemsQTotal; ++i){
        cout << waitTime[i] <<endl;
    }

    //mean wait time
    for (int i =1; i < itemsQTotal; ++i){
        if (waitTime[i]!=0) {
            temp2++;
        }
        temp += waitTime[i];
    }
    temp = temp / (temp2);
    // case if only one item added
    if (itemsQTotal == 1) {
        temp = 0;
    }
    cout << "Mean Wait Time: ";
    cout << temp << endl;

    //median wait time
    newArr = new int[temp2];
    for (int i =0; i <= temp2;++i) {
        newArr[i]=0;
    }
    for (int i = 0; i <= temp2; ++i) {
        if (waitTime[i+1]!=0)
            newArr[i] = waitTime[i+1];
    }    
    if (temp2%2 == 0) {
        if (temp2==0) {
            cout << "Median Wait Time: 0" << endl;
        }
        else {
            cout << "Median Wait Time: ";
            cout << newArr[temp2/2] <<endl;
        }
        
    }
    else {
        cout << "Median Wait Time: ";
        cout << newArr[(temp2-1)/2] << endl;
    }

    //longest wait time
    temp = 0;
    if (temp2 <=1) {
        if (temp2 ==0) {
            cout << "Longest Wait Time: 0" <<endl;
        }
        else {
            cout << "Longest Wait Time: ";
            cout << waitTime[1] <<endl;
        }
    }
    else {
        for (int j = 0; j <=temp2;j++) {
            if (temp < newArr[j]) {
                temp = newArr[j];
            }
        }
        cout << "Longest Wait Time: ";
        cout << temp << endl;
    }
    
    //number of students waiting over 10 mins
    temp = 0;
    for (int j = 0; j <= temp2;j++) {
        if (newArr[j] > 10) {
            temp++;
        }
    }
    if (temp2==0)
        temp = 0;
    cout << "Number of Students waiting over 10 mins: ";
    cout << temp <<endl;

    //mean window idle time ----------------------------------------------------------------------------------
    temp = 0;
    temp2 = 0;
    for (int j = 0; j < globalLineCount-2;j++) {
        if (idle[j]!=0) {
            temp2++;
        }
        temp += idle[j];
    }
    if (temp2 !=0 && temp !=0) {
        temp = temp / (temp2);
    }
    else {
        temp = 0;
    }   
    cout << "Mean Window Idle Time: ";
    cout << temp << endl;
    
    //longest window idle time
    temp = 0;
    for (int j = 0; j < temp2;j++) {
        if (temp < idle[j]) {
            temp = idle[j];
        }
    }
    cout << "Longest Window Idle Time: ";
    cout << temp << endl;

    //number of windows idle for over 5 mins
    temp = 0;
    for (int j = 0; j <=temp2;j++) {
        if (idle[j] > 5) {
            temp++;
        }
    }
    cout << "Number of Windows idle over 5 mins: ";
    cout << temp <<endl;


    //more cleanup
    delete[] waitTime;
    delete[] newArr;
}