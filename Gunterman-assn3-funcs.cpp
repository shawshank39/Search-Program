//******************************************************************************************
// FILE NAME: 		Gunterman-assn3-funcs.cpp
// DESCRIPTION: 	This file contains the ADT function definitions for assn 1.
//
// FUNCTIONS: 		getRandNumArray -	fills empty array with unique random integers
//            		generateRandNum - 	generates random integer
//                  ensureUnique-		checks number to be stored agaisnt array to determine uniqueness
//***************************************************************************************** 

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// prototypes header file
#include "GuntermanShaw-assn3-common.h"
#include "Gunterman-assn3-funcs.h"
#include "Shaw-assn3-funcs.h"

using namespace std;

//*********************************************************************
// FUNCTION: 			getRandNumArray
// DESCRIPTION: 		Generates 5000 random integers and stores integers into array
// 						for tests
// INPUT:
//		Parameters:		randNumArray[] - array to be filled
// OUTPUT:
// 		Parameters: 	randNumArray[] - array of random integers
// CALLS TO: 			generateRandNum
// 						ensureUniqueNum
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
void getRandNumArray(int randNumArray[]){
	// variables
	const int MAX = 5000;
	int currentIndex = 0;
	int randomNum = 0;
	bool isUnique;
	
	// Use seed here instead of each iteration of generateRandNum
	srand(time(NULL));
	
	// for each index, generate random integer and check for unique
	for (int i = 0; i <= (MAX-1); i++){
		randomNum = generateRandNum();
		isUnique = ensureUniqueNum(randNumArray, randomNum);
		
		// if not unique, then continue to generate and check
		// random integers until a unique is created
		if (isUnique==false){
			while (isUnique==false ){
				randomNum = generateRandNum();
				isUnique = ensureUniqueNum(randNumArray, randomNum);
			}
		}
		
		// insert unique random number in current index
		// then incremement current index
		randNumArray[currentIndex] = randomNum;
		currentIndex++;
	}	
	return;
	
}

//*********************************************************************
// FUNCTION: 		ensureUniqueNum
// DESCRIPTION: 	Compares random integer to list of stored integers to ensure
// 					integer is unique
// INPUT:
// 		Parameters: randomArray[] - array of random integers
// 					randNum- random integer to compare
// OUTPUT:
// 		Return val: isUnique: boolean value to determine if unique
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
bool ensureUniqueNum (int randomArray[], int randNum ){
	// variables
	bool isUnique = true;
	const int MAX_INDEX = 4999;
	int index = 0;
	
		// while unique and index is less than max indices
		while ((isUnique==true) && (index <= MAX_INDEX) ){
			// if number to check equals a number in array
			// then unique is set to false else increment 
			// the index and keep searching
			if (randNum == randomArray[index]){
				isUnique = false;
			} else {
				index++;
			}
		}
		return isUnique;
	
}

//*********************************************************************
// FUNCTION: 		generateRandNum
// DESCRIPTION: 	Generates a random integer
// OUTPUT: 			randNum- random integer
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
int generateRandNum(){
	int randNum = 0;
	const int MAX_RAND_NUM = 30000;
	// calls rand and modulos against the range limit
	randNum = rand() % MAX_RAND_NUM + 1;
	return randNum;
}

//*********************************************************************
// FUNCTION: testChaining
// DESCRIPTION: 		Takes an array of random integers, tablesize, 
//						attempts to fill hash array and resolve collisions 
//						with chaining. Then performs search for every 
//						other array in random array and calculates average number
//						of items searched and theoretical average with Knuth�s formula
// INPUT:
// 		Parameters: randomArray[] - array of random integers
//					chainList- uninitialized array of pointers
// 					tableSize - size of hash table to create
//
// CALLS TO: 		createPtrHTable
// 					addToList
// 					destroyList
// 					searchChainTable
// 					calcActualAvg
// 					calcPredictedAvg
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
void testChaining(hashNode **&chainList, int randNumArray[], int tableSize){
	int numToSearch =0;
	int indexToStore=0;
	int rollingCount=0;
	int numToStore=0;
	double predAverage=0;
	double actAverage=0;
	char whichTest= 'C';
	int totalSearched = 2500; // Replace with constant!
	int count = 0;
	
	// initialize array of pointers
	createPtrHTable(tableSize, chainList);
	
	// fill separate chaining hash table and resolve collisions
	// by adding node to linked list at array index
	for (int i = 0; i < MAX_SIZE; i++ ){
		indexToStore = randNumArray[i]%tableSize;
		numToStore = randNumArray[i];
		addToList(chainList, numToStore, indexToStore);
	}
	
	// search array for even numbers and track items examined
	for (int n = 1; n < MAX_SIZE; n=n+2){
	 	
	 		numToSearch = randNumArray[n];
	 		rollingCount += searchChaining(chainList, numToSearch, tableSize);
		 
	 }
	
	// calculate actual average
	actAverage= calcActualAvg(rollingCount, totalSearched );
	
	// calculate predicted average using Knuth's formula
	predAverage= calcPredictedAvg(tableSize, whichTest);
	
	
	cout << "Chaining:" << endl;
    cout << setw(5) << " " << rollingCount << " items examined (avg = "  
         << fixed << setprecision(3) << actAverage << " items examined per search)"
         << endl;
   
    cout << setw(7) << " " << "vs predicted Knuth avg = " << predAverage 
         << " items examined per search"<< endl << endl;
	 
	 // destroy lists after finished
	for (int m = 0; m < tableSize; m++ ){
	 	destroyList(chainList, m);
	}
	 return;	 
}

