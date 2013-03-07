// ------------
// Valgrind.c++
// ------------

#include <cassert>  // assert
#include <iostream> // cout, endl

int main () {
    using namespace std;
    cout << "Valgrind.c++" << endl;

    int a[3];
    a[3] = 0;

    int* p = new int;

    cout << "Done." << endl;
    return 0;}

/*
% g++ -ansi -pedantic -Wall Valgrind.c++ -o Valgrind.c++.app
% valgrind Valgrind.c++.app
==31976== Memcheck, a memory error detector.
==31976== Copyright (C) 2002-2008, and GNU GPL'd, by Julian Seward et al.
==31976== Using LibVEX rev 1878, a library for dynamic binary translation.
==31976== Copyright (C) 2004-2008, and GNU GPL'd, by OpenWorks LLP.
==31976== Using valgrind-3.4.0, a dynamic binary instrumentation framework.
==31976== Copyright (C) 2000-2008, and GNU GPL'd, by Julian Seward et al.
==31976== For more details, rerun with: -v
==31976==
Valgrind.c++
Done.
==31976== Warning: client switching stacks?  SP change: 0xbeae8a68 --> 0xfffffffc
==31976==          to suppress, use: --max-stackframe=1095857556 or greater
==31976== Invalid read of size 4
==31976==    at 0x80488E9: main (in /v/filer4b/downing/public_html/examples/c++/Valgrind.c++.app)
==31976==  Address 0xfffffffc is not stack'd, malloc'd or (recently) free'd
==31976==
==31976== Process terminating with default action of signal 11 (SIGSEGV)
==31976==  Access not within mapped region at address 0xFFFFFFFC
==31976==    at 0x80488E9: main (in /v/filer4b/downing/public_html/examples/c++/Valgrind.c++.app)
==31976==  If you believe this happened as a result of a stack overflow in your
==31976==  program's main thread (unlikely but possible), you can try to increase
==31976==  the size of the main thread stack using the --main-stacksize= flag.
==31976==  The main thread stack size used in this run was 16777216.
==31976==
==31976== Process terminating with default action of signal 11 (SIGSEGV)
==31976==  Access not within mapped region at address 0xFFFFFFF8
==31976==    at 0x401E3AC: _vgnU_freeres (vg_preloaded.c:56)
==31976==  If you believe this happened as a result of a stack overflow in your
==31976==  program's main thread (unlikely but possible), you can try to increase
==31976==  the size of the main thread stack using the --main-stacksize= flag.
==31976==  The main thread stack size used in this run was 16777216.
==31976==
==31976== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 17 from 1)
==31976== malloc/free: in use at exit: 4 bytes in 1 blocks.
==31976== malloc/free: 2 allocs, 1 frees, 6 bytes allocated.
==31976== For counts of detected errors, rerun with: -v
==31976== searching for pointers to 1 not-freed blocks.
==31976== checked 107,892 bytes.
==31976==
==31976== LEAK SUMMARY:
==31976==    definitely lost: 4 bytes in 1 blocks.
==31976==      possibly lost: 0 bytes in 0 blocks.
==31976==    still reachable: 0 bytes in 0 blocks.
==31976==         suppressed: 0 bytes in 0 blocks.
==31976== Rerun with --leak-check=full to see details of leaked memory.
*/
