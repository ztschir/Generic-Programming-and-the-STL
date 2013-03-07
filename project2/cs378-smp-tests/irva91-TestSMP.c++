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

// -----------
// TestSMP
// -----------

struct TestSMP : CppUnit::TestFixture {
    //lists of the structs that I created
    Man listMen [5];
    Woman listWomen [5];

    // ----------
    // fill women
    // ----------
    void test_fill_women_1 () {
	std::istringstream r("1 2 1 4 3 5\n2 2 1 4 3 5\n3 2 1 4 3 5\n4 2 1 4 3 5\n5 2 1 4 3 5\n");
	fill_women(listWomen, r, 5);

        CPPUNIT_ASSERT(listWomen[0].ranks[0] == 2);
    	CPPUNIT_ASSERT(listWomen[1].ranks[1] == 1);
    	CPPUNIT_ASSERT(listWomen[2].ranks[2] == 4);
   	CPPUNIT_ASSERT(listWomen[3].ranks[3] == 3);
    	CPPUNIT_ASSERT(listWomen[4].ranks[4] == 5);}

    void test_fill_women_2 () {
        std::istringstream r("1 1 5 4 3 2\n2 3 4 5 2 1\n3 4 3 2 5 1\n4 1 3 5 4 2\n5 5 4 3 2 1\n");
	fill_women(listWomen, r, 5);
        CPPUNIT_ASSERT(listWomen[0].ranks[0] == 1);
    	CPPUNIT_ASSERT(listWomen[1].ranks[1] == 4);
    	CPPUNIT_ASSERT(listWomen[2].ranks[2] == 2);
   	CPPUNIT_ASSERT(listWomen[3].ranks[3] == 4);
    	CPPUNIT_ASSERT(listWomen[4].ranks[4] == 1);}

    void test_fill_women_3 () {
	std::istringstream r("1 5 3 4 2 1\n2 2 3 4 5 1\n3 1 5 2 4 3\n4 4 5 3 2 1\n5 3 1 4 5 2\n");
	fill_women(listWomen, r, 5);
        CPPUNIT_ASSERT(listWomen[0].ranks[0] == 5);
    	CPPUNIT_ASSERT(listWomen[1].ranks[1] == 3);
    	CPPUNIT_ASSERT(listWomen[2].ranks[2] == 2);
   	CPPUNIT_ASSERT(listWomen[3].ranks[3] == 2);
    	CPPUNIT_ASSERT(listWomen[4].ranks[4] == 2);}

    // --------
    // fill men
    // --------
    void test_fill_men_1 () {
	std::istringstream r("1 2 1 4 3 5\n2 2 1 4 3 5\n3 2 1 4 3 5\n4 2 1 4 3 5\n5 2 1 4 3 5\n");
        fill_men(listMen, listWomen, r, 5);
        CPPUNIT_ASSERT(listMen[0].ranks[0] == 2);
    	CPPUNIT_ASSERT(listMen[1].ranks[1] == 1);
    	CPPUNIT_ASSERT(listMen[2].ranks[2] == 4);
   	CPPUNIT_ASSERT(listMen[3].ranks[3] == 3);
    	CPPUNIT_ASSERT(listMen[4].ranks[4] == 5);}

    void test_fill_men_2 () {
        std::istringstream r("1 1 5 4 3 2\n2 3 4 5 2 1\n3 4 3 2 5 1\n4 1 3 5 4 2\n5 5 4 3 2 1\n");
        fill_men(listMen, listWomen, r, 5);
        CPPUNIT_ASSERT(listMen[0].ranks[0] == 1);
    	CPPUNIT_ASSERT(listMen[1].ranks[1] == 4);
    	CPPUNIT_ASSERT(listMen[2].ranks[2] == 2);
   	CPPUNIT_ASSERT(listMen[3].ranks[3] == 4);
    	CPPUNIT_ASSERT(listMen[4].ranks[4] == 1);}

    void test_fill_men_3 () {
	std::istringstream r("1 5 3 4 2 1\n2 2 3 4 5 1\n3 1 5 2 4 3\n4 4 5 3 2 1\n5 3 1 4 5 2\n");
        fill_men(listMen, listWomen, r, 5);
        CPPUNIT_ASSERT(listMen[0].ranks[0] == 5);
    	CPPUNIT_ASSERT(listMen[1].ranks[1] == 3);
    	CPPUNIT_ASSERT(listMen[2].ranks[2] == 2);
   	CPPUNIT_ASSERT(listMen[3].ranks[3] == 2);
    	CPPUNIT_ASSERT(listMen[4].ranks[4] == 2);}

    // ----
    // print
    // ----
    void test_print_1 () {
        std::ostringstream w;
        print (listMen, w, 5);
	CPPUNIT_ASSERT(w.str() == "1 0\n2 0\n3 0\n4 0\n5 0\n");}

    void test_print_2 () {
        std::ostringstream w;
	listMen[0].engagedTo = 5;
	listMen[1].engagedTo = 4;
	listMen[2].engagedTo = 2;
	listMen[3].engagedTo = 1;
	listMen[4].engagedTo = 3;
        print (listMen, w, 5);
	CPPUNIT_ASSERT(w.str() == "1 5\n2 4\n3 2\n4 1\n5 3\n");}

