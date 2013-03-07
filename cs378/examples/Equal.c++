// ---------
// Equal.c++
// ---------

#include <algorithm> // equal
#include <cassert>   // assert
#include <cstring>   // strlen
#include <iostream>  // cout, endl

bool equal_1 (const char* b, const char* e, const char* c) {
    while (b != e) {
        if (*b != *c)
            return false;
        ++b;
        ++c;}
    return true;}

template <typename II1, typename II2>
bool equal_2 (II1 b, II1 e, II2 c) {
    while (b != e) {
        if (*b != *c)
            return false;
        ++b;
        ++c;}
    return true;}

int main () {
    using namespace std;
    cout << "Equal.c++" << endl;

    const char a[] = "abCbA";
    const int  s   = strlen(a);
    const char b[] = "abCbAabCbA";

    assert(equal  (a, a + s, b));
    assert(equal_1(a, a + s, b));
    assert(equal_2(a, a + s, b));

    cout << "Done." << endl;
    return 0;}
