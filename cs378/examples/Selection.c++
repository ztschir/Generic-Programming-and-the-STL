// -------------
// Selection.c++
// -------------

#include <cassert>  // assert
#include <iostream> // cout, endl

int f (int n) {
    int m;
    if (n < 0)
        m = -1;
    else if (n > 0)
        m = 1;
    else
        m = 0;
    return m;}

int g (int n) {
    return (n < 0) ? -1 : (n > 0) ? 1 : 0;}

int h (int n) {
    int m;
    switch (n) {
        case -2:
            m = -1;
            break;
        case 3:
            m = 1;
            break;
        default:
            m = 0;}
    return m;}

int main () {
    using namespace std;
    cout << "Selection.c++" << endl;

    assert(f(-2) == -1);
    assert(f( 0) ==  0);
    assert(f( 3) ==  1);

    assert(g(-2) == -1);
    assert(g( 0) ==  0);
    assert(g( 3) ==  1);

    assert(h(-2) == -1);
    assert(h( 0) ==  0);
    assert(h( 3) ==  1);

    {
    int s = 0;
    if (int i = 2)
        s = i;
    else
        s = i + 1;
//  assert(i == 2); // error: 'i' was not declared in this scope
    assert(s == 2);
    }

    {
    int s = 0;
    switch (int i = 2) {
        case 0:
            s = i + 1;
            break;
        default:
            s = i;
            break;}
//  assert(i == 2);      // error: 'i' was not declared in this scope
    assert(s == 2);
    }

    cout << "Done." << endl;
    return 0;}
