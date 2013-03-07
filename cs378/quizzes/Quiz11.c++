/*
CS378: Quiz #11 (9 pts)
*/

/* -----------------------------------------------------------------------
1. What is the output of the following program?
   (9 pts)

A()

new:
A(A) ~A()

allocator:
A(A) ~A()

vector:
A(A) ~A()

~A()
*/

#include <iostream> // cout, endl
#include <memory>   // allocator
#include <vector>   // vector

using namespace std;

struct A {
    A () {                  // default constructor
        cout << "A() ";}

    A (const A&) {          // copy constructor
        cout << "A(A) ";}

    ~A () {                 // destructor
        cout << "~A() ";}};

int main () {
    {
    A v;
    cout << endl << endl;

    {
    cout << "new:" << endl;
    A* p = new A(v);
    delete p;
    }
    cout << endl << endl;

    {
    cout << "allocator:" << endl;
    allocator<A> x;
    A* p = x.allocate(1);
    x.construct(p, v);
    x.destroy(p);
    x.deallocate(p, 1);
    }
    cout << endl << endl;

    {
    cout << "vector:" << endl;
    vector<A> x(1, v);
    }
    cout << endl << endl;
    }
    cout << endl;

    return 0;}