//*********************************************************************
// FUNCTION: 			createPtrHTable
// DESCRIPTION: 		Creates chaining hash table to store integers and resolve collisions
// INPUT: 
//		Parameters:		chainHTable- array to be initialized
// 						tableSize- size of array to initialize
// OUTPUT:
// 		Parameters: 	chainHTable- array to be initialized
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
void createPtrHTable(int tableSize, hashNode **&chainHTable){
	
	// allocate memory for new array
	chainHTable = new (nothrow) hashNode*[tableSize]();
	
	if (chainHTable == NULL){
		cout << "Out of heap space!!" << endl;
	}

	return;
}

//*********************************************************************
// FUNCTION: 		addToList
// DESCRIPTION: 	Adds integer to linked list in chaining table
// INPUT:
// 		Parameters: HTable - array of linked lists
// 					index- index indicating where the number will be stored
// 					numToStore- integer to be stored in chaining table
// OUTPUT:
//		Parameters: HTable by reference
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
void addToList(hashNode **&hTable, int numToStore, int index ){
 	
 	// allocate memory for new node
 	hashNode *newNode = new (nothrow) hashNode;
	
	// if memory not allocated, issue error
 	if (newNode == NULL){
 		cout << "Out of heap space!" << endl;
	}else{
	 	// initialize node
	 	newNode->data = numToStore;
	 	newNode->next = NULL;
	 	
	 	// if list at index is empty, set first node else 
	 	// add to the front of the linked list
	 	if (hTable[index]==NULL){
		 	hTable[index] = newNode;
	 	}else{
	 		newNode->next = hTable[index];
	 		hTable[index] = newNode;
	 	}
	}
	 return;
 }
 
 //*********************************************************************
// FUNCTION: 			destroyList
// DESCRIPTION: 		Deallocates memory at index of chaining table
// INPUT: 
//		Parameters:		chainList- array of linked lists
// 						index - index containing list to destroy
//OUTPUT:
// 		Parameters: 	chainList - array of linked lists
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
 bool destroyList(hashNode **&chainList, int index){
 	// Declare temp node
	hashNode* nodeToDelete;
	
	// Set destroy flag to false
	bool isDestroyed = false;
	
	// if no data stored at index, issue message
	// else iterate through list and delete nodes
	if (chainList[index] != NULL){
	
		while(chainList[index]!= NULL){
		
	 		nodeToDelete = chainList[index];
	 		chainList[index] = chainList[index]->next;
	 		delete nodeToDelete;
		}
	}
	
	// Whether no data existed or all data destroyed, alter flag
	isDestroyed = true;
	return isDestroyed;
 }
 
 //*********************************************************************
// FUNCTION: 			searchChaining
// DESCRIPTION: 		Searches chain table for half of the integers in the list of random
// 						integers and calculates number of items examined
// INPUT:
// 		Parameters: 	chainArray- array of random integers
// 						numTosearch- number to find in hash table
// OUTPUT:
// 		Parameters: 	itemsExamined- number of items examined
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
 int searchChaining(hashNode **&chainArray, int numToSearch, int tableSize){
 	int itemsExamined = 0;
 	bool isFound = false;
 	int index = 0;
	hashNode* tempNode;
	
	// Calculate initial key from first hash
 	index = numToSearch % tableSize;
 	
 	// Set temp node to head of linked list at array index
	tempNode = chainArray[index];
	
	// If location is empty, issue message, else
	// compare search term to each item in list until found
 	if (tempNode==NULL){
 		cout << "No values stored in this location" << endl;
	 }else{
 		do  {
				// if data match found, increment items examined
				// and exit loop, else proceed to next node
				if (tempNode->data == numToSearch){
		 		isFound = true;
		 		}else{
				 	tempNode= tempNode->next;
		 		}
			 	itemsExamined++;
		}while(tempNode!=NULL && isFound == false );
	}
	return itemsExamined;
 }
 //*********************************************************************
// FUNCTION: 		getHTableSize
// DESCRIPTION: 	Returns size of array
// INPUT:
// 		Parameters: hTable- hash table to be evaluated
// OUTPUT:
// 		Parameters: tableSize- size of the hash table
//
//IMPLEMENTED BY: Starlla Gunterman
//**********************************************************************
int getHTableSize(){
	// variables
	int tableSize = 0;
	// constants
	const int MIN = 6700;
	
	// prompt user for table size
	cout << "Please enter desired table size to test: ";
	cin >> tableSize;
	
	// make sure table size is over the minimum value
	while (tableSize < MIN ){
	cout << "Table size too low. "
		 << "Please enter desired table size to test: ";
	cin >> tableSize;	
	}
	return tableSize;
 }
