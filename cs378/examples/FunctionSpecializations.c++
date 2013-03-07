// ---------------------------
// FunctionSpecializations.c++
// ---------------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

// non-template
std::string f (int) {
    return "f(int)";}

// primary template for T
template <typename T>
std::string f (T) {
    return "f(T)";}

// secondary template for T with T == int*
template <>
std::string f<int*> (int*) {
    return "f<int*>(int*)";}

// secondary template for T with T == double*
template <>
std::string f<double*> (double*) {
    return "f<double*>(double*)";}

// primary template for T*
template <typename T>
std::string f (T*) {
    return "f(T*)";}

// secondary template for T* with T == double
template <>
std::string f<double> (double*) {
    return "f<double>(double*)";}

int main () {
    using namespace std;
    cout << "FunctionSpecializations.c++" << endl;

    int    i = 2;
    double d = 3.4;

    // non-template
    assert(f(i)           == "f(int)");

    // primary template for T
    assert(f(d)           == "f(T)");                // T == double
    assert(f<int>(i)      == "f(T)");                // T == int
    assert(f<int>(d)      == "f(T)");                // T == int
    assert(f<double>(i)   == "f(T)");                // T == double
    assert(f<double>(d)   == "f(T)");                // T == double

    // secondary template for T
    assert(f<int*>(&i)    == "f<int*>(int*)");       // T == int*
    assert(f<double*>(&d) == "f<double*>(double*)"); // T == double*

    // primary template for T*
    assert(f(&i)          == "f(T*)");               // T == int
    assert(f<int>(&i)     == "f(T*)");               // T == int

    // secondary template for T*
    assert(f(&d)          == "f<double>(double*)");  // T == double
    assert(f<double>(&d)  == "f<double>(double*)");  // T == double

    cout << "Done." << endl;
    return 0;}
