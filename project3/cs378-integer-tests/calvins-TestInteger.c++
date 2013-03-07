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
#include <vector>    // vector

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
		const int a[] = {4, 3, 2};
		const int b[] = {0, 0, 4, 3, 2};
		int x[10];
		const int* p = shift_left_digits(a, a + 3, 2, x);
		CPPUNIT_ASSERT((p - x) == 5);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

	void test_shift_left_digits_1 () {
		const int a[] = {2};
		const int b[] = {2};
		int x[10];
		const int* p = shift_left_digits(a, a + 1, 0, x);
		CPPUNIT_ASSERT((p - x) == 1);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

	void test_shift_left_digits_2 () {
        using namespace std;
        vector<int> a (4, 100);
		const int b[] = {0, 0, 100, 100, 100, 100};
		int x[10];
		const int* p = shift_left_digits(a.begin(), a.end(), 2, x);
		CPPUNIT_ASSERT((p - x) == 6);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

	// ------------------
	// shift_right_digits
	// ------------------

	void test_shift_right_digits () {
		const int a[] = {4, 3, 2};
		const int b[] = {2};
		int x[10];
		const int* p = shift_right_digits(a, a + 3, 2, x);
		CPPUNIT_ASSERT((p - x) == 1);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

	void test_shift_right_digits_1 () {
		const int a[] = {4, 3, 2};
		const int b[] = {0};
		int x[10];
		const int* p = shift_right_digits(a, a + 3, 4, x);
		CPPUNIT_ASSERT((p - x) == 1);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

	void test_shift_right_digits_2 () {
        using namespace std;
        vector<int> a (4, 100);
		const int b[] = {100, 100};
		int x[10];
		const int* p = shift_right_digits(a.begin(), a.end(), 2, x);
		CPPUNIT_ASSERT((p - x) == 2);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
	// -----------
	// plus_digits
	// -----------

	void test_plus_digits () {
		const int a[] = {4, 3, 2};
		const int b[] = {7, 6, 5};
		const int c[] = {1, 0, 8};
		int x[10];
		const int* p = plus_digits(a, a + 3, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_plus_digits_1 () {
		const int a[] = {4, 3, 2};
		const int b[] = {6, 5};
		const int c[] = {0, 9, 2};
		int x[10];
		const int* p = plus_digits(a, a + 3, b, b + 2, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_plus_digits_2 () {
		const int a[] = {3, 2};
		const int b[] = {6, 5, 4};
		const int c[] = {9, 7, 4};
		int x[10];
		const int* p = plus_digits(a, a + 2, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_plus_digits_3 () {
		const int a[] = {3, 2, 0, 0, 0};
		const int b[] = {6, 5, 4};
		const int c[] = {9, 7, 4};
		int x[10];
		const int* p = plus_digits(a, a + 5, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	// ------------
	// minus_digits
	// ------------

	void test_minus_digits () {
        // using namespace std;
		const int a[] = {1, 0, 8};
		const int b[] = {7, 6, 5};
		const int c[] = {4, 3, 2};
		int x[10];
		const int* p = minus_digits(a, a + 3, b, b + 3, x);
        /*
        // For debugging:
        cout << endl;
        for (int i = 0;i<3;++i) {
            cout << x[i] << " "; }
        cout << endl;
        */
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_minus_digits_1 () {
		const int a[] = {4, 3, 2};
		const int b[] = {5, 6};
		const int c[] = {9, 6, 1};
		int x[10];
		const int* p = minus_digits(a, a + 3, b, b + 2, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_minus_digits_2 () {
		const int a[] = {8, 0, 1};
		const int b[] = {8, 0, 1};
		const int c[] = {0};
		int x[10];
		const int* p = minus_digits(a, a + 3, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 1);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	// -----------------
	// multiplies_digits
	// -----------------

	void test_multiplies_digits () {
		const int a[] = {4, 3, 2};
		const int b[] = {7, 6, 5};
		const int c[] = {8, 7, 6, 2, 3, 1};
		int x[10];
		const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 6);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_multiplies_digits_1 () {
		const int a[] = {0, 1};
		const int b[] = {0, 1};
		const int c[] = {0, 0, 1};
		int x[10];
		const int* p = multiplies_digits(a, a + 2, b, b + 2, x);
        /*
        // For debugging:
        std::cout << std::endl;
        for (int i = 0;i<3;++i) {
            std::cout << x[i] << " "; }
        std::cout << std::endl;
        */
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_multiplies_digits_2 () {
		const int a[] = {9, 8};
		const int b[] = {7, 6, 5};
		const int c[] = {3, 6, 4, 0, 5};
		int x[10];
		const int* p = multiplies_digits(a, a + 2, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 5);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	// --------------
	// divides_digits
	// --------------

	void test_divides_digits () {
		const int a[] = {8, 7, 6, 2, 3, 1};
		const int b[] = {7, 6, 5};
		const int c[] = {4, 3, 2};
		int x[10];
		const int* p = divides_digits(a, a + 6, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_divides_digits_1 () {
		const int a[] = {1, 3, 2};
		const int b[] = {1};
		const int c[] = {1, 3, 2};
		int x[10];
		const int* p = divides_digits(a, a + 3, b, b + 1, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_divides_digits_2 () {
		const int a[] = {0, 0, 0, 0, 1};
		const int b[] = {0, 0, 1};
		const int c[] = {0, 0, 1};
		int x[10];
		const int* p = divides_digits(a, a + 6, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
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
			const Integer<int> x("2048"); }
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_constructor_3 () {
		try {
			const Integer<int> x(2); }
            // std::cout << std::endl << x << std::endl; }
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

	void test_abs_3 () {
		try {
			const Integer<int> x = 0;
			const Integer<int> y = abs(x);
			CPPUNIT_ASSERT(x == 0);
			CPPUNIT_ASSERT(y == 0);}
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
			CPPUNIT_ASSERT(!(98765 != y)); }
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_equal_to_1 () {
		try {
			const Integer<int> x = 0;
			const Integer<int> y = 0;
			CPPUNIT_ASSERT(      x == y);
			CPPUNIT_ASSERT(      x == 0);
			CPPUNIT_ASSERT(  0 == x);
			CPPUNIT_ASSERT(    !(x != y));
			CPPUNIT_ASSERT(    !(x != 0));
			CPPUNIT_ASSERT(!(0 != y)); }
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_equal_to_2 () {
		try {
			const Integer<int> x = 12345;
			const Integer<int> y = 98765;
			CPPUNIT_ASSERT(      x != y);
			CPPUNIT_ASSERT(      x != 98765);
			CPPUNIT_ASSERT(  98765 != x);
			CPPUNIT_ASSERT(    !(x == y));
			CPPUNIT_ASSERT(    !(x == 98765));
			CPPUNIT_ASSERT(!(98765 != y)); }
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// --------
	// less_than
	// --------

	void test_less_than () {
		try {
			const Integer<int> x = 12345;
			const Integer<int> y = 98765;
			CPPUNIT_ASSERT(      x < y);
			CPPUNIT_ASSERT(      x < 98765);
			CPPUNIT_ASSERT(      x <= y);
			CPPUNIT_ASSERT(      x <= 98765);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_less_than_1 () {
		try {
			const Integer<int> x = 98765;
			const Integer<int> y = 98765;
			CPPUNIT_ASSERT(    !(x < y));
			CPPUNIT_ASSERT(    !(x < 98765));
			CPPUNIT_ASSERT(      x <= y);
			CPPUNIT_ASSERT(      x <= 98765);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_less_than_2 () {
		try {
			const Integer<int> x = -12345;
			const Integer<int> y = 98765;
			CPPUNIT_ASSERT(      x < y);
			CPPUNIT_ASSERT(      x < 98765);
			CPPUNIT_ASSERT(      x <= y);
			CPPUNIT_ASSERT(      x <= 98765);}
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

	void test_negation_1 () {
		try {
			const Integer<int> x = -98765;
			const Integer<int> y = -x;
			CPPUNIT_ASSERT(y == 98765);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_negation_2 () {
		try {
			Integer<int> x = 98765;
            x = -x;
			CPPUNIT_ASSERT(x == -98765);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// --------
	// addition
	// --------

	void test_addition () {
		try {
			const Integer<int> x = 123;
			const Integer<int> y = 456;
            const Integer<int> z = x + y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 579);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_addition_1 () {
		try {
			const Integer<int> x = 123;
			const Integer<int> y = -456;
            const Integer<int> z = x + y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == -333);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_addition_2 () {
		try {
			const Integer<int> x = -123;
			const Integer<int> y = -456;
            const Integer<int> z = x + y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == -579);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_addition_3 () {
		try {
			const Integer<int> x = -123;
			const Integer<int> y = 0;
            const Integer<int> z = x + y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == -123);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// --------
	// subtraction
	// --------

	void test_subtraction () {
		try {
			const Integer<int> x = 579;
			const Integer<int> y = 456;
            const Integer<int> z = x - y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 123);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_subtraction_1 () {
		try {
			const Integer<int> x = 123;
			const Integer<int> y = -456;
            const Integer<int> z = x - y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 579);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_subtraction_2 () {
		try {
			const Integer<int> x = -123;
			const Integer<int> y = 456;
            const Integer<int> z = x - y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == -579);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_subtraction_3 () {
		try {
			const Integer<int> x = -123;
			const Integer<int> y = -579;
            const Integer<int> z = x - y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 456);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// --------------
	// multiplication
	// --------------

	void test_multiplication () {
		try {
			const Integer<int> x = 123;
			const Integer<int> y = 456;
            const Integer<int> z = x * y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 56088);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_multiplication_1 () {
		try {
			const Integer<int> x = 123;
			const Integer<int> y = -456;
            const Integer<int> z = x * y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == -56088);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_multiplication_2 () {
		try {
			const Integer<int> x = -123;
			const Integer<int> y = -456;
            const Integer<int> z = x * y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 56088);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_multiplication_3 () {
		try {
			const Integer<int> x = 10;
			const Integer<int> y = 10;
            const Integer<int> z = x * y;
            // std::cout << std::endl << z << std::endl;
			CPPUNIT_ASSERT(z == 100);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

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

	void test_output_1 () {
		try {
			const Integer<int> x = 98765;
			const Integer<int> y = 12345;
			std::ostringstream out;
            out << x << y;
			CPPUNIT_ASSERT(out.str() == "9876512345");}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_output_2 () {
		try {
			const Integer<int> x = -98765;
			std::ostringstream out;
            out << x;
			CPPUNIT_ASSERT(out.str() == "-98765");}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// ---
	// pow
	// ---
	void test_pow () {
		try {
			Integer<int>       x = 2;
			const int          e =  10;
			Integer<int>&      y = x.pow(e);
            Integer<int>       z("1024");
            // std::cout << y << std::endl << z <<std::endl;
			CPPUNIT_ASSERT( e == 10);
			CPPUNIT_ASSERT( x ==  z);
			CPPUNIT_ASSERT(&x ==   &y);
            }
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_pow_1 () {
		try {
			Integer<int>       x = 98;
			const int          e = 98;
			Integer<int>&      y = x.pow(e);
            Integer<int>       z("1380878341261486750656911803252309726876604105686729638072729543243701479670593033211008001443536626310535980077544691196522513327846303307992442770355560270350429006522588433404602387992091295744");
			CPPUNIT_ASSERT( e == 98);
			CPPUNIT_ASSERT( x ==  z);
			CPPUNIT_ASSERT(&x ==   &y);
            }
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	void test_pow_2 () {
		try {
			const Integer<int> x = 98;
			const int          e =  98;
			const Integer<int> y = pow(x, e);
            Integer<int>       z("1380878341261486750656911803252309726876604105686729638072729543243701479670593033211008001443536626310535980077544691196522513327846303307992442770355560270350429006522588433404602387992091295744");
			CPPUNIT_ASSERT(x == 98);
			CPPUNIT_ASSERT(e ==  98);
			CPPUNIT_ASSERT(y ==     z);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestInteger);

	CPPUNIT_TEST(test_shift_left_digits);
	CPPUNIT_TEST(test_shift_left_digits_1);
	CPPUNIT_TEST(test_shift_left_digits_2);

	CPPUNIT_TEST(test_shift_right_digits);
	CPPUNIT_TEST(test_shift_right_digits_1);
	CPPUNIT_TEST(test_shift_right_digits_2);

	CPPUNIT_TEST(test_plus_digits);
	CPPUNIT_TEST(test_plus_digits_1);
	CPPUNIT_TEST(test_plus_digits_2);
	CPPUNIT_TEST(test_plus_digits_3);

	CPPUNIT_TEST(test_minus_digits);
	CPPUNIT_TEST(test_minus_digits_1);
	CPPUNIT_TEST(test_minus_digits_2);

	CPPUNIT_TEST(test_multiplies_digits);
	CPPUNIT_TEST(test_multiplies_digits_1);
	CPPUNIT_TEST(test_multiplies_digits_2);
    /*

	CPPUNIT_TEST(test_divides_digits);
	CPPUNIT_TEST(test_divides_digits_1);
	CPPUNIT_TEST(test_divides_digits_2);
    */
	CPPUNIT_TEST(test_constructor_1);
	CPPUNIT_TEST(test_constructor_2);
	CPPUNIT_TEST(test_constructor_3);

	CPPUNIT_TEST(test_abs_1);
	CPPUNIT_TEST(test_abs_2);
	CPPUNIT_TEST(test_abs_3);

    CPPUNIT_TEST(test_equal_to);
    CPPUNIT_TEST(test_equal_to_1);
    CPPUNIT_TEST(test_equal_to_2);
    
    CPPUNIT_TEST(test_less_than);
    CPPUNIT_TEST(test_less_than_1);
    CPPUNIT_TEST(test_less_than_2);

	CPPUNIT_TEST(test_negation);
	CPPUNIT_TEST(test_negation_1);
	CPPUNIT_TEST(test_negation_2);

	CPPUNIT_TEST(test_addition);
	CPPUNIT_TEST(test_addition_1);
	CPPUNIT_TEST(test_addition_2);
	CPPUNIT_TEST(test_addition_3);

	CPPUNIT_TEST(test_subtraction);
	CPPUNIT_TEST(test_subtraction_1);
	CPPUNIT_TEST(test_subtraction_2);
	CPPUNIT_TEST(test_subtraction_3);

	CPPUNIT_TEST(test_multiplication);
	CPPUNIT_TEST(test_multiplication_1);
	CPPUNIT_TEST(test_multiplication_2);
	CPPUNIT_TEST(test_multiplication_3);

	CPPUNIT_TEST(test_output);
	CPPUNIT_TEST(test_output_1);
	CPPUNIT_TEST(test_output_2);

	CPPUNIT_TEST(test_pow);
	CPPUNIT_TEST(test_pow_1);
	CPPUNIT_TEST(test_pow_2);

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
