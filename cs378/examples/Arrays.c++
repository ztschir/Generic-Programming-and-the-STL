// ----------
// Arrays.c++
// ----------

#include <algorithm> // copy, count, equal, fill
#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <iostream>  // cout, endl
#include <vector>    // vector

struct A     {int i; void f () {}};
struct B : A {int j; void f () {}};

void f1 (int p[]) {
    assert(sizeof(p) == 8);
    ++p;
    ++p[0];
    ++*p;}

void f2 (int* p) {
    assert(sizeof(p) == 8);
    ++p;
    ++p[0];
    ++*p;}

int main () {
    using namespace std;
    cout << "Arrays.c++" << endl;

    {
    int a[] = {2, 3, 4};
    assert(*a == a[0]);
    assert(a  == &a[0]);
    assert(sizeof(a)     != sizeof(&a[0]));
    assert(sizeof(a)     == 12);
    assert(sizeof(&a[0]) == 8);
//  ++a;                                    // error: lvalue required as left operand of assignment
    ++a[0];
    assert(*a   == 3);
//  assert(a[3] == 0);                      // undefined
    }

    {
    const std::size_t s = 10;
    const int         a[s] = {2, 3, 4};
    assert(a[1]     == 3);
    assert(*(a + 1) == 3);
    assert(a[s - 1] == 0);
//  ++a;                                // error: lvalue required as left operand of assignment
//  ++a[1];                             // error: increment of read-only location
    }

    {
    const std::size_t s = 10;
//  const int         a[s];   // error: uninitialized const 'a'
    int a[s];
//  assert(a[0] == 0);        // undetermined
    }

    {
    const std::size_t s = 10;
    const int         a[s] = {};
    assert(a[0] == 0);
    }

    {
    int a[] = {2, 3, 4};
    assert(a[1] == 3);
    f1(a);
    assert(a[1] == 5);
    f2(a);
    assert(a[1] == 7);
    }

    {
    int        a[] = {2, 3, 4};
//  int        b[] = a;             // error: initializer fails to determine size of 'b'
    int* const b   = a;
    assert(a         == b);
    assert(sizeof(a) != sizeof(b));
    assert(sizeof(a) == 12);
    assert(sizeof(b) ==  8);
    ++a[1];
    assert(a[1] == 4);
    assert(b[1] == 4);
    }

    {
    int          a[] = {2, 3, 4};
    const size_t s   = sizeof(a) / sizeof(a[0]);
    int b[s];
    copy(a, a + s, b);
    assert(a != b);
    assert(equal(a, a + s, b));
    ++a[1];
    assert(a[1] == 4);
    assert(b[1] == 3);
    }

    {
    int a[] = {2, 3, 4};
    int b[] = {5, 6, 7};
//  b = a;                                     // error: invalid array assignment
    const size_t s = sizeof(a) / sizeof(a[0]);
    copy(a, a + s, b);
    assert(a != b);
    assert(equal(a, a + s, b));
    ++a[1];
    assert(a[1] == 4);
    assert(b[1] == 3);
    }

    {
    int a[] = {2, 3, 4};
    int b[] = {2, 2, 3};
    copy(a, a + 2, a + 1);      // GNU optimization
    assert(equal(a, a + 3, b));
    }

    {
    int a[] = {2, 3, 4};
    int b[] = {3, 4, 4};
    copy(a + 1, a + 3, a);
    assert(equal(a, a + 3, b));
    }

    {
    const std::size_t       s = 10;
    const int               v =  2;
          int*        const a = new int[s];
    fill(a, a + s, v);
    assert(count(a, a + s, v) == s);        // warning: comparison between signed and unsigned integer expressions
    f1(a);
    assert(a[1] == v + 2);
    f2(a);
    assert(a[1] == v + 4);
    delete [] a;
    }

    {
    const std::size_t       s = 10;
    const int               v =  2;
          int*        const a = new int[s];
    fill(a, a + s, v);
    int* const b = a;
    assert(&a[1] == &b[1]);
    int* const x = new int[s];
    copy(a, a + s, x);
    assert( a[1] ==  x[1]);
    assert(&a[1] != &x[1]);
    delete [] a;
    delete [] x;
    }

    {
    const std::size_t       s = 10;
    const int               v =  2;
          int*        const a = new int[s];
    fill(a, a + s, v);
    int* b = new int[s];
    fill(b, b + s, v);
//  b = a;                                  // memory leak
    copy(a, a + s, b);
    assert( a[1] ==  b[1]);
    assert(&a[1] != &b[1]);
    delete [] a;
    delete [] b;
    }

    {
//  int*    const a = new double[10]; // error: cannot convert 'double*' to 'int*    const' in initialization
//  double* const a = new int[10];    // error: cannot convert 'int*'    to 'double* const' in initialization
    }

    {
//  B a[] = {A(), A(), A()}; // error: conversion from "A" to non-scalar type "B" requested
    }

    {
    A a[] = {B(), B(), B()}; // slice
    a[1].f();                // A::f();
    }

    {
    A* const a = new B[10];       // dangerous
    a[0].f();                     // A::f()
//  a[1].f();                     // undefined
//  delete [] a;                  // undefined
    static_cast<B*>(a)[1].f();    // B::f()
    delete [] static_cast<B*>(a); // ~B::B() and ~A::A()
    }

    {
    const std::size_t s = 10;
    const int         v =  2;
          vector<int> x(s, v);
    assert(x.size() == s);
    assert(x[0]     == v);
    vector<int> y(x);
    assert(x.size() == y.size());
    assert( x[1]    ==  y[1]);
    assert(&x[1]    != &y[1]);
    vector<int> z(2 * s, v);
    x = z;
    assert(x.size() == z.size());
    assert( x[1]    ==  z[1]);
    assert(&x[1]    != &z[1]);
    }

    {
//  vector<A>* const p = new vector<B>; // error: cannot convert 'std::vector<B, std::allocator<B> >*' to 'std::vector<A, std::allocator<A> >* const' in initialization
    }

    cout << "Done." << endl;
    return 0;}
