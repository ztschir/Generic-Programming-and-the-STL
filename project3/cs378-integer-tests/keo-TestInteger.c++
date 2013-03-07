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
	% g++ -ansi -pedantic -ldl -Wall TestInteger.c++ -lcppunit -o TestInteger.c++.app
	% valgrind TestInteger.c++.app >& TestInteger.out
*/

// --------
// includes
#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner
#include "Integer.h"

//using namespace std;
using std::vector;

// -----------
// TestInteger
struct TestInteger : CppUnit::TestFixture {
	// -----------------
	// shift_left_digits
	void test_shift_left_digits_1 () {
		const int a[] = {2, 3, 4};
		const int b[] = {2, 3, 4, 0, 0};
		int x[10];
		int n = 2;		// shift number
		const int* p = shift_left_digits(a, a + 3, n, x);
		CPPUNIT_ASSERT( (p - x) == 5);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b) );
	}
	
	void test_shift_left_digits_2 () {
		const int a[] = {9, 2, 1};
		const int b[] = {9, 2, 1};
		int x[10];
		int n = 0;		// shift number
		const int* p = shift_left_digits(a, a + 3, n, x);
		CPPUNIT_ASSERT((p - x) == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b) );
	}
	
	void test_shift_left_digits_3 () {
		const int a[] = {5};
		const int b[] = {5, 0, 0};
		int x[10];
		int n = 2;		// shift number
		const int* p = shift_left_digits(a, a + 1, n, x);
		CPPUNIT_ASSERT((p - x) == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b) );
	}

	// ------------------
	// shift_right_digits
	void test_shift_right_digits () {
		const int a[] = {2, 3, 4};
		const int b[] = {2};		// answer
		int x[10];
		const int* p = shift_right_digits(a, a + 3, 2, x);
		CPPUNIT_ASSERT((p - x) == 1);		// length of answer
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b) );}

	// -----------
	// plus_digits
	void test_plus_digits_1 () {
		const int a[] = {2, 3, 4};
		const int b[] = {5, 6, 7};
		const int c[] = {8, 0, 1};
		int x[10];
		int aSize = sizeof a/sizeof a[0];
		int bSize = sizeof b/sizeof b[0];
		int cSize = sizeof c/sizeof c[0];
		const int* p = plus_digits(a, a + aSize, b, b + bSize, x);
		CPPUNIT_ASSERT(p - x == cSize);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c) );
	}
	
	void test_plus_digits_2 () {
		const int a[] = {7, 5, 8};
		const int b[] = {3, 1};
		const int c[] = {7, 8, 9};
		int x[10];
		int aSize = sizeof a/sizeof a[0];
		int bSize = sizeof b/sizeof b[0];
		int cSize = sizeof c/sizeof c[0];
		const int* p = plus_digits(a, a + aSize, b, b + bSize, x);
		
		CPPUNIT_ASSERT(p - x == cSize);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c) );
	}
	
	void test_plus_digits_3 () {
		const int a[] = {7, 5};
		const int b[] = {2, 1, 3, 7};
		const int c[] = {2, 2, 1, 2};
		int x[10];
		int aSize = sizeof a/sizeof a[0];
		int bSize = sizeof b/sizeof b[0];
		int cSize = sizeof c/sizeof c[0];
		const int* p = plus_digits(a, a + aSize, b, b + bSize, x);
		CPPUNIT_ASSERT(p - x == cSize);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c) );
	}
	
	// ------------
	// minus_digits
	void test_minus_digits () {
		const int a[] = {8, 0, 1};
		const int b[] = {5, 6, 7};
		const int c[] = {2, 3, 4};
		int x[10];
		const int* p = minus_digits(a, a + 3, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	// -----------------
	// multiplies_digits
	void test_multiplies_digits_1 () {
		const int a[] = {2, 3, 4};
		const int b[] = {5, 6, 7};
		const int c[] = {1, 3, 2, 6, 7, 8};
			int x[10];
		const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 6);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
		
	void test_multiplies_digits_2 () {
		const int a[] = {1, 2};
		const int b[] = {2, 0, 0};
		const int c[] = {2, 4, 0, 0};
			int x[10];
		const int* p = multiplies_digits(a, a + 2, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 4);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

	void test_multiplies_digits_3 () {
		const int a[] = {1, 0, 0, 0};
		const int b[] = {1, 0, 0};
		const int c[] = {1, 0, 0, 0, 0, 0};
			int x[10];
		int aSize = sizeof a/sizeof a[0];
		int bSize = sizeof b/sizeof b[0];
		int cSize = sizeof c/sizeof c[0];
		const int* p = multiplies_digits(a, a + aSize, b, b + bSize, x);
		CPPUNIT_ASSERT(cSize == 6);
		CPPUNIT_ASSERT(p - x == cSize);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c) );
	}
	
	void test_multiplies_digits_4 () {
		const int a[] = {1, 0, 0, 0};
		const int b[] = {1, 0, 0, 0};
		const int c[] = {1, 0, 0, 0, 0, 0, 0};
			int x[10];
		int aSize = sizeof a/sizeof a[0];
		int bSize = sizeof b/sizeof b[0];
		int cSize = sizeof c/sizeof c[0];
		const int* p = multiplies_digits(a, a + aSize, b, b + bSize, x);
		CPPUNIT_ASSERT(cSize == 7);
		//if(DEBUG) cerr << "BOOYAKASHA! " << p - x << endl;
		//if(DEBUG) print(x, x+3);
		CPPUNIT_ASSERT(p - x == cSize);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c) );
	}
	
	void test_multiplies_digits_5 () {
		vector<int> a (4, 0);
		a[0] = 1;
		vector<int>::iterator ab = a.begin();
		vector<int>::iterator ae = a.end();
		
		vector<int> b (4, 0);
		b[0] = 1;
		vector<int>::iterator bb = b.begin();
		vector<int>::iterator be = b.end();
		
		//const int c[] = {1, 0, 0, 0, 0, 0, 0};
		vector<int> x (7, 0);
		vector<int>::iterator xb = x.begin();
	/*	int aSize = sizeof a/sizeof a[0];
		int bSize = sizeof b/sizeof b[0];
		int cSize = sizeof c/sizeof c[0];*/
		multiplies_digits(ab, ae, bb, be, xb);
		//int size = e-b;
		/*cerr << "multdig: " << x.size() << endl;
		for(;xb != x.end(); ++xb)
			cerr << " " << *xb;
		cerr << endl;
		*/
		//CPPUNIT_ASSERT(cSize == 7);
		//if(DEBUG) cerr << "BOOYAKASHA! " << p - x << endl;
		//if(DEBUG) print(x, x+3);
		//CPPUNIT_ASSERT(p - x == cSize);
		//CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c) );
	}
		
	// --------------
	// divides_digits
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
	void test_constructor_1 () {
		try {
			const Integer<int> x(2147483647);}		// max int value
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}

	void test_constructor_2 () {
		try {
			const Integer<int> x = 24816;}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}

	void test_constructor_3 () {
		try {
			const Integer<int> x("2");
			CPPUNIT_ASSERT(x == 2);
		}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}
	
	void test_constructor_4 () {
		try {
			const Integer<int> x("abc");
			CPPUNIT_ASSERT(false);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));}
	}

	void test_constructor_5 () {
		try {
			const Integer<int, vector<int> > x = 10;}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}

	// ---
	// operator <
	void test_less_than_1(){
		const Integer<int> x(40);
		const Integer<int, vector<int> > y = 80;
		
		CPPUNIT_ASSERT(x < y);
		CPPUNIT_ASSERT(!(y < x) );
		CPPUNIT_ASSERT(!(x < x) );
		CPPUNIT_ASSERT(!(y < y) );
	}
	
	void test_less_than_2(){
		const Integer<int> x = 0;
		const Integer<int> y = 0;
		
		CPPUNIT_ASSERT(!(x < y) );
		CPPUNIT_ASSERT(!(y < x) );
		CPPUNIT_ASSERT(!(x < x) );
		CPPUNIT_ASSERT(!(y < y) );
	}
	
	void test_less_than_3(){
		const Integer<int> x = -80;
		const Integer<int> y = 40;
		
		CPPUNIT_ASSERT( (x < y) );
		CPPUNIT_ASSERT(!(y < x) );
		CPPUNIT_ASSERT(!(x < x) );
		CPPUNIT_ASSERT(!(y < y) );
	}
	
	void test_less_than_4(){
		const Integer<int> x = 20;
		const Integer<int> y = -30;
		
		CPPUNIT_ASSERT(!(x < y) );
		CPPUNIT_ASSERT( (y < x) );
		CPPUNIT_ASSERT(!(x < x) );
		CPPUNIT_ASSERT(!(y < y) );
	}
	
	void test_less_than_5(){
		const Integer<int> x = -22;
		const Integer<int> y = -333;
		
		CPPUNIT_ASSERT(!(x < y) );
		CPPUNIT_ASSERT( (y < x) );
		CPPUNIT_ASSERT(!(x < x) );
		CPPUNIT_ASSERT(!(y < y) );
	}
	
	void test_less_than_6(){
		const Integer<int> x(404);
		const Integer<int, vector<int> > y = 80;
		
		CPPUNIT_ASSERT(!(x < y) );
		CPPUNIT_ASSERT( (y < x) );
		CPPUNIT_ASSERT(!(x < x) );
		CPPUNIT_ASSERT(!(y < y) );
	}
	

	// ---
	// abs
	void test_abs_1 () {
		try {
			Integer<int>  x = -98765;
			Integer<int>& y = x.abs();
			CPPUNIT_ASSERT( x == 98765);		// implicit call to Integer constructor
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

	// --------
	// negation
	void test_negation_1 () {
		try {
			const Integer<int> x = 98765;
			const Integer<int> y = -x;
			CPPUNIT_ASSERT(y == -98765);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}
	
	void test_negation_2 () {
		try {
			const Integer<int> x = -98765;
			const Integer<int> y = -x;
			CPPUNIT_ASSERT(y == 98765);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}
	
	void test_negation_3 () {
		try {
			const Integer<int> x = 0;
			const Integer<int> y = 0;
		}catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}

	// ------
	// output
	void test_output () {
		try {
			const Integer<int> x = 98765;
			std::ostringstream out;
			out << x;
			CPPUNIT_ASSERT(out.str() == "98765");}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}}
	
	// -----
	// operator +=
	void test_plusequals_1(){
		Integer<int> x = 2;
		Integer<int> y = 3;
		
		CPPUNIT_ASSERT( (x += y) == 5);
		CPPUNIT_ASSERT( x == 5);
		CPPUNIT_ASSERT( y == 3);
	}
	
	void test_plusequals_2(){
		Integer<int> x = 0;
		Integer<int> y = 0;
		
		CPPUNIT_ASSERT( (x += y) == 0);
		CPPUNIT_ASSERT( x == 0);
		CPPUNIT_ASSERT( y == 0);
	}
	
	void test_plusequals_3(){
		Integer<int> x = 11;
		Integer<int> y = 537;
		
		CPPUNIT_ASSERT( (x += y) == 548);
		CPPUNIT_ASSERT( x == 548);
		CPPUNIT_ASSERT( y == 537);
	}
	
	void test_plusequals_4(){
		Integer<int> x = 537;
		Integer<int> y = 11;
		
		CPPUNIT_ASSERT( (x += y) == 548);
		CPPUNIT_ASSERT( x == 548);
		CPPUNIT_ASSERT( y == 11);
	}
	
	void test_plusequals_5(){
		Integer<int> x = 1000000;
		Integer<int> y = 2000000;
		
		CPPUNIT_ASSERT( (x += y) == 3000000);
		CPPUNIT_ASSERT( x == 3000000);
		CPPUNIT_ASSERT( y == 2000000);
	}
	
	// -----
	// operator -=
	void test_minusequals_1(){
		Integer<int> x = 3;
		Integer<int> y = 2;
		
		CPPUNIT_ASSERT( (x -= y) == 1);
		CPPUNIT_ASSERT( x == 1);
		CPPUNIT_ASSERT( y == 2);
	}
	
	void test_minusequals_2(){
		Integer<int> x = 5;
		Integer<int> y = 7;
		
		CPPUNIT_ASSERT( (x -= y) == -2);
		CPPUNIT_ASSERT( x == -2);
		CPPUNIT_ASSERT( y == 7);
	}
	
	void test_minusequals_3(){
		Integer<int> x = 23;
		Integer<int> y = 11;
		
		CPPUNIT_ASSERT( (x -= y) == 12);
		CPPUNIT_ASSERT( x == 12);
		CPPUNIT_ASSERT( y == 11);
	}
	
	void test_minusequals_4(){
		Integer<int> x = 3;
		Integer<int> y = 11;
		
		CPPUNIT_ASSERT( (x -= y) == -7);
		CPPUNIT_ASSERT( x == -7);
		CPPUNIT_ASSERT( y == 11);
	}
	
	// -----
	// operator *=
	void test_multequals_1(){
		Integer<int> x = 3;
		Integer<int> y = 2;
		
		CPPUNIT_ASSERT( (x *= y) == 6);
		CPPUNIT_ASSERT( x == 6);
		CPPUNIT_ASSERT( y == 2);
	}
	
	void test_multequals_2(){
		Integer<int> x = 5;
		Integer<int> y = 3;
		
		CPPUNIT_ASSERT( (x *= y) == 15);
		CPPUNIT_ASSERT( x == 15);
		CPPUNIT_ASSERT( y == 3);
	}
	
	void test_multequals_3(){
		Integer<int> x = 3;
		Integer<int> y = 21;
		
		CPPUNIT_ASSERT( (x *= y) == 63);
		CPPUNIT_ASSERT( x == 63);
		CPPUNIT_ASSERT( y == 21);
	}
	
	void test_multequals_4(){
		Integer<int> x = 12;
		Integer<int> y = 3;
		
		CPPUNIT_ASSERT( (x *= y) == 36);
		CPPUNIT_ASSERT( x == 36);
		CPPUNIT_ASSERT( y == 3);
	}
	
	void test_multequals_5(){
		Integer<int> x = 12;
		Integer<int> y = 200;
		//if(DEBUG){ x *= y; cerr << "multequals: " << x << endl;}
		CPPUNIT_ASSERT( (x *= y) == 2400);
		CPPUNIT_ASSERT( x == 2400);
		CPPUNIT_ASSERT( y == 200);
	}
	
	// -----
	// operator /=
	void test_divequals_1(){
		Integer<int> x = 6;
		Integer<int> y = 2;
		
		CPPUNIT_ASSERT( (x /= y) == 3);
		CPPUNIT_ASSERT( x == 3);
		CPPUNIT_ASSERT( y == 2);
	}

	// ---
	// pow
	void test_pow_1 () {
		try {
			Integer<int>       x = 98765;
			const int          e =  9867;
			Integer<int>&      y = x.pow(e);
			CPPUNIT_ASSERT( e == 9867);
			CPPUNIT_ASSERT( x != 98765);
			CPPUNIT_ASSERT(&x ==   &y);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
		}

	void test_pow_2 () {
		try {
			const Integer<int> x = 98765;
			const int          e =  9867;
			const Integer<int> y = pow(x, e);
			CPPUNIT_ASSERT(x == 98765);
			CPPUNIT_ASSERT(e ==  9867);
			//CPPUNIT_ASSERT(y ==     0);
		}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}

	void test_pow_3 () {
		try {
			const Integer<int> x = 3;
			const int          e = 2;
			const Integer<int> y = pow(x, e);
			CPPUNIT_ASSERT(x == 3);
			CPPUNIT_ASSERT(e == 2);
			CPPUNIT_ASSERT(y == 9);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}

	void test_pow_4 () {
		try {
			const Integer<int> x = 10;
			const int          e = 6;
			const Integer<int> y = pow(x, e);
			CPPUNIT_ASSERT(x == 10);
			CPPUNIT_ASSERT(e == 6);
			CPPUNIT_ASSERT(y == 1000000);}
		catch (std::invalid_argument& e) {
			CPPUNIT_ASSERT(false);}
	}
	
	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestInteger);
	CPPUNIT_TEST(test_shift_left_digits_1);
	CPPUNIT_TEST(test_shift_left_digits_2);
	CPPUNIT_TEST(test_shift_left_digits_3);
	CPPUNIT_TEST(test_shift_right_digits);
	
	CPPUNIT_TEST(test_plus_digits_1);
	CPPUNIT_TEST(test_plus_digits_2);
	CPPUNIT_TEST(test_plus_digits_3);
	CPPUNIT_TEST(test_minus_digits);
	CPPUNIT_TEST(test_multiplies_digits_1);
	CPPUNIT_TEST(test_multiplies_digits_2);
	CPPUNIT_TEST(test_multiplies_digits_3);
	CPPUNIT_TEST(test_multiplies_digits_4);
	CPPUNIT_TEST(test_multiplies_digits_5);
	CPPUNIT_TEST(test_divides_digits);
	
	CPPUNIT_TEST(test_constructor_1);
	CPPUNIT_TEST(test_constructor_2);
	CPPUNIT_TEST(test_constructor_3);
	CPPUNIT_TEST(test_constructor_4);
	CPPUNIT_TEST(test_constructor_5);
	CPPUNIT_TEST(test_less_than_1);
	CPPUNIT_TEST(test_less_than_2);
	CPPUNIT_TEST(test_less_than_3);
	CPPUNIT_TEST(test_less_than_4);
	CPPUNIT_TEST(test_less_than_5);
	CPPUNIT_TEST(test_less_than_6);
	CPPUNIT_TEST(test_negation_1);
	CPPUNIT_TEST(test_negation_2);
	CPPUNIT_TEST(test_negation_3);
	CPPUNIT_TEST(test_abs_1);
	CPPUNIT_TEST(test_abs_2);
	CPPUNIT_TEST(test_output);
	CPPUNIT_TEST(test_plusequals_1);
	CPPUNIT_TEST(test_plusequals_2);
	CPPUNIT_TEST(test_plusequals_3);
	CPPUNIT_TEST(test_plusequals_4);
	CPPUNIT_TEST(test_plusequals_5);
	CPPUNIT_TEST(test_minusequals_1);
	CPPUNIT_TEST(test_minusequals_3);
	CPPUNIT_TEST(test_multequals_1);
	CPPUNIT_TEST(test_multequals_2);
	CPPUNIT_TEST(test_multequals_3);
	CPPUNIT_TEST(test_multequals_4);
	CPPUNIT_TEST(test_multequals_5);
	CPPUNIT_TEST(test_pow_1);
	CPPUNIT_TEST(test_pow_2);
	CPPUNIT_TEST(test_pow_3);
	CPPUNIT_TEST(test_pow_4);
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);          // turn off synchronization with C I/O
	cout << "TestInteger.c++" << endl << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestInteger::suite() );
	tr.run();
	
	cout << "Done." << endl;
	return 0;
}