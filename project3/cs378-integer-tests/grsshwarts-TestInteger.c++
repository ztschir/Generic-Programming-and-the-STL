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
#include <cstring> // strcmp
#include <sstream> // ostringstream
#include <stdexcept> // invalid_argument
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TestSuite.h" // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {
    // -----------------
    // shift_left_digits
    // -----------------

    void test_shift_left_digits1() {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4, 0, 0};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_left_digits2() {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_left_digits3() {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4, 0, 0, 0, 0, 0, 0}; 
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 6, x);
        CPPUNIT_ASSERT((p - x) == 9);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

        void test_shift_right_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

        void test_shift_right_digits3 () {
        const int a[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 3, x);
        CPPUNIT_ASSERT((p - x) == 0);}
    // -----------
    // plus_digits
    // -----------

    void test_plus_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
	void test_plus_digits2 () {
        const int a[] = {6, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 2, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits3 () {
        const int a[] = {2, 3, 4};
        const int b[] = {9, 9, 5, 5};
        const int c[] = {1, 0, 1, 8, 9};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits4 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 9, 5, 5};
        const int c[] = {6, 1, 8, 9};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits5 () {
        const int a[] = {0};
        const int b[] = {5, 9, 5, 5};
        const int c[] = {5, 9, 5, 5};
              int x[10];
        const int* p = plus_digits(a, a+1, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // ------------
    // minus_digits
    // ------------

    void test_minus_digits1 () {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits2 () {
        const int a[] = {8, 0, 1};
        const int b[] = {8, 0, 0};
        const int c[] = {1};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits3 () {
        const int a[] = {1, 8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------------
    // compare_to helper
    // -----------------
    void test_compare_to1 () {
        const int a[] = {2};
        const int b[] = {5, 5};
        const int p = compare_to(a, a+1, b, b + 2);
        CPPUNIT_ASSERT( p == -1);
    }

    void test_compare_to2 () {
        const int a[] = {7, 2};
        const int b[] = {5, 5};
        const int p = compare_to(a, a+2, b, b + 2);
        CPPUNIT_ASSERT( p == 1);
    }

    void test_compare_to3 () {
        const int b[] = {7, 2};
        const int a[] = {5, 5};
        const int p = compare_to(a, a+2, b, b + 2);
        CPPUNIT_ASSERT( p == -1);
    }

    void test_compare_to4 () {
        const int a[] = {1, 1, 2};
        const int b[] = {5, 5};
        const int p = compare_to(a, a+3, b, b + 2);
        CPPUNIT_ASSERT( p == 1);
    }

    void test_compare_to5 () {
        const int a[] = {5, 5};
        const int b[] = {5, 5};
        const int p = compare_to(a, a+2, b, b + 2);
        CPPUNIT_ASSERT( p == 0);
    }

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits1 () {
        const int a[] = {5, 3, 6};
        const int b[] = {4};
        const int c[] = {2, 1, 4, 4};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits3 () {
        const int a[] = {5, 3, 6};
        const int b[] = {0};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 0);}

    void test_multiplies_digits4 (){
        const int a[] = {4};
        const int b[] = {5, 3, 6};
        const int c[] = {2, 1, 4, 4};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits5 (){
        const int a[] = {9};
        const int b[] = {5};
        const int c[] = {4, 5};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 2);
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
        const int b[] = {1, 3, 2, 6, 7, 8};
        const int a[] = {5, 6, 7};
        const int c[] = {0};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 6, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits3 () {
        const int a[] = {5, 6, 7};
        const int b[] = {5, 6, 7};
        const int c[] = {1};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits4 () {
        const int a[] = {0};
        const int b[] = {5, 6, 7};
        const int c[] = {0};
              int x[10];
        const int* p = divides_digits(a, a + 1, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
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

    void test_abs_1 () {
        try {
            Integer<int> x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_2 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // equal_to
    // --------

    void test_equal_to1() {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT( x == y);
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT( 98765 == x);
            CPPUNIT_ASSERT( !(x != y));
            CPPUNIT_ASSERT( !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_equal_to2() {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 3;
            CPPUNIT_ASSERT(!(x == y));
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT( 98765 == x);
            CPPUNIT_ASSERT((x != y));
            CPPUNIT_ASSERT( !(x != 98765));
            CPPUNIT_ASSERT((98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // less than
    // --------
    
    void test_lessthan1() {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT(!(x < y));
            CPPUNIT_ASSERT(!(x > y));
            CPPUNIT_ASSERT(x <= y);
            CPPUNIT_ASSERT(x >= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_lessthan2() {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 3;
            CPPUNIT_ASSERT(!(x < y));
           CPPUNIT_ASSERT(x > y);
            CPPUNIT_ASSERT(!(x <= y));
            CPPUNIT_ASSERT(x >= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_lessthan3() {
        try {
            const Integer<int> x = 3;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT(x < y);
           CPPUNIT_ASSERT(!(x > y));
            CPPUNIT_ASSERT(x <= y);
            CPPUNIT_ASSERT(!(x >= y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    // --------
    // negation
    // --------

    void test_negation () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);
            CPPUNIT_ASSERT(x == 98765);
            const Integer<int> z = -(-x);
            CPPUNIT_ASSERT(z == 98765);
            CPPUNIT_ASSERT(x == 98765);
            }
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
            const Integer<int> x("45");
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "45");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    // ---
    // plus equals
    // ---
    void test_plus_equals1 () {
        try {
            Integer<int> x("98765");
            const Integer<int> y("5");
            x += y;
            CPPUNIT_ASSERT(x == 98770);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_plus_equals2 () {
        try {
            Integer<int> x("98765");
            x += 5;
            CPPUNIT_ASSERT(x == 98770);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_plus_equals3 () {
        try {
            Integer<int> x("98765");
            x += -5;
            CPPUNIT_ASSERT(x == 98760);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // minus equals
    // ---
    void test_minus_equals1 () {
        try {
            Integer<int> x("98765");
            const Integer<int> y("5");
            x -= y;
            CPPUNIT_ASSERT(x == 98760);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_minus_equals2 () {
        try {
            Integer<int> x("98765");
            x -= 5;
            CPPUNIT_ASSERT(x == 98760);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_minus_equals3 () {
        try {
            Integer<int> x("98765");
            x -= -5;
            CPPUNIT_ASSERT(x == 98770);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // ---
    // multiplies equals
    // ---
    void test_multiplies_equals1 () {
        try {
            Integer<int> x("5");
            const Integer<int> y("5");
            x *= y;
            CPPUNIT_ASSERT(x == 25);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_multiplies_equals2 () {
        try {
            Integer<int> x("9");
            x *= 5;
            CPPUNIT_ASSERT(x == 45);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_multiplies_equals3 () {
        try {
            Integer<int> x("9");
            x *= -5;
            CPPUNIT_ASSERT(x == -45);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // divide equals
    // ---
    void test_divide_equals1 () {
        try {
            Integer<int> x("45");
            const Integer<int> y("5");
            x /= y;
            CPPUNIT_ASSERT(x == 9);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_equals2 () {
        try {
            Integer<int> x("45");
            x /= 5;
            CPPUNIT_ASSERT(x == 9);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_equals3 () {
        try {
            Integer<int> x("45");
            x /= -5;
            CPPUNIT_ASSERT(x == -9);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // shift left equals
    // ---

    void test_shift_left_equals1() {
        try {
            Integer<int> x("234");
            x <<= 2;
            CPPUNIT_ASSERT(x == 23400);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_left_equals2() {
        try {
            Integer<int> x("1");
            x <<= 5;
            CPPUNIT_ASSERT(x == 100000);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_left_equals3() {
        try {
            Integer<int> x("234");
            x <<= -1;
            CPPUNIT_ASSERT(x == 23);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // ---
    // shift right equals
    // ---
    void test_shift_right_equals1() {
        try {
            Integer<int> x("234");
            x >>= 2;
            CPPUNIT_ASSERT(x == 2);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_right_equals2() {
        try {
            Integer<int> x("110000");
            x >>= 5;
            CPPUNIT_ASSERT(x == 1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_right_equals3() {
        try {
            Integer<int> x("234");
            x >>= -1;
            CPPUNIT_ASSERT(x == 2340);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}


    // ---
    // mod equals
    // ---
    void test_mod_equals1() {
        try {
            Integer<int> x("234");
            x %= 100;
            CPPUNIT_ASSERT(x == 34);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals2() {
        try {
            Integer<int> x("234");
            x %= 117;
            CPPUNIT_ASSERT(x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals3() {
        try {
            Integer<int> x("-234");
            x %= 100;
            CPPUNIT_ASSERT(x == 66);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_equals4() {
        try {
            Integer<int> x("-234");
            x %= 117;
            CPPUNIT_ASSERT(x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int> x = 98765;
            const int e = 0;
            Integer<int>& y = x.pow(e);
            CPPUNIT_ASSERT( e == 0);
            CPPUNIT_ASSERT( x == 1);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_2 () {
        try {
            const Integer<int> x = 98765;
            const int e = 1;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e == 1);
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_3 () {
        try {
            const Integer<int> x = 0;
            const int e = 451651;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(e == 451651);
            CPPUNIT_ASSERT(y == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits1);
    CPPUNIT_TEST(test_shift_left_digits2);
    CPPUNIT_TEST(test_shift_left_digits3);
    CPPUNIT_TEST(test_shift_right_digits1);
    CPPUNIT_TEST(test_shift_right_digits2);
    CPPUNIT_TEST(test_shift_right_digits3);
    CPPUNIT_TEST(test_plus_digits1);
    CPPUNIT_TEST(test_plus_digits2);
    CPPUNIT_TEST(test_plus_digits3);
    CPPUNIT_TEST(test_plus_digits4);
    CPPUNIT_TEST(test_plus_digits5);
    CPPUNIT_TEST(test_minus_digits1);
    CPPUNIT_TEST(test_minus_digits2);
    CPPUNIT_TEST(test_minus_digits3);
    CPPUNIT_TEST(test_compare_to1);
    CPPUNIT_TEST(test_compare_to2);
    CPPUNIT_TEST(test_compare_to3);
    CPPUNIT_TEST(test_compare_to4);
    CPPUNIT_TEST(test_compare_to5);
   	CPPUNIT_TEST(test_multiplies_digits1);
    CPPUNIT_TEST(test_multiplies_digits2);
   	CPPUNIT_TEST(test_multiplies_digits3);
   	CPPUNIT_TEST(test_multiplies_digits4);
    CPPUNIT_TEST(test_multiplies_digits5);
    CPPUNIT_TEST(test_divides_digits1);
    CPPUNIT_TEST(test_divides_digits2);
    CPPUNIT_TEST(test_divides_digits3);
    CPPUNIT_TEST(test_divides_digits4);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_equal_to1);
    CPPUNIT_TEST(test_equal_to2);
    CPPUNIT_TEST(test_lessthan1);
    CPPUNIT_TEST(test_lessthan2);
    CPPUNIT_TEST(test_lessthan3);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_output1);
    CPPUNIT_TEST(test_output2);
    CPPUNIT_TEST(test_plus_equals1);
    CPPUNIT_TEST(test_plus_equals2);
    CPPUNIT_TEST(test_plus_equals3);
    CPPUNIT_TEST(test_minus_equals1);
    CPPUNIT_TEST(test_minus_equals2);
    CPPUNIT_TEST(test_minus_equals3);
    CPPUNIT_TEST(test_multiplies_equals1);
    CPPUNIT_TEST(test_multiplies_equals2);
    CPPUNIT_TEST(test_multiplies_equals3);
    CPPUNIT_TEST(test_divide_equals1);
    CPPUNIT_TEST(test_divide_equals2);
    CPPUNIT_TEST(test_divide_equals3);
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
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST(test_pow_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestInteger.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestInteger::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}