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
#include <vector>
#include <deque>

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
    // -----------------
    // shift_left_digits
    // -----------------

	/* 
	 * My version of this algorithm doesn't do anything useful because
	 * my internal digit container has to grow to accomodate a left shift,
	 * and in so doing, the left shift is accomplished. Nevertheless, I
	 * wrote the algorithm as it would be if the input and output were
	 * different containers. The unit tests are a bit silly, though.
	 */
    void test_shift_left_digits_1() {
        const int a[] = {0, 0, 4, 3, 2};
        const int b[] = {0, 0, 4, 3, 2};
              int x[10];
        const int* p = shift_left_digits(a, a + 5, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

    void test_shift_left_digits_2() {
        const int a[] = {0, 7};
        const int b[] = {0, 7};
              int x[10];
        const int* p = shift_left_digits(a, a + 2, 1, x);
        CPPUNIT_ASSERT((p - x) == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

    void test_shift_left_digits_3() {
        const int a[] = {0, 0, 0, 0, 0, 8};
        const int b[] = {0, 0, 0, 0, 0, 8};
              int x[10];
        const int* p = shift_left_digits(a, a + 6, 5, x);
        CPPUNIT_ASSERT((p - x) == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits_1() {
        const int a[] = {4, 3, 2};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

    void test_shift_right_digits_2() {
        const int a[] = {9, 8};
        const int b[] = {8};
              int x[10];
        const int* p = shift_right_digits(a, a + 2, 1, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

    void test_shift_right_digits_3() {
        const int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        const int b[] = {8, 7, 6, 5, 4, 3, 2, 1};
              int x[10];
        const int* p = shift_right_digits(a, a + 9, 1, x);
        CPPUNIT_ASSERT((p - x) == 8);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

    // -----------
    // plus_digits
    // -----------

    void test_plus_digits_1() {
        const int a[] = {4, 3, 2};
        const int b[] = {7, 6, 5};
        const int c[] = {1, 0, 8};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_plus_digits_2() {
        const int a[] = {2, 3, 4};
        const int b[] = {0};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_plus_digits_3() {
        const int a[] = {0, 0, 0, 1};
        const int b[] = {0, 0, 0, 9};
        const int c[] = {0, 0, 0, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_plus_digits_4() {
        const int a[] = {4, 3, 2, 1};
        const int b[] = {5, 4, 3, 2};
        const int c[] = {9, 7, 5, 3};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_plus_digits_5() {
        const int a[] = {1, 9, 2, 9};
        const int b[] = {5, 4, 8, 2};
        const int c[] = {6, 3, 1, 2, 1};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_plus_digits_6() {
        const int a[] = {1, 9, 2, 9, 0, 0, 0, 0};
        const int b[] = {5, 4, 8, 2};
        const int c[] = {6, 3, 1, 2, 1, 0, 0, 0};
              int x[10];
        const int* p = plus_digits(a, a + 8, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 8);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    // ------------
    // minus_digits
    // ------------

    void test_minus_digits_1() {
        const int a[] = {1, 0, 8};
        const int b[] = {7, 6, 5};
        const int c[] = {4, 3, 2};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_minus_digits_2() {
        const int a[] = {0, 0, 1};
        const int b[] = {1};
        const int c[] = {9, 9, 0};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_minus_digits_3() {
        const int a[] = {5, 6, 7, 8};
        const int b[] = {1, 2, 3, 3};
        const int c[] = {4, 4, 4, 5};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_minus_digits_4() {
        const int a[] = {9, 8, 1, 0, 0, 1};
        const int b[] = {9, 9, 9, 9, 9};
        const int c[] = {0, 9, 1, 0, 0, 0};
              int x[10];
        const int* p = minus_digits(a, a + 6, b, b + 5, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_minus_digits_5() {
        const int a[] = {1, 3, 2, 6};
        const int b[] = {4, 8, 7};
        const int c[] = {7, 4, 4, 5};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_minus_digits_6() {
        const int a[] = {9, 2, 1, 8};
        const int b[] = {0};
        const int c[] = {9, 2, 1, 8};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_minus_digits_7() {
        const int a[] = {1, 0, 8};
        const int b[] = {7, 6, 5};
        const int c[] = {4, 3, 2};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// --------------------
	// strip_trailing_zeros
	// --------------------
	
	void test_strip_trailing_zeros_1() {
		vector<int> a;
		a.push_back(1);
		a.push_back(2);
		a.push_back(3);
		strip_trailing_zeros(a);
		CPPUNIT_ASSERT(a.size() == 3);
		CPPUNIT_ASSERT(a[0] == 1);
		CPPUNIT_ASSERT(a[1] == 2);
		CPPUNIT_ASSERT(a[2] == 3);
	}

	void test_strip_trailing_zeros_2() {
		vector<int> a;
		a.push_back(1);
		a.push_back(2);
		a.push_back(0);
		strip_trailing_zeros(a);
		CPPUNIT_ASSERT(a.size() == 2);
		CPPUNIT_ASSERT(a[0] == 1);
		CPPUNIT_ASSERT(a[1] == 2);
	}

	void test_strip_trailing_zeros_3() {
		vector<int> a;
		a.push_back(1);
		a.push_back(2);
		a.push_back(0);
		a.push_back(0);
		a.push_back(0);
		strip_trailing_zeros(a);
		CPPUNIT_ASSERT(a.size() == 2);
		CPPUNIT_ASSERT(a[0] == 1);
		CPPUNIT_ASSERT(a[1] == 2);
	}

	void test_strip_trailing_zeros_4() {
		vector<int> a;
		a.push_back(0);
		strip_trailing_zeros(a);
		CPPUNIT_ASSERT(a.size() == 1);
		CPPUNIT_ASSERT(a[0] == 0);
	}

	void test_strip_trailing_zeros_5() {
		vector<int> a;
		a.push_back(0);
		a.push_back(0);
		a.push_back(0);
		a.push_back(0);
		a.push_back(0);
		strip_trailing_zeros(a);
		CPPUNIT_ASSERT(a.size() == 1);
		CPPUNIT_ASSERT(a[0] == 0);
	}

	void test_strip_trailing_zeros_6() {
		vector<int> a;
		a.push_back(0);
		a.push_back(0);
		a.push_back(8);
		a.push_back(8);
		a.push_back(9);
		strip_trailing_zeros(a);
		CPPUNIT_ASSERT(a.size() == 5);
		CPPUNIT_ASSERT(a[0] == 0);
		CPPUNIT_ASSERT(a[1] == 0);
		CPPUNIT_ASSERT(a[2] == 8);
		CPPUNIT_ASSERT(a[3] == 8);
		CPPUNIT_ASSERT(a[4] == 9);
	}

	// -------------
	// mult_by_digit
	// -------------
	
	void test_mult_by_digit_1() {
        const int a[] = {4, 3, 2};
        const int b   =  2;
        const int c[] = {8, 6, 4};
              int x[10];
        const int* p = mult_by_digit(a, a + 3, b, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_mult_by_digit_2() {
        const int a[] = {4, 3, 2, 1};
        const int b   =  9;
        const int c[] = {6, 0, 1, 1, 1};
              int x[10];
        const int* p = mult_by_digit(a, a + 4, b, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_mult_by_digit_3() {
        const int a[] = {1};
        const int b   =  1;
        const int c[] = {1};
              int x[10];
        const int* p = mult_by_digit(a, a + 1, b, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_mult_by_digit_4() {
        const int a[] = {5};
        const int b   =  5;
        const int c[] = {5, 2};
              int x[10];
        const int* p = mult_by_digit(a, a + 1, b, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_mult_by_digit_5() {
        const int a[] = {9, 9, 9, 9};
        const int b   =  9;
        const int c[] = {1, 9, 9, 9, 8};
              int x[10];
        const int* p = mult_by_digit(a, a + 4, b, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_mult_by_digit_6() {
        const int a[] = {9, 9, 9, 9};
        const int b   =  1;
        const int c[] = {9, 9, 9, 9};
              int x[10];
        const int* p = mult_by_digit(a, a + 4, b, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits_0() {
        const int a[] = {1, 2};
        const int b[] = {4, 3};
        const int c[] = {4, 1, 7};
              int x[10];
        const int* p = multiplies_digits(a, a + 2, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_1() {
        const int a[] = {4, 3, 2};
        const int b[] = {7, 6, 5};
        const int c[] = {8, 7, 6, 2, 3, 1};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_2() {
        const int a[] = {4, 3, 2, 1};
        const int b[] = {2};
        const int c[] = {8, 6, 4, 2};
              int x[10];
        const int* p = multiplies_digits(a, a + 4, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_3() {
        const int a[] = {2, 1, 8, 9};
        const int b[] = {1};
        const int c[] = {2, 1, 8, 9};
              int x[10];
        const int* p = multiplies_digits(a, a + 4, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_4() {
        const int a[] = {1};
        const int b[] = {1};
        const int c[] = {1};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_5() {
        const int a[] = {5, 5};
        const int b[] = {5, 5};
        const int c[] = {5, 2, 0, 3};
              int x[10];
        const int* p = multiplies_digits(a, a + 2, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_6() {
        const int a[] = {4, 3, 2, 1};
        const int b[] = {8, 7, 6, 5};
        const int c[] = {2, 5, 6, 6, 0, 0, 7};
              int x[10];
        const int* p = multiplies_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 7);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_7() {
        const int a[] = {4, 2, 6, 5};
        const int b[] = {0, 0, 1};
        const int c[] = {0, 0, 4, 2, 6, 5};
              int x[10];
        const int* p = multiplies_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_multiplies_digits_8() {
        const int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        const int b[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
		const int c[] = {1,2,5,0,9,1,0,5,7,8,7,5,1,4,2,5,1};
              int x[20];
        const int* p = multiplies_digits(a, a + 9, b, b + 9, x);
        CPPUNIT_ASSERT(p - x == 17);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// -------------------
	// dig_less_than_eq_to
	// -------------------

	void test_dig_less_than_eq_to_1() {
		const int a[] = {2, 2};
		const int b[] = {2, 2};
		const bool c = dig_less_than_eq_to(a, a + 2, b, b + 2);
		CPPUNIT_ASSERT(c == true);
	}

	void test_dig_less_than_eq_to_2() {
		const int a[] = {3, 2};
		const int b[] = {4, 2};
		const bool c = dig_less_than_eq_to(a, a + 2, b, b + 2);
		CPPUNIT_ASSERT(c == true);
	}

	void test_dig_less_than_eq_to_3() {
		const int a[] = {0, 0, 2};
		const int b[] = {0, 0, 0, 2};
		const bool c = dig_less_than_eq_to(a, a + 3, b, b + 4);
		CPPUNIT_ASSERT(c == true);
	}

	void test_dig_less_than_eq_to_4() {
		const int a[] = {0, 0, 0, 2};
		const int b[] = {0, 0, 2};
		const bool c = dig_less_than_eq_to(a, a + 4, b, b + 3);
		CPPUNIT_ASSERT(c == false);
	}

	void test_dig_less_than_eq_to_5() {
		const int a[] = {4, 3, 2, 1};
		const int b[] = {9, 8, 7};
		const bool c = dig_less_than_eq_to(a, a + 4, b, b + 3);
		CPPUNIT_ASSERT(c == false);
	}

	void test_dig_less_than_eq_to_6() {
		const int a[] = {5, 4, 3, 2};
		const int b[] = {5, 4, 3, 3};
		const bool c = dig_less_than_eq_to(a, a + 4, b, b + 4);
		CPPUNIT_ASSERT(c == true);
	}

	void test_dig_less_than_eq_to_7() {
		const int a[] = {7, 6, 5, 4};
		const int b[] = {8, 6, 5, 4};
		const bool c = dig_less_than_eq_to(a, a + 4, b, b + 4);
		CPPUNIT_ASSERT(c == true);
	}

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits_1() {
        const int a[] = {8, 7, 6, 2, 3, 1};
        const int b[] = {7, 6, 5};
        const int c[] = {4, 3, 2, 0, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_2() {
        const int a[] = {9, 1, 8, 0, 8, 5};
        const int b[] = {3, 2, 1};
        const int c[] = {2, 2, 7, 4, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_3() {
        const int a[] = {0, 0, 0, 0, 0, 1};
        const int b[] = {3, 2, 1};
        const int c[] = {3, 1, 8, 0, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_4() {
        const int a[] = {0, 0, 1};
        const int b[] = {0, 0, 1};
        const int c[] = {1, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_5() {
        const int a[] = {0, 0, 1};
        const int b[] = {9, 9};
        const int c[] = {1, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_6() {
        const int a[] = {6, 6, 6};
        const int b[] = {2, 7, 3};
        const int c[] = {1, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_7() {
        const int a[] = {8, 8, 8, 8, 8};
        const int b[] = {1, 1, 1, 1, 1};
        const int c[] = {8, 0, 0, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 5, b, b + 5, x);
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_8() {
        const int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        const int b[] = {3, 1, 2, 4, 8};
        const int c[] = {8, 2, 7, 1, 1, 0, 0, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 9, b, b + 5, x);
        CPPUNIT_ASSERT(p - x == 9);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_9() {
        const int a[] = {0, 0, 0, 1};
        const int b[] = {1, 0, 1};
        const int c[] = {9, 0, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// leaves two zeros in front of dividend after first subtraction
    void test_divides_digits_10() {
		const int a[] = {5, 0, 0, 9};
        const int b[] = {0, 0, 1};
        const int c[] = {0, 9, 0, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

    void test_divides_digits_11() {
		const int a[] = {0, 0, 5};
        const int b[] = {5, 2};
        const int c[] = {0, 2, 0};
              int x[10] = {0};
        const int* p = divides_digits(a, a + 3, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// --------------
	// grow_container
	// --------------
	
	void test_grow_container_1() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 5;
		deque<int>::size_type s = grow_container(a, n, 'a');
		CPPUNIT_ASSERT(s == 11);
		CPPUNIT_ASSERT(a.size() == s);
		CPPUNIT_ASSERT(a.back() == 0);
	}

	void test_grow_container_2() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 15;
		deque<int>::size_type s = grow_container(a, n, 'a');
		CPPUNIT_ASSERT(s == 16);
		CPPUNIT_ASSERT(a.size() == s);
		for (int i = 0; i < 6; ++i)
			CPPUNIT_ASSERT(a[a.size() - (1 + i)] == 0);
		CPPUNIT_ASSERT(a[a.size() - (1 + 6)] != 0);
	}

	void test_grow_container_3() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 10;
		deque<int>::size_type s = grow_container(a, n, 'a');
		CPPUNIT_ASSERT(s == 11);
		CPPUNIT_ASSERT(a.size() == s);
		CPPUNIT_ASSERT(a.back() == 0);
		CPPUNIT_ASSERT(a[a.size() - 2] != 0);
	}

	void test_grow_container_4() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 3;
		deque<int>::size_type s = grow_container(a, n, 'm');
		CPPUNIT_ASSERT(s == 13);
		CPPUNIT_ASSERT(a.size() == s);
		CPPUNIT_ASSERT(a.back() == 0);
	}

	void test_grow_container_5() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 20;
		deque<int>::size_type s = grow_container(a, n, 'm');
		CPPUNIT_ASSERT(s == 30);
		CPPUNIT_ASSERT(a.size() == s);
		CPPUNIT_ASSERT(a.back() == 0);
	}

	void test_grow_container_6() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 10;
		deque<int>::size_type s = grow_container(a, n, 'm');
		CPPUNIT_ASSERT(s == 20);
		CPPUNIT_ASSERT(a.size() == s);
		CPPUNIT_ASSERT(a.back() == 0);
	}

	void test_grow_container_7() {
		deque<int> a;
		for (int i = 0; i < 10; ++i)
			a.push_back(i);
		deque<int>::size_type n = 1;
		deque<int>::size_type s = grow_container(a, n, 'm');
		CPPUNIT_ASSERT(s == 11);
		CPPUNIT_ASSERT(a.size() == s);
		CPPUNIT_ASSERT(a.back() == 0);
	}

	// --------------
	// operator_equal
	// --------------
	
	void test_operator_equal_1() {
		try {
			const Integer<int> x("1234567891011121314151617181920");
			const Integer<int> y("1234567891011121314151617181920");
			CPPUNIT_ASSERT(x == y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_2() {
		try {
			const Integer<int> x(123);
			const Integer<int> y(-123);
			CPPUNIT_ASSERT(!(x == y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_3() {
		try {
			const Integer<int> x("0");
			const Integer<int> y("0");
			CPPUNIT_ASSERT(x == y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_4() {
		try {
			const Integer<int> x("0");
			const Integer<int> y("-000");
			CPPUNIT_ASSERT(x == y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_5() {
		try {
			const Integer<int> x("1");
			const Integer<int> y("1");
			CPPUNIT_ASSERT(x == y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_6() {
		try {
			const Integer<int> x("-98765");
			const Integer<int> y("-98765");
			CPPUNIT_ASSERT(x == y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_7() {
		try {
			const Integer<int> x("1234");
			const Integer<int> y("123");
			CPPUNIT_ASSERT(!(x == y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_equal_8() {
		try {
			const Integer<int> x("123");
			const Integer<int> y("1234");
			CPPUNIT_ASSERT(!(x == y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

    void test_operator_equal_9() {
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

	// ------------------
	// operator_not_equal
	// ------------------
	
	void test_operator_not_equal_1() {
		try {
			const Integer<int> x( "234567891011121314151617181920");
			const Integer<int> y("1234567891011121314151617181920");
			CPPUNIT_ASSERT(x != y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_not_equal_2() {
		try {
			const Integer<int> x(123);
			const Integer<int> y(-123);
			CPPUNIT_ASSERT(x != y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_not_equal_3() {
		try {
			const Integer<int> x("0");
			const Integer<int> y("0");
			CPPUNIT_ASSERT(!(x != y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_not_equal_4() {
		try {
			const Integer<int> x("1234567891011121314151617181920");
			const Integer<int> y("234567891011121314151617181920");
			CPPUNIT_ASSERT(x != y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_not_equal_5() {
		try {
			const Integer<int> x("123456789101112131415161718192");
			const Integer<int> y("1234567891011121314151617181920");
			CPPUNIT_ASSERT(x != y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_not_equal_6() {
		try {
			const Integer<int> x("1234567891011121314151617181920");
			const Integer<int> y("123456789101112131415161718192");
			CPPUNIT_ASSERT(x != y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	// ------------------
	// operator_less_than
	// ------------------
	
	void test_operator_less_than_1() {
		try {
			const Integer<int> x("1234");
			const Integer<int> y("234");
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_2() {
		try {
			const Integer<int> x("234");
			const Integer<int> y("1234");
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_3() {
		try {
			const Integer<int> x("4321");
			const Integer<int> y("4255");
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_4() {
		try {
			const Integer<int> x("-1235");
			const Integer<int> y("1234");
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_5() {
		try {
			const Integer<int> x("0");
			const Integer<int> y("0");
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_6() {
		try {
			const Integer<int> x("-55");
			const Integer<int> y("600000");
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_7() {
		try {
			const Integer<int> x(-55);
			const Integer<int> y(600000);
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_8() {
		try {
			const Integer<int> x(0);
			const Integer<int> y(-1);
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_9() {
		try {
			const Integer<int> x(-1234);
			const Integer<int> y(234);
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_10() {
		try {
			const Integer<int> x(-234);
			const Integer<int> y(1234);
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_11() {
		try {
			const Integer<int> x(556677);
			const Integer<int> y(556677);
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_12() {
		try {
			const Integer<int> x(556677);
			const Integer<int> y(-556677);
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_13() {
		try {
			const Integer<int> x(0);
			const Integer<int> y(100);
			CPPUNIT_ASSERT(x < y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_14() {
		try {
			const Integer<int> x(0);
			const Integer<int> y(-100);
			CPPUNIT_ASSERT(!(x < y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// ---------------------------
	// operator_less_than_or_equal
	// ---------------------------
	
	void test_operator_less_than_or_equal_1() {
		try {
			const Integer<int> x(0);
			const Integer<int> y(0);
			CPPUNIT_ASSERT(x <= y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_or_equal_2() {
		try {
			const Integer<int> x(100);
			const Integer<int> y("-200");
			CPPUNIT_ASSERT(!(x <= y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_less_than_or_equal_3() {
		try {
			const Integer<int> x(-5050);
			const Integer<int> y(5050);
			CPPUNIT_ASSERT(x <= y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// ---------------------
	// operator_greater_than
	// ---------------------
	
	void test_operator_greater_than_1() {
		try {
			const Integer<int> x("1234");
			const Integer<int> y("234");
			CPPUNIT_ASSERT(x > y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_greater_than_2() {
		try {
			const Integer<int> x("-234");
			const Integer<int> y("-235");
			CPPUNIT_ASSERT(x > y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_greater_than_3() {
		try {
			const Integer<int> x("4321");
			const Integer<int> y("4255");
			CPPUNIT_ASSERT(x > y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// ------------------------------
	// operator_greater_than_or_equal
	// ------------------------------
	
	void test_operator_greater_than_or_equal_1() {
		try {
			const Integer<int> x(0);
			const Integer<int> y(0);
			CPPUNIT_ASSERT(x >= y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_greater_than_or_equal_2() {
		try {
			const Integer<int> x(100);
			const Integer<int> y("-200");
			CPPUNIT_ASSERT(x >= y);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_operator_greater_than_or_equal_3() {
		try {
			const Integer<int> x(-5050);
			const Integer<int> y(5050);
			CPPUNIT_ASSERT(!(x >= y));
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

    // -----------
    // constructor
    // -----------

    void test_constructor_1() {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    void test_constructor_2() {
        try {
            const Integer<int> x("2");
			const int y = 2;
			CPPUNIT_ASSERT(x == 2);
			CPPUNIT_ASSERT(2 == x);
			CPPUNIT_ASSERT(x == y);
			CPPUNIT_ASSERT(y == x);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_3() {
        try {
            const Integer<int> x(2);
			CPPUNIT_ASSERT(x == 2);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_4() {
        try {
            const Integer<int> x("0");
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_5() {
        try {
            const Integer<int> x("1234567890");
			CPPUNIT_ASSERT(x == 1234567890);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_6() {
        try {
            const Integer<int> x("-67");
			CPPUNIT_ASSERT(x == -67);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_7() {
        try {
            const Integer<int> x("-0");
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_8() {
        try {
            const Integer<int> x("-067");
			CPPUNIT_ASSERT(x == -67);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_9() {
        try {
            const Integer<int> x("067");
			CPPUNIT_ASSERT(x == 67);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_10() {
        try {
            const Integer<int> x("-0000067");
			CPPUNIT_ASSERT(x == -67);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_11() {
        try {
            const Integer<int> x("0000067");
			CPPUNIT_ASSERT(x == 67);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_12() {
        try {
            const Integer<int> x("50005");
			CPPUNIT_ASSERT(x == 50005);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_13() {
        try {
            const Integer<int> x("98000");
			CPPUNIT_ASSERT(x == 98000);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_14() {
        try {
            const Integer<int> x("001002003000");
			CPPUNIT_ASSERT(x == 1002003000);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_15() {
        try {
            const Integer<int> x(1010101010);
			CPPUNIT_ASSERT(x == 1010101010);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_16() {
        try {
            const Integer<int> x("-1287654321");
			CPPUNIT_ASSERT(x == -1287654321);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_constructor_17() {
        try {
            const Integer<int> x("001002-000");
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    void test_constructor_18() {
        try {
            const Integer<int> x("1010101010-");
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    void test_constructor_19() {
        try {
            const Integer<int> x("-a287654321");
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    void test_constructor_20() {
        try {
            const Integer<int> x("-228765432a");
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    void test_constructor_21() {
        try {
            const Integer<int> x("-22876a4321");
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    void test_constructor_22() {
        try {
            const Integer<int> x("--22876");
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::Integer()") == 0);
		}
	}

    // ---
    // abs
    // ---

    void test_abs_1() {
        try {
            Integer<int> x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(&x == &y);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_abs_2() {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y ==  98765);
			CPPUNIT_ASSERT(&x != &y);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_abs_3() {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(y == 98765);
			CPPUNIT_ASSERT(&x != &y);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    // --------
    // negation
    // --------

    void test_negation_1() {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_negation_2() {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == 98765);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_negation_3() {
        try {
            const Integer<int> x = 0;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

	// ---------------
	// increment (pre)
	// ---------------
	
    void test_increment_pre_1() {
        try {
            Integer<int> x = 98765;
            const Integer<int> y = ++x;
            CPPUNIT_ASSERT(x == 98766);
            CPPUNIT_ASSERT(y == 98766);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_increment_pre_2() {
        try {
            Integer<int> x = 0;
            const Integer<int> y = ++x;
            CPPUNIT_ASSERT(x == 1);
            CPPUNIT_ASSERT(y == 1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_increment_pre_3() {
        try {
            Integer<int> x = -1;
            const Integer<int> y = ++x;
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_increment_pre_4() {
        try {
            Integer<int> x = -1110;
            const Integer<int> y = ++x;
            CPPUNIT_ASSERT(x == -1109);
            CPPUNIT_ASSERT(y == -1109);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

	// ----------------
	// increment (post)
	// ----------------
	
    void test_increment_post_1() {
        try {
            Integer<int> x = 98765;
            const Integer<int> y = x++;
            CPPUNIT_ASSERT(x == 98766);
            CPPUNIT_ASSERT(y == 98765);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_increment_post_2() {
        try {
            Integer<int> x = 0;
            const Integer<int> y = x++;
            CPPUNIT_ASSERT(x == 1);
            CPPUNIT_ASSERT(y == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_increment_post_3() {
        try {
            Integer<int> x = -1;
            const Integer<int> y = x++;
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y == -1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_increment_post_4() {
        try {
            Integer<int> x = -1110;
            const Integer<int> y = x++;
            CPPUNIT_ASSERT(x == -1109);
            CPPUNIT_ASSERT(y == -1110);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

	// ---------------
	// decrement (pre)
	// ---------------
	
    void test_decrement_pre_1() {
        try {
            Integer<int> x = 98765;
            const Integer<int> y = --x;
            CPPUNIT_ASSERT(x == 98764);
            CPPUNIT_ASSERT(y == 98764);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_decrement_pre_2() {
        try {
            Integer<int> x = 0;
            const Integer<int> y = --x;
            CPPUNIT_ASSERT(x == -1);
            CPPUNIT_ASSERT(y == -1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_decrement_pre_3() {
        try {
            Integer<int> x = 1;
            const Integer<int> y = --x;
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_decrement_pre_4() {
        try {
            Integer<int> x = -1110;
            const Integer<int> y = --x;
            CPPUNIT_ASSERT(x == -1111);
            CPPUNIT_ASSERT(y == -1111);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

	// ----------------
	// decrement (post)
	// ----------------
	
    void test_decrement_post_1() {
        try {
            Integer<int> x = 98765;
            const Integer<int> y = x--;
            CPPUNIT_ASSERT(x == 98764);
            CPPUNIT_ASSERT(y == 98765);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_decrement_post_2() {
        try {
            Integer<int> x = 0;
            const Integer<int> y = x--;
            CPPUNIT_ASSERT(x == -1);
            CPPUNIT_ASSERT(y == 0);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_decrement_post_3() {
        try {
            Integer<int> x = 1;
            const Integer<int> y = x--;
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y == 1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_decrement_post_4() {
        try {
            Integer<int> x = -1110;
            const Integer<int> y = x--;
            CPPUNIT_ASSERT(x == -1111);
            CPPUNIT_ASSERT(y == -1110);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

	// -----------
	// plus_equals
	// -----------
	
	void test_plus_equals_1() {
		try {
			Integer<int> x = 5050;
			const Integer<int> y = 0;
			x += y;
			CPPUNIT_ASSERT(x == 5050);
			CPPUNIT_ASSERT(y == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_2() {
		try {
			Integer<int> x = 0;
			const Integer<int> y = 78879;
			x += y;
			CPPUNIT_ASSERT(x == 78879);
			CPPUNIT_ASSERT(y == 78879);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_3() {
		try {
			Integer<int> x = 998899;
			const Integer<int> y = 4334;
			x += y;
			CPPUNIT_ASSERT(x == 1003233);
			CPPUNIT_ASSERT(y == 4334);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_4() {
		try {
			Integer<int> x = -987;
			const Integer<int> y = -123;
			x += y;
			CPPUNIT_ASSERT(x == -1110);
			CPPUNIT_ASSERT(y == -123);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// (+) += (-)
	void test_plus_equals_5() {
		try {
			Integer<int> x = 7654321;
			const Integer<int> y = -678989;
			x += y;
			CPPUNIT_ASSERT(x == 6975332);
			CPPUNIT_ASSERT(y == -678989);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_6() {
		try {
			Integer<int> x = 989898;
			const Integer<int> y = -989898;
			x += y;
			CPPUNIT_ASSERT(x == 0);
			CPPUNIT_ASSERT(y == -989898);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_7() {
		try {
			Integer<int> x = 765765;
			const Integer<int> y = -9879879;
			x += y;
			CPPUNIT_ASSERT(x == -9114114);
			CPPUNIT_ASSERT(y == -9879879);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// (-) += (+)
	void test_plus_equals_8() {
		try {
			Integer<int> x = -5050;
			const Integer<int> y = 6000;
			x += y;
			CPPUNIT_ASSERT(x == 950);
			CPPUNIT_ASSERT(y == 6000);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_9() {
		try {
			Integer<int> x = -8080;
			const Integer<int> y = 8080;
			x += y;
			CPPUNIT_ASSERT(x == 0);
			CPPUNIT_ASSERT(y == 8080);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_plus_equals_10() {
		try {
			Integer<int> x = -123456789;
			const Integer<int> y = 298765;
			x += y;
			CPPUNIT_ASSERT(x == -123158024);
			CPPUNIT_ASSERT(y == 298765);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// -----------
	// minus_equals
	// -----------
	
	void test_minus_equals_1() {
		try {
			Integer<int> x = 5050;
			const Integer<int> y = 0;
			x -= y;
			CPPUNIT_ASSERT(x == 5050);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_minus_equals_2() {
		try {
			Integer<int> x = 0;
			const Integer<int> y = 78879;
			x -= y;
			CPPUNIT_ASSERT(x == -78879);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// (+) -= (-)
	void test_minus_equals_3() {
		try {
			Integer<int> x = 998899;
			const Integer<int> y = -4334;
			x -= y;
			CPPUNIT_ASSERT(x == 1003233);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// (-) -= (+)
	void test_minus_equals_4() {
		try {
			Integer<int> x = -987;
			const Integer<int> y = 123;
			x -= y;
			CPPUNIT_ASSERT(x == -1110);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// (+) -= (+)
	void test_minus_equals_5() {
		try {
			Integer<int> x = 7654321;
			const Integer<int> y = 678989;
			x -= y;
			CPPUNIT_ASSERT(x == 6975332);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_minus_equals_6() {
		try {
			Integer<int> x = 989898;
			const Integer<int> y = 989898;
			x -= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_minus_equals_7() {
		try {
			Integer<int> x = 765765;
			const Integer<int> y = 9879879;
			x -= y;
			CPPUNIT_ASSERT(x == -9114114);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// (-) -= (-)
	void test_minus_equals_8() {
		try {
			Integer<int> x = -5050;
			const Integer<int> y = -6000;
			x -= y;
			CPPUNIT_ASSERT(x == 950);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_minus_equals_9() {
		try {
			Integer<int> x = -8080;
			const Integer<int> y = -8080;
			x -= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_minus_equals_10() {
		try {
			Integer<int> x = -123456789;
			const Integer<int> y = -298765;
			x -= y;
			CPPUNIT_ASSERT(x == -123158024);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// -----------
	// times_equal
	// -----------
	
	void test_times_equals_1() {
		try {
			Integer<int> x = 0;
			const Integer<int> y = 77;
			x *= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_2() {
		try {
			Integer<int> x = -8844;
			const Integer<int> y = 1;
			x *= y;
			CPPUNIT_ASSERT(x == -8844);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_3() {
		try {
			Integer<int> x = 456;
			const Integer<int> y = 0;
			x *= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_4() {
		try {
			Integer<int> x = 1;
			const Integer<int> y = 12345;
			x *= y;
			CPPUNIT_ASSERT(x == 12345);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_5() {
		try {
			Integer<int> x = 1;
			const Integer<int> y = -678989;
			x *= y;
			CPPUNIT_ASSERT(x == -678989);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_6() {
		try {
			Integer<int> x = -50;
			const Integer<int> y = -9001;
			x *= y;
			CPPUNIT_ASSERT(x == 450050);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_7() {
		try {
			Integer<int> x = 999;
			const Integer<int> y = -999999;
			x *= y;
			CPPUNIT_ASSERT(x == -998999001);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_times_equals_8() {
		try {
			Integer<int> x = -4;
			const Integer<int> y = 5;
			x *= y;
			CPPUNIT_ASSERT(x == -20);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// ------------
	// divide_equal
	// ------------
	
	void test_divide_equals_1() {
		try {
			Integer<int> x = 100;
			const Integer<int> y = 0;
			x /= y;
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(strcmp(e.what(),
					"Integer::operator/=(const Integer& rhs)") == 0);
		}
	}

	void test_divide_equals_2() {
		try {
			Integer<int> x = -8844;
			const Integer<int> y = 1;
			x /= y;
			CPPUNIT_ASSERT(x == -8844);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_3() {
		try {
			Integer<int> x = 0;
			const Integer<int> y = 5412;
			x /= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_4() {
		try {
			Integer<int> x = 444;
			const Integer<int> y = -11;
			x /= y;
			CPPUNIT_ASSERT(x == -40);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_5() {
		try {
			Integer<int> x = -500;
			const Integer<int> y = 25;
			x /= y;
			CPPUNIT_ASSERT(x == -20);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_6() {
		try {
			Integer<int> x = -132678;
			const Integer<int> y = -567;
			x /= y;
			CPPUNIT_ASSERT(x == 234);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_7() {
		try {
			Integer<int> x = 989898;
			const Integer<int> y = 989898;
			x /= y;
			CPPUNIT_ASSERT(x == 1);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_8() {
		try {
			Integer<int> x = -4;
			const Integer<int> y = -20;
			x /= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_9() {
		try {
			Integer<int> x = -989898;
			const Integer<int> y = -989898;
			x /= y;
			CPPUNIT_ASSERT(x == 1);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_divide_equals_10() {
		try {
			Integer<int> x = -4;
			const Integer<int> y = 20;
			x /= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// ---------
	// mod_equal
	// ---------
	
	void test_mod_equals_1() {
		try {
			Integer<int> x = 5;
			const Integer<int> y = 0;
			x %= y;
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(strcmp(e.what(),
					"Integer::operator%=(const Integer& rhs)") == 0);
		}
	}

	void test_mod_equals_2() {
		try {
			Integer<int> x = 0;
			const Integer<int> y = 123;
			x %= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_3() {
		try {
			Integer<int> x = 456;
			const Integer<int> y = 456;
			x %= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_4() {
		try {
			Integer<int> x = -987;
			const Integer<int> y = 987;
			x %= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_5() {
		try {
			Integer<int> x = 25;
			const Integer<int> y = 4;
			x %= y;
			CPPUNIT_ASSERT(x == 1);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_6() {
		try {
			Integer<int> x = -25;
			const Integer<int> y = 4;
			x %= y;
			CPPUNIT_ASSERT(x == -1);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_7() {
		try {
			Integer<int> x = 989899;
			const Integer<int> y = 989898;
			x %= y;
			CPPUNIT_ASSERT(x == 1);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_8() {
		try {
			Integer<int> x = 500;
			const Integer<int> y = 50;
			x %= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_9() {
		try {
			Integer<int> x = 1234;
			const Integer<int> y = 5000;
			x %= y;
			CPPUNIT_ASSERT(x == 1234);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_mod_equals_10() {
		try {
			Integer<int> x = 1;
			const Integer<int> y = 1;
			x %= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// -----------------
	// shift_left_equals
	// -----------------
	
	void test_left_shift_equals_1() {
		try {
			Integer<int> x = 5;
			const int y = -1;
			x <<= y;
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(strcmp(e.what(),
						"Integer::operator<<=(int n)") == 0);
		}
	}

	void test_left_shift_equals_2() {
		try {
			Integer<int> x = -8844;
			const int y = 1;
			x <<= y;
			CPPUNIT_ASSERT(x == -88440);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_left_shift_equals_3() {
		try {
			Integer<int> x = 456;
			const int y = 1;
			x <<= y;
			CPPUNIT_ASSERT(x == 4560);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_left_shift_equals_4() {
		try {
			Integer<int> x = 0;
			const int y = 100;
			x <<= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_left_shift_equals_5() {
		try {
			Integer<int> x = 100;
			const int y = 0;
			x <<= y;
			CPPUNIT_ASSERT(x == 100);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_left_shift_equals_6() {
		try {
			Integer<int> x = 56;
			const int y = 4;
			x <<= y;
			CPPUNIT_ASSERT(x == 560000);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	// -----------------
	// shift_right_equals
	// -----------------
	
	void test_right_shift_equals_1() {
		try {
			Integer<int> x = 5;
			const int y = -1;
			x >>= y;
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(strcmp(e.what(),
						"Integer::operator>>=(int n)") == 0);
		}
	}

	void test_right_shift_equals_2() {
		try {
			Integer<int> x = -8844;
			const int y = 1;
			x >>= y;
			CPPUNIT_ASSERT(x == -884);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_right_shift_equals_3() {
		try {
			Integer<int> x = 456;
			const int y = 1;
			x >>= y;
			CPPUNIT_ASSERT(x == 45);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_right_shift_equals_4() {
		try {
			Integer<int> x = 0;
			const int y = 100;
			x >>= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_right_shift_equals_5() {
		try {
			Integer<int> x = 100;
			const int y = 0;
			x >>= y;
			CPPUNIT_ASSERT(x == 100);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_right_shift_equals_6() {
		try {
			Integer<int> x = 56;
			const int y = 4;
			x >>= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

	void test_right_shift_equals_7() {
		try {
			Integer<int> x = 112;
			const int y = 400;
			x >>= y;
			CPPUNIT_ASSERT(x == 0);
		} catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);
		}
	}

    // ------
    // output
    // ------

    void test_output_1() {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_output_2() {
        try {
            const Integer<int> x = -98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_output_3() {
        try {
            const Integer<int> x = 0;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "0");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    // ---
    // pow
    // ---

    void test_pow_1() {
        try {
            Integer<int>       x = 2;
            const int          e =  4423;
            Integer<int>&      y = x.pow(e);
							   --y;

			ostringstream expected("285542542228279613901563566102164008326164238644702889199247456602284400390600653875954571505539843239754513915896150297878399377056071435169747221107988791198200988477531339214282772016059009904586686254989084815735422480409022344297588352526004383890632616124076317387416881148592486188361873904175783145696016919574390765598280188599035578448591077683677175520434074287726578006266759615970759521327828555662781678385691581844436444812511562428136742490459363212810180276096088111401003377570363545725120924073646921576797146199387619296560302680261790118132925012323046444438622308877924609373773012481681672424493674474488537770155783006880852648161513067144814790288366664062257274665275787127374649231096375001170901890786263324619578795731425693805073056119677580338084333381987500902968831935913095269821311141322393356490178488728982288156282600813831296143663845945431144043753821542871277745606447858564159213328443580206422714694913091762716447041689678070096773590429808909616750452927258000843500344831628297089902728649981994387647234574276263729694848304750917174186181130688518792748622612293341368928056634384466646326572476167275660839105650528975713899320211121495795311427946254553305387067821067601768750977866100460014602138408448021225053689054793742003095722096732954750721718115531871310231057902608580607");

			ostringstream result;
			result << x;

            CPPUNIT_ASSERT(e == 4423);
            CPPUNIT_ASSERT(&x ==   &y);
            CPPUNIT_ASSERT(expected.str() == result.str());
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_2() {
        try {
            const Integer<int> x = 111;
            const int          e =  4;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 111);
            CPPUNIT_ASSERT(e ==  4);
            CPPUNIT_ASSERT(y == 151807041);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_3() {
        try {
            Integer<int>       x = 0;
            const int          e = 0;
            x.pow(e);
			CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::pow(int e)") == 0);
		}
	}

    void test_pow_4() {
        try {
            const Integer<int> x = 9876;
            const int          e =  -2;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(false);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer::pow(int e)") == 0);
		}
	}

    void test_pow_5() {
        try {
            Integer<int>       x = 98765;
            const int          e =  0;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT(e == 0);
            CPPUNIT_ASSERT(x == 1);
            CPPUNIT_ASSERT(&x == &y);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_6() {
        try {
            const Integer<int> x = 1;
            const int          e =  9867;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 1);
            CPPUNIT_ASSERT(e == 9867);
            CPPUNIT_ASSERT(y == 1);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_7() {
        try {
            Integer<int>       x = 9876;
            const int          e = 1;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT(e == 1);
            CPPUNIT_ASSERT(x == 9876);
            CPPUNIT_ASSERT(&x ==   &y);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_8() {
        try {
            const Integer<int> x = -55;
            const int          e =  5;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == -55);
            CPPUNIT_ASSERT(e == 5);
            CPPUNIT_ASSERT(y == -503284375);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    void test_pow_9() {
        try {
            Integer<int>       x = 1231;
            const int          e =  3;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT(e == 3);
            CPPUNIT_ASSERT(x == 1865409391);
            CPPUNIT_ASSERT(&x == &y);
		} catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);
		}
	}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits_1);
    CPPUNIT_TEST(test_shift_left_digits_2);
    CPPUNIT_TEST(test_shift_left_digits_3);
    CPPUNIT_TEST(test_shift_right_digits_1);
    CPPUNIT_TEST(test_shift_right_digits_2);
    CPPUNIT_TEST(test_shift_right_digits_3);
    CPPUNIT_TEST(test_plus_digits_1);
    CPPUNIT_TEST(test_plus_digits_2);
    CPPUNIT_TEST(test_plus_digits_3);
    CPPUNIT_TEST(test_plus_digits_4);
    CPPUNIT_TEST(test_plus_digits_5);
    CPPUNIT_TEST(test_plus_digits_6);
    CPPUNIT_TEST(test_minus_digits_1);
    CPPUNIT_TEST(test_minus_digits_2);
    CPPUNIT_TEST(test_minus_digits_3);
    CPPUNIT_TEST(test_minus_digits_4);
    CPPUNIT_TEST(test_minus_digits_5);
    CPPUNIT_TEST(test_minus_digits_6);
    CPPUNIT_TEST(test_minus_digits_7);
	CPPUNIT_TEST(test_strip_trailing_zeros_1);
	CPPUNIT_TEST(test_strip_trailing_zeros_2);
	CPPUNIT_TEST(test_strip_trailing_zeros_3);
	CPPUNIT_TEST(test_strip_trailing_zeros_4);
	CPPUNIT_TEST(test_strip_trailing_zeros_5);
	CPPUNIT_TEST(test_strip_trailing_zeros_6);
	CPPUNIT_TEST(test_mult_by_digit_1);
	CPPUNIT_TEST(test_mult_by_digit_2);
	CPPUNIT_TEST(test_mult_by_digit_3);
	CPPUNIT_TEST(test_mult_by_digit_4);
	CPPUNIT_TEST(test_mult_by_digit_5);
	CPPUNIT_TEST(test_mult_by_digit_6);
    CPPUNIT_TEST(test_multiplies_digits_0);
    CPPUNIT_TEST(test_multiplies_digits_1);
    CPPUNIT_TEST(test_multiplies_digits_2);
    CPPUNIT_TEST(test_multiplies_digits_3);
    CPPUNIT_TEST(test_multiplies_digits_4);
    CPPUNIT_TEST(test_multiplies_digits_5);
    CPPUNIT_TEST(test_multiplies_digits_6);
    CPPUNIT_TEST(test_multiplies_digits_7);
    CPPUNIT_TEST(test_multiplies_digits_8);
    CPPUNIT_TEST(test_dig_less_than_eq_to_1);
    CPPUNIT_TEST(test_dig_less_than_eq_to_2);
    CPPUNIT_TEST(test_dig_less_than_eq_to_3);
    CPPUNIT_TEST(test_dig_less_than_eq_to_4);
    CPPUNIT_TEST(test_dig_less_than_eq_to_5);
    CPPUNIT_TEST(test_dig_less_than_eq_to_6);
    CPPUNIT_TEST(test_dig_less_than_eq_to_7);
    CPPUNIT_TEST(test_divides_digits_1);
    CPPUNIT_TEST(test_divides_digits_2);
    CPPUNIT_TEST(test_divides_digits_3);
    CPPUNIT_TEST(test_divides_digits_4);
    CPPUNIT_TEST(test_divides_digits_5);
    CPPUNIT_TEST(test_divides_digits_6);
    CPPUNIT_TEST(test_divides_digits_7);
    CPPUNIT_TEST(test_divides_digits_8);
    CPPUNIT_TEST(test_divides_digits_9);
    CPPUNIT_TEST(test_divides_digits_10);
    CPPUNIT_TEST(test_divides_digits_11);
	CPPUNIT_TEST(test_grow_container_1);
	CPPUNIT_TEST(test_grow_container_2);
	CPPUNIT_TEST(test_grow_container_3);
	CPPUNIT_TEST(test_grow_container_4);
	CPPUNIT_TEST(test_grow_container_5);
	CPPUNIT_TEST(test_grow_container_6);
	CPPUNIT_TEST(test_grow_container_7);
    CPPUNIT_TEST(test_operator_equal_1);
    CPPUNIT_TEST(test_operator_equal_2);
    CPPUNIT_TEST(test_operator_equal_3);
    CPPUNIT_TEST(test_operator_equal_4);
    CPPUNIT_TEST(test_operator_equal_5);
    CPPUNIT_TEST(test_operator_equal_6);
    CPPUNIT_TEST(test_operator_equal_7);
    CPPUNIT_TEST(test_operator_equal_8);
    CPPUNIT_TEST(test_operator_equal_9);
    CPPUNIT_TEST(test_operator_not_equal_1);
    CPPUNIT_TEST(test_operator_not_equal_2);
    CPPUNIT_TEST(test_operator_not_equal_3);
    CPPUNIT_TEST(test_operator_less_than_1);
    CPPUNIT_TEST(test_operator_less_than_2);
    CPPUNIT_TEST(test_operator_less_than_3);
    CPPUNIT_TEST(test_operator_less_than_4);
    CPPUNIT_TEST(test_operator_less_than_5);
    CPPUNIT_TEST(test_operator_less_than_6);
    CPPUNIT_TEST(test_operator_less_than_7);
    CPPUNIT_TEST(test_operator_less_than_8);
    CPPUNIT_TEST(test_operator_less_than_9);
    CPPUNIT_TEST(test_operator_less_than_10);
    CPPUNIT_TEST(test_operator_less_than_11);
    CPPUNIT_TEST(test_operator_less_than_12);
    CPPUNIT_TEST(test_operator_less_than_13);
    CPPUNIT_TEST(test_operator_less_than_14);
    CPPUNIT_TEST(test_operator_less_than_or_equal_1);
    CPPUNIT_TEST(test_operator_less_than_or_equal_2);
    CPPUNIT_TEST(test_operator_less_than_or_equal_3);
    CPPUNIT_TEST(test_operator_greater_than_1);
    CPPUNIT_TEST(test_operator_greater_than_2);
    CPPUNIT_TEST(test_operator_greater_than_3);
    CPPUNIT_TEST(test_operator_greater_than_or_equal_1);
    CPPUNIT_TEST(test_operator_greater_than_or_equal_2);
    CPPUNIT_TEST(test_operator_greater_than_or_equal_3);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_constructor_5);
    CPPUNIT_TEST(test_constructor_6);
    CPPUNIT_TEST(test_constructor_7);
    CPPUNIT_TEST(test_constructor_8);
    CPPUNIT_TEST(test_constructor_9);
    CPPUNIT_TEST(test_constructor_10);
    CPPUNIT_TEST(test_constructor_11);
    CPPUNIT_TEST(test_constructor_12);
    CPPUNIT_TEST(test_constructor_13);
    CPPUNIT_TEST(test_constructor_14);
    CPPUNIT_TEST(test_constructor_15);
    CPPUNIT_TEST(test_constructor_16);
    CPPUNIT_TEST(test_constructor_17);
    CPPUNIT_TEST(test_constructor_18);
    CPPUNIT_TEST(test_constructor_19);
    CPPUNIT_TEST(test_constructor_20);
    CPPUNIT_TEST(test_constructor_21);
    CPPUNIT_TEST(test_constructor_22);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_abs_3);
    CPPUNIT_TEST(test_negation_1);
    CPPUNIT_TEST(test_negation_2);
    CPPUNIT_TEST(test_negation_3);
	CPPUNIT_TEST(test_increment_pre_1);
	CPPUNIT_TEST(test_increment_pre_2);
	CPPUNIT_TEST(test_increment_pre_3);
	CPPUNIT_TEST(test_increment_pre_4);
	CPPUNIT_TEST(test_increment_post_1);
	CPPUNIT_TEST(test_increment_post_2);
	CPPUNIT_TEST(test_increment_post_3);
	CPPUNIT_TEST(test_increment_post_4);
	CPPUNIT_TEST(test_decrement_pre_1);
	CPPUNIT_TEST(test_decrement_pre_2);
	CPPUNIT_TEST(test_decrement_pre_3);
	CPPUNIT_TEST(test_decrement_pre_4);
	CPPUNIT_TEST(test_decrement_post_1);
	CPPUNIT_TEST(test_decrement_post_2);
	CPPUNIT_TEST(test_decrement_post_3);
	CPPUNIT_TEST(test_decrement_post_4);
	CPPUNIT_TEST(test_plus_equals_1);
	CPPUNIT_TEST(test_plus_equals_2);
	CPPUNIT_TEST(test_plus_equals_3);
	CPPUNIT_TEST(test_plus_equals_4);
	CPPUNIT_TEST(test_plus_equals_5);
	CPPUNIT_TEST(test_plus_equals_6);
	CPPUNIT_TEST(test_plus_equals_7);
	CPPUNIT_TEST(test_plus_equals_8);
	CPPUNIT_TEST(test_plus_equals_9);
	CPPUNIT_TEST(test_plus_equals_10);
	CPPUNIT_TEST(test_minus_equals_1);
	CPPUNIT_TEST(test_minus_equals_2);
	CPPUNIT_TEST(test_minus_equals_3);
	CPPUNIT_TEST(test_minus_equals_4);
	CPPUNIT_TEST(test_minus_equals_5);
	CPPUNIT_TEST(test_minus_equals_6);
	CPPUNIT_TEST(test_minus_equals_7);
	CPPUNIT_TEST(test_minus_equals_8);
	CPPUNIT_TEST(test_minus_equals_9);
	CPPUNIT_TEST(test_minus_equals_10);
	CPPUNIT_TEST(test_times_equals_1);
	CPPUNIT_TEST(test_times_equals_2);
	CPPUNIT_TEST(test_times_equals_3);
	CPPUNIT_TEST(test_times_equals_4);
	CPPUNIT_TEST(test_times_equals_5);
	CPPUNIT_TEST(test_times_equals_6);
	CPPUNIT_TEST(test_times_equals_7);
	CPPUNIT_TEST(test_times_equals_8);
	CPPUNIT_TEST(test_divide_equals_1);
	CPPUNIT_TEST(test_divide_equals_2);
	CPPUNIT_TEST(test_divide_equals_3);
	CPPUNIT_TEST(test_divide_equals_4);
	CPPUNIT_TEST(test_divide_equals_5);
	CPPUNIT_TEST(test_divide_equals_6);
	CPPUNIT_TEST(test_divide_equals_7);
	CPPUNIT_TEST(test_divide_equals_8);
	CPPUNIT_TEST(test_divide_equals_9);
	CPPUNIT_TEST(test_divide_equals_10);
	CPPUNIT_TEST(test_mod_equals_1);
	CPPUNIT_TEST(test_mod_equals_2);
	CPPUNIT_TEST(test_mod_equals_3);
	CPPUNIT_TEST(test_mod_equals_4);
	CPPUNIT_TEST(test_mod_equals_5);
	CPPUNIT_TEST(test_mod_equals_6);
	CPPUNIT_TEST(test_mod_equals_7);
	CPPUNIT_TEST(test_mod_equals_8);
	CPPUNIT_TEST(test_mod_equals_9);
	CPPUNIT_TEST(test_mod_equals_10);
	CPPUNIT_TEST(test_left_shift_equals_1);
	CPPUNIT_TEST(test_left_shift_equals_2);
	CPPUNIT_TEST(test_left_shift_equals_3);
	CPPUNIT_TEST(test_left_shift_equals_4);
	CPPUNIT_TEST(test_left_shift_equals_5);
	CPPUNIT_TEST(test_left_shift_equals_6);
	CPPUNIT_TEST(test_right_shift_equals_1);
	CPPUNIT_TEST(test_right_shift_equals_2);
	CPPUNIT_TEST(test_right_shift_equals_3);
	CPPUNIT_TEST(test_right_shift_equals_4);
	CPPUNIT_TEST(test_right_shift_equals_5);
	CPPUNIT_TEST(test_right_shift_equals_6);
	CPPUNIT_TEST(test_right_shift_equals_7);
    CPPUNIT_TEST(test_output_1);
    CPPUNIT_TEST(test_output_2);
    CPPUNIT_TEST(test_output_3);
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST(test_pow_3);
    CPPUNIT_TEST(test_pow_4);
    CPPUNIT_TEST(test_pow_5);
    CPPUNIT_TEST(test_pow_6);
    CPPUNIT_TEST(test_pow_7);
    CPPUNIT_TEST(test_pow_8);
    CPPUNIT_TEST(test_pow_9);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    ios_base::sync_with_stdio(false);          // turn off synchronization with C I/O
    cout << "TestInteger.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestInteger::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
