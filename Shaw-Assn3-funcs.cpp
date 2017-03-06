//******************************************************************************************
// FILE NAME:       Shaw-assn3-funcs.cpp
// DESCRIPTION:     This file contains the ADT function definitions for assn 3.
//
// FUNCTIONS:       testLinProbe - Manager function for the Linear Probe test
//                  testDblHash -  Manager function for the Double Hashing Test
//                  startLinProbe - Linear Probe collision handler
//                  startDblHash - Double Hashing collision handler
//                  searchOpenAddrTable - Searching function that returns the 
//                                        number of items examined.
//                  calcActualAvg - Calculates the actual average number of items 
//                                  per search
//                  calcPredictedAvg - Calculates the predicted average number of 
//                                     items per search
//***************************************************************************************** 
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Shaw-assn3-funcs.h"
#include "GuntermanShaw-assn3-common.h"
using namespace std;

//*********************************************************************
// FUNCTION: testLinProbe
// DESCRIPTION: Takes an array of random integers and table size, attempts to fill hash
//              array and resolve collisions with linear probing. Then performs search
//              for every other array in random array and calculates average number
//              of items searched and theoretical average with Knuth’s formula
// INPUT:
//      Parameters: 
//          randomArray[] - array of random integers
//          tableSize - size of hash table to create
// CALLS TO:
//      startLinProbe
//      searchOpenAddrTable
//      calcActualAvg
//      calcPredictedAvg
//IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
void testLinProbe(int randomArray[], int tableSize)
{
    double predAverage, actAverage;
    char whichTest = 'L'; // Used to denote this is the Linear Probe Test
    int openAddrTable[tableSize]; // The linear probing methods Hash Table
    int currentNum, key, index, itemsExamined; 
    
    // Walks the openAddrTable to initialize the values to zero
    for (int f = 0; f < tableSize; f++)
    {
        openAddrTable[f] = 0;
    }
    
    //For loop walks the Random Array gets one number at a time for processing
    for (int i = 0; i < MAX_SIZE; i++)
    { 
        
        // Assigns the current number from the random array to currentNum
        currentNum = randomArray[i]; 
        
        // Creates the initial Key
        key = currentNum % tableSize;
        
        // If this Array location is empty... fill it.
        if (openAddrTable[key] == 0)
        {
            openAddrTable[key] = currentNum;
        }   
        else // Else handle collision via linear probing
        {
            index = startLinProbe(openAddrTable, key, tableSize);
            openAddrTable[index] = currentNum;
        }
       
    } // End for loop
    
    // Run the search 
    itemsExamined = searchOpenAddrTable (openAddrTable, randomArray, whichTest, tableSize);
    
    // Actual Average 
    actAverage = calcActualAvg (itemsExamined, TOTAL_SEARCHED);
    
    // Predicted Average 
    predAverage = calcPredictedAvg (tableSize, whichTest);
    
    // Output the results of the test to the screen
    cout << "Linear Probing:" << endl;
    cout << setw(5) << " " << itemsExamined << " items examined (avg = "  
         << fixed << setprecision(3) << actAverage << " items examined per search)"
            << endl;
   
    cout << setw(7) << " " << "vs predicted Knuth avg = " << predAverage 
            << " items examined per search"<< endl << endl;
}

