// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestInteger.c++ -o TestInteger.c++.app
    % valgrind TestInteger.c++.app >& TestInteger.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {
    // -----------------
    // shift_left_digits
    // -----------------

    void test_shift_left_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {0,0,2, 3, 4,};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
        
        
    void test_shift_left_digits_1 () {
        const int a[] = {2, 3, 4, 9, 9, 9, 9};
        const int b[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 4, 9, 9, 9, 9};
              int x[30];
        const int* p = shift_left_digits(a, a + 7, 20, x);
        CPPUNIT_ASSERT((p - x) == 27);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
        
        
    void test_shift_left_digits_2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {0, 2, 3, 4};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 1, x);
        CPPUNIT_ASSERT((p - x) == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
        
        
    void test_shift_left_digits_3 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

        
    void test_shift_right_digits_1 () {
        const int a[] = {1, 2, 3, 4, 5, 6 , 7, 8 ,9, 0, 1 ,2 ,3 ,4 ,5};
        const int b[] = {5};
              int x[20];
        const int* p = shift_right_digits(a, a + 15, 14, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

        
    void test_shift_right_digits_2 () {
        const int a[] = {2, 3, 4, 9, 9, 9, 9, 9, 5};
        const int b[] = {9, 9, 5};
              int x[10];
        const int* p = shift_right_digits(a, a + 9, 6, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

        
    void test_shift_right_digits_3 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    // -----------
    // plus_digits
    // -----------

    void test_plus_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {7, 9, 1, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits_1 () {
        const int a[] =    {5, 3, 4};
        const int b[] =    {5, 6, 7};
        const int c[] =    {0, 0, 2, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits_2 () {
        const int a[] =    {9, 8};
        const int b[] =       {1};
        const int c[] =    {0, 9};
              int x[5];
        const int* p = plus_digits(a, a + 2, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits_3 () {
        const int a[] =    {9, 9};
        const int b[] =       {1};
        const int c[] =    {0, 0, 1};
              int x[5];
        const int* p = plus_digits(a, a + 2, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
        
    void test_plus_digits_4 () {
        const int a[] =    {9, 9};
        const int b[] =    {1, 1};
        const int c[] =    {0, 1, 1};
              int x[5];
        const int* p = plus_digits(a, a + 2, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits_5 () {
        const int a[] =    {9, 9, 9, 9, 9, 9, 9};
        const int b[] =    {1};
        const int c[] = {0, 0, 0, 0, 0, 0, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 7, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 8);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits_6 () {
        const int a[] =    {1};
        const int b[] =    {9, 9, 9, 9, 9, 9, 9};
        const int c[] =    {0, 0, 0, 0, 0, 0, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 1, b, b + 7, x);
        CPPUNIT_ASSERT(p - x == 8);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits_7 () {
        const int a[] =    {0};
        const int b[] =    {9, 9, 9, 9, 9, 9, 9};
        const int c[] =    {9, 9, 9, 9, 9, 9, 9};
              int x[10];
        const int* p = plus_digits(a, a + 1, b, b + 7, x);
        CPPUNIT_ASSERT(p - x == 7);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits_8 () {
        const int a[] =    {0, 1, 9, 9, 8};
        const int b[] =    {1, 9, 9, 8};
        const int c[] =    {1, 0, 9, 8, 9};
              int x[10];
        const int* p = plus_digits(a, a + 5, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        

        
        
        


    // ------------
    // minus_digits
    // ------------
     
    
    //WORKS
     void test_minus_digits () {
                    
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {7, 5, 6};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits1 () {
        const int a[] = {0, 0, 0, 1};
        const int b[] = {1, 0, 0, 1};
        const int c[] = {1};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

        //WORKS
    void test_minus_digits2 () {
        const int a[] = {8, 8, 8};
        const int b[] = {9, 9, 1};
        const int c[] = {9, 8, 6};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits3 () {
        const int a[] = { 0, 0, 0, 0, 1};
        const int b[] =  {1};
        const int c[] =    {9, 9, 9, 9};
              int x[10];
        const int* p = minus_digits(a, a + 5, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
        
        
        
        
        

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits () {
        const int a[] = {0, 1};
        const int b[] = {3, 3};
        const int c[] = {0, 3, 3};
              int x[10];
        const int* p = multiplies_digits(a, a + 2, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits1 () {
        const int a[] = {9, 9, 9};
        const int b[] = {9, 9, 9};
        const int c[] = {1, 0, 0, 8, 9, 9};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits2 () {
        const int a[] = {4, 3, 2};
        const int b[] = {1};
        const int c[] = {4, 3, 2};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits3 () {
        const int a[] = {0, 0, 0, 0, 1};
        const int b[] = {2, 1};
        const int c[] = {0, 0, 0, 0, 2, 1};
              int x[10];
        const int* p = multiplies_digits(a, a + 5, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
        
        

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits0 () {
        const int a[] = {2,1,4};
        const int b[] = {2, 1};
        const int c[] = {4,3};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits01 () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {5,4,1,1};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits1 () {
        const int a[] = {1, 0, 0, 8, 9, 9};
        const int b[] = {9, 9, 9};
        const int c[] = {9, 9, 9};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {1};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits3 () {
        const int a[] = {0, 0, 0, 0, 2, 1};
        const int b[] = {2, 1};
        const int c[] = {0, 0, 0, 0, 1};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------
    // constructor
    // -----------

    void test_constructor_1 () {
        try {
            const Integer<int> x("abc");
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);}}

    void test_constructor_2 () {
        try {
            const Integer<int> x("2");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_3 () {
        try {
            const Integer<int> x(2);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_4 () {
        try {
            const Integer<int> x("0");
            }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_5 () {        try {
            const Integer<int> x("999");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_6 () {
        try {
            const Integer<int> x("test");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);}}

    void test_constructor_7 () {
        try {
            const Integer<int> x("-999");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_8 () {
        try {
            const Integer<int> x(-999);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // abs
    // ---

    void test_abs_n1 () {
        try {
            Integer<int>  x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT(&x == &y);
            CPPUNIT_ASSERT( x == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_0 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y ==  98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_1 () {
        try {
            Integer<int>  x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( y == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    void test_abs_2 () {
        try {
            Integer<int> x = -98765;
            Integer<int> y = x.abs();
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    void test_abs_3 () {
        try {
            Integer<int>  x = -1;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 1);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_4 () {
        try {
            Integer<int> x = 100;
            Integer<int> y = x.abs();
            CPPUNIT_ASSERT(x == 100);
            CPPUNIT_ASSERT(y == 100);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_5 () {
        try {
            Integer<int> x = -999;
            x.abs();
            CPPUNIT_ASSERT(x == 999);
}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // --------
    // equal_to
    // --------

    void test_equal_to () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 98765);
            CPPUNIT_ASSERT(  98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to1 () {
        try {
            const Integer<int> x = 100;
            const Integer<int> y = 100;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 100);
            CPPUNIT_ASSERT(  100 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 100));
            CPPUNIT_ASSERT(!(100 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to2 () {
        try {
            const Integer<int> x = 999;
            const Integer<int> y = 999;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 999);
            CPPUNIT_ASSERT(  999 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 999));
            CPPUNIT_ASSERT(!(999 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to3 () {
        try {
            const Integer<int> x = 1;
            const Integer<int> y = 1;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 1);
            CPPUNIT_ASSERT(  1 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 1));
            CPPUNIT_ASSERT(!(1 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to4 () {
        try {
            const Integer<int> x = -1;
            const Integer<int> y = -1;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == -1);
            CPPUNIT_ASSERT(  -1 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != -1));
            CPPUNIT_ASSERT(!(-1 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to5 () {

        try {
            const Integer<int> x = -1;
            const Integer<int> y = -1;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x != 1);
            CPPUNIT_ASSERT(  1 != x);
            CPPUNIT_ASSERT(      y != 1);
            CPPUNIT_ASSERT(  1 != y);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != -1));
            CPPUNIT_ASSERT(!(-1 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // --------
    // negation
    // --------

    void test_negation () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_negation1 () {
        try {
            const Integer<int> x = 999;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -999);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_negation2 () {
        try {
            const Integer<int> x = 1;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
   
     void test_negation3 () {
        try {
            const Integer<int> x = 1000000000;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -1000000000);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ------
    // output
    // ------

    void test_output () {
        try {
            Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output1 () {
        try {
            Integer<int> x = 999;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "999");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output2 () {
        try {
            Integer<int> x = 1;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "1");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output3 () {
        try {
            Integer<int> x = 10000000;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "10000000");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output4 () {
        try {
            Integer<int> x = -20;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-20");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int>       x = 500;
            const int          e =  9;
            Integer<int>      y = x.pow(e);
            CPPUNIT_ASSERT( e == 9);
            CPPUNIT_ASSERT( x ==    500);
            CPPUNIT_ASSERT(y ==   Integer<int>("1953125000000000000000000"));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_2 () {
        try {
            const Integer<int> x = 10;
            const int          e =  10;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 10);
            CPPUNIT_ASSERT(e ==  10);
            CPPUNIT_ASSERT(y ==  Integer<int>("10000000000"));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_3 () {
        try {
            Integer<int>       x = 2;
            const int          e =  3;
            Integer<int>      y = x.pow(e);
            CPPUNIT_ASSERT( e == 3);
            CPPUNIT_ASSERT( x == 2);
            CPPUNIT_ASSERT( y ==  8);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_4 () {
        try {
            const Integer<int> x = 2;
            const int          e = 4;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 2);
            CPPUNIT_ASSERT(e == 4);
            CPPUNIT_ASSERT(y == 16);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_5 () {
        try {
            const Integer<int> x = 98765;
            const int          e =  1;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e ==  1);
            CPPUNIT_ASSERT(y ==     98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // plus equals
    // ---

    void test_plus_equals1 () {
        try {
            Integer<int> x(40);
            const Integer<int> y(10);
            x += y;
            CPPUNIT_ASSERT(x == 50);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_plus_equals2 () {
        try {
            Integer<int> x("50");
            x += 30;
            CPPUNIT_ASSERT(x == 80);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_plus_equals3 () {
        try {
            Integer<int> x("20");
            x += 10;
            CPPUNIT_ASSERT(x == 30);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    void test_plus_equals4 () {
        try {
            Integer<int> x("10");
            x += 50;
            CPPUNIT_ASSERT(x == 60);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    void test_plus_equals5 () {
        try {
            Integer<int> x("10");
            x += 50000;
            CPPUNIT_ASSERT(x == 50010);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // minus equals
    // ---

    void test_minus_equals1 () {
        try {
            Integer<int> x("100");
            const Integer<int> y("5");
            x -= y;
            CPPUNIT_ASSERT(x == 95);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_minus_equals2 () {
        try {
            Integer<int> x("100");
            x -= 5;
            CPPUNIT_ASSERT(x == 95);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_minus_equals3 () {
        try {
            Integer<int> x("100");
            x -= 5;
            CPPUNIT_ASSERT(x == 95);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // multiply equals
    // ---

    void test_multiplies_equals1 () {
        try {
            Integer<int> x("10");
            const Integer<int> y("5");
            x *= y;
            CPPUNIT_ASSERT(x == 50);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_multiplies_equals2 () {
        try {
            Integer<int> x("5");
            x *= 5;
            CPPUNIT_ASSERT(x == 25);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_multiplies_equals3 () {
        try {
            Integer<int> x("10");
            x *= 5;
            CPPUNIT_ASSERT(x == 50);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // divide equals
    // ---

    void test_divide_equals1 () {
        try {
            Integer<int> x("100");
            const Integer<int> y("5");
            x /= y;
            CPPUNIT_ASSERT(x == 20);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_equals2 () {
        try {
            Integer<int> x("50");
            x /= 5;
            CPPUNIT_ASSERT(x == 10);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_equals3 () {
        try {
            Integer<int> x("100");
            x /= 5;
            CPPUNIT_ASSERT(x == 20);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_equals4 () {
        try {
            Integer<int> x("412");
            x /= 12;
            CPPUNIT_ASSERT(x == 34);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // shift left equals
    // ---

    void test_shift_left_equals1() {
        try {
            Integer<int> x("100");
            x <<= 2;
            CPPUNIT_ASSERT(x == 10000);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_left_equals2() {
        try {
            Integer<int> x("5");
            x <<= 2;
            CPPUNIT_ASSERT(x == 500);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_left_equals3() {
        try {
            Integer<int> x("11");
            x <<= 1;
            CPPUNIT_ASSERT(x == 110);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // shift right equals
    // ---

    void test_shift_right_equals1() {
        try {
            Integer<int> x("1111");
            x >>= 3;
            CPPUNIT_ASSERT(x == 1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_right_equals2() {
        try {
            Integer<int> x("999");
            x >>= 1;
            CPPUNIT_ASSERT(x == 99);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_right_equals3() {
        try {
            Integer<int> x("11");
            x >>= 1;
            CPPUNIT_ASSERT(x == 1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // ---
    // mod equals
    // ---

    void test_mod_equals1() {
        try {
            Integer<int> x("105");
            x %= 100;
            CPPUNIT_ASSERT(x == 5);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals2() {
        try {
            Integer<int> x("100");
            x %= 100;
            CPPUNIT_ASSERT(x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals3() {
        try {
            Integer<int> x("1050");
            x %= 100;
            CPPUNIT_ASSERT(x == 50);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals4() {
        try {
            Integer<int> x("1050");
            x %= 1;
            CPPUNIT_ASSERT(x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals5() {
        try {
            Integer<int> x("1050");
            x %= 2;
            CPPUNIT_ASSERT(x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits);
    CPPUNIT_TEST(test_shift_left_digits_1);
    CPPUNIT_TEST(test_shift_left_digits_2);
    CPPUNIT_TEST(test_shift_left_digits_3);
    
    CPPUNIT_TEST(test_shift_right_digits);
    CPPUNIT_TEST(test_shift_right_digits_1);
    CPPUNIT_TEST(test_shift_right_digits_2);
    CPPUNIT_TEST(test_shift_right_digits_3);
        
    CPPUNIT_TEST(test_plus_digits);
    CPPUNIT_TEST(test_plus_digits_1);
    CPPUNIT_TEST(test_plus_digits_2);
    CPPUNIT_TEST(test_plus_digits_3);
    CPPUNIT_TEST(test_plus_digits_4);
    CPPUNIT_TEST(test_plus_digits_5);
    CPPUNIT_TEST(test_plus_digits_6);
    CPPUNIT_TEST(test_plus_digits_7);
    CPPUNIT_TEST(test_plus_digits_8);
    
    CPPUNIT_TEST(test_minus_digits);
    CPPUNIT_TEST(test_minus_digits1);
    CPPUNIT_TEST(test_minus_digits2);
    CPPUNIT_TEST(test_minus_digits3);
    
    CPPUNIT_TEST(test_multiplies_digits);
    CPPUNIT_TEST(test_multiplies_digits1);
    CPPUNIT_TEST(test_multiplies_digits2);
    CPPUNIT_TEST(test_multiplies_digits3);    
    
    CPPUNIT_TEST(test_divides_digits0);
    CPPUNIT_TEST(test_divides_digits01);
    CPPUNIT_TEST(test_divides_digits1);
    CPPUNIT_TEST(test_divides_digits2);
    CPPUNIT_TEST(test_divides_digits3);

    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_constructor_5);
    CPPUNIT_TEST(test_constructor_6);
    CPPUNIT_TEST(test_constructor_7);
    CPPUNIT_TEST(test_constructor_8);

    CPPUNIT_TEST(test_abs_n1);
    CPPUNIT_TEST(test_abs_0);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_abs_3);
    CPPUNIT_TEST(test_abs_4);
    CPPUNIT_TEST(test_abs_5);

    CPPUNIT_TEST(test_equal_to);
    CPPUNIT_TEST(test_equal_to1);
    CPPUNIT_TEST(test_equal_to2);
    CPPUNIT_TEST(test_equal_to3);
    CPPUNIT_TEST(test_equal_to4);
    CPPUNIT_TEST(test_equal_to5);

    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_negation1);
    CPPUNIT_TEST(test_negation2);
    CPPUNIT_TEST(test_negation3);

    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_output1);
    CPPUNIT_TEST(test_output2);
    CPPUNIT_TEST(test_output3);
    CPPUNIT_TEST(test_output4);

    CPPUNIT_TEST(test_plus_equals1);
    CPPUNIT_TEST(test_plus_equals2);
    CPPUNIT_TEST(test_plus_equals3);    
    CPPUNIT_TEST(test_plus_equals4);    
    CPPUNIT_TEST(test_plus_equals5);    

    CPPUNIT_TEST(test_minus_equals1);
    CPPUNIT_TEST(test_minus_equals2);
    CPPUNIT_TEST(test_minus_equals3);

    CPPUNIT_TEST(test_multiplies_equals1);
    CPPUNIT_TEST(test_multiplies_equals2);
    CPPUNIT_TEST(test_multiplies_equals3);

    CPPUNIT_TEST(test_divide_equals1);
    CPPUNIT_TEST(test_divide_equals2);
    CPPUNIT_TEST(test_divide_equals3);
    CPPUNIT_TEST(test_divide_equals4);

    CPPUNIT_TEST(test_shift_left_equals1);
    CPPUNIT_TEST(test_shift_left_equals2);
    CPPUNIT_TEST(test_shift_left_equals3);

    CPPUNIT_TEST(test_shift_right_equals1);
    CPPUNIT_TEST(test_shift_right_equals2);
    CPPUNIT_TEST(test_shift_right_equals3);

    CPPUNIT_TEST(test_mod_equals1);
    CPPUNIT_TEST(test_mod_equals2);
    CPPUNIT_TEST(test_mod_equals3);
    CPPUNIT_TEST(test_mod_equals4);
    CPPUNIT_TEST(test_mod_equals5);

    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST(test_pow_3);
    CPPUNIT_TEST(test_pow_4);
    CPPUNIT_TEST(test_pow_5);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);          // turn off synchronization with C I/O
    cout << "TestInteger.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestInteger::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
