
/*
Fin's tests
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -ldl -Wall TestSMP.c++ -lcppunit -o TestSMP.c++.app
    % valgrind TestSMP.c++.app >& TestSMP.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner
#include "SMP.h"

// -----------
// TestCollatz
// -----------

struct TestSMP : CppUnit::TestFixture {
    // ----
    // read
    // ----
	void test_read_women () {
		// initialize buckets
		std::istringstream r("1 1\n1 1\n");
		int n = 1;
		int** women = new int*[1];
		women[0] = new int[1];
		int** men = new int*[1];
		men[0] = new int[1];
		// test smp_read
		smp_read(r,n,women,men);
		CPPUNIT_ASSERT(women[0][0] == 1);
		// clean up
		delete [] women[0];
		delete [] women;
		delete [] men[0];
		delete [] men;}

	void test_read_men () {
		// initialize buckets
		std::istringstream r("1 1\n1 1\n");
		int n = 1;
		int** women = new int*[1];
		women[0] = new int[1];
		int** men = new int*[1];
		men[0] = new int[1];
		// test smp_read
		smp_read(r,n,women,men);
		CPPUNIT_ASSERT(men[0][0] == 1);
		// clean up
		delete [] women[0];
		delete [] women;
		delete [] men[0];
		delete [] men;}

	void test_read () {
		// initialize buckets
		std::istringstream r("1 1 2\n2 1 2\n1 1 2\n2 1 2\n");
		int n = 2;
		int** women = new int*[2];
		women[0] = new int[2];
		women[1] = new int[2];
		int** men = new int*[2];
		men[0] = new int[2];
		men[1] = new int[2];
		// test smp read
		smp_read(r,n,women,men);
		CPPUNIT_ASSERT(women[0][0] == 1);
		CPPUNIT_ASSERT(women[0][1] == 2);
		CPPUNIT_ASSERT(women[1][0] == 1);
		CPPUNIT_ASSERT(women[1][1] == 2);
		CPPUNIT_ASSERT(men[0][0] == 1);
		CPPUNIT_ASSERT(men[0][1] == 2);
		CPPUNIT_ASSERT(men[1][0] == 1);
		CPPUNIT_ASSERT(men[1][1] == 2);
		// clean up
		delete [] women[0];
		delete [] women[1];
		delete [] women;
		delete [] men[0];
		delete [] men[1];
		delete [] men;}


	// ------
	// invert
	// ------
	void test_invert_1 () {
		// declare variables
		int n = 2;
		int** src = new int*[n];
		src[0] = new int[n];
		src[1] = new int[n];
		int** dest = new int*[n];
		dest[0] = new int[n];
		dest[1] = new int[n];
		// set src values
		src[0][0] = 1;
		src[0][1] = 2;
		src[1][0] = 2;
		src[1][1] = 1;
		// test smp_invert
		smp_invert(n,src,dest);
		assert(dest[0][0] == 1);
		assert(dest[0][1] == 2);
		assert(dest[1][0] == 2);
		assert(dest[1][1] == 1);
		// clean up
		delete [] src[0];
		delete [] src[1];
		delete [] src;
		delete [] dest[0];
		delete [] dest[1];
		delete [] dest;
	}

	void test_invert_2 () {
		// declare variables
		int n = 3;
		int** src = new int*[n];
		src[0] = new int[n];
		src[1] = new int[n];
		src[2] = new int[n];
		int** dest = new int*[n];
		dest[0] = new int[n];
		dest[1] = new int[n];
		dest[2] = new int[n];
		// set src values
		src[0][0] = 1;
		src[0][1] = 2;
		src[0][2] = 3;
		src[1][0] = 3;
		src[1][1] = 1;
		src[1][2] = 2;
		src[2][0] = 2;
		src[2][1] = 1;
		src[2][2] = 3;
		// test smp_invert
		smp_invert(n,src,dest);
		assert(dest[0][0] == 1);
		assert(dest[0][1] == 2);
		assert(dest[0][2] == 3);
		assert(dest[1][0] == 2);
		assert(dest[1][1] == 3);
		assert(dest[1][2] == 1);
		assert(dest[2][0] == 2);
		assert(dest[2][1] == 1);
		assert(dest[2][2] == 3);
		// clean up
		delete [] src[0];
		delete [] src[1];
		delete [] src[2];
		delete [] src;
		delete [] dest[0];
		delete [] dest[1];
		delete [] dest[2];
		delete [] dest;
	}

	void test_invert_3 () {
		// declare variables
		int n = 3;
		int** src = new int*[n];
		src[0] = new int[n];
		src[1] = new int[n];
		src[2] = new int[n];
		int** dest = new int*[n];
		dest[0] = new int[n];
		dest[1] = new int[n];
		dest[2] = new int[n];
		// set src values
		src[0][0] = 1;
		src[0][1] = 3;
		src[0][2] = 2;
		src[1][0] = 2;
		src[1][1] = 3;
		src[1][2] = 1;
		src[2][0] = 3;
		src[2][1] = 1;
		src[2][2] = 2;
		// test smp_invert
		smp_invert(n,src,dest);
		assert(dest[0][0] == 1);
		assert(dest[0][1] == 3);
		assert(dest[0][2] == 2);
		assert(dest[1][0] == 3);
		assert(dest[1][1] == 1);
		assert(dest[1][2] == 2);
		assert(dest[2][0] == 2);
		assert(dest[2][1] == 3);
		assert(dest[2][2] == 1);
		// clean up
		delete [] src[0];
		delete [] src[1];
		delete [] src[2];
		delete [] src;
		delete [] dest[0];
		delete [] dest[1];
		delete [] dest[2];
		delete [] dest;
	}

	// ---------------
	// prefer_constant
	// ---------------
	void test_prefer_constant_true () {
		// declare variables
		int n = 2;
		int m_old = 1;
		int m_new = 2;
		int * prefs = new int[n];
		// set some values
		prefs[0] = 2;
		prefs[1] = 1;
		// test smp_prefer_constant
		assert(smp_prefer_constant(n,m_old,m_new,prefs));
		// clean up
		delete [] prefs;
	}

	void test_prefer_constant_false () {
		// declare variables
		int n = 2;
		int m_old = 1;
		int m_new = 2;
		int * prefs = new int[n];
		// set some values
		prefs[0] = 1;
		prefs[1] = 2;
		// test smp_prefer_constant
		assert(!smp_prefer_constant(n,m_old,m_new,prefs));
		// clean up
		delete [] prefs;
	}

	void test_prefer_constant () {
		// declare variables
		int n = 3;
		int m_old = 1;
		int m_new = 2;
		int * prefs = new int[n];
		// set some values
		prefs[0] = 3;
		prefs[1] = 1;
		prefs[2] = 2;
		// test smp_prefer_constant
		assert(smp_prefer_constant(n,m_old,m_new,prefs));
		// clean up
		delete [] prefs;
	}

	// ------
	// prefer
	// ------
	void test_prefer_linear_true () {
		// set some values
		int n = 2;
		int m_old = 1;
		int m_new = 2;
		int prefs[2] = {2,1};
		// test smp_prefer_linear
		assert(smp_prefer_linear(n,m_old,m_new,prefs));
	}

	void test_prefer_linear_false () {
		// set some values
		int n = 2;
		int m_old = 1;
		int m_new = 2;
		int prefs[2] = {1,2};
		// test smp_prefer_linear
		assert(!smp_prefer_linear(n,m_old,m_new,prefs));
	}

	void test_prefer_linear () {
		// set some values
		int n = 3;
		int m_old = 1;
		int m_new = 2;
		int prefs[3] = {3,1,2};
		// test smp_prefer_linear
		assert(!smp_prefer_linear(n,m_old,m_new,prefs));
	}

	// ----
	// eval
	// ----
	void test_eval_1 () {
		// declare var
		int n = 1;
		int** women = new int*[1];
		women[0] = new int[1];
		women[0][0] = 1;
		int** men = new int*[1];
		men[0] = new int[1];
		men[0][0] = 1;
		int* result = new int[n];
		// test smp_eval
		smp_eval(n, women, men, result);
		CPPUNIT_ASSERT(result[0] == 1);
		// clean up
		delete [] women[0];
		delete [] women;
		delete [] men[0];
		delete [] men;
		delete [] result;
	}

	void test_eval_2 () {
		// declare var
		int n = 2;
		int** women = new int*[2];
		women[0] = new int[2];
		women[0][0] = 1;
		women[0][1] = 2;
		women[1] = new int[2];
		women[1][0] = 1;
		women[1][1] = 2;
		int** men = new int*[2];
		men[0] = new int[2];
		men[0][0] = 1;
		men[0][1] = 2;
		men[1] = new int[2];
		men[1][0] = 1;
		men[1][1] = 2;
		int* result = new int[n];
		// test smp_eval
		smp_eval(n, women, men, result);
		CPPUNIT_ASSERT(result[0] == 1);
		CPPUNIT_ASSERT(result[1] == 2);
		// clean up
		delete [] women[0];
		delete [] women[1];
		delete [] women;
		delete [] men[0];
		delete [] men[1];
		delete [] men;
		delete [] result;
	}

	void test_eval_3 () {
		// declare var
		int n = 2;
		int** women = new int*[2];
		women[0] = new int[2];
		women[0][0] = 1;
		women[0][1] = 2;
		women[1] = new int[2];
		women[1][0] = 1;
		women[1][1] = 2;
		int** men = new int*[2];
		men[0] = new int[2];
		men[0][0] = 2;
		men[0][1] = 1;
		men[1] = new int[2];
		men[1][0] = 2;
		men[1][1] = 1;
		int* result = new int[n];
		// test smp_eval
		smp_eval(n, women, men, result);
		CPPUNIT_ASSERT(result[0] == 2);
		CPPUNIT_ASSERT(result[1] == 1);
		// clean up
		delete [] women[0];
		delete [] women[1];
		delete [] women;
		delete [] men[0];
		delete [] men[1];
		delete [] men;
		delete [] result;
	}

	// -----
    // print
    // -----
	void test_print_1 () {
		// declare var
		std::ostringstream w;
		int n = 1;
		int* result = new int[1];
		// set some values
		result[0] = 1;
		// test smp_print
		smp_print(w, n, result);
		assert(w.str() == "1 1\n");
		// clean up
		delete [] result;
	}	

	void test_print_2 () {
		// decalare var
		std::ostringstream w;
		int n = 2;
		int* result = new int[2];
		// set some values
		result[0] = 1;
		result[1] = 2;
		// test smp_print
		smp_print(w, n, result);
		assert(w.str() == "1 1\n2 2\n");
		// clean up
		delete [] result;
	}

	void test_print_3 () {
		// declare var
		std::ostringstream w;
		int n = 2;
		int* result = new int[2];
		// set some values
		result[0] = 2;
		result[1] = 1;
		// test smp_print
		smp_print(w, n, result);
		assert(w.str() == "1 2\n2 1\n");
		// clean up
		delete [] result;
	}

	// -----
	// solve
	// -----
	void test_solve_1 () {
		std::istringstream r("1\n1\n1 1\n1 1\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 1\n");
	}

	void test_solve_2 () {
		std::istringstream r("1\n2\n1 1 2\n2 1 2\n1 1 2\n2 1 2\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 1\n2 2\n");
	}

	void test_solve_3 () {
		std::istringstream r("1\n2\n1 1 2\n2 1 2\n1 2 1\n2 2 1\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 2\n2 1\n");
	}

	// tests weird input format (women aren't listed in canonical order)
	void test_solve_4 () {
		std::istringstream r("1\n2\n2 1 2\n1 1 2\n1 1 2\n2 1 2\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 1\n2 2\n");
	}

	// tests case where a couple is broken apart
	void test_solve_5 () {
		std::istringstream r("1\n2\n1 2 1\n2 2 1\n1 1 2\n2 1 2\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 2\n2 1\n");
	}

	// 2 tests
	void test_solve_6 () {
		std::istringstream r("2\n1\n1 1\n1 1\n2\n1 1 2\n2 1 2\n1 1 2\n2 1 2\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 1\n1 1\n2 2\n");
	}
	
	// sphere example
	void test_solve_sphere_1 () {
		std::istringstream r("1\n4\n1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2\n1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 3\n2 2\n3 1\n4 4\n");
	}

	// sphere example
	void test_solve_sphere_2 () {
		std::istringstream r("1\n7\n1 3 4 2 1 6 7 5\n2 6 4 2 3 5 1 7\n3 6 3 5 7 2 4 1\n4 1 6 3 2 4 7 5\n5 1 6 5 3 4 7 2\n6 1 7 3 4 5 6 2\n7 5 6 2 4 3 7 1\n1 4 5 3 7 2 6 1\n2 5 6 4 7 3 2 1\n3 1 6 5 4 3 7 2\n4 3 5 6 7 2 4 1\n5 1 7 6 4 3 5 2\n6 6 3 7 5 2 4 1\n7 1 7 4 2 6 5 3\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 4\n2 5\n3 1\n4 3\n5 7\n6 6\n7 2\n");
	}

	// sphere example
	void test_solve_sphere_3 () {
		std::istringstream r("2\n4\n1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2\n1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1\n7\n1 3 4 2 1 6 7 5\n2 6 4 2 3 5 1 7\n3 6 3 5 7 2 4 1\n4 1 6 3 2 4 7 5\n5 1 6 5 3 4 7 2\n6 1 7 3 4 5 6 2\n7 5 6 2 4 3 7 1\n1 4 5 3 7 2 6 1\n2 5 6 4 7 3 2 1\n3 1 6 5 4 3 7 2\n4 3 5 6 7 2 4 1\n5 1 7 6 4 3 5 2\n6 6 3 7 5 2 4 1\n7 1 7 4 2 6 5 3\n");
		std::ostringstream w;
		smp_solve(r,w);
		assert(w.str() == "1 3\n2 2\n3 1\n4 4\n1 4\n2 5\n3 1\n4 3\n5 7\n6 6\n7 2\n");
	}

    // -----
    // suite
    // -----
    CPPUNIT_TEST_SUITE(TestSMP);
	CPPUNIT_TEST(test_read_women);
	CPPUNIT_TEST(test_read_men);
	CPPUNIT_TEST(test_read);
	CPPUNIT_TEST(test_invert_1);
	CPPUNIT_TEST(test_invert_2);
	CPPUNIT_TEST(test_invert_3);
	CPPUNIT_TEST(test_prefer_constant_true);
	CPPUNIT_TEST(test_prefer_constant_false);
	CPPUNIT_TEST(test_prefer_constant);
	CPPUNIT_TEST(test_prefer_linear_true);
	CPPUNIT_TEST(test_prefer_linear_false);
	CPPUNIT_TEST(test_prefer_linear);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST(test_solve_1);
	CPPUNIT_TEST(test_solve_2);
	CPPUNIT_TEST(test_solve_3);
	CPPUNIT_TEST(test_solve_4);
	CPPUNIT_TEST(test_solve_5);
	CPPUNIT_TEST(test_solve_6);
	CPPUNIT_TEST(test_solve_sphere_1);
	CPPUNIT_TEST(test_solve_sphere_2); 
	CPPUNIT_TEST(test_solve_sphere_3); 
    CPPUNIT_TEST_SUITE_END();};

	// ----
	// main
	// ----
	int main () {
    	using namespace std;
    	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    	cout << "TestSMP.c++" << endl;

    	CppUnit::TextTestRunner tr;
    	tr.addTest(TestSMP::suite());
    	tr.run();

    	cout << "Done." << endl;
    	return 0;}

