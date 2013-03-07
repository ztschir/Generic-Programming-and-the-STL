// -------------
// Iteration.c++
// -------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <list>     // list

int main () {
    using namespace std;
    cout << "Iteration.c++" << endl;

    {
    int i = 0;
    int s = 0;
    while (i != 10) {
        s += i;
        ++i;}
    assert(i == 10);
    assert(s == 45);
    }

    {
    int i = 0;
    int s = 0;
    do {
        s += i;
        ++i;}
    while (i != 10);
    assert(i == 10);
    assert(s == 45);
    }

    {
    int s = 0;
    for (int i = 0; i != 10; ++i)
        s += i;
//  assert(i == 10);              // error: name lookup of 'i' changed for new ISO 'for' scoping
    assert(s == 45);
    }

    {
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    int s = 0;
    for (int i = 0, j = 0; i != 3; ++i, ++j)
        s += a[i] + b[j];
    assert(s == 27);
    }

    cout << "Done." << endl;
    return 0;}
