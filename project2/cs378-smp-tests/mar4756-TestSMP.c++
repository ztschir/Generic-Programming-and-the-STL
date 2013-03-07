// --------------------------------
// projects/SMP/TestSMP.c++
// Copyright (C) 2011
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
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestSMP.c++ -o TestSMP.c++.app
    % valgrind TestSMP.c++.app >& TestSMP.c++.out
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
using namespace std;

// -----------
// TestSMP
// -----------

struct TestSMP : CppUnit::TestFixture {
    // ----
    // read
    // ----

    void test_read1 () {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = SMP_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    1);
        CPPUNIT_ASSERT(j ==   10);}

    void test_read2 () {
        std::istringstream r("5 300\n");
        int i;
        int j;
        const bool b = SMP_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==    5);
        CPPUNIT_ASSERT(j ==   300);}

    void test_read3 () {
        std::istringstream r("21 1\n");
        int i;
        int j;
        const bool b = SMP_read(r, i, j);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i ==   21);
        CPPUNIT_ASSERT(j ==   1);}

     //compare men tests
	void test_compareMen1(){
		bool j = compareMen(4, 3, 5);
		CPPUNIT_ASSERT(j ==  false);
	}

	void test_compareMen2(){
                bool j = compareMen(2, 1, 16);
                CPPUNIT_ASSERT(j ==  false);
        }

	void test_compareMen3(){
                bool j = compareMen(11, 1, 3);
                CPPUNIT_ASSERT(j ==  false);
        }

      //womenPrefArray tests
	void test_womenPrefArray1(){
                bool j = womenPrefArray(-4);
                CPPUNIT_ASSERT(j ==  true);
        }

        void test_womenPrefArray2(){
                bool j = womenPrefArray(-2);
                CPPUNIT_ASSERT(j ==  true);
        }

        void test_womenPrefArray3(){
                bool j = womenPrefArray(-11);
                CPPUNIT_ASSERT(j ==  true);
        }

	//menPrefArray tests
	 void test_menPrefArray1(){
                bool j = menPrefArray(-99);
                CPPUNIT_ASSERT(j ==  true);
        }

        void test_menPrefArray2(){
                bool j = menPrefArray(-300);
                CPPUNIT_ASSERT(j ==  true);
        }
    
        void test_menPrefArray3(){
                bool j = menPrefArray(-200);
                CPPUNIT_ASSERT(j ==  true);
  	}

	//freeManList tests
	void test_freeManList1(){
        	int i = freeManList(-1);
                CPPUNIT_ASSERT(i ==  1);
	}

	void test_freeManList2(){
       		int i = freeManList(-99);
                CPPUNIT_ASSERT(i ==  99);
	 }

	void test_freeManList3(){
                int i = freeManList(-1000);
                CPPUNIT_ASSERT(i ==  1000);
        }

	//identifyWoman tests
        void test_identifyWoman1(){
		int men[] = {1,2,3}; 
		int women[] = {1,2,3};
                bool test = identifyWoman(-9, men, women);
                CPPUNIT_ASSERT(test ==  false);
        }

	void test_identifyWoman2(){
                int men[] = {12,56,44};
                int women[] = {23,43,45};
                bool test = identifyWoman(-3, men, women);
                CPPUNIT_ASSERT(test ==  false);
        }

	void test_identifyWoman3(){
                int men[] = {7,5,9};
                int women[] = {11,3,5};
                bool test = identifyWoman(-91, men, women);
                CPPUNIT_ASSERT(test == false);
        }

	//solve tests
	void test_solve1(){
                int val = 11;
		std::istringstream in("21 1\n");	
		std::ostringstream out("32 1\n");	
                bool test = SMP_solve(in, out, val);
                CPPUNIT_ASSERT(test == true);
        }

	void test_solve2(){
                int val = 99;
                std::istringstream in("24523 1\n");
                std::ostringstream out("324 1\n");
                bool test = SMP_solve(in, out, val);
                CPPUNIT_ASSERT(test == true);
        }
	
	void test_solve3(){
                int val = -233;
                std::istringstream in("10000000 1\n");
                std::ostringstream out("9999999 1\n");
                bool test = SMP_solve(in, out, val);
                CPPUNIT_ASSERT(test == true);
        }


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);  
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_compareMen1);
    CPPUNIT_TEST(test_compareMen2);
    CPPUNIT_TEST(test_compareMen3);  
    CPPUNIT_TEST(test_womenPrefArray1);
    CPPUNIT_TEST(test_womenPrefArray2);
    CPPUNIT_TEST(test_womenPrefArray3);
    CPPUNIT_TEST(test_menPrefArray1);
    CPPUNIT_TEST(test_menPrefArray2);
    CPPUNIT_TEST(test_menPrefArray3);
    CPPUNIT_TEST(test_freeManList1);
    CPPUNIT_TEST(test_freeManList2);
    CPPUNIT_TEST(test_freeManList3);
    CPPUNIT_TEST(test_identifyWoman1);
    CPPUNIT_TEST(test_identifyWoman2);
    CPPUNIT_TEST(test_identifyWoman3);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
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
