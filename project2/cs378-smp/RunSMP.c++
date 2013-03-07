// -------------------------------
// projects/collatz/RunSMP.c++
// -------------------------------

/*
 To run the program:
 % g++ -ansi -pedantic -Wall RunSMP.c++ -o RunSMP.c++.app
 % valgrind RunSMP.c++.app < RunSMP.in >& RunSMP.out
 
 To configure Doxygen:
 % doxygen -g
 That creates the file "Doxyfile".
 Make the following edits:
 EXTRACT_ALL            = YES
 EXTRACT_PRIVATE        = YES
 EXTRACT_STATIC         = YES
 GENERATE_LATEX         = NO
 
 To document the program:
 % doxygen Doxyfile
 */

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout, ios_base

#include "SMP.h"

// ----
// main
// ----

/**
 * Calls the solveSMP function
 */
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    solveSMP(cin, cout);
    return 0;}