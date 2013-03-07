// -------
// Pow.c++
// -------

#include <cassert>  // assert
#include <cmath>    // pow
#include <iostream> // cout, endl

/**
 * O(log n) in space
 * O(log n) in time
 * Precondition: (e >= 0) && ((n != 0) || (e != 0))
 */
template <typename T, typename U>
T my_pow (const T& n, const U& e) {
    assert((e >= 0) && ((n != 0) || (e != 0)));
    if (n == 0)
        return 0;
    if (e == 0)
        return 1;
    const T p = my_pow(n, e / 2);
    if (!(e & 1))
        return p * p;
    return p * p * n;}

int main () {
    using namespace std;
    cout << "Pow.c++" << endl;

    assert(pow( 0, 1) ==     0);
    assert(pow( 1, 0) ==     1);
    assert(pow( 1, 1) ==     1);
    assert(pow( 2, 0) ==     1);
    assert(pow( 2, 1) ==     2);
    assert(pow( 2, 2) ==     4);
    assert(pow( 2, 3) ==     8);
    assert(pow( 2, 4) ==    16);
    assert(pow( 2, 5) ==    32);
    assert(pow( 2, 6) ==    64);
    assert(pow( 2, 7) ==   128);
    assert(pow(-3, 0) ==     1);
    assert(pow(-3, 1) ==    -3);
    assert(pow(-3, 2) ==     9);
    assert(pow(-3, 3) ==   -27);
    assert(pow(-3, 4) ==    81);
    assert(pow(-3, 5) ==  -243);
    assert(pow(-3, 6) ==   729);
    assert(pow(-3, 7) == -2187);

    assert(my_pow( 0, 1) ==     0);
    assert(my_pow( 1, 0) ==     1);
    assert(my_pow( 1, 1) ==     1);
    assert(my_pow( 2, 0) ==     1);
    assert(my_pow( 2, 1) ==     2);
    assert(my_pow( 2, 2) ==     4);
    assert(my_pow( 2, 3) ==     8);
    assert(my_pow( 2, 4) ==    16);
    assert(my_pow( 2, 5) ==    32);
    assert(my_pow( 2, 6) ==    64);
    assert(my_pow( 2, 7) ==   128);
    assert(my_pow(-3, 0) ==     1);
    assert(my_pow(-3, 1) ==    -3);
    assert(my_pow(-3, 2) ==     9);
    assert(my_pow(-3, 3) ==   -27);
    assert(my_pow(-3, 4) ==    81);
    assert(my_pow(-3, 5) ==  -243);
    assert(my_pow(-3, 6) ==   729);
    assert(my_pow(-3, 7) == -2187);

    cout << "Done." << endl;
    return 0;}
