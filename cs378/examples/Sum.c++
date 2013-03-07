// -------
// Sum.c++
// -------

#include <cassert>    // assert
#include <functional> // plus
#include <iostream>   // cout, endl
#include <list>       // list
#include <numeric>    // accumulate, inner_product
#include <set>        // list
#include <vector>     // vector

int sum_1 (int* a, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i)
        s += a[i];
    return s;}

int sum_2 (int* b, int* e) {
    int s = 0;
    while (b < e) {
        s += *b;
        ++b;}
    return s;}

template <typename T>
T sum_3 (T* b, T* e, T v) {
    while (b < e) {
        v += *b;
        ++b;}
    return v;}

template <typename I, typename T>
T sum_4 (I b, I e, T v) {
    while (b < e) {
        v += *b;
        ++b;}
    return v;}

template <typename I, typename T>
T sum_5 (I b, I e, T v) {
    while (b != e) {
        v += *b;
        ++b;}
    return v;}

int main () {
    using namespace std;
    cout << "Sum.c++" << endl;

    int a[] = {2, 3, 4};

    assert(     sum_1(a, 3)        == 9);
    assert(     sum_2(a, a + 3)    == 9);
    assert(     sum_3(a, a + 3, 0) == 9);
    assert(     sum_4(a, a + 3, 0) == 9);
    assert(     sum_5(a, a + 3, 0) == 9);
    assert(accumulate(a, a + 3, 0) == 9);

    {
    vector<int> x(a, a + 3);
    vector<int>::iterator b = x.begin();
    vector<int>::iterator e = x.end();
//  assert(     sum_1(x,     3)        == 9);
    assert(     sum_1(&x[0], 3)        == 9);
    assert(     sum_1(&*b,   3)        == 9);
//  assert(     sum_2(b, e)            == 9);
    assert(     sum_2(&x[0], &x[3])    == 9);
    assert(     sum_2(&*b,   &*e)      == 9);
//  assert(     sum_3(b, e, 0)         == 9);
    assert(     sum_3(&x[0], &x[3], 0) == 9);
    assert(     sum_3(&*b,   &*e,   0) == 9);
    assert(     sum_4(b, e, 0)         == 9);
    assert(     sum_5(b, e, 0)         == 9);
    assert(accumulate(b, e, 0)         == 9);
    }

    {
    list<int> x(a, a + 3);
    list<int>::iterator b = x.begin();
    list<int>::iterator e = x.end();
//  assert(     sum_1(x, 3)    == 9);
//  assert(     sum_2(b, e)    == 9);
//  assert(     sum_3(b, e, 0) == 9);
//  assert(     sum_4(b, e, 0) == 9);
    assert(     sum_5(b, e, 0) == 9);
    assert(accumulate(b, e, 0) == 9);
    }

    {
    set<int> x(a, a + 3);
    set<int>::iterator b = x.begin();
    set<int>::iterator e = x.end();
//  assert(     sum_1(x, 3)    == 9);
//  assert(     sum_2(b, e)    == 9);
//  assert(     sum_3(b, e, 0) == 9);
//  assert(     sum_4(b, e, 0) == 9);
    assert(     sum_5(b, e, 0) == 9);
    assert(accumulate(b, e, 0) == 9);
    }

    cout << "Done." << endl;
    return 0;}
