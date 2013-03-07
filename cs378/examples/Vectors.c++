// -----------
// Vectors.c++
// -----------

#include <algorithm> // count
#include <cassert>   // assert
#include <cstring>   // strcmp
#include <iostream>  // cout, endl
#include <stdexcept> // out_of_range
#include <string>    // string
#include <vector>    // vector

#include "Vector.h" // my_vector

template <typename C>
void vectors (
        const typename C::value_type& v1,
        const typename C::value_type& v2,
        const typename C::value_type& v3) {

    typedef typename C::value_type value_type;

    {
    const C x;
    assert(x.empty());
    assert(x.size()     == 0);
    assert(x.capacity() == 0);
    }

    {
    C x(10);
    assert(!x.empty());
    assert(x.size()                                     == 10);
    assert(x.capacity()                                 == 10);
    assert(std::count(x.begin(), x.end(), value_type()) == 10);
    }

    {
    const C x(10, v1);
    assert(!x.empty());
    assert(x.size()                           == 10);
    assert(x.capacity()                       == 10);
    assert(std::count(x.begin(), x.end(), v1) == 10);
    }

    {
    C x(10);
    assert(x.size()     == 10);
    assert(x.capacity() == 10);
    x.reserve(5);
    assert(x.size()     == 10);
    assert(x.capacity() == 10);
    x.reserve(15);
    assert(x.size()     == 10);
    assert(x.capacity() == 15);
    }

    {
    C x(10);
    assert(x.size()     == 10);
    assert(x.capacity() == 10);
    x.resize(5);
    assert(x.size()     ==  5);
    assert(x.capacity() == 10);
    x.resize(8);
    assert(x.size()     ==  8);
    assert(x.capacity() == 10);
    x.resize(15);
    assert(x.size()     == 15);
    assert(x.capacity() == 16);
    x.resize(50);
    assert(x.size()     == 50);
    assert(x.capacity() == 50);
    }

    {
    C x(10);
    x[0] = v1;
    x[1] = v2;
    x[2] = v3;
    assert(x[ 1] == v2);
//  assert(x[10] == v2);
    try {
        assert(x.at(10) == v2);}
    catch (const std::out_of_range& e) {
        assert(std::strcmp(e.what(), "vector::_M_range_check") == 0);}
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    x.push_back(v1);
    x.push_back(v2);
    assert(x.size()     == 5);
    assert(x.capacity() == 8);
    x.pop_back();
    assert(x.size()     == 4);
    assert(x.capacity() == 8);
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    assert(x.size()     == 3);
    assert(x.capacity() == 4);
    const C y(x);
    assert(y.size()     == 3);
    assert(y.capacity() == 3);
    assert(x == y);
    }

    {
    const C x(10, v1);
    C       y(20, v2);
    assert(y.size()     == 20);
    assert(y.capacity() == 20);
    assert(x != y);
    y = x;
    assert(y.size()     == 10);
    assert(y.capacity() == 20);
    assert(x == y);
    }

    {
    const C x(15, v1);
    C       y(10, v2);
    assert(y.size()     == 10);
    assert(y.capacity() == 10);
    y.push_back(v2);
    assert(y.size()     == 11);
    assert(y.capacity() == 20);
    assert(x != y);
    y = x;
    assert(y.size()     == 15);
    assert(y.capacity() == 20);
    assert(x == y);
    }

    {
    const C x(20, v1);
    C       y(10, v2);
    assert(y.size()     == 10);
    assert(y.capacity() == 10);
    assert(x != y);
    y = x;
    assert(y.size()     == 20);
    assert(y.capacity() == 20);
    assert(x == y);
    }}

int main () {
    using namespace std;
    cout << "Vectors.c++" << endl;

    vectors<    vector<string> >("abc", "def", "ghi");
    vectors< my_vector<string> >("abc", "def", "ghi");

    cout << "Done." << endl;
    return 0;}
