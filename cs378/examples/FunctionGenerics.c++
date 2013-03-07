// --------------------
// FunctionGenerics.c++
// --------------------

// parametric compile-time polymorphism

#include <cassert>  // assert
#include <cstring>  // strcmp
#include <iostream> // cout, endl
#include <string>   // string
#include <vector>   // vector

// concept LessThanComparable<T> {
//     bool operator < (const T&, const T&);}

struct A {
    int _n;

    A (int n) :
            _n (n)
        {}};

bool operator < (const A& lhs, const A& rhs) {
    return lhs._n < rhs._n;}

struct B : A {
    B (int n) :
            A (n)
        {}};

// concept_map LessThanComparable<A>

// template
template <typename T>
// requires LessThanComparable<T>
const T& my_max (const T& x, const T& y) {
    if (x < y)
        return y;
    return x;}

// template
template <typename T>
const T* my_max (const T* x, const T* y) {
    if (*x < *y)
        return y;
    return x;}

// non-template
const char* my_max (const char* x, const char* y) {
    if (std::strcmp(x, y) < 0)
        return y;
    return x;}

// template
template <typename T>
void my_swap (T& x, T& y) {
    T tmp = x;
    x = y;
    y = tmp;}

// template
template <typename T>
void my_swap (std::vector<T>& x, std::vector<T>& y) {
    x.swap(y);}

// non-template
void my_swap (int& x, int& y) {
    assert(&x != &y);
    x ^= y;
    y ^= x;
    x ^= y;}

int main () {
    using namespace std;
    cout << "FunctionGenerics.c++" << endl;

    assert(my_max(2,   3)   == 3);
//  assert(my_max(2,   3.4) == 3);                                  // error: cannot convert "double" to "const char*"
//  assert(my_max(2.3, 4)   == 4);                                  // error: cannot convert "double" to "const char*"
    assert(my_max(2.3, 4.5) == 4.5);

    assert(my_max<int>(2,   3.4) == 3);
    assert(my_max<int>(2.3, 4)   == 4);

    assert(my_max<double>(2,   3.4) == 3.4);
    assert(my_max<double>(2.3, 4)   == 4);

    {
    const int i = 2;
    const int j = 3;
    assert(my_max(&i, &j) == &j);
    }

    assert(strcmp(my_max("abc", "def"), "def") == 0);

    assert(strcmp(my_max<      char>  ("ggg", "ghi"), "ggg") == 0); // <T*>
    assert(strcmp(my_max<const char*> ("stu", "pqr"), "stu") == 0); // <T>

    {
    A x = 2;
    A y = 3;
    assert(&max(x, y) == &y);
    }

    {
    B x = 2;
    B y = 3;
    assert(&max(x, y) == &y);
    }

    {
    int i = 2;
    int j = 3;
    my_swap(i, j);
    assert(i == 3);
    assert(j == 2);
    }

    {
    double d = 2;
    double e = 3;
    my_swap(d, e);
    assert(d == 3);
    assert(e == 2);
    }

    {
    vector<int> x(10, 2);
    vector<int> y(20, 3);
    my_swap(x, y);
    assert(x.size() == 20);
    assert(y.size() == 10);
    }

    cout << "Done." << endl;
    return 0;}
