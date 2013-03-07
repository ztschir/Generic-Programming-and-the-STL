// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2011
// Glenn P. Downing
// --------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

// --------
// global
// --------
const int sizeOfCache = 1000000;
int cycleLengthCache[sizeOfCache] = {0};

// ------------
// collatz_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// collatz_eval_single_helper
// ------------

/**
 * @param inputNumber is the number to calculate the cycle length
 * @param cycleLength is the current cycle length for the recursive function
 * @return the max cycle length for input i
 */
short collatz_eval_single_helper (unsigned long inputNumber, short cycleLength) {
    assert(inputNumber > 0);
    assert(cycleLength >= 0);
    
    if(inputNumber < (unsigned long)sizeOfCache && cycleLengthCache[inputNumber] != 0){
        
        return cycleLengthCache[inputNumber] + cycleLength;
    }
    else if(inputNumber == 1){
        cycleLengthCache[1] = 1;
        return cycleLength;
    }
    else{
        unsigned long previousValue = inputNumber;
        short previousCycleLength = cycleLength;
        
        if(inputNumber % 2 == 0)
            inputNumber /= 2;
        else{
            inputNumber += (inputNumber >> 1) + 1;
            ++cycleLength;
        }
        ++cycleLength;
        
        short finalCycleLength = collatz_eval_single_helper(inputNumber, cycleLength);
        if(previousValue < (unsigned long)sizeOfCache)
            cycleLengthCache[previousValue] = finalCycleLength - previousCycleLength;
        return finalCycleLength;
    }
}


// ------------
// collatz_eval_single
// ------------

/**
 * @param inputNumber is the number to calculate the cycle length for
 * @return the max cycle length for input i
 */
short collatz_eval_single (int inputNumber) {
    short cycleLength = 0;
    return collatz_eval_single_helper((unsigned long)inputNumber, cycleLength);
}

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    // <your code>
    
    // Need to switch the numbers around if they 
    // are in reverse order
    if(i > j){
        int temp = i;
        i = j;
        j = temp;
    }
    
    int v = 1;
    while(i <= j){
        int current = (int)collatz_eval_single(i);
        if(current > v){
            v = current;
        }
        ++i;
    }
    assert(v > 0);
    return v;}

// -------------
// collatz_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    // Precache ranges between 1 and 1000 for small speed increase
    collatz_eval(1, 1000);
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
