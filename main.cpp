#include "linkedList.h"
#include "listNode.h"
#include "queue.h"
#include "handler.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
   string input;
   if (argc > 1) {
		cout << "Opening: " << argv[1] << endl;
		input = argv[1];
	}
	else {
		cout << "Enter File Name: " <<endl;		// used in case of no file name recieved from terminal
		cin >> input;
	}

    //testing phase
    handler test;
    test.getFile(input);
    test.dataSorter();
    test.simulation();
    test.displayMetrics();

    return 0;
}