/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestSMP.c++ -o TestSMP.c++.app
    % valgrind TestSMP.c++.app >& TestSMP.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstreamen, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "SMP.h"

// -------
// TestSMP
// -------

/**
 * Unit tests
 */
struct TestSMP : CppUnit::TestFixture {
    // ---------------
    // readTestCaseSMP
    // ---------------
	
	/**
     * Test the readTestCaseSMP function
     */
	void test_readTestCaseSMP_1 () {
	    std::istringstream r("1\n1\n1 1\n1 1");
	    const int t = readTestCaseSMP(r);
	    CPPUNIT_ASSERT (t == 1);
	}
	
	void test_readTestCaseSMP_2 () {
	    std::istringstream r("4\n2\n1 1 2\n2 1 2\n1 1 2\n2 2 1\n2\n1 1 2\n2 2 1\n1 2 1\n2 2 1\n3\n1 3 2 1\n2 2 3 1\n3 3 1 2\n1 2 1 3\n2 1 2 3\n3 2 3 1\n3\n1 3 2 1\n2 2 3 1\n3 3 1 2\n1 2 3 1\n2 3 2 1\n3 2 1 3");
	    const int t = readTestCaseSMP(r);
	    CPPUNIT_ASSERT (t == 4);
	}
	
	void test_readTestCaseSMP_3 () {
	    std::istringstream r("2\n4\n1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2\n1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1\n7\n1 3 4 2 1 6 7 5\n2 6 4 2 3 5 1 7\n3 6 3 5 7 2 4 1\n4 1 6 3 2 4 7 5\n5 1 6 5 3 4 7 2\n6 1 7 3 4 5 6 2\n7 5 6 2 4 3 7 1\n1 4 5 3 7 2 6 1\n2 5 6 4 7 3 2 1\n3 1 6 5 4 3 7 2\n4 3 5 6 7 2 4 1\n5 1 7 6 4 3 5 2\n6 6 3 7 5 2 4 1\n7 1 7 4 2 6 5 3");
	    const int t = readTestCaseSMP(r);
	    CPPUNIT_ASSERT (t == 2);
	}
  	
	// -------
    // readSMP
    // -------
    
	/**
     * Test the readSMP function
     */
	void test_readSMP_1 () {
	  std::istringstream r("1\n1 1\n1 1");
	  int unengagedMen[501];

	  const int num_pairs = readSMP(r, men, women, unengagedMen);
	  
	  CPPUNIT_ASSERT(num_pairs == 1);
	  for(int i = 1; i <= num_pairs; i++) {
	    CPPUNIT_ASSERT(unengagedMen[i] == i); // sorting arr since order does not matter
	    CPPUNIT_ASSERT(women[i].manEngagedWith == 0); // engaged to dummy person
		CPPUNIT_ASSERT(men[i].position == 1); // ptr set to the begining of pref list
	  }
	  
	  CPPUNIT_ASSERT(women[1].pref[0] == 2);   // start pref from 0 due dummy person
	  CPPUNIT_ASSERT(women[1].pref[1] == 1);
	  
	  CPPUNIT_ASSERT(men[1].pref[1] == 1);   // start from 1
	}
	
	void test_readSMP_2 () {
	  std::istringstream r("2\n1 1 2\n2 1 2\n1 1 2\n2 2 1");
	  int unengagedMen[501];

	  const int num_pairs = readSMP(r, men, women, unengagedMen);
	  
	  CPPUNIT_ASSERT(num_pairs == 2);
	  for(int i = 1; i <= num_pairs; i++) {
	    CPPUNIT_ASSERT(unengagedMen[i] == i); // sorting arr since order does not matter
	    CPPUNIT_ASSERT(women[i].manEngagedWith == 0); // engaged to dummy person
		CPPUNIT_ASSERT(men[i].position == 1); // ptr set to the begining of pref list
	  }
	  
	  CPPUNIT_ASSERT(women[1].pref[0] == 3);   // start pref from 0 due dummy person
	  CPPUNIT_ASSERT(women[1].pref[1] == 1);
	  CPPUNIT_ASSERT(women[1].pref[2] == 2);
	  CPPUNIT_ASSERT(women[1].pref[0] == 3);   // start pref from 0 due dummy person
	  CPPUNIT_ASSERT(women[2].pref[1] == 1);
	  CPPUNIT_ASSERT(women[2].pref[2] == 2);
	  
	  CPPUNIT_ASSERT(men[1].pref[1] == 1);   // start from 1
	  CPPUNIT_ASSERT(men[1].pref[2] == 2);
	  CPPUNIT_ASSERT(men[2].pref[1] == 2);   // start from 1
	  CPPUNIT_ASSERT(men[2].pref[2] == 1);
	}
	
	void test_readSMP_3 () {
	  std::istringstream r("3\n1 3 2 1\n2 2 3 1\n3 3 1 2\n1 2 1 3\n2 1 2 3\n3 2 3 1");
	  int unengagedMen[501];

	  const int num_pairs = readSMP(r, men, women, unengagedMen);
	  
	  CPPUNIT_ASSERT(num_pairs == 3);
	  for(int i = 1; i <= num_pairs; i++) {
	    CPPUNIT_ASSERT(unengagedMen[i] == i); // sorting arr since order does not matter
	    CPPUNIT_ASSERT(women[i].manEngagedWith == 0); // engaged to dummy person
		CPPUNIT_ASSERT(men[i].position == 1); // ptr set to the begining of pref list
	  }
	  
	  CPPUNIT_ASSERT(women[1].pref[0] == 4);   // start pref from 0 due dummy person
	  CPPUNIT_ASSERT(women[1].pref[1] == 3);
	  CPPUNIT_ASSERT(women[1].pref[2] == 2);
	  CPPUNIT_ASSERT(women[1].pref[3] == 1);
	  CPPUNIT_ASSERT(women[2].pref[0] == 4);   // start pref from 0 due dummy person
	  CPPUNIT_ASSERT(women[2].pref[1] == 3);
	  CPPUNIT_ASSERT(women[2].pref[2] == 1);
	  CPPUNIT_ASSERT(women[2].pref[3] == 2);
	  CPPUNIT_ASSERT(women[3].pref[0] == 4);   // start pref from 0 due dummy person
	  CPPUNIT_ASSERT(women[3].pref[1] == 2);
	  CPPUNIT_ASSERT(women[3].pref[2] == 3);
	  CPPUNIT_ASSERT(women[3].pref[3] == 1);
	  
	  CPPUNIT_ASSERT(men[1].pref[1] == 2);   // start from 1
	  CPPUNIT_ASSERT(men[1].pref[2] == 1);
	  CPPUNIT_ASSERT(men[1].pref[3] == 3);
	  CPPUNIT_ASSERT(men[2].pref[1] == 1);   // start from 1
	  CPPUNIT_ASSERT(men[2].pref[2] == 2);
	  CPPUNIT_ASSERT(men[2].pref[3] == 3);
	  CPPUNIT_ASSERT(men[3].pref[1] == 2);   // start from 1
	  CPPUNIT_ASSERT(men[3].pref[2] == 3);
	  CPPUNIT_ASSERT(men[3].pref[3] == 1);
	}
	
	// ------
	// evalSMP
	// ------
	
	/**
     * Test the evalSMP function
     */
	void test_evalSMP_1 () {
	  int unengagedMen[501];

	  int num_pairs;
	  
	  num_pairs = 1;
	  for(int i = 1; i <= num_pairs; i++) {
	    unengagedMen[i] = i; // sorting arr since order does not matter
	    women[i].manEngagedWith = 0; // engaged to dummy person
		men[i].position = 1; // ptr set to the begining of pref list
	  }
	  
	  women[1].pref[0] = 2;   // start pref from 0 due dummy person
	  women[1].pref[1] = 1;
	  
	  men[1].pref[1] = 1;   // start from 1
	  
	  CPPUNIT_ASSERT(women[1].manEngagedWith = 1);
	}
	
	void test_evalSMP_2 () {
	  int unengagedMen[501];

	  int num_pairs;
	  
	  num_pairs = 2;
	  for(int i = 1; i <= num_pairs; i++) {
	    unengagedMen[i] = i; // sorting arr since order does not matter
	    women[i].manEngagedWith = 0; // engaged to dummy person
		men[i].position = 1; // ptr set to the begining of pref list
	  }
	  
	  women[1].pref[0] = 3;   // start pref from 0 due dummy person
	  women[1].pref[1] = 1;
	  women[1].pref[2] = 2;
	  women[1].pref[0] = 3;   // start pref from 0 due dummy person
	  women[2].pref[1] = 1;
	  women[2].pref[2] = 2;
	  
	  men[1].pref[1] = 1;   // start from 1
	  men[1].pref[2] = 2;
	  men[2].pref[1] = 2;   // start from 1
	  men[2].pref[2] = 1;
	
	  CPPUNIT_ASSERT(women[1].manEngagedWith = 1);
	  CPPUNIT_ASSERT(women[2].manEngagedWith = 2);
	}
	
	void test_evalSMP_3 () {
	  int unengagedMen[501];

	  int num_pairs;
	  
	  num_pairs = 3;
	  for(int i = 1; i <= num_pairs; i++) {
	    unengagedMen[i] = i; // sorting arr since order does not matter
	    women[i].manEngagedWith = 0; // engaged to dummy person
		men[i].position = 1; // ptr set to the begining of pref list
	  }
	  
	  women[1].pref[0] = 4;   // start pref from 0 due dummy person
	  women[1].pref[1] = 3;
	  women[1].pref[2] = 2;
	  women[1].pref[3] = 1;
	  women[2].pref[0] = 4;   // start pref from 0 due dummy person
	  women[2].pref[1] = 3;
	  women[2].pref[2] = 1;
	  women[2].pref[3] = 2;
	  women[3].pref[0] = 4;   // start pref from 0 due dummy person
	  women[3].pref[1] = 2;
	  women[3].pref[2] = 3;
	  women[3].pref[3] = 1;
	  
	  men[1].pref[1] = 2;   // start from 1
	  men[1].pref[2] = 1;
	  men[1].pref[3] = 3;
	  men[2].pref[1] = 1;   // start from 1
	  men[2].pref[2] = 2;
	  men[2].pref[3] = 3;
	  men[3].pref[1] = 2;   // start from 1
	  men[3].pref[2] = 3;
	  men[3].pref[3] = 1;
	
	  CPPUNIT_ASSERT(women[1].manEngagedWith = 3);
	  CPPUNIT_ASSERT(women[2].manEngagedWith = 2);
	  CPPUNIT_ASSERT(women[3].manEngagedWith = 1);
	}

	// --------
	// writeSMP
	// --------
	
	/**
     * Test the writeSMP function
     */
	void test_writeSMP_1 () {
	  std::ostringstream o;
	  int num_pairs = 1;

	  
	  women[1].manEngagedWith = 1;
	  women[1].pref[0] = 2; // dummy 
	  women[1].pref[1] = 1;
	  
	  writeSMP(o, women, num_pairs);
	  CPPUNIT_ASSERT(o.str() == "1 1\n");
	}
	
	void test_writeSMP_2 () {
	  std::ostringstream o;
	  int num_pairs = 2;
	  
	  women[1].manEngagedWith = 1;
	  women[1].pref[0] = 3; // dummy 
	  women[1].pref[1] = 1;
	  women[1].pref[2] = 2;
	  women[2].manEngagedWith = 2;
	  women[2].pref[0] = 3; // dummy 
	  women[2].pref[1] = 2;
	  women[2].pref[2] = 1;
	  
	  writeSMP(o, women, num_pairs);
	  CPPUNIT_ASSERT(o.str() == "1 1\n2 2\n");
	}
	