//*********************************************************************
// FUNCTION: testDblHash
// DESCRIPTION: Takes an array of random integers and table size, attempts to fill hash
//              array and resolve collisions with double hashing. Then performs search
//              for every other array in random array and calculates average number
//              of items searched and theoretical average with Knuth's formula
// INPUT:
//      Parameters: 
//          randomArray[] - array of random integers
//          tableSize - size of hash table to create
// CALLS TO:
//      startDblHash
//      searchOpenAddrTable
//      calcActualAvg
//      calcPredictedAvg
//IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
void testDblHash(int randomArray[], int tableSize)
{
    
    char whichTest = 'D'; // denotes the test is Double Hashing
    int openAddrTable [tableSize]; // The Double Hashing methods hash table.
    double predAverage, actAverage;
    int currentNum, key, itemsExamined, index;
    int totalSearched = MAX_SIZE / 2; 
    
    
    // Walks the openAddrTable to initialize the values to zero
    for (int f = 0; f < tableSize; f++)
    {
        openAddrTable[f] = 0;
    }
    
    //For loop walks the Random Array gets one number at a time for processing
    for (int i = 0; i < MAX_SIZE; i++)
    { 
        
        // Assigns the current number from the random array to currentNum
        currentNum = randomArray[i]; 
        
        // Creates the initial key
        key = currentNum % tableSize;
        
        // If this Array location is empty... fill it.
        if (openAddrTable[key] == 0)
        {
            openAddrTable[key] = currentNum;
        }   
        else // Else handle collision via linear probing
        {
            index =  startDblHash(openAddrTable, key, tableSize);
            openAddrTable[index] = currentNum;
        }
       
    } // End for loop
    
    // Run the search 
    itemsExamined = searchOpenAddrTable (openAddrTable, randomArray, whichTest, tableSize);
    
    // Actual Average
    actAverage = calcActualAvg (itemsExamined, totalSearched);
    
    // Predicted Average calculation
    predAverage = calcPredictedAvg (tableSize, whichTest);
    
    // Output the test results to the screen
    cout << "Double Hashing:" << endl;
    cout << setw(5) << " " << itemsExamined << " items examined (avg = "  
         << fixed << setprecision(3) << actAverage << " items examined per search)"
            << endl;
   
    cout << setw(7) << " " << "vs predicted Knuth avg = " << predAverage 
            << " items examined per search"<< endl << endl;
    
   
}

//*********************************************************************
// FUNCTION: startLinProbe
// DESCRIPTION: Takes the Open Addressing Array, initialKey, and tableSizs as input 
//              parameters and returns an integer location where the item needs to 
//              be inserted.
// INPUT:
//      Parameters: 
//          openAddrTable[]- hash table to probe
//          initialKey - initial key Value coming into the function
//          tableSize - size of the hash table array
// OUTPUT:
//      Return val: index- index found as result of linear probe
// IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
int startLinProbe (int openAddrTable[], int initialKey, int tableSize)
{
    int currentIndex;   // Integer value for the current index
    bool empty = false; // bool value for if the array location is empty
    
    currentIndex = initialKey; // assign the key to current Index
    
    do {
        currentIndex++; 
        
        // if the Array location is empty, return true
        if (openAddrTable[currentIndex] == 0)
            empty = true;
        
        // If we have reached the end of the array, move to the front
        if (currentIndex == (tableSize - 1))
            currentIndex = 0;
        
        
    } while (!empty);
    
    
    return currentIndex;
}

//*********************************************************************
// FUNCTION: startDblHash
// DESCRIPTION: Takes the Open Addressing Array, initial key, and table size as
//              input parameters and returns an integer location where the item 
//              needs to be inserted.
// INPUT:
//      Parameters: 
//          openAddrTable[]- hash table to probe
//          initialKey - initial key value 
//          tableSize - table size of the hash table.
// OUTPUT:
//      Return val: index- index found as result of double hash
//
//IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
int startDblHash (int openAddrTable[], int initialKey, int tableSize)
{
    int currentIndex; // Current Index of the array
    int secMod = (initialKey % (tableSize - 2)) + 1; // Second mod calculation
    
    bool empty = false; // bool value for if the array location is empty
    
    
    
    currentIndex = initialKey; // assign the key to current Index
   
    do { 
        
        // currentIndex calculation (new key = current key + x mod tableSize)
        currentIndex = (currentIndex + secMod) % tableSize;
        
        // if the Array location is empty, return true
        if (openAddrTable[currentIndex] == 0)
            empty = true;
        
        
    } while (!empty);
    
    
    return currentIndex;
}

