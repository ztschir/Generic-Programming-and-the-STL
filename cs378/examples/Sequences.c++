// -------------
// Sequences.c++
// -------------

#include <algorithm> // copy, count, equal
#include <cassert>   // assert
#include <deque>     // deque
#include <iostream>  // cout, endl
#include <list>      // list
#include <string>    // string
#include <vector>    // vector

#include "Vector.h"

template <typename C>
void sequences (
        const typename C::value_type& v1,
        const typename C::value_type& v2,
        const typename C::value_type& v3) {

    typedef typename C::value_type value_type;

    {
    const C x;
    assert(x.empty());
    assert(!x.size());
    }

    {
    C x(10);
    assert(!x.empty());
    assert(x.size()                                     == 10);
    assert(std::count(x.begin(), x.end(), value_type()) == 10);
    }

    {
    const C x(10, v1);
    assert(!x.empty());
    assert(x.size()                           == 10);
    assert(std::count(x.begin(), x.end(), v1) == 10);
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y(x);
    assert(x == y);
    y.pop_back();
    assert(x.size() == 3);
    assert(x.back() == v3);
    assert(y.size() == 2);
    assert(y.back() == v2);
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y;
    y.push_back(v3);
    y.push_back(v1);
    assert(x != y);
    y = x;
    assert(x == y);
    y.pop_back();
    assert(x.size() == 3);
    assert(x.back() == v3);
    assert(y.size() == 2);
    assert(y.back() == v2);
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y;
    y.push_back(v1);
    y.push_back(v2);
    x.swap(y);
    assert(x.size() == 2);
    assert(x.back() == v2);
    assert(y.size() == 3);
    assert(y.back() == v3);
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y(x.size());
    std::copy(x.begin(), x.end(), y.begin());
    assert(std::equal(x.begin(), x.end(), y.begin()));
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    assert(x.front() == v1);
    x.front() = v2;
    assert(x.front() == v2);
    assert(x.back()  == v3);
    x.back()  = v2;
    assert(x.back()  == v2);
    }

    {
    C x;
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    C y;
    y.push_back(v1);
    y.push_back(v2);
    y.push_back(v3);
    assert(x == y);
    assert(x <= y);
    assert(x >= y);
    assert(!(x != y));
    assert(!(x <  y));
    assert(!(x >  y));
    }}

int main () {
    using namespace std;
    cout << "Sequences.c++" << endl;

    sequences<    vector<string> >("abc", "def", "ghi");
    sequences<     deque<string> >("abc", "def", "ghi");
    sequences<      list<string> >("abc", "def", "ghi");
    sequences< my_vector<string> >("abc", "def", "ghi");

    cout << "Done." << endl;
    return 0;}
