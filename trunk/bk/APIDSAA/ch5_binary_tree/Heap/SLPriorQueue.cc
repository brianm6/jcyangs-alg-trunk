// Module Name: SLPriorQueue.cc
// Objective: Show the sample to use the generic sorted list priority queue
// 			  implementation
// Author: jcyang[at]ymail.com
// Date: 29.Jan.2010
// Revision: Alpha

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "SLPriorQueue.h"
#include "..\BST\Random.h"
#include "..\BST\Comp.h"
using namespace std;

int main() {
	int size;
	const int maxsize = 256;
	int inputMethod;
	string* strJobArr;
	int* intPriorArr; // bigger number higher priority
	string insertJob;
	int insertPrior;

	srand(time(NULL));
	strJobArr = new string[maxsize];
	intPriorArr = new int[maxsize];

	cout << "size = ";
	cin >> size;
	cout << "input method(random = 0, manual = 1) = ";
	cin >> inputMethod;
	for (int i = 0; i < size; i++) {
		if (inputMethod == 0) {
			strJobArr[i] = randomStrGen(6);
			intPriorArr[i] = rand() % 10;
		} else if (inputMethod == 1) {
			cout << "\t" << i << "st job-priority pair = ";
			cin >> strJobArr[i] >> intPriorArr[i];
		}
	}
	
	cout << "+ the input job-priority pair is : " << endl;
	for (int i = 0; i < size; i++) 
		cout << strJobArr[i] << setw(20) << intPriorArr[i] << endl;
	cout << endl;
	
	SLPriorQueue<string, int, IntComparator> slPriorQueue(strJobArr, intPriorArr, size, maxsize);

	cout << "+ after build up the priority queue : " << endl;
	slPriorQueue.show();
	cout << endl;

	// insert job-priority pair
	cout << "+ insert job-priority pair = ";
	cin >> insertJob >> insertPrior;

	slPriorQueue.insert(insertJob, insertPrior);

	cout << "+ after inserted the job-priority pair : " << endl;
	slPriorQueue.show();
	cout << endl;

	// peek next job
	string nextJob;
	slPriorQueue.peekNext(nextJob);
	cout << "+ peek next job = " << nextJob << endl;
	cout << endl;

	// remove next job
	slPriorQueue.show();
	cout << endl;
	slPriorQueue.getNext(nextJob);
	cout << "+ remove next job = " << nextJob << endl;
	slPriorQueue.show();
	
	return 0;
}
