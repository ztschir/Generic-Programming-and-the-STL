// --------
// Auto.c++
// --------

/*
% g++-4.5 -pedantic -std=c++0x -Wall Auto.c++ -o Auto.c++.app
% Auto.c++.app
*/

#include <cassert>
#include <iostream>

int main () {
    using namespace std;
    cout << "Auto.c++" << endl;

    auto b = true;
    assert(sizeof(b)    == 1);
    assert(sizeof(bool) == 1);

    auto c = 'a';
    assert(sizeof(c)    == 1);
    assert(sizeof(char) == 1);

    auto i = 2;
    assert(sizeof(i)   == 4);
    assert(sizeof(int) == 4);

    auto j = 2L;
    assert(sizeof(j)    == 8);
    assert(sizeof(long) == 8);

    auto f = 2.34F;
    assert(sizeof(f)     == 4);
    assert(sizeof(float) == 4);

    auto d = 2.34;
    assert(sizeof(d)      == 8);
    assert(sizeof(double) == 8);

    auto ld = 2.34L;
    assert(sizeof(ld)          == 16);
    assert(sizeof(long double) == 16);

    cout << "Done." << endl;
    return 0;}
