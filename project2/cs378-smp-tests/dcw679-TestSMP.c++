// --------------------------------
// TestSMP.c++
// Chris Renke/Dillon Williams
// Glenn P. Downing - CS378
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
#include <map>
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
    // solve
    // ----

    void test_solve_1 () {
        int num_proposors = 1;
        Man one;
        one.man_id = 1;
        one.proposed_to = 0;
        one.preferences[0] = 1;
        one.preferences[1] = 1;
        list<Man> free_men_list;
        free_men_list.push_back(one);
        Woman woman_list[501];
        woman_list[1].engaged_to = 0;
        woman_list[1].man_priorities[0] = 501;
        woman_list[1].man_priorities[1] = 1;
        ostringstream w;
        SMP_solve(num_proposors, woman_list, free_men_list, w);
        CPPUNIT_ASSERT(w.str() == "1 1\n");}


    void test_solve_2 () {
        int num_proposors = 2;
        Man one;
        one.man_id = 1;
        one.proposed_to = 0;
        one.preferences[0] = 1;
        one.preferences[1] = 1;
        one.preferences[2] = 2;
        Man two;
        two.man_id = 2;
        two.proposed_to = 0;
        two.preferences[0] = 1;
        two.preferences[1] = 2;
        two.preferences[2] = 1;

        list<Man> free_men_list;
        free_men_list.push_back(one);
        free_men_list.push_back(two);
        Woman woman_list[501];
        woman_list[1].engaged_to = 0;
        woman_list[1].man_priorities[0] = 501;
        woman_list[1].man_priorities[1] = 2;
        woman_list[1].man_priorities[2] = 1;
        woman_list[2].engaged_to = 0;
        woman_list[2].man_priorities[0] = 501;
        woman_list[2].man_priorities[1] = 1;
        woman_list[2].man_priorities[2] = 1;

        ostringstream w;
        SMP_solve(num_proposors, woman_list, free_men_list, w);
        CPPUNIT_ASSERT(w.str() == "1 1\n2 2\n");}


    void test_solve_3 () {
        int num_proposors = 2;
        Man one;
        one.man_id = 1;
        one.proposed_to = 0;
        one.preferences[0] = 1;
        one.preferences[1] = 2;
        one.preferences[2] = 1;
        Man two;
        two.man_id = 2;
        two.proposed_to = 0;
        two.preferences[0] = 1;
        two.preferences[1] = 1;
        two.preferences[2] = 2;

        list<Man> free_men_list;
        free_men_list.push_back(one);
        free_men_list.push_back(two);
        Woman woman_list[501];
        woman_list[1].engaged_to = 0;
        woman_list[1].man_priorities[0] = 501;
        woman_list[1].man_priorities[1] = 1;
        woman_list[1].man_priorities[2] = 2;
        woman_list[2].engaged_to = 0;
        woman_list[2].man_priorities[0] = 501;
        woman_list[2].man_priorities[1] = 2;
        woman_list[2].man_priorities[2] = 1;

        ostringstream w;
        SMP_solve(num_proposors, woman_list, free_men_list, w);
        CPPUNIT_ASSERT(w.str() == "1 2\n2 1\n");}

    // -----
    // setup
    // -----

    // with two cases
    void test_setup_1 () {
        istringstream r("2\n1\n1 1\n1 1\n2\n1 1 2\n2 1 2\n1 1 2\n2 1 2");
        ostringstream w;
        SMP_setup(r, w);
        CPPUNIT_ASSERT(w.str() == "1 1\n1 1\n2 2\n");}

    // one case -- test
    void test_setup_2 () {
        istringstream r("1\n2\n1 1 2\n2 1 2\n1 2 1\n2 2 1");
        ostringstream w;
        SMP_setup(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2\n2 1\n");}
    
    // example from sphere
    void test_setup_3 () {
        istringstream r("1\n4\n1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2\n1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1");
        ostringstream w;
        SMP_setup(r, w);
        CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n4 4\n");}
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_solve_1);
    CPPUNIT_TEST(test_solve_2);
    CPPUNIT_TEST(test_solve_3);
    CPPUNIT_TEST(test_setup_1);
    CPPUNIT_TEST(test_setup_2);
    CPPUNIT_TEST(test_setup_3);
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
