// --------
// Copy.c++
// --------

#include <algorithm> // copy
#include <cassert>   // assert
#include <cstring>   // strcmp, strlen
#include <iostream>  // cout, endl

char* copy_1 (const char* b, const char* e, char* x) {
    while (b != e) {
        *x = *b;
        ++b;
        ++x;}
    return x;}

template <typename II, typename OI>
OI copy_2 (II b, II e, OI x) {
    while (b != e) {
        *x = *b;
        ++b;
        ++x;}
    return x;}

int main () {
    using namespace std;
    cout << "Copy.c++" << endl;

    const char a[] = "abCbA";
    const int  s   = strlen(a);

    {
    char x[] = "xxxxxxxx";
    const char* const p = copy(a, a + s, x);
    assert(strcmp(x, "abCbAxxx") == 0);
    assert(p - x == s);
    assert(!strncmp(x, "abCbA", s));
    }

    {
    char x[] = "xxxxxxxx";
    const char* const p = copy_1(a, a + s, x);
    assert(strcmp(x, "abCbAxxx")  == 0);
    assert(p - x == s);
    assert(strncmp(x, "abCbA", s) == 0);
    }

    {
    char x[] = "xxxxxxxx";
    const char* const p = copy_2(a, a + s, x);
    assert(strcmp(x, "abCbAxxx")  == 0);
    assert(p - x == s);
    assert(strncmp(x, "abCbA", s) == 0);
    }

    cout << "Done." << endl;
    return 0;}
