//***********************************************************************************
//	CODE FILENAME:		GuntermanShaw-assn3-main.cpp
//	DESCRIPTION:		This program creates an array of random unique integers that is
//						used to populate a hash table. Three different kinds of hash 
//						collisions are tested: linear probing, double hashing, and
//						separate chaining. The program then searches for half of the items
//						in the random array and calculates the actual average number of
//						items that were examined for each collision resolution method as
//						well as the predicted average using Knuth's formulas.
//
//	CLASS/TERM:			CS 372/Spring 8W1 2017
//	DESIGNER:			Starlla Gunterman and Kevin Shaw
//	FUNCTIONS:			// TODO: add function lists
//
//***********************************************************************************
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "GuntermanShaw-assn3-common.h"
#include "Gunterman-assn3-funcs.h"
#include "Shaw-assn3-funcs.h"

using namespace std;

int main() {
    
    double loadFactor;
    double totalNumOfItems = static_cast<double>(MAX_SIZE);
    int tableSize = 0;

	// declare array to store random numbers
	int randNumArray[MAX_SIZE];
	
	// call to get random number array	
	getRandNumArray(randNumArray);

        // declare array of hashNodes
	hashNode **chainArray;
        
        // get table size from user
	tableSize = getHTableSize();  
        
        // Calculate the load factor
        loadFactor = totalNumOfItems / tableSize;
        
       // Display program header
        cout << endl <<  MAX_SIZE << " items loaded into " << tableSize << " element hash table" << endl;
        cout << fixed << setprecision(3)<<  "LoadFactor: "<< loadFactor << endl << endl;
        cout << "Result of searching for " << TOTAL_SEARCHED << " items:" << endl << endl;
        
        // Test 1 - Linear Probing
        testLinProbe(randNumArray, tableSize);
        
        // Test 2 - Double Hashing 
        testDblHash(randNumArray, tableSize);
        
        // Test 3 - Chaining
        testChaining(chainArray, randNumArray, tableSize);  
        
return 0;
}

