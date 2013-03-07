// -------------
// Variables.c++
// -------------

#include <algorithm> // equal
#include <cassert>   // assert
#include <iostream>  // cout, endl

int main () {
    using namespace std;
    cout << "Variables.c++" << endl;

    {
    int i = 2;
    int v = i;
    ++v;
    assert(i  == 2);
    assert(v  == 3);
    assert(&i != &v);
    }

    {
    int  j = 2;
    int* p = &j;
    ++*p;
    assert(j  == 3);
    assert(*p == 3);
    assert(p  == &j);
    }

    {
    int  k = 2;
    int& r = k;
    ++r;
    assert(k  == 3);
    assert(r  == 3);
    assert(&r == &k);
    }

    {
    int   i = 2;
    int*  p = &i;
    int*& r = p;
    ++*r;
    assert(i  == 3);
    assert(*p == 3);
    assert(*r == 3);
    assert(&r == &p);
    }

    {
    int a[] = {2, 3, 4};
    assert(*a == a[0]);
    assert(a  == &a[0]);
    assert(sizeof(a)     != sizeof(&a[0]));
    assert(sizeof(a)     == 12);
    assert(sizeof(&a[0]) == 8);
//  ++a;                                    // error: lvalue required as left operand of assignment
    ++a[1];
    ++*(a + 1);
    assert(a[1]     == 5);
    assert(*(a + 1) == 5);
//  assert(a[3]     == 0);                  // undefined
    }

    {
    int a[] = {2, 3, 4};
//  int b[] = a;                    // error: initializer fails to determine size of 'b'
    int* b  = a;
    assert(a         == b);
    assert(sizeof(a) != sizeof(b));
    assert(sizeof(a) == 12);
    assert(sizeof(b) ==  8);
    ++b[1];
    assert(a[1] == 4);
    assert(b[1] == 4);
    }

    {
    int a[] = {2, 3, 4};
    int b[] = {2, 3, 4};
    assert(a != b);
    assert(equal(a, a + 3, b));
    }

    cout << "Done." << endl;
    return 0;}
