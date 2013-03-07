// -----------
// Returns.c++
// -----------

#include <cassert>  // assert
#include <iostream> // cout, endl

int f () {
    int i = 2;
    return i;}

int* g () {
    int j = 2;
    return &j;} // warning: address of local variable 'j' returned

int& h () {
    int k = 2;
    return k;} // warning: reference to local variable 'k' returned

const char* c1 () {
    const char a[] = "abcd"; // 'a' is a local array
    assert(sizeof(a) == 5);
//  a = "def";               // error: assignment of read-only variable ‘a’
    return a;}               // warning: address of local variable 'a' returned

const char* c2 () {
    const char* a = "abcd"; // 'a' is a local pointer
    assert(sizeof(a) == 8);
    a = "def";
    return a;}

const char* c3 () {
    return "def";}

int main () {
    using namespace std;
    cout << "Returns.c++" << endl;

    {
    int v = f();
    assert(v == 2);
//  int* p = &f();  // error: lvalue required as unary ‘&’ operand
//  int& r = f();   // error: invalid initialization of non-const reference of type ‘int&’ from a temporary of type ‘int’
    }

    {
    int v = *g();
//  assert(v == 2);  // Valgrind: Conditional jump or move depends on uninitialised value(s)
    int* p = g();
//  assert(*p == 2); // Valgrind: Conditional jump or move depends on uninitialised value(s)
    int& r = *g();
//  assert(r == 2);  // Valgrind: Conditional jump or move depends on uninitialised value(s)
    }

    {
    int v = h();
//  assert(v == 2);  // Valgrind: Conditional jump or move depends on uninitialised value(s)
    int* p = &h();
//  assert(*p == 2); // Valgrind: Conditional jump or move depends on uninitialised value(s)
    int& r = h();
//  assert(r == 2);  // Valgrind: Conditional jump or move depends on uninitialised value(s)
    }

    assert(c1() != "abc");
    assert(c2() == c3());

    cout << "Done." << endl;
    return 0;}
