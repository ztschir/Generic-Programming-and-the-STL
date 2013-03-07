// --------
// Fill.c++
// --------

#include <algorithm> // fill
#include <cassert>   // assert
#include <cstring>   // strcmp, strlen
#include <iostream>  // cout, endl

void fill_1 (char* b, char* e, char v) {
    while (b != e) {
        *b = v;
        ++b;}}

template <typename FI, typename T>
void fill_2 (FI b, FI e, const T& v) {
    while (b != e) {
        *b = v;
        ++b;}}

int main () {
    using namespace std;
    cout << "Fill.c++" << endl;

    {
          char a[] = "abCbA";
    const int  s   = strlen(a);
    fill(a, a + s, 'x');
    assert(strcmp(a, "xxxxx") == 0);
    }

    {
          char a[] = "abCbA";
    const int  s   = strlen(a);
    fill_1(a, a + s, 'x');
    assert(strcmp(a, "xxxxx") == 0);
    }

    {
          char a[] = "abCbA";
    const int  s   = strlen(a);
    fill_2(a, a + s, 'x');
    assert(strcmp(a, "xxxxx") == 0);
    }

    cout << "Done." << endl;
    return 0;}
