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

#define private public
#define class struct
#include "Integer.h"
#undef private
#undef class

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
        int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 5);
        CPPUNIT_ASSERT(std::equal(x, p, b));
    }
    void test_shift_left_digits_zero () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        int* p = shift_left_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 3);
        CPPUNIT_ASSERT(std::equal(x, p, b));
    }
    void test_shift_left_digits_empty () {
        const int a[] = {0};
        const int b[] = {0, 0, 0};
              int x[10];
        int* p = shift_left_digits(a, a + 1, 2, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 3);
        CPPUNIT_ASSERT(std::equal(x, p, b));
    }

    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }
    void test_shift_right_digits_zero () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }
    void test_shift_right_digits_all () {
        const int a[] = {2, 3, 4};
              int x[10];
        int* p = shift_right_digits(a, a + 3, 3, x);
        CPPUNIT_ASSERT_EQUAL(p, &x[0]);
    }

    // -----------
    // plus_digits
    // -----------

    void test_plus_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT_EQUAL(3, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_plus_digits_carry_over () {
        const int a[] = {2, 3, 4};
        const int b[] = {8, 6, 7};
        const int c[] = {1, 1, 0, 1};
              int x[10];
        int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT_EQUAL(4, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_plus_digits_zero () {
        const int a[] = {2, 3, 4};
        const int b[] = {0};
        const int c[] = {2, 3, 4};
              int x[10];
        int* p = plus_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT_EQUAL(3, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_plus_digits_different_length () {
        const int a[] = {2, 3, 4};
        const int b[] = {6, 7};
        const int c[] = {3, 0, 1};
              int x[10];
        int* p = plus_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT_EQUAL(3, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }

    // ------------
    // minus_digits
    // ------------

    void test_minus_digits () {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 3);
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_minus_digits_different_length () {
        const int a[] = {8, 0, 1};
        const int b[] = {6, 7};
        const int c[] = {7, 3, 4};
              int x[10];
        int* p = minus_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 3);
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_minus_digits_long_borrow () {
        const int a[] = {8, 0, 0, 1};
        const int b[] = {5, 4, 6};
        const int c[] = {7, 4, 5, 5};
              int x[10];
        int* p = minus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 4);
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_minus_digits_zero () {
        const int a[] = {8, 0, 1};
        const int b[] = {0};
        const int c[] = {8, 0, 1};
              int x[10];
        int* p = minus_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT_EQUAL((int)(p - x), 3);
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT_EQUAL(6, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_multiplies_digits_different_length () {
        const int a[] = {2, 3, 4};
        const int b[] = {6, 7};
        const int c[] = {1, 5, 6, 7, 8};
              int x[10];
        int* p = multiplies_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT_EQUAL(5, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_multiplies_digits_zero () {
        const int a[] = {2, 3, 4};
        const int b[] = {0};
        const int c[] = {0};
              int x[10];
        int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT_EQUAL(1, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_multiplies_digits_long () {
        const int a[] = {2, 3, 4};
        const int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        const int c[] = {2, 8, 8, 8, 8, 8, 8, 8, 6, 2, 6};
              int x[11];
        int* p = multiplies_digits(a, a + 3, b, b + 9, x);
        CPPUNIT_ASSERT_EQUAL(11, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT_EQUAL(3, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }
    void test_divides_digits_larger_divisor () {
        const int a[] = {5, 6, 7};
        const int b[] = {1, 3, 2, 6, 7, 8};
        const int c[] = {0};
              int x[10];
        int* p = divides_digits(a, a + 3, b, b + 6, x);
        CPPUNIT_ASSERT_EQUAL(1, (int)(p - x));
        CPPUNIT_ASSERT(std::equal(x, p, c));
    }

    // -----------
    // constructor
    // -----------

    void test_constructor_string_valid () {
        try {
            const Integer<int> x("2");
            CPPUNIT_ASSERT_EQUAL(Integer<int>(2), x);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_constructor_string_valid_negative () {
        try {
            const Integer<int> x("-10");
            CPPUNIT_ASSERT_EQUAL(Integer<int>(-10), x);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_constructor_string_invalid () {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_constructor_string_invalid_negative () {
        try {
            const Integer<int> x("-abc");
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_constructor_string_invalid_empty () {
        try {
            const Integer<int> x("");
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_constructor_string_invalid_negative_zero () {
        try {
            const Integer<int> x("-0");
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_constructor_string_invalid_malformed () {
        try {
            const Integer<int> x("-");
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }

    void test_constructor_int () {
        try {
            const Integer<int> x(2);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_constructor_int_multiple_digits () {
        try {
            const Integer<int> x(234);
            CPPUNIT_ASSERT_EQUAL(2, x.digits[0]);
            CPPUNIT_ASSERT_EQUAL(3, x.digits[1]);
            CPPUNIT_ASSERT_EQUAL(4, x.digits[2]);
            CPPUNIT_ASSERT_EQUAL(false, x.is_negative);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_constructor_int_negative () {
        try {
            const Integer<int> x(-102);
            CPPUNIT_ASSERT(x.is_negative);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_constructor_int_zero () {
        try {
            const Integer<int> x(0);
            CPPUNIT_ASSERT_EQUAL(1, (int)x.digits.size());
            CPPUNIT_ASSERT_EQUAL(0, x.digits[0]);
        } catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    // ---
    // abs
    // ---

    void test_abs_negative () {
        try {
            Integer<int> x = -98765;
            x.abs();
            CPPUNIT_ASSERT(x == 98765);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_abs_positive () {
        try {
            Integer<int> x = 98765;
            x.abs();
            CPPUNIT_ASSERT(x == 98765);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_abs_zero () {
        try {
            Integer<int> x = 0;
            x.abs();
            CPPUNIT_ASSERT(x == 0);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }

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
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }

    // --------
    // negation
    // --------

    void test_negation_positive () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_negation_negative () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == 98765);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_negation_zero () {
        const Integer<int> x = 0;
        const Integer<int> y = -x;
        CPPUNIT_ASSERT(y == 0);
    }

    // ------
    // output
    // ------

    void test_output () {
        const Integer<int> x = 98765;
        std::ostringstream out;
        out << x;
        CPPUNIT_ASSERT(out.str() == "98765");
    }
    void test_output_negative () {
        const Integer<int> x = -98765;
        std::ostringstream out;
        out << x;
        CPPUNIT_ASSERT(out.str() == "-98765");
    }
    void test_output_zero () {
        const Integer<int> x = 0;
        std::ostringstream out;
        out << x;
        CPPUNIT_ASSERT(out.str() == "0");
    }

    void test_plus_equals_positive () {
        Integer<int> x = 10;
        Integer<int> y = 20;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(30), x);
    }
    void test_plus_equals_negative_1 () {
        Integer<int> x = -10;
        Integer<int> y = 35;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(25), x);
    }
    void test_plus_equals_negative_2 () {
        Integer<int> x = -50;
        Integer<int> y = 100;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(50), x);
    }
    void test_plus_equals_negative_3 () {
        Integer<int> x = -20;
        Integer<int> y = 5;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(-15), x);
    }
    void test_plus_equals_negative_4 () {
        Integer<int> x = 20;
        Integer<int> y = -20;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(0), x);
    }
    void test_plus_equals_negative_rhs_1 () {
        Integer<int> x = 100;
        Integer<int> y = -50;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(50), x);
    }
    void test_plus_equals_negative_rhs_2 () {
        Integer<int> x = 5;
        Integer<int> y = -20;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(-15), x);
    }
    void test_plus_equals_negative_rhs_3 () {
        Integer<int> x = 20;
        Integer<int> y = -20;
        x += y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(0), x);
    }

    void test_times_equals_positive () {
        Integer<int> x = 10;
        Integer<int> y = 20;
        x *= y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(200), x);
    }
    void test_times_equals_negative () {
        Integer<int> x = 10;
        Integer<int> y = -5;
        x *= y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(-50), x);
    }
    void test_times_equals_both_negative () {
        Integer<int> x = -6;
        Integer<int> y = -5;
        x *= y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(30), x);
    }
    void test_times_equals_zero () {
        Integer<int> x = -6;
        Integer<int> y = 0;
        x *= y;
        CPPUNIT_ASSERT_EQUAL(Integer<int>(0), x);
    }

    // ---
    // pow
    // ---

    void test_pow_simple () {
        try {
            Integer<int> x = 5;
            x.pow(3);
            CPPUNIT_ASSERT(x == 125);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_pow_large () {
        try {
            Integer<int> x = 123;
            x.pow(4);
            CPPUNIT_ASSERT(x == 228886641);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_pow_zero () {
        try {
            Integer<int> x = 0;
            x.pow(4);
            CPPUNIT_ASSERT(x == 0);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_pow_zero_exponent () {
        try {
            Integer<int> x = 10;
            x.pow(0);
            CPPUNIT_ASSERT(x == 1);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_pow_negative_zero_exponent () {
        try {
            Integer<int> x = -123;
            x.pow(0);
            CPPUNIT_ASSERT(x == 1);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
        }
    }
    void test_pow_exceptions () {
        try {
            Integer<int> x = 100;
            x.pow(-1);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
        try {
            Integer<int> x = 0;
            x.pow(0);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }

    void test_equality_operator_same () {
        const Integer<int> x = 100;
        // const Integer<int> y = 100;
        // CPPUNIT_ASSERT(x == y);
    }
    void test_equality_operator_different () {
        const Integer<int> x = 100;
        const Integer<int> y = 101;
        CPPUNIT_ASSERT(x != y);
    }
    void test_equality_operator_different_sign_only () {
        const Integer<int> x = 100;
        const Integer<int> y = -100;
        CPPUNIT_ASSERT(x != y);
    }

    void test_less_than_positives_yes () {
        const Integer<int> x = 100;
        const Integer<int> y = 200;
        CPPUNIT_ASSERT_EQUAL(true, x < y);
    }
    void test_less_than_positives_no () {
        const Integer<int> x = 200;
        const Integer<int> y = 100;
        CPPUNIT_ASSERT_EQUAL(false, x < y);
    }
    void test_less_than_positives_equal () {
        const Integer<int> x = 100;
        const Integer<int> y = 100;
        CPPUNIT_ASSERT_EQUAL(false, x < y);
    }
    void test_less_than_negatives_yes () {
        const Integer<int> x = -200;
        const Integer<int> y = -100;
        CPPUNIT_ASSERT_EQUAL(true, x < y);
    }
    void test_less_than_negatives_no () {
        const Integer<int> x = -100;
        const Integer<int> y = -200;
        CPPUNIT_ASSERT_EQUAL(false, x < y);
    }
    void test_less_than_negatives_equal () {
        const Integer<int> x = -100;
        const Integer<int> y = -100;
        CPPUNIT_ASSERT_EQUAL(false, x < y);
    }
    void test_less_than_mixed_yes () {
        const Integer<int> x = -1;
        const Integer<int> y = 100;
        CPPUNIT_ASSERT_EQUAL(true, x < y);
    }
    void test_less_than_mixed_no () {
        const Integer<int> x = 100;
        const Integer<int> y = -1;
        CPPUNIT_ASSERT_EQUAL(false, x < y);
    }

    void test_shift_equals_left () {
        Integer<int> x = 5;
        Integer<int> y = 50;
        x <<= 1;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_left_zero_1 () {
        Integer<int> x = 5;
        Integer<int> y = 5;
        x <<= 0;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_left_zero_2 () {
        Integer<int> x = 0;
        Integer<int> y = 0;
        x <<= 0;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_left_negative () {
        Integer<int> x = -5;
        Integer<int> y = -50;
        x <<= 1;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_left_exceptions () {
        try {
            Integer<int> x = 100;
            x <<= -1;
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_shift_equals_right () {
        Integer<int> x = 50;
        Integer<int> y = 5;
        x >>= 1;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_right_zero () {
        Integer<int> x = 5;
        Integer<int> y = 5;
        x >>= 0;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_right_negative () {
        Integer<int> x = -50;
        Integer<int> y = -5;
        x >>= 1;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_right_all () {
        Integer<int> x = 5;
        Integer<int> y = 0;
        x >>= 1;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_shift_equals_right_exceptions () {
        try {
            Integer<int> x = 100;
            x >>= -1;
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }

    void test_divide_equals_exceptions () {
        try {
            Integer<int> x = 100;
            x /= 0;
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_divide_equals_positive () {
        Integer<int> x = 100;
        Integer<int> y = 20;
        x /= 5;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_divide_equals_large_divisor () {
        Integer<int> x = 100;
        Integer<int> y = 0;
        x /= 1000;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_divide_equals_negative () {
        Integer<int> x = -35;
        Integer<int> y = -5;
        x /= 7;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_divide_equals_negative_large_divisor () {
        Integer<int> x = -100;
        Integer<int> y = 0;
        x /= 1000;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }

    void test_mod_equals_exceptions () {
        try {
            Integer<int> x = 100;
            x %= 0;
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
        try {
            Integer<int> x = 100;
            x %= -1;
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));
        }
    }
    void test_mod_equals () {
        Integer<int> x = 8;
        Integer<int> y = 3;
        x %= 5;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }
    void test_mod_equals_zero () {
        Integer<int> x = 0;
        Integer<int> y = 0;
        x %= 1000;
        CPPUNIT_ASSERT_EQUAL(y, x);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits);
    CPPUNIT_TEST(test_shift_left_digits_zero);
    CPPUNIT_TEST(test_shift_left_digits_empty);
    CPPUNIT_TEST(test_shift_right_digits);
    CPPUNIT_TEST(test_shift_right_digits_zero);
    CPPUNIT_TEST(test_shift_right_digits_all);
    CPPUNIT_TEST(test_plus_digits);
    CPPUNIT_TEST(test_plus_digits_carry_over);
    CPPUNIT_TEST(test_plus_digits_different_length);
    CPPUNIT_TEST(test_plus_digits_zero);
    CPPUNIT_TEST(test_minus_digits);
    CPPUNIT_TEST(test_minus_digits_different_length);
    CPPUNIT_TEST(test_minus_digits_zero);
    CPPUNIT_TEST(test_minus_digits_long_borrow);
    CPPUNIT_TEST(test_constructor_int);
    CPPUNIT_TEST(test_constructor_int_multiple_digits);
    CPPUNIT_TEST(test_constructor_int_negative);
    CPPUNIT_TEST(test_constructor_int_zero);
    CPPUNIT_TEST(test_constructor_string_valid);
    CPPUNIT_TEST(test_constructor_string_valid_negative);
    CPPUNIT_TEST(test_constructor_string_invalid);
    CPPUNIT_TEST(test_constructor_string_invalid_empty);
    CPPUNIT_TEST(test_constructor_string_invalid_negative);
    CPPUNIT_TEST(test_constructor_string_invalid_negative_zero);
    CPPUNIT_TEST(test_constructor_string_invalid_malformed);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_output_negative);
    CPPUNIT_TEST(test_output_zero);
    CPPUNIT_TEST(test_equality_operator_same);
    CPPUNIT_TEST(test_equality_operator_different);
    CPPUNIT_TEST(test_equality_operator_different_sign_only);
    CPPUNIT_TEST(test_abs_positive);
    CPPUNIT_TEST(test_abs_negative);
    CPPUNIT_TEST(test_abs_zero);
    CPPUNIT_TEST(test_negation_positive);
    CPPUNIT_TEST(test_negation_negative);
    CPPUNIT_TEST(test_negation_zero);
    CPPUNIT_TEST(test_less_than_positives_yes);
    CPPUNIT_TEST(test_less_than_positives_no);
    CPPUNIT_TEST(test_less_than_positives_equal);
    CPPUNIT_TEST(test_less_than_negatives_yes);
    CPPUNIT_TEST(test_less_than_negatives_no);
    CPPUNIT_TEST(test_less_than_negatives_equal);
    CPPUNIT_TEST(test_less_than_mixed_yes);
    CPPUNIT_TEST(test_less_than_mixed_no);
    CPPUNIT_TEST(test_plus_equals_positive);
    CPPUNIT_TEST(test_plus_equals_negative_1);
    CPPUNIT_TEST(test_plus_equals_negative_2);
    CPPUNIT_TEST(test_plus_equals_negative_3);
    CPPUNIT_TEST(test_plus_equals_negative_4);
    CPPUNIT_TEST(test_plus_equals_negative_rhs_1);
    CPPUNIT_TEST(test_plus_equals_negative_rhs_2);
    CPPUNIT_TEST(test_plus_equals_negative_rhs_3);
    CPPUNIT_TEST(test_multiplies_digits);
    CPPUNIT_TEST(test_multiplies_digits_zero);
    CPPUNIT_TEST(test_multiplies_digits_different_length);
    CPPUNIT_TEST(test_multiplies_digits_long);
    CPPUNIT_TEST(test_times_equals_positive);
    CPPUNIT_TEST(test_times_equals_zero);
    CPPUNIT_TEST(test_times_equals_negative);
    CPPUNIT_TEST(test_times_equals_both_negative);
    CPPUNIT_TEST(test_shift_equals_left);
    CPPUNIT_TEST(test_shift_equals_left_zero_1);
    CPPUNIT_TEST(test_shift_equals_left_zero_2);
    CPPUNIT_TEST(test_shift_equals_left_negative);
    CPPUNIT_TEST(test_shift_equals_left_exceptions);
    CPPUNIT_TEST(test_shift_equals_right);
    CPPUNIT_TEST(test_shift_equals_right_zero);
    CPPUNIT_TEST(test_shift_equals_right_negative);
    CPPUNIT_TEST(test_shift_equals_right_all);
    CPPUNIT_TEST(test_shift_equals_right_exceptions);
    CPPUNIT_TEST(test_divides_digits);
    CPPUNIT_TEST(test_divides_digits_larger_divisor);
    CPPUNIT_TEST(test_divide_equals_positive);
    CPPUNIT_TEST(test_divide_equals_negative);
    CPPUNIT_TEST(test_divide_equals_negative_large_divisor);
    CPPUNIT_TEST(test_divide_equals_large_divisor);
    CPPUNIT_TEST(test_divide_equals_exceptions);
    CPPUNIT_TEST(test_mod_equals);
    CPPUNIT_TEST(test_mod_equals_zero);
    CPPUNIT_TEST(test_mod_equals_exceptions);
    CPPUNIT_TEST(test_pow_simple);
    CPPUNIT_TEST(test_pow_large);
    CPPUNIT_TEST(test_pow_zero);
    CPPUNIT_TEST(test_pow_zero_exponent);
    CPPUNIT_TEST(test_pow_negative_zero_exponent);
    CPPUNIT_TEST(test_pow_exceptions);
    CPPUNIT_TEST_SUITE_END();
};

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
    return 0;
}
