// ---------------
// CommandLine.c++
// ---------------

/*
% CommandLine.c++.app Nothing to be done.
*/

#include <algorithm> // equal
#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <string>    // string

int main (int argc, char* argv[]) {
    using namespace std;
    cout << "CommandLine.c++" << endl;

    assert(argc == 5);

    const string a[] = {"CommandLine.c++.app", "Nothing", "to", "be", "done."};
//  assert(argv == a);
    assert(equal(argv, argv + 5, a));

    cout << "Done." << endl;
    return 0;}