	void test_writeSMP_3 () {
	  std::ostringstream o;
	  int num_pairs = 3;

	  
	  women[1].manEngagedWith = 3;
	  women[1].pref[0] = 4; // dummy 
	  women[1].pref[1] = 3;
	  women[1].pref[2] = 2;
	  women[1].pref[3] = 1;
	  women[2].manEngagedWith = 2;
	  women[2].pref[0] = 4; // dummy 
	  women[2].pref[1] = 2;
	  women[2].pref[2] = 3;
	  women[2].pref[3] = 1;
	  women[3].manEngagedWith = 1;
	  women[3].pref[0] = 4; // dummy 
	  women[3].pref[1] = 3;
	  women[3].pref[2] = 1;
	  women[3].pref[3] = 2;
	  
	  writeSMP(o, women, num_pairs);
	  CPPUNIT_ASSERT(o.str() == "1 3\n2 1\n3 2\n");
	}
	
	// --------
	// solveSMP
	// --------
	
	/**
     * Test the solveSMP function
     */
	void test_solveSMP_1 () {
	  std::istringstream r("1\n1\n1 1\n1 1");
	  std::ostringstream w;
	  solveSMP(r, w);
	  CPPUNIT_ASSERT(w.str() == "1 1\n");
    }
	
	void test_solveSMP_2 () {
	  std::istringstream r("4\n2\n1 1 2\n2 1 2\n1 1 2\n2 2 1\n2\n1 1 2\n2 2 1\n1 2 1\n2 2 1\n3\n1 3 2 1\n2 2 3 1\n3 3 1 2\n1 2 1 3\n2 1 2 3\n3 2 3 1\n3\n1 3 2 1\n2 2 3 1\n3 3 1 2\n1 2 3 1\n2 3 2 1\n3 2 1 3");
	  std::ostringstream w;
	  solveSMP(r, w);
	  CPPUNIT_ASSERT(w.str() == "1 1\n2 2\n1 1\n2 2\n1 3\n2 1\n3 2\n1 3\n2 2\n3 1\n");
    }
	
	void test_solveSMP_3 () {
	  std::istringstream r("2\n4\n1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2\n1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1\n7\n1 3 4 2 1 6 7 5\n2 6 4 2 3 5 1 7\n3 6 3 5 7 2 4 1\n4 1 6 3 2 4 7 5\n5 1 6 5 3 4 7 2\n6 1 7 3 4 5 6 2\n7 5 6 2 4 3 7 1\n1 4 5 3 7 2 6 1\n2 5 6 4 7 3 2 1\n3 1 6 5 4 3 7 2\n4 3 5 6 7 2 4 1\n5 1 7 6 4 3 5 2\n6 6 3 7 5 2 4 1\n7 1 7 4 2 6 5 3");
	  std::ostringstream w;
	  solveSMP(r, w);
	  CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n4 4\n1 4\n2 5\n3 1\n4 3\n5 7\n6 6\n7 2\n");
    }

    // -----
    // suite
    // -----

    /**
     * Call the unit tests
     */

    	CPPUNIT_TEST_SUITE(TestSMP);
    	CPPUNIT_TEST(test_readTestCaseSMP_1);
	CPPUNIT_TEST(test_readTestCaseSMP_2);
	CPPUNIT_TEST(test_readTestCaseSMP_3);
	CPPUNIT_TEST(test_readSMP_1);
	CPPUNIT_TEST(test_readSMP_2);
	CPPUNIT_TEST(test_readSMP_3);
	CPPUNIT_TEST(test_evalSMP_1);
	CPPUNIT_TEST(test_evalSMP_2);
	CPPUNIT_TEST(test_evalSMP_3);
	CPPUNIT_TEST(test_writeSMP_1);
	CPPUNIT_TEST(test_writeSMP_2);
	CPPUNIT_TEST(test_writeSMP_2);
	CPPUNIT_TEST(test_solveSMP_1);
	CPPUNIT_TEST(test_solveSMP_2);
	CPPUNIT_TEST(test_solveSMP_3);
    	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

/**
 * Test the SMP program
 */
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestSMP.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestSMP::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