//*********************************************************************
// FUNCTION: searchOpenAddrTable
// DESCRIPTION: Takes the Open Addressing Array, random array, char for which test, 
//              and table size, as input parameters and returns an integer value 
//              for the number of items examined.
// INPUT:
//      Parameters: 
//          openAddrTable[]- hash table to search
//          randNumArray[]- random int array to search
//          whichTest - Char value for whether the test is linear probing or 
//              double hashing.
//          tableSize - size of the hashtable
// OUTPUT:
//      Return val: itemsExamined- number of items examined
//IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
int searchOpenAddrTable (int openAddrTable[], int randNumArray[], char whichTest, int tableSize)
{
    int itemsExamined = 0;
    int currentNum, secMod, currentIndex, key, initialKey;
    bool found;
    
    if (whichTest == 'L')
    {
        // for loop that walks the randNumArray grabbing one number at a time
        for (int i = 1; i < MAX_SIZE; i = i + 2)
        {
            // Resets the found flag for each new number
            found = false;
            
            // gets the current number in the random number array
            currentNum = randNumArray[i]; 
            
            // creates the initial key
            key = currentNum % tableSize; 
            
            // Do...while walks the openAddrTable to find the number
            do
            {
                // Increment count for number of items examined
                itemsExamined++;
                
                // Checks to see if the number equals the current number in array
                if (currentNum == openAddrTable[key])
                {
                    // Found it!
                    found = true;
                }
                    
               
                // If you have reached the end of the array, go back to the beginning
                if (key == (tableSize - 1))
                    key = -1;
                
                key++;
            } while(!found); // End do...while
        } // End For Loop
    }
    else if (whichTest == 'D')  
    {
        // Double Hashing if else
        
        for (int i = 1; i < MAX_SIZE; i = i + 2)
        {
            // Resets the flag for each number
            found = false;
            
            // gets the current number in the random number array
            currentNum = randNumArray[i]; 
            
            // creates the initial key
            initialKey = currentNum % tableSize; 
            
            // Calculates the second mod
            secMod = (initialKey % (tableSize - 2)) + 1; 
            
            // assign the key to current Index
            currentIndex = initialKey; 
           
            // Do...while walks the openAddrTable to find the number
            do
            {
                // Increment count for the number of items examined
                itemsExamined++;
                
                // Checks to see if the number equals the current number in array
                if (currentNum == openAddrTable[currentIndex])
                    found = true;
        
                // applies the second mod to alter the index on next pass of the loop
                currentIndex = (currentIndex + secMod) % tableSize;
                
            } while(!found); // End do...while
        } // End For Loop

    } // End Double Hashing else if..
    
    
    return itemsExamined;
}
//*********************************************************************
// FUNCTION: calcActualAvg
// DESCRIPTION: Takes the amount of items actually examined and the total items
//              searched and returns the Actual Average.
// INPUT:
//      Parameters: 
//          itemsExamined- number of items examined in search
//          totalSearched- total items searched
// OUTPUT:
//      Return val: actualAvg- actual average of items examined
//IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
double calcActualAvg (int itemsExamined, int totalSearched)
{
	double average;
	double decItemsExamined = static_cast<double>(itemsExamined); 
	double decTotalSearched = static_cast<double>(totalSearched); // 2500
        
        // Calculate average
	average = decItemsExamined / decTotalSearched;

	return average;
}

//*********************************************************************
// FUNCTION: calcPredictedAvg
// DESCRIPTION: Takes the tableSize, and character for which test is being computed
//              as input parameters and will use the constant for number of records in
//              the table (5000). Returns the computed average
// INPUT:
//      Parameters: 
//          tableSize- size of the table
//          whichTest- collision method to calculate average for
// OUTPUT:
//      Return val: predictedAvg- predicted average of items examined
//IMPLEMENTED BY: Kevin Shaw
//**********************************************************************
double calcPredictedAvg (int tableSize, char whichTest)
{	
	double average; 
	double totalNumOfItems = static_cast<double>(MAX_SIZE);  
	double loadFactor = totalNumOfItems / tableSize;
        
	
        if (whichTest == 'L') // Linear Probing
	{
            // 1/2 {1 + (1 / (1 - a))}
            average = .5 * (1 + (1 / (1 - loadFactor)));

	}
	else if (whichTest == 'D') // Double Hash
	{
            //-(1/α)ln(1 - α)
            average = -(1/ loadFactor) * log(1 - loadFactor);

	}
	else if (whichTest == 'C') // Chain test
	{
            average = 1 + (loadFactor / 2);

	}

	return average;
}
