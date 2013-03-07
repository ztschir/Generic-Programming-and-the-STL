// -------------
// Functions.c++
// -------------

#include <cassert>    // assert
#include <functional> // multiplies, plus
#include <iostream>   // cout, endl

int plus_1 (int x, int y) {
    return x + y;}

int multiplies_1 (int x, int y) {
    return x * y;}

template <typename T>
T plus_2 (T x, T y) {
    return x + y;}

template <typename T>
T multiplies_2 (T x, T y) {
    return x * y;}

struct plus_3 {
    int operator () (int x, int y) const {
        return x + y;}};

struct multiplies_3 {
    int operator () (int x, int y) const {
        return x * y;}};

template <typename T>
struct plus_4 {
    T operator () (const T& x, const T& y) const {
        return x + y;}};

template <typename T>
struct multiplies_4 {
    T operator () (const T& x, const T& y) const {
        return x * y;}};

int f (int (*bf) (int, int), int x, int y, int z) {
    return bf(bf(x, y), z);}

template <typename BF, typename T>
T g (BF bf, const T& x, const T& y, const T& z) {
    return bf(bf(x, y), z);}

int main () {
    using namespace std;
    cout << "Functions.c++" << endl;

    assert(plus_1      (2, 3) == 5);
    assert(multiplies_1(2, 3) == 6);

    assert(plus_2      (2, 3) == 5);
    assert(multiplies_2(2, 3) == 6);

    assert(plus_3()      (2, 3) == 5);
    assert(multiplies_3()(2, 3) == 6);

    assert(plus_4<int>()      (2, 3) == 5);
    assert(multiplies_4<int>()(2, 3) == 6);

    assert(plus<int>()      (2, 3) == 5);
    assert(multiplies<int>()(2, 3) == 6);

    assert(f(plus_1,       2, 3, 4) ==  9);
    assert(f(multiplies_1, 2, 3, 4) == 24);

    assert(f(plus_2,       2, 3, 4) ==  9);
    assert(f(multiplies_2, 2, 3, 4) == 24);

//  assert(f(plus_3(),       2, 3, 4) ==  9); // doesn't compile
//  assert(f(multiplies_3(), 2, 3, 4) == 24); // doesn't compile

//  assert(f(plus_4<int>(),       2, 3, 4) ==  9); // doesn't compile
//  assert(f(multiplies_4<int>(), 2, 3, 4) == 24); // doesn't compile

//  assert(f(plus<int>(),       2, 3, 4) ==  9); // doesn't compile
//  assert(f(multiplies<int>(), 2, 3, 4) == 24); // doesn't compile

    assert(g(plus_1,       2, 3, 4) ==  9);
    assert(g(multiplies_1, 2, 3, 4) == 24);

    assert(g(plus_2<int>,       2, 3, 4) ==  9);
    assert(g(multiplies_2<int>, 2, 3, 4) == 24);

    assert(g(plus_3(),       2, 3, 4) ==  9);
    assert(g(multiplies_3(), 2, 3, 4) == 24);

    assert(g(plus_4<int>(),       2, 3, 4) ==  9);
    assert(g(multiplies_4<int>(), 2, 3, 4) == 24);

    assert(g(plus<int>(),       2, 3, 4) ==  9);
    assert(g(multiplies<int>(), 2, 3, 4) == 24);

    cout << "Done." << endl;
    return 0;}
