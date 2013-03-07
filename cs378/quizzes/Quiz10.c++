/*
CS378: Quiz #10 (9 pts)
*/

/* -----------------------------------------------------------------------
1. What is the output of the following program?
   You MUST get the newlines right to get full credit.
   Write the word "blank" to indicate a blank line.
   (9 pts)

A(int) A(int) A(int) A() A()
A() A() A()
~A() ~A() ~A()
~A() ~A() ~A() ~A() ~A()
*/

#include <iostream> // cout, endl
#include <cstddef>  // size_t

using namespace std;

struct A {
    A () {                     // default constructor
        cout << "A() ";}

    A (int) {                  // int constructor
        cout << "A(int) ";}

    A (const A&) {             // copy constructor
        cout << "A(A) ";}

    A& operator = (const A&) { // copy assignment operator
        cout << "=(A) ";
        return *this;}

    ~A () {                    // destructor
        cout << "~A() ";}};

int main () {
    {
    A a[5] = {2, 3, 4};
    cout << endl;

    A* p = new A[3];
    cout << endl;

    delete [] p;
    cout << endl;
    }
    cout << endl;

    return 0;}
