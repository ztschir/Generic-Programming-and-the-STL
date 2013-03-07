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
        const int a[] = {1, 1, 1, 1, 1};
        const int b[] = {8, 8, 8, 8};
        const int c[] = {1, 9, 9, 9, 9};
              int x[10];
        const int* p = plus_digits(a, a + 5, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
        
    void test_plus_digits3 () {
        const int a[] = {9};
        const int b[] = {1, 2, 3};
        const int c[] = {1, 3, 2};
              int x[10];
        const int* p = plus_digits(a, a + 1, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits4 () {
        const int a[] = {3, 9, 3, 2, 1, 6};
        const int b[] = {6, 5, 5, 3, 6, 0};
        const int c[] = {1, 0, 4, 8, 5, 7, 6};
              int x[10];
        const int* p = plus_digits(a, a + 6, b, b + 6, x);
        CPPUNIT_ASSERT(p - x == 7);
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
        const int a[] = {1, 0, 0, 0};
        const int b[] = {9, 9, 9};
        const int c[] = {1};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 3, x);
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
    // multiply_helper
    // -----------------

    void test_multiply_helper1 () {
        const int a[] = {2, 3, 4};
        const int b = 1;
        vector<int> c;
        c.push_back(4);
        c.push_back(3);
        c.push_back(2);
        vector<int> p = multiply_helper(a, a + 3, b);
        CPPUNIT_ASSERT(p == c);}
        
     void test_multiply_helper2 () {
        const int a[] = {2, 3, 4};
        const int b = 5;
        vector<int> c;
        c.push_back(0);
        c.push_back(7);
        c.push_back(1);
        c.push_back(1);
        vector<int> p = multiply_helper(a, a + 3, b);
        CPPUNIT_ASSERT(p == c);
        }
     
     void test_multiply_helper3 () {
        const int a[] = {2, 3, 4};
        const int b = 0;
        vector<int> c;
        c.push_back(0);
        vector<int> p = multiply_helper(a, a + 3, b);
        CPPUNIT_ASSERT(p == c);}

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
      
        
    void test_multiplies_digits2 () {
        const int a[] = {2};
        const int b[] = {2};
        const int c[] = {4};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
       
    void test_multiplies_digits3 () {
        const int a[] = {6, 5, 5, 3, 6};
        const int b[] = {1, 6};
        const int c[] = {1, 0, 4, 8, 5, 7, 6};
              int x[10];
        const int* p = multiplies_digits(a, a + 5, b, b + 2, x);
        //cout << "printing p-x " << p-x << endl;
        CPPUNIT_ASSERT(p - x == 7);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
        
/*
    // --------------
    // divides_digits
    // --------------

    void test_divides_digits () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------
    // constructor
    // -----------
*/
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
            Integer<int>  x = -98765;
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
            CPPUNIT_ASSERT(y ==  98765);}
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
            CPPUNIT_ASSERT(!(98765 != y));
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    
    // --------
    // multiply_equal_to
    // --------

    void test_multiply_equal_to1 () {
        try {
            Integer<int> x = 987;
            const Integer<int> y = 987;
            x *= y;
            //cout << "X = " << x << endl;
            CPPUNIT_ASSERT(x == 974169);
            CPPUNIT_ASSERT(y == 987);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    void test_multiply_equal_to2 () {
        try {
            Integer<int> x = 2;
            const Integer<int> y = 2;
            x *= y;
            //cout << "X = " << x << endl;
            CPPUNIT_ASSERT(x == 4);
            CPPUNIT_ASSERT(y == 2);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    void test_multiply_equal_to3 () {
        try {
            Integer<int> x = 10;
            const Integer<int> y = 10;
            x *= y;
            //cout << "X = " << x << endl;
            CPPUNIT_ASSERT(x == 100);
            CPPUNIT_ASSERT(y == 10);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // --------
    // negation
    // --------

    void test_negation1 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_negation2 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_negation3 () {
        try {
            const Integer<int> x = 0;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}     

   // --------
    // minus_equal_to
    // --------

    void test_minus_equal_to1 () {
        try {
            Integer<int> x = 987;
            const Integer<int> y = 987;
            x -= y;
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y == 987);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_equal_to2 () {
        try {
            Integer<int> x = 123456789;
            const Integer<int> y = 1;
            x -= y;
            CPPUNIT_ASSERT(x == 123456788);
            CPPUNIT_ASSERT(y == 1);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    void test_minus_equal_to3 () {
        try {
            Integer<int> x = -124;
            const Integer<int> y = -123;
            x -= y;
            CPPUNIT_ASSERT(x == -1);
            CPPUNIT_ASSERT(y == -123);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }


   // --------
    // plus_equal_to
    // --------

    void test_plus_equal_to1 () {
        try {
            Integer<int> x = 987;
            const Integer<int> y = 987;
            x += y;
            CPPUNIT_ASSERT(x == 1974);
            CPPUNIT_ASSERT(y == 987);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_equal_to2 () {
        try {
            Integer<int> x = 123456789;
            const Integer<int> y = 1;
            x += y;
            CPPUNIT_ASSERT(x == 123456790);
            CPPUNIT_ASSERT(y == 1);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    void test_plus_equal_to3 () {
        try {
            Integer<int> x = 124;
            const Integer<int> y = -123;
            x += y;
            CPPUNIT_ASSERT(x == 1);
            CPPUNIT_ASSERT(y == -123);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    
    
   // --------
    // shift_left_equal_to
    // --------

    void test_shift_left_equal_to1 () {
        try {
            Integer<int> x = 987;
            int y = 5;
            x <<= y;
            CPPUNIT_ASSERT(x == 98700000);
            CPPUNIT_ASSERT(y == 5);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_shift_left_equal_to2 () {
        try {
            Integer<int> x = 1;
            int y = 1;
            x <<= y;
            CPPUNIT_ASSERT(x == 10);
            CPPUNIT_ASSERT(y == 1);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    void test_shift_left_equal_to3 () {
        try {
            Integer<int> x = 123456;
            int y = 1;
            x <<= y;
            CPPUNIT_ASSERT(x == 1234560);
            CPPUNIT_ASSERT(y == 1);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    
    
    // --------
    // shift_right_equal_to
    // --------

    void test_shift_right_equal_to1 () {
        try {
            Integer<int> x = 987;
            int y = 2;
            x >>= y;
            CPPUNIT_ASSERT(x == 9);
            CPPUNIT_ASSERT(y == 2);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_shift_right_equal_to2 () {
        try {
            Integer<int> x = 100000;
            int y = 1;
            x >>= y;
            CPPUNIT_ASSERT(x == 10000);
            CPPUNIT_ASSERT(y == 1);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }
    
    void test_shift_right_equal_to3 () {
        try {
            Integer<int> x = 123456;
            int y = 1;
            x >>= y;
            CPPUNIT_ASSERT(x == 12345);
            CPPUNIT_ASSERT(y == 1);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ------
    // output
    // ------

    void test_output () {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int>       x = 8;
            const int          e =  10;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT( e == 10);
            CPPUNIT_ASSERT( x ==  1073741824);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_2 () {
        try {
            const Integer<int> x = 8;
            const int          e =  10;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 8);
            CPPUNIT_ASSERT(e ==  10);
            CPPUNIT_ASSERT(y == 1073741824);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_3 () {
        try {
            Integer<int>       x = 2;
            const int          e =  3;

            Integer<int>&      y = x.pow(e);

            CPPUNIT_ASSERT( e == 3);
            CPPUNIT_ASSERT( x ==  8);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_pow_4 () {
        try {
            Integer<int>       x = 2;
            const int          e =  30;
            Integer<int>&      y = x.pow(e);
            //cout << "pow: " << y << endl;
            CPPUNIT_ASSERT( e == 30);
            CPPUNIT_ASSERT( x ==  1073741824);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_lt_1 (){
       try {
            const Integer<int> x = 98765;
            const Integer<int> y = 9867;
            const int          e = 9867;
            CPPUNIT_ASSERT(y < x);
            CPPUNIT_ASSERT(x > y);
            CPPUNIT_ASSERT(x > e);
            CPPUNIT_ASSERT(e < x);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    void test_lt_2 (){
       try {
            const Integer<int> x = 98765;
            const Integer<int> y = -9867;
            const int          e = -9867;
            CPPUNIT_ASSERT(y < x);
            CPPUNIT_ASSERT(x > y);
            CPPUNIT_ASSERT(x > e);
            CPPUNIT_ASSERT(e < x);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    void test_lt_3 (){
       try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98756;
            const int          e = 98752;
            CPPUNIT_ASSERT(y < x);
            CPPUNIT_ASSERT(x > y);
            CPPUNIT_ASSERT(x > e);
            CPPUNIT_ASSERT(e < x);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_output_1 (){
       try {
            const Integer<int> x("98765");
            ostringstream oss;
            oss << x;
            string s = oss.str();
            CPPUNIT_ASSERT(s == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
            
            
    void test_isPowerOfTwo_1 (){
        try {
            Integer<int> x("0");
            CPPUNIT_ASSERT(!x.isPowerOfTwo(10));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_isPowerOfTwo_2 (){
        try {
            Integer<int> x("0");
            CPPUNIT_ASSERT(!x.isPowerOfTwo(1025));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_isPowerOfTwo_3 (){
        try {
            Integer<int> x("0");
            CPPUNIT_ASSERT(x.isPowerOfTwo(1024));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}} 
            
            
    void test_processE_1 (){
        try {
            Integer<int> x("0");
            CPPUNIT_ASSERT(x.processE(10) == 8);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
     void test_processE_2 (){
        try {
            Integer<int> x("0");
            CPPUNIT_ASSERT(x.processE(16) == 16);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}      
     void test_processE_3 (){
        try {
            Integer<int> x("0");
            CPPUNIT_ASSERT(x.processE(2) == 2);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
            
     void test_quickExp_1 (){
        try {
            Integer<int> x("2");
            CPPUNIT_ASSERT(x.quickExp(8) == 256);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
     void test_quickExp_2 (){
        try {
            Integer<int> x("4");
            CPPUNIT_ASSERT(x.quickExp(8) == 65536);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
     void test_quickExp_3 (){
        try {
            Integer<int> x("2");
            CPPUNIT_ASSERT(x.quickExp(4) == 16);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

     void test_dummy1 (){
        try{
            Integer<int> x(2);
            Integer<int> y(2);
            Integer<int> r = x.pow(16);
            CPPUNIT_ASSERT(r  == 65536);
            r *= y.pow(4);
            //cout << "r: " << r << endl;
            CPPUNIT_ASSERT(r  == 1048576);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
      void test_dummy2 (){
        try{
            Integer<int> x(65536);
            Integer<int> y(16);
            x *= y;
            //cout << "x " << x << endl;
            CPPUNIT_ASSERT(x  == 1048576);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits);
    CPPUNIT_TEST(test_shift_right_digits1);
    CPPUNIT_TEST(test_shift_right_digits2);
    CPPUNIT_TEST(test_plus_digits1);
    CPPUNIT_TEST(test_plus_digits2);
    CPPUNIT_TEST(test_plus_digits3);
    CPPUNIT_TEST(test_plus_digits4);
    CPPUNIT_TEST(test_minus_digits1);
    CPPUNIT_TEST(test_minus_digits2);
    CPPUNIT_TEST(test_minus_digits3);
    CPPUNIT_TEST(test_multiply_helper1);
    CPPUNIT_TEST(test_multiply_helper2);
    CPPUNIT_TEST(test_multiply_helper3);
    CPPUNIT_TEST(test_multiplies_digits1);
    CPPUNIT_TEST(test_multiplies_digits2);
    CPPUNIT_TEST(test_multiplies_digits3);
//    CPPUNIT_TEST(test_divides_digits);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_negation1);
    CPPUNIT_TEST(test_negation2);
    CPPUNIT_TEST(test_negation3);
    CPPUNIT_TEST(test_minus_equal_to1);
    CPPUNIT_TEST(test_minus_equal_to2);
    CPPUNIT_TEST(test_minus_equal_to3);
    CPPUNIT_TEST(test_plus_equal_to1);
    CPPUNIT_TEST(test_plus_equal_to2);
    CPPUNIT_TEST(test_plus_equal_to3);
    CPPUNIT_TEST(test_shift_left_equal_to1);
    CPPUNIT_TEST(test_shift_left_equal_to2);
    CPPUNIT_TEST(test_shift_left_equal_to3);
    CPPUNIT_TEST(test_shift_right_equal_to1);
    CPPUNIT_TEST(test_shift_right_equal_to2);
    CPPUNIT_TEST(test_shift_right_equal_to3);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST(test_pow_3);
    CPPUNIT_TEST(test_pow_4);
    CPPUNIT_TEST(test_equal_to);
    CPPUNIT_TEST(test_multiply_equal_to1);
    CPPUNIT_TEST(test_multiply_equal_to2);
    CPPUNIT_TEST(test_multiply_equal_to3);
    CPPUNIT_TEST(test_lt_1);
    CPPUNIT_TEST(test_lt_2);
    CPPUNIT_TEST(test_lt_3);
    CPPUNIT_TEST(test_output_1);
    CPPUNIT_TEST(test_isPowerOfTwo_1);
    CPPUNIT_TEST(test_isPowerOfTwo_2);
    CPPUNIT_TEST(test_isPowerOfTwo_3);
    CPPUNIT_TEST(test_processE_1);
    CPPUNIT_TEST(test_processE_2);
    CPPUNIT_TEST(test_processE_3);
    CPPUNIT_TEST(test_quickExp_1);
    CPPUNIT_TEST(test_quickExp_2);
    CPPUNIT_TEST(test_quickExp_3);
    CPPUNIT_TEST(test_dummy1);
    CPPUNIT_TEST(test_dummy2);
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