    void test_print_3 () {
        std::ostringstream w;
	listMen[0].engagedTo = 4;
	listMen[1].engagedTo = 2;
	listMen[2].engagedTo = 1;
	listMen[3].engagedTo = 5;
	listMen[4].engagedTo = 3;
        print (listMen, w, 5);
	CPPUNIT_ASSERT(w.str() == "1 4\n2 2\n3 1\n4 5\n5 3\n");}

    // ---------------
    // woman is single
    // ---------------
    void test_woman_is_single_1 () {
        woman_is_single (listWomen, listMen, 3, 2);
        CPPUNIT_ASSERT(listWomen[3].engaged == 3);
	CPPUNIT_ASSERT(listMen[2].engagedTo == 4);
	CPPUNIT_ASSERT(listMen[2].engaged == true);
	CPPUNIT_ASSERT(listMen[2].indexOfProposed == 1);}

    void test_woman_is_single_2 () {
        woman_is_single (listWomen, listMen, 4, 1);
        CPPUNIT_ASSERT(listWomen[4].engaged == 2);
	CPPUNIT_ASSERT(listMen[1].engagedTo == 5);
	CPPUNIT_ASSERT(listMen[1].engaged == true);
	CPPUNIT_ASSERT(listMen[1].indexOfProposed == 1);}

    void test_woman_is_single_3 () {
        woman_is_single (listWomen, listMen, 0, 4);
        CPPUNIT_ASSERT(listWomen[0].engaged == 5);
	CPPUNIT_ASSERT(listMen[4].engagedTo == 1);
	CPPUNIT_ASSERT(listMen[4].engaged == true);
	CPPUNIT_ASSERT(listMen[4].indexOfProposed == 1);}

    // ------------
    // woman switch
    // ------------
    void test_woman_switch_1 () {
	woman_switch(listWomen, listMen, 2, 3, 1);
	CPPUNIT_ASSERT(listMen[2].indexOfProposed == 1);
	CPPUNIT_ASSERT(listMen[2].engaged == true);
	CPPUNIT_ASSERT(listMen[2].engagedTo == 2);
	CPPUNIT_ASSERT(listMen[3].engaged == false);
	CPPUNIT_ASSERT(listMen[3].engagedTo == 0);
	CPPUNIT_ASSERT(listWomen[1].engaged = 3);}

    void test_woman_switch_2 () {
	woman_switch(listWomen, listMen, 3, 4, 2);
	CPPUNIT_ASSERT(listMen[3].indexOfProposed == 1);
	CPPUNIT_ASSERT(listMen[3].engaged == true);
	CPPUNIT_ASSERT(listMen[3].engagedTo == 3);
	CPPUNIT_ASSERT(listMen[4].engaged == false);
	CPPUNIT_ASSERT(listMen[4].engagedTo == 0);
	CPPUNIT_ASSERT(listWomen[2].engaged = 4);}

    void test_woman_switch_3 () {
	woman_switch(listWomen, listMen, 1, 0, 2);
	CPPUNIT_ASSERT(listMen[1].indexOfProposed == 1);
	CPPUNIT_ASSERT(listMen[1].engaged == true);
	CPPUNIT_ASSERT(listMen[1].engagedTo == 3);
	CPPUNIT_ASSERT(listMen[0].engaged == false);
	CPPUNIT_ASSERT(listMen[0].engagedTo == 0);
	CPPUNIT_ASSERT(listWomen[2].engaged = 2);}

    // ---------
    // smp solve
    // ---------
    void test_smp_solve_1 (){
	std::istringstream r("4\n1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2\n1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1");
	std::ostringstream w;
	smp_solve(r, w, 1);
	CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n4 4\n");
    }

    void test_smp_solve_2 (){
	std::istringstream r("3\n1 3 1 2\n2 2 1 3\n3 1 3 2\n1 3 2 1\n2 2 3 1\n3 3 1 2\n");
	std::ostringstream w;
	smp_solve(r, w, 1);
	CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n");
    }

    void test_smp_solve_3 (){
	std::istringstream r("5\n1 4 3 5 1 2\n2 2 1 3 5 4\n3 5 1 3 4 2\n4 4 3 1 2 5\n5 1 3 2 4 5\n1 5 3 2 4 1\n2 2 5 3 1 4\n3 5 3 1 2 4\n4 3 2 5 4 1\n5 1 5 4 3 2");
	std::ostringstream w;
	smp_solve(r, w, 1);
	CPPUNIT_ASSERT(w.str() == "1 5\n2 2\n3 3\n4 4\n5 1\n");
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);

    //fill woman test cases
    CPPUNIT_TEST(test_fill_women_1);
    CPPUNIT_TEST(test_fill_women_2);
    CPPUNIT_TEST(test_fill_women_3);

    //fill men test cases
    CPPUNIT_TEST(test_fill_men_1);
    CPPUNIT_TEST(test_fill_men_2);
    CPPUNIT_TEST(test_fill_men_3);

    //print test cases
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);

    //woman single test cases
    CPPUNIT_TEST(test_woman_is_single_1);
    CPPUNIT_TEST(test_woman_is_single_2);
    CPPUNIT_TEST(test_woman_is_single_3);

    //woman switch test cases
    CPPUNIT_TEST(test_woman_switch_1);
    CPPUNIT_TEST(test_woman_switch_2);
    CPPUNIT_TEST(test_woman_switch_3);

    //smp solve test cases
    CPPUNIT_TEST(test_smp_solve_1);
    CPPUNIT_TEST(test_smp_solve_2);
    CPPUNIT_TEST(test_smp_solve_3);

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

