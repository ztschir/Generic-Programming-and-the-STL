// --------------
// Exceptions.c++
// --------------

#include <cassert>   // assert
#include <cstring>   // strcmp
#include <iostream>  // cout, endl
#include <stdexcept> // domain_error
#include <string>    // string

int f (bool b) {
    if (b)
        throw std::domain_error("abc");
    return 0;}

int main () {
    using namespace std;
    cout << "Exceptions.c++" << endl;

    try {
        assert(f(false) == 0);
        }
    catch (domain_error& e) {
        assert(false);}

    try {
        assert(f(true) == 1);
        assert(false);
        }
    catch (domain_error& e) {
//      assert(       e                == "abc");  // error: no match for ‘operator==’ in ‘e == "abc"’
        assert(       e.what()         != "abc");  // warning: comparison with string literal results in unspecified behavior
        assert(strcmp(e.what(), "abc") == 0);
        assert(string(e.what())        == "abc");}

    domain_error x("abc");
    logic_error& r = x;
    exception&   s = r;

    cout << "Done." << endl;
    return 0;}
