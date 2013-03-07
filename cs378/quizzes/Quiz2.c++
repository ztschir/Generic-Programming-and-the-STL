/*
CS378: Quiz #2 (9 pts)
*/

/* -----------------------------------------------------------------------
1. Which of the following is true? Maybe more than one.
   [Collatz]
   (3 pts)

a. (n / 2),  with n even, always produces an even
b. (n / 2),  with n even, always produces an odd
c. (3n + 1), with n odd,  always produces an even
d. (3n + 1), with n odd,  always produces an odd

c.
*/

/* -----------------------------------------------------------------------
2. What is the output of the following program?
   [Collatz]
   (3 pts)

5
11
*/

#include <iostream> // cout, endl

using namespace std;

int f (int n) {
    return n + (n >> 1) + 1;}

int main () {
    cout << f(3) << endl;
    cout << f(7) << endl;
    return 0;}

/* -----------------------------------------------------------------------
3. In the context of Project #1: Collatz, what is f() computing?
   [Collatz]
   (3 pts)

For odd n it's computing (3n + 1) / 2.
(3n + 1) / 2
3n/2 + 1/2
n + n/2 + 1/2
n + n/2 + 1, because n is odd
n + (n >> 1) + 1
*/
