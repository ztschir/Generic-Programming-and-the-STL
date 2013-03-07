#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "SMP.h"

struct TestSMP : CppUnit::TestFixture {

    void test_solve1 () {
        std::istringstream r("1\n4\n1 4 3 2 1\n2 1 4 2 3\n3 4 3 2 1\n4 3 2 1 4\n1 1 2 3 4\n2 2 3 4 1\n3 4 3 1 2\n4 1 4 3 2\n");
        std::ostringstream w;
        smp_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 4\n2 1\n3 2\n4 3\n");}

    void test_solve2 () {
        std::istringstream r("1\n6\n1 4 5 3 2 6 1\n2 6 4 2 5 1 3\n3 6 5 4 3 2 1\n4 4 5 2 1 6 3\n5 5 4 3 2 1 6\n6 1 5 2 4 3 6\n1 1 5 3 6 4 2\n2 5 2 6 4 3 1\n3 4 5 3 6 1 2\n4 6 2 1 3 4 5\n5 6 4 2 1 3 5\n6 6 5 3 4 1 2\n");
        std::ostringstream w;
        smp_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2\n2 4\n3 6\n4 5\n5 3\n6 1\n");}

    void test_solve3 () {
        std::istringstream r("2\n2\n1 2 1\n2 2 1\n1 1 2\n2 1 2\n3\n1 1 2 3\n2 1 3 2\n3 2 3 1\n1 2 1 3\n2 3 2 1\n3 2 1 3\n");
        std::ostringstream w;
        smp_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "1 2\n2 1\n1 3\n2 1\n3 2\n");}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestSMP.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestSMP::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}