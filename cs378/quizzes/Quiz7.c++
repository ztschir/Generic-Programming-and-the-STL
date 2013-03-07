/*
CS378: Quiz #7 (9 pts)
*/

/* -----------------------------------------------------------------------
1. In the paper, "A Bug and a Crash" about the Ariane 5, what was the
   software bug?
   (2 pts)

the conversion of a 64-bit number to a 16-bit number
*/

/* -----------------------------------------------------------------------
2. In the paper, "Mariner 1", what was the software bug?
   (1 pt)

the ommission of a hyphen
*/

/* -----------------------------------------------------------------------
3. What is the output of the following program?
   (6 pts)

3 3 false
3 4 true
*/

#include <iostream> // cout, endl

int& f (int& i) {
    return ++i;}

int main () {
    using namespace std;
    cout << boolalpha;   // bool outputs as true or false

    {
    int i = 2;
    int j = f(i);
    cout << i          << " ";
    ++j;
    cout << i          << " ";
    cout << (&i == &j) << endl;
    }

    {
    int  i = 2;
    int& j = f(i);
    cout << i          << " ";
    ++j;
    cout << i          << " ";
    cout << (&i == &j) << endl;
    }

    return 0;}
