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

using namespace std;

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {

    void test_sandbox () {
        const Integer<int> x("01234");
        
        std::ostringstream out;
        out << x;

        CPPUNIT_ASSERT(out.str() == "01234");
    }

    void test_constructor_negative_int () {
        const Integer<int> x(-50);
        
        std::ostringstream out;
        out << x;

        CPPUNIT_ASSERT(out.str() == "-50");
    }

    void test_constructor_zero_int () {
        const Integer<int> x(0);
        
        std::ostringstream out;
        out << x;

        CPPUNIT_ASSERT(out.str() == "0");
    }

    void test_constructor_negative_string () {
        const Integer<int> x("-342");
        
        std::ostringstream out;
        out << x;

        CPPUNIT_ASSERT(out.str() == "-342");
    }

    // -----------------
    // shift_left_digits
    // -----------------
    void test_shift_left_digits1 () {
        const int a[] = {2, 3, 4, 0};
        const int b[] = {2, 3, 4, 0, 0, 0};
              int x[10];
        const int* p = shift_left_digits(a, a + 4, 2, x);
        CPPUNIT_ASSERT((p - x) == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_left_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_left_digits3 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, -1, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_left_digits4 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4, 0, 0};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    // ------------------
    // shift_right_digits
    // ------------------
    void test_shift_right_digits1 () {
        const int a[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 3, x);
        CPPUNIT_ASSERT((p - x) == 0);}

    void test_shift_right_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, -1, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_right_digits3 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}


    void test_shift_right_digits4 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    // -----------
    // plus_digits
    // -----------

    void test_plus_digits1 () {
        const int a[] =    {9, 0, 0};
        const int b[] =    {1, 0, 0};
        const int c[] = {1, 0, 0, 0};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);

        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits2 () {
        const int a[] = {3, 2, 3, 4};
        const int b[] =    {5, 6, 7};
        const int c[] = {3, 8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_plus_digits2_flipped () {
        const int a[] =    {5, 6, 7};
        const int b[] = {3, 2, 3, 4};
        const int c[] = {3, 8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_plus_digits3 () {
        const int a[] =    {9, 9, 9};
        const int b[] =          {1};
        const int c[] = {1, 0, 0, 0};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_plus_digits4 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);

        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits_writeOnSelf () {
        const int a[] =    {5, 6, 7};
              int b[] = {3, 2, 3, 4};
        const int c[] = {3, 8, 0, 1};

        const int* p = plus_digits(a, a + 3, b, b + 4, b);

        CPPUNIT_ASSERT(p - b == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(b), p, c));}


    // ------------
    // minus_digits
    // ------------
    void test_minus_digits1 () {
        const int a[] = {7, 8, 4, 3};
        const int b[] =    {5, 6, 8};
        const int c[] = {7, 2, 7, 5};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_minus_digits2 () {
        const int a[] = {7, 0, 4, 3};
        const int b[] =    {5, 6, 8};
        const int c[] = {6, 4, 7, 5};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits3 () {
        const int a[] = {1, 0, 2, 3};
        const int b[] =    {5, 0, 2};
        const int c[] =    {5, 2, 1};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 3, x);

        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}



    void test_minus_digits4 () {
        const int a[] = {1, 0, 0, 0, 0};
        const int b[] =    {9, 9, 9, 9};
        const int c[] =             {1};
              int x[10];
        const int* p = minus_digits(a, a + 5, b, b + 4, x);

        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_minus_digits5 () {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------------
    // multiplies_digits
    // -----------------


    void test_multiplies_digits1 () {
        const int a[] =    {2, 3, 4};
        const int b[] =          {7};
        const int c[] = {1, 6, 3, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);

        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

        void test_multiplies_digits2 () {
        const int a[] =    {2, 3, 4};
        const int b[] =       {1, 7};
        const int c[] = {3, 9, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 2, x);

        // std::cout << p-x << std::endl;
        // for(int i=0; i<4; ++i){
        //     std::cout << x[i] << " ";
        // }
        // std::cout << std::endl;


        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}



    void test_multiplies_digits3 () {
        const int a[] = {8, 4, 5, 9, 2, 5};
        const int b[] = {5, 6, 9, 8, 4, 2};
        const int c[] = {4, 8, 2, 0, 4, 3, 5, 9, 3, 8, 5, 0};
              int x[20];
        const int* p = multiplies_digits(a, a + 6, b, b + 6, x);

        CPPUNIT_ASSERT(p - x == 12);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits4 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);

        // std::cout << p-x << std::endl;
        // for(int i=0; i<4; ++i){
        //     std::cout << x[i] << " ";
        // }
        // std::cout << std::endl;

        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits1 () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_divides_digits2 () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {2, 3, 4};
        const int c[] = {5, 6, 7};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_divides_digits3 () {
        const int a[] = {2,3,7,4,8,3,1,2};
        const int b[] = {9,6,3,2};
        const int c[] = {2,4,6,5};
              int x[10];
        const int* p = divides_digits(a, a + 8, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_divides_digits4 () {
        const int a[] = {1,0,0,0,8};
        const int b[] = {1,0,7};
        const int c[] = {9,3};
              int x[10];
        const int* p = divides_digits(a, a + 5, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_divides_digits5 () {
        const int a[] = {9,9,9,9,9,9,9,9,9,9};
        const int b[] = {9,9};
        const int c[] = {1,0,1,0,1,0,1,0,1};
              int x[10];
        const int* p = divides_digits(a, a + 10, b, b + 2, x);

        CPPUNIT_ASSERT(p - x == 9);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------
    // constructor
    // -----------

    void test_constructor_1 () {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));}}

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

    // ---
    // abs
    // ---

    void test_integer_abs_1 () {
        try {
            Integer<int>  x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    void test_integer_abs_2 () {
        try {
            Integer<int>  x = 98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_1 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x ==  98765);
            CPPUNIT_ASSERT(y ==  98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_2 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y ==  98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // equal_to
    // --------

    void test_equal_to1 () {
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



    void test_equal_to2 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = -98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == -98765);
            CPPUNIT_ASSERT(  -98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != -98765));
            CPPUNIT_ASSERT(!(-98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_equal_to3 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -98765;
            CPPUNIT_ASSERT(      x != y);
            CPPUNIT_ASSERT(      x != -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // --------
    // less than
    // --------        


    void test_less_than1 () {
        try {
            const Integer<int> x = 1;
            const Integer<int> y = 2;
            CPPUNIT_ASSERT(      x < y);
            CPPUNIT_ASSERT(      x <= y);
            CPPUNIT_ASSERT(      y > x);
            CPPUNIT_ASSERT(      y >= x);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    void test_less_than2 () {
        try {
            const Integer<int> x = 2;
            const Integer<int> y = 2;
            CPPUNIT_ASSERT(      !(x < y));
            CPPUNIT_ASSERT(      x <= y);
            CPPUNIT_ASSERT(      !(x > y));
            CPPUNIT_ASSERT(      x >= y);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}



    void test_less_than3 () {
        try {
            const Integer<int> x = 2;
            CPPUNIT_ASSERT(      x < 5);
            CPPUNIT_ASSERT(      x <= 5);
            CPPUNIT_ASSERT(      x > -1);
            CPPUNIT_ASSERT(      x >= -1);
        }
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

    // ------
    // output
    // ------

    void test_output1 () {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    void test_output2 () {
        try {
            const Integer<int> x = -98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    void test_output3 () {
        try {
            const Integer<int> x = 0;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "0");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    //============================
    // plus equal
    //============================

    void test_integer_plus_equal1 () {
        Integer<int> x =  900;
        const Integer<int> y =  100;

        x += y;

        CPPUNIT_ASSERT(x == 1000);}

    void test_integer_plus_equal2 () {
        Integer<int>        x =  3234;
        const Integer<int>  y =  1100;

        x += y;

        CPPUNIT_ASSERT(x == 4334);}


    void test_integer_plus_equal3 () {
        Integer<int>        x =  -3234;
        const Integer<int>  y =  1100;

        x += y;

        CPPUNIT_ASSERT(x == -2134);}



    void test_integer_plus_equal4 () {
        Integer<int>        x =  3234;
        const Integer<int>  y =  -1100;

        x += y;

        CPPUNIT_ASSERT(x == 2134);}



    void test_integer_plus_equal5 () {
        Integer<int>        x =  -3234;
        const Integer<int>  y =  -1100;

        x += y;

        CPPUNIT_ASSERT(x == -4334);}

    void test_integer_plus_equal6 () {
        Integer<int>        x =  20;
        const Integer<int>  y =  40;

        x += y;

        CPPUNIT_ASSERT(x == 60);}

    void test_integer_plus_equal7 () {
        Integer<int>        x =  -20;
        const Integer<int>  y =  40;

        x += y;

        CPPUNIT_ASSERT(x == 20);}

    void test_integer_plus_equal8 () {
        Integer<int>        x =  -40;
        const Integer<int>  y =  40;

        x += y;

        CPPUNIT_ASSERT(x == 0);}

    void test_integer_plus_equal9 () {
        Integer<int>        x =  40;
        const Integer<int>  y =  -40;

        x += y;

        CPPUNIT_ASSERT(x == 0);}


    //============================
    // minus equal
    //============================

    void test_integer_minus_equal1 () {
        Integer<int> x       =  50;
        const Integer<int> y =  100;

        x -= y;

        CPPUNIT_ASSERT(x == -50);}

    void test_integer_minus_equal2 () {
        Integer<int> x       =  -50;
        const Integer<int> y =  100;

        x -= y;

        CPPUNIT_ASSERT(x == -150);}

    void test_integer_minus_equal3 () {
        Integer<int> x       =  50;
        const Integer<int> y =  -100;

        x -= y;

        CPPUNIT_ASSERT(x == 150);}

    void test_integer_minus_equal4 () {
        Integer<int> x       =  -50;
        const Integer<int> y =  -100;

        x -= y;

        CPPUNIT_ASSERT(x == 50);}

    void test_integer_minus_equal5 () {
        Integer<int> x       =  100;
        const Integer<int> y =  50;

        x -= y;

        CPPUNIT_ASSERT(x == 50);}

    void test_integer_minus_equal6 () {
        Integer<int> x       =  100;
        const Integer<int> y =  -50;

        x -= y;

        CPPUNIT_ASSERT(x == 150);}

    void test_integer_minus_equal7 () {
        Integer<int> x       =  -100;
        const Integer<int> y =  50;

        x -= y;

        CPPUNIT_ASSERT(x == -150);}

    void test_integer_minus_equal8 () {
        Integer<int> x       =  -100;
        const Integer<int> y =  -50;

        x -= y;

        CPPUNIT_ASSERT(x == -50);}



    void test_integer_minus_equal9 () {
        Integer<int> x       =  100;
        const Integer<int> y =  100;

        x -= y;

        CPPUNIT_ASSERT(x == 0);}

    //============================
    // multiply equal
    //============================

    void test_integer_multiply_equal1 () {
        Integer<int> x       =  123;
        const Integer<int> y =  57;
        Integer<int> z       =  123;

        x *= y;

        CPPUNIT_ASSERT(x == 7011);
        CPPUNIT_ASSERT(z * y == 7011);
        CPPUNIT_ASSERT(y * z == 7011);}

    void test_integer_multiply_equal2 () {
        Integer<int> x       =  -123;
        const Integer<int> y =  57;

        x *= y;
        
        CPPUNIT_ASSERT(x == -7011);}

    void test_integer_multiply_equal3 () {
        Integer<int> x       =  123;
        const Integer<int> y =  -57;

        x *= y;
        
        CPPUNIT_ASSERT(x == -7011);}

    void test_integer_multiply_equal4 () {
        Integer<int> x       =  -123;
        const Integer<int> y =  -57;

        x *= y;
        
        CPPUNIT_ASSERT(x == 7011);}

    void test_integer_multiply_equal5 () {
        Integer<int> x       =  123;
        const Integer<int> y =  0;

        x *= y;
        
        CPPUNIT_ASSERT(x == 0);}

    void test_integer_multiply_equal6 () {
        Integer<int> x       =  0;
        const Integer<int> y =  -57;

        x *= y;
        
        CPPUNIT_ASSERT(x == 0);}


    //============================
    // divide equal
    //============================


    void test_integer_divide_equal1 () {
        Integer<int> x       =  132678;
        const Integer<int> y =  567;

        x /= y;

        CPPUNIT_ASSERT(x == 234);}

    void test_integer_divide_equal2 () {
        Integer<int> x       =  132678;
        const Integer<int> y =  234;

        x /= y;

        CPPUNIT_ASSERT(x == 567);}

    void test_integer_divide_equal3 () {
        Integer<int> x       =  23748312;
        const Integer<int> y =  9632;

        x /= y;

        CPPUNIT_ASSERT(x == 2465);}

    void test_integer_divide_equal4 () {
        Integer<int> x       =  10008;
        const Integer<int> y =  107;

        x /= y;

        CPPUNIT_ASSERT(x == 93);}

    void test_integer_divide_equal5 () {
        Integer<int> x       =  99999999;
        const Integer<int> y =  99;

        x /= y;

        CPPUNIT_ASSERT(x == 1010101);}

    //============================
    // shift left equal
    //============================

    void test_integer_shift_left_equal1 () {
        Integer<int> x("100");
        x <<= 2;

        CPPUNIT_ASSERT(x == 10000);}

    void test_integer_shift_left_equal2 () {
        Integer<int> x("123");
        x <<= 5;

        CPPUNIT_ASSERT(x == 12300000);}

    void test_integer_shift_left_equal3 () {
        Integer<int> x("321");
        x <<= 0;

        CPPUNIT_ASSERT(x == 321);}


    //============================
    // shift right equal
    //============================

    void test_integer_shift_right_equal1 () {
        Integer<int> x("100");
        x >>= 2;

        CPPUNIT_ASSERT(x == 1);}

    void test_integer_shift_right_equal2 () {
        Integer<int> x("321321");
        x >>= 4;

        CPPUNIT_ASSERT(x == 32);}

    void test_integer_shift_right_equal3 () {
        Integer<int> x("987654321");
        x >>= 0;

        CPPUNIT_ASSERT(x == 987654321);}

    //============================
    // pow
    //============================
    void test_pow_1 () {
        try {
            Integer<int>       x = 98765;
            const int          e =  0;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT( e == 0);
            CPPUNIT_ASSERT( x ==    1);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    void test_pow_2 () {
        try {
            Integer<int>       x = 98765;
            const int          e =  1;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT( e == 1);
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_3 () {
        try {
            Integer<int>       x = 98765;
            const int          e =  2;
            Integer<int>&      y = x.pow(e);

            Integer<int> solution("9754525225");
            CPPUNIT_ASSERT( x == solution);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}



    void test_pow_4 () {
        try {
            Integer<int>       x = 16;
            const int          e =  3;
            Integer<int>&      y = x.pow(e);

            Integer<int> solution("4096");
            CPPUNIT_ASSERT( x == solution);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_5 () {
        try {
            Integer<int>       x = 98;
            const int          e = 98;
            Integer<int>&      y = x.pow(e);

            Integer<int> solution("1380878341261486750656911803252309726876604105686729638072729543243701479670593033211008001443536626310535980077544691196522513327846303307992442770355560270350429006522588433404602387992091295744");
            CPPUNIT_ASSERT( x == solution);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_6 () {
        try {
            Integer<int>       x = 16;
            const int          e =  3;
            Integer<int>&      y = x.pow(e);

            Integer<int> solution("4096");
            CPPUNIT_ASSERT( x == solution);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_7 () {
        try {
            Integer<int>       x = 16;
            const int          e =  3;
            Integer<int>&      y = x.pow(e);

            Integer<int> solution("4096");
            CPPUNIT_ASSERT( x == solution);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);

    CPPUNIT_TEST(test_sandbox);
    CPPUNIT_TEST(test_constructor_negative_int);
    CPPUNIT_TEST(test_constructor_zero_int);
    CPPUNIT_TEST(test_constructor_negative_string);

    CPPUNIT_TEST(test_shift_left_digits1);
    CPPUNIT_TEST(test_shift_left_digits2);
    CPPUNIT_TEST(test_shift_left_digits3);
    CPPUNIT_TEST(test_shift_left_digits4);
    CPPUNIT_TEST(test_shift_right_digits1);
    CPPUNIT_TEST(test_shift_right_digits2);
    CPPUNIT_TEST(test_shift_right_digits3);
    CPPUNIT_TEST(test_shift_right_digits4);
    CPPUNIT_TEST(test_plus_digits1);
    CPPUNIT_TEST(test_plus_digits2);
    CPPUNIT_TEST(test_plus_digits2_flipped);
    CPPUNIT_TEST(test_plus_digits3);
    CPPUNIT_TEST(test_plus_digits4);
    CPPUNIT_TEST(test_plus_digits_writeOnSelf);

    CPPUNIT_TEST(test_minus_digits1);
    CPPUNIT_TEST(test_minus_digits2);
    CPPUNIT_TEST(test_minus_digits3);
    CPPUNIT_TEST(test_minus_digits4);
    CPPUNIT_TEST(test_minus_digits5);

    CPPUNIT_TEST(test_multiplies_digits1);
    CPPUNIT_TEST(test_multiplies_digits2);
    CPPUNIT_TEST(test_multiplies_digits3);
    CPPUNIT_TEST(test_multiplies_digits4);

    CPPUNIT_TEST(test_divides_digits1);
    CPPUNIT_TEST(test_divides_digits2);
    CPPUNIT_TEST(test_divides_digits3);
    CPPUNIT_TEST(test_divides_digits4);
    CPPUNIT_TEST(test_divides_digits5);

    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_integer_abs_1);
    CPPUNIT_TEST(test_integer_abs_2);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_equal_to1);
    CPPUNIT_TEST(test_equal_to2);
    CPPUNIT_TEST(test_equal_to3);

    CPPUNIT_TEST(test_less_than1);
    CPPUNIT_TEST(test_less_than2);
    CPPUNIT_TEST(test_less_than3);

    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_output1);
    CPPUNIT_TEST(test_output2);
    CPPUNIT_TEST(test_output3);

    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST(test_pow_3);
    CPPUNIT_TEST(test_pow_4);
    CPPUNIT_TEST(test_pow_5);
    CPPUNIT_TEST(test_pow_6);
    CPPUNIT_TEST(test_pow_7);

    CPPUNIT_TEST(test_integer_plus_equal1);
    CPPUNIT_TEST(test_integer_plus_equal2);
    CPPUNIT_TEST(test_integer_plus_equal3);
    CPPUNIT_TEST(test_integer_plus_equal4);
    CPPUNIT_TEST(test_integer_plus_equal5);
    CPPUNIT_TEST(test_integer_plus_equal6);
    CPPUNIT_TEST(test_integer_plus_equal7);
    CPPUNIT_TEST(test_integer_plus_equal8);
    CPPUNIT_TEST(test_integer_plus_equal9);

    CPPUNIT_TEST(test_integer_minus_equal1);
    CPPUNIT_TEST(test_integer_minus_equal2);
    CPPUNIT_TEST(test_integer_minus_equal3);
    CPPUNIT_TEST(test_integer_minus_equal4);
    CPPUNIT_TEST(test_integer_minus_equal5);
    CPPUNIT_TEST(test_integer_minus_equal6);
    CPPUNIT_TEST(test_integer_minus_equal7);
    CPPUNIT_TEST(test_integer_minus_equal8);
    CPPUNIT_TEST(test_integer_minus_equal9);

    CPPUNIT_TEST(test_integer_multiply_equal1);
    CPPUNIT_TEST(test_integer_multiply_equal2);
    CPPUNIT_TEST(test_integer_multiply_equal3);
    CPPUNIT_TEST(test_integer_multiply_equal4);
    CPPUNIT_TEST(test_integer_multiply_equal5);
    CPPUNIT_TEST(test_integer_multiply_equal6);


    CPPUNIT_TEST(test_integer_divide_equal1);
    CPPUNIT_TEST(test_integer_divide_equal2);
    CPPUNIT_TEST(test_integer_divide_equal3);
    CPPUNIT_TEST(test_integer_divide_equal4);
    CPPUNIT_TEST(test_integer_divide_equal5);

    CPPUNIT_TEST(test_integer_shift_left_equal1);
    CPPUNIT_TEST(test_integer_shift_left_equal2);
    CPPUNIT_TEST(test_integer_shift_left_equal3);

    CPPUNIT_TEST(test_integer_shift_right_equal1);
    CPPUNIT_TEST(test_integer_shift_right_equal2);
    CPPUNIT_TEST(test_integer_shift_right_equal3);

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
