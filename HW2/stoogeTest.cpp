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

/* Alex's stoogesort: Given vector A, sort A[0...n-1] by
 * recursively sorting first two thirds, then second two thirds,
 * and then the first two thirds again by using the base case
 * of n = 2 and the lower index contains a higher value than
 * the higher index
 * Recurrence: T(n) = 3 * T(3n/2) + 1
 * Reasoning: 3 subproblems, each subproblem is of 3n/2 cost, with 1 indicating constant time operations
 */
void stoogeSort(vector <int>& vec, int low, int high)
{
	// Base case: n = 2, low element has higher value so swap
	if (vec.at(low) > vec.at(high))
	{
		int temp = vec.at(low);
		vec.at(low) = vec.at(high);
		vec.at(high) = temp;
	}

	// Recursive cases, n > 2
	if (high - low + 1 > 2)
	{
		int twoThirds = (high - low + 1) / 3; // ceiling(2n/3)
		
		// Recursive cases
		stoogeSort(vec, low, high - twoThirds); // sort first two thirds
		stoogeSort(vec, low + twoThirds, high); // sort second two thirds
		stoogeSort(vec, low, high - twoThirds); // sort first two thirds again
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

		stoogeSort(intVec2, 0, intVec2.size() - 1);
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

	insertOutput.open("stoogeTest.out", fstream::in | fstream::out | fstream::app);

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
