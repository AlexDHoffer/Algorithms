/* Alex Hoffer: Parse a text file line by line and sort each line using insertion sort. Print the results to a file named "insert.out". */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

ofstream insertOutput; // Our output file.

/* An in-place sorting algorithm that follows the following procedure:
 * 	Given array A of length n:
 * 		- Let j = 0. 
 * 		- While j <= n
 * 			- Let key = A[j]
 * 			- Let i = j - 1
 * 			- While i > 0 and A[i] > key
 * 				- Let A[i + 1] = A[i]
 * 				- Decrement i
 * 			- Increment j
 * 			- Let A[i + 1] = key 
 */
void insertionSort(vector <int>& intVec)
{
	for (int i = 0; i < intVec.size(); i++) // Starting at second index, loop through the vector and compare the currently selected index to the indices before it.
	{
		int j = i;

		while (j > 0 && (intVec.at(j) < intVec.at(j - 1)))
		{
			int swapper = intVec.at(j);
			intVec.at(j) = intVec.at(j - 1);
			intVec.at(j - 1) = swapper;
			j -= 1;
		}
	}
}

// Generate random vectors.
void getIntVecs(vector < vector <int> >& intVec, int sizeOfEachVector, int sizeOfOverallVector)
{
	int intRange = 10001; // We want values from [0, 10000]

	for (int i = 0; i < sizeOfOverallVector; i++)
	{
		vector <int> tempVec;

		for (int j = 0; j < sizeOfEachVector; j++)
		{
			int randInt = rand() % intRange;
			tempVec.push_back(randInt);
		}	

		intVec.push_back(tempVec);
	}
}

// Sort the vectors in the vector and print out the results to the output file.
void processIntVec(vector < vector <int> > intVec)
{
	for (int i = 0; i < intVec.size(); i++)
	{
		vector <int> intVec2 = intVec.at(i);

		insertionSort(intVec2);
	}
}

int main(int argc, char* argv[])
{
	clock_t t;
	t = clock();

	if (argc != 2)
	{
		cout << "usage: " << argv[0] << " sizeOfEachVector" << endl;
		exit(1);
	}

	int sizeOfEachVector = atoi(argv[1]); // Our n. How big will each vector be?
	int numVectorsToSort = 20; // How many vectors of random ints should we make?

	srand(time(NULL));

	vector < vector <int> > intVec;		

	insertOutput.open("insertTest.out", fstream::in | fstream::out | fstream::app);

	getIntVecs(intVec, sizeOfEachVector, numVectorsToSort);

	processIntVec(intVec);

	insertOutput << "**BEGIN**" << endl;
	insertOutput << "Size of each vector: " << sizeOfEachVector << endl;
	insertOutput << "Number of vectors sorted: " << numVectorsToSort << endl;
	
	t = clock() - t;
	float convertedTime = ((float)t)/(CLOCKS_PER_SEC);
	insertOutput << "Total runtime: " << convertedTime << " seconds " << endl;

	insertOutput << "**END**" << endl << endl;

	insertOutput.close();

	return 0;
}
