// --------------
// Assertions.c++
// --------------

/*
Turn OFF assertions at compile time with NDEBUG.
% g++ -ansi -pedantic -DNDEBUG -Wall Assertions.c++ -o Assertions.c++.app
% Assertions.c++.app
*/

//#define NDEBUG

#include <cassert>  // assert
#include <iostream> // cout, endl

int cycle_length (int n) {
    assert(n > 0);
    int c = 0;
    while (n > 1) {
        if ((n % 2) == 0)
            n = (n / 2);
        else
            n = (3 * n) + 1;
        ++c;}
    assert(c > 0);
    return c;}

int main () {
    using namespace std;
    cout << "Assertions.c++" << endl;

    assert(cycle_length(1) == 1);
    assert(cycle_length(5) == 6);

    cout << "Done." << endl;
    return 0;}

/*
Assertions.c++
Assertion failed: (c > 0), function cycle_length, file Assertions.c++, line 25.
*/
