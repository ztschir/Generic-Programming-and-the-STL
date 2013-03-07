/*
CS378: Quiz #9 (9 pts)
*/

#include <cassert>  // assert
#include <iostream> // cout, endl

using namespace std;

class Integer {
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        return lhs._i < rhs._i;}

    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    private:
        int _i;

    public:
        Integer (int i) :
                _i (i)
            {}

        Integer& operator += (const Integer& rhs) {
            _i += rhs._i;
            return *this;}};

int main () {
    Integer x = 2;
    Integer y = 2;
    assert(x <= y);

    Integer z = (x + y);
    assert(x <= z);

    cout << "Done" << endl;
    return 0;}

/* -----------------------------------------------------------------------
1. Define the operator<=() in terms of operator<().
   (5 pts)
*/

/* -----------------------------------------------------------------------
2. Define the operator+() in terms of operator+=().
   (4 pts)
*/
