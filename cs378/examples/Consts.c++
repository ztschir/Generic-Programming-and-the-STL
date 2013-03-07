// ----------
// Consts.c++
// ----------

#include <cassert>  // assert
#include <iostream> // cout, endl

int main () {
    using namespace std;
    cout << "Consts.c++" << endl;

    {
    int i = 2;
    ++i;
    assert(i == 3);
    }

    {
//  const int ci;     // error: uninitialized const 'ci'
    const int ci = 4;
//  ++ci;             // error: increment of read-only variable 'ci'
    assert(ci == 4);
    }

    // many-location, read/write pointer
    {
          int  i  = 2;
    const int  ci = 3;
          int* p;
    p  = &i;
    ++*p;
    assert(i == 3);
//  p = &ci;        // error: invalid conversion from 'const int*' to 'int*'
    }

    // many-location, read-only pointer
    {
          int  i  = 2;
    const int  ci = 3;
    const int* pc;
    pc = &ci;
//  ++*pc;                         // error: increment of read-only location
//  int* p = pc;                   // error: invalid conversion from 'const int*' to 'int*'
    int* p = const_cast<int*>(pc);
//  ++*p;                          // undefined
    pc = &i;                       // ?
    p = const_cast<int*>(pc);
    ++*p;
    assert(i == 3);
    }

    // one-location, read/write pointer
    {
          int        i  = 2;
    const int        ci = 3;
//        int* const cp;       // error: uninitialized const 'cp'
//        int* const cp = &ci; // error: invalid conversion from 'const int*' to 'int*'
          int* const cp = &i;
//  cp = &i;                   // error: assignment of read-only variable 'cp'
    ++*cp;
    assert(i == 3);
    }

    // one-location, read-only pointer
    {
          int        i   = 2;
    const int        ci  = 3;
    const int* const cpc = &ci;
    const int* const cqc = &i;
//  cqc = &ci;                  // error: assignment of read-only variable 'cqc'
//  ++*cqc;                                                   // error: increment of read-only location
    }

    // read/write reference
    {
          int  i  = 2;
    const int  ci = 3;
//        int& r;      // error: 'r' declared as reference but not initialized
//        int& r = ci; // error: invalid initialization of reference of type 'int&' from expression of type 'const int'
          int& r = i;
    ++r;
    assert(i == 3);
    }

    // read-only reference
    {
          int  i  = 2;
    const int  ci = 3;
    const int& rc = ci;
    const int& sc = i;
//  ++sc;               // error: increment of read-only reference 'sc'
    }

    // reference to a many-location, read/write pointer
    {
    int i = 2;
    typedef int* pointer;
    pointer  p = &i;
    pointer& r = p;
    ++*r;
    assert(i == 3);
    r = 0;
    assert(p == 0);
    }

    // const reference to a many-location, read/write pointer
    {
    int i = 2;
    typedef int* pointer;
          pointer  p = &i;
    const pointer& r = p;
    ++*r;
    assert(i == 3);
//  r = 0;                 // error: assignment of read-only reference 'r'
    p = 0;
    assert(r == 0);
    }

    // reference to a many-location, read-only pointer
    {
    int i = 2;
    typedef const int* pointer_to_constant;
    pointer_to_constant  p = &i;
    pointer_to_constant& r = p;
//  ++*r;                                   // error: increment of read-only location
//  ++*p;                                   // error: increment of read-only location
    r = 0;
    assert(p == 0);
    }

    // const reference to a many-location, read-only pointer
    {
    int i = 2;
    typedef const int* pointer_to_constant;
          pointer_to_constant  p = &i;
    const pointer_to_constant& r = p;
//  ++*r;                                   // error: increment of read-only location
//  ++*p;                                   // error: increment of read-only location
//  r = 0;                                  // error: assignment of read-only reference 'r'
    p = 0;
    assert(r == 0);
    }

    // reference to a one-location, read/write pointer
    {
    int i = 2;
    typedef int* const constant_pointer;
    constant_pointer  p = &i;
    constant_pointer& r = p;
    ++*r;
    assert(i == 3);
//  r = 0;                               // error: assignment of read-only reference 'r'
//  p = 0;                               // error: assignment of read-only reference 'p'
    }

    // reference to a one-location, read-only pointer
    {
    int i = 2;
    typedef const int* const constant_pointer_to_constant;
    constant_pointer_to_constant  p = &i;
    constant_pointer_to_constant& r = p;
//  ++*r;                                                  // error: increment of read-only location
//  ++*p;                                                  // error: increment of read-only location
//  r = 0;                                                 // error: assignment of read-only reference 'r'
//  p = 0;                                                 // error: assignment of read-only reference 'p'
    }

    // reference to read-only,  many-location pointer referring to read/write, many-location pointer
    // reference to read/write, many-location pointer referring to read-only,  many-location pointer
    {
    int i = 2;
    typedef       int* pointer;
    typedef const int* pointer_to_constant;
    pointer              p  = &i;
    pointer_to_constant  pc = p;
//  pointer_to_constant& r  = p;            // error: invalid initialization of reference of type ‘const int*&’ from expression of type ‘int*’
//  pointer              q  = pc;           // error: invalid conversion from ‘const int*’ to ‘int*’
//  pointer&             s  = pc;           // error: invalid initialization of reference of type ‘int*&’ from expression of type ‘const int*’
    }

    // reference to read-only,  one-location pointer referring to read/write, one-location pointer
    // reference to read/write, one-location pointer referring to read-only,  one-location pointer
    {
    int i = 2;
    typedef       int* const const_pointer;
    typedef const int* const const_pointer_to_constant;
    const_pointer              cp  = &i;
    const_pointer_to_constant  cpc = cp;
    const_pointer_to_constant& r   = cp;
//  const_pointer              cq  = cpc;               // error: invalid conversion from ‘const int* const’ to ‘int*’
//  const_pointer&             s   = cpc;               // error: invalid initialization of reference of type ‘int* const&’ from expression of type ‘const int* const’
    }

    cout << "Done." << endl;
    return 0;}
