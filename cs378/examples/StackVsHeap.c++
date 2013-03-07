// ---------------
// StackVsHeap.c++
// ---------------

#include <cassert>  // assert
#include <cstring>  // strcmp
#include <iostream> // cout, endl

int f (int n) {
    if (n == 0)
        return 0;
    return 1 + f(n - 1);}

int main () {
    using namespace std;
    cout << "StackVsHeap.c++" << endl;

    {
    assert(f(1234567L) == 1234567L); // 12345678L will fail
    }

    try {
        int* a = new int[12345678912345L];}
    catch (const bad_alloc& e) {
        assert(false);}

    try {
        int* a = new int[123456789123456L];
        assert(false);}
    catch (const bad_alloc& e) {
        assert(strcmp(e.what(), "std::bad_alloc") == 0);}

    cout << "Done." << endl;
    return 0;}

/*
*** [StackVsHeap.c++x] Segmentation fault
*/

/*
malloc: *** mmap(size=493827156496384) failed (error code=12)
*** error: can't allocate region
*** set a breakpoint in malloc_error_break to debug
*/
