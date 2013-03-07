/*
CS378: Quiz #8 (9 pts)
*/

/* -----------------------------------------------------------------------
1. What is the output of the following program?
   (2 pts)

1 2
*/

#include <iostream> // cout, endl

using namespace std;

enum Color {
    red,
    green,
    blue = green,
    yellow};

int main () {
    cout << blue   << " ";
    cout << yellow << endl;
    return 0;}

/* -----------------------------------------------------------------------
2. What advantage is there in representing something like color with an
   enum instead of an int?
   (3 pts)

a run-time error becomes a compile-time error
*/

/* -----------------------------------------------------------------------
3. What is the purpose of cbegin() and cend()?
   [Sec. 6.3, Pg. 192]
   (2 pts)

to force the return of read-only iterators
*/

/* -----------------------------------------------------------------------
4. When is the "_if" suffix used in the names of algorithms?
   [Sec. 11.2.2, Pg. 507]
   (2 pts)

when you can call two forms of an algorithm that have the same number of
parameters either by passing a value or by passing a function
*/
