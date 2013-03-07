#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "SMP.h"

struct TestSMP : CppUnit::TestFixture {


// std::istringstream woman2("2 2 1 3 4\n");
// std::istringstream woman3("3 1 3 4 2\n");
// std::istringstream woman4("4 4 3 1 2\n");


    // =====================
    // Initializer Methods
    // =====================


    Woman getTestWoman1 () {    
        const int NUM_COUPLES = 4;
        Woman woman;
        std::istringstream woman_input("1 4 3 1 2\n");
        smp_read_multiple(woman_input, woman.preferences, NUM_COUPLES+1);
        woman.populatePreferencesByMan(NUM_COUPLES);

        return woman;
    }

    Man getTestMan1 () {    
        const int NUM_COUPLES = 4;
        Man man;
        std::istringstream man_input("1 4 3 1 2\n");
        smp_read_multiple(man_input, man.preferences, NUM_COUPLES+1);

        return man;
    }

    // =====================
    // Dummy Test
    // =====================

    void test_true () {
        CPPUNIT_ASSERT(true);}


    // =====================
    // Woman
    // =====================

    void test_woman_populatePreferencesByMan() {
        const int NUM_COUPLES = 4;
        Woman woman;
        std::istringstream woman_input("1 4 3 1 2\n");
        smp_read_multiple(woman_input, woman.preferences, NUM_COUPLES+1);
        woman.populatePreferencesByMan(NUM_COUPLES);
        CPPUNIT_ASSERT(woman.preferences_by_man[4] == 1);
        CPPUNIT_ASSERT(woman.preferences_by_man[3] == 2);
        CPPUNIT_ASSERT(woman.preferences_by_man[1] == 3);
        CPPUNIT_ASSERT(woman.preferences_by_man[2] == 4);
    }

    void test_woman_engageTo() {
        Woman woman = getTestWoman1();
        woman.engageTo(3);

        CPPUNIT_ASSERT(woman.engaged_to_man == 3);
    }

    void test_woman_foundBetterMan1(){
        Woman woman = getTestWoman1();
        woman.engageTo(3);
        bool result = woman.foundBetterMan(4);

        CPPUNIT_ASSERT(result == true);
    }


    void test_woman_foundBetterMan2(){
        Woman woman = getTestWoman1();
        woman.engageTo(3);
        bool result = woman.foundBetterMan(1);

        CPPUNIT_ASSERT(result == false);
    }


    void test_woman_foundBetterMan3(){
        Woman woman = getTestWoman1();
        bool result = woman.foundBetterMan(4);

        CPPUNIT_ASSERT(result == true);
    }

    void test_woman_isNotEngaged1(){
        Woman woman = getTestWoman1();

        CPPUNIT_ASSERT(woman.isNotEngaged());
    }

    void test_woman_isNotEngaged2(){
        Woman woman = getTestWoman1();
        woman.engageTo(1);

        CPPUNIT_ASSERT(!woman.isNotEngaged());
    }

    void test_woman_isNotEngaged3(){
        Woman woman = getTestWoman1();
        woman.engageTo(1);
        woman.engageTo(2);

        CPPUNIT_ASSERT(!woman.isNotEngaged());
    }

    void test_woman_reset(){
        Woman woman = getTestWoman1();
        woman.engageTo(3);
        woman.reset();

        CPPUNIT_ASSERT(woman.isNotEngaged());
    }

    // =====================
    // Man
    // =====================

    void test_man_getNextPreference1(){
        Man man = getTestMan1();
        int result = man.getNextPreference();

        CPPUNIT_ASSERT(result == 4);
    }

    void test_man_getNextPreference2(){
        Man man = getTestMan1();

        man.getNextPreference();
        int result = man.getNextPreference();

        CPPUNIT_ASSERT(result == 3);
    }

    void test_man_getNextPreference3(){
        Man man = getTestMan1();

        man.getNextPreference();
        man.getNextPreference();
        man.getNextPreference();
        int result = man.getNextPreference();

        CPPUNIT_ASSERT(result == 2);
    }

    // =====================
    // FreeMenList
    // =====================

    void test_FreeMenList_addMan1(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);

        CPPUNIT_ASSERT(freeMenList.free_men[1] == 3);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 1);
    }


    void test_FreeMenList_addMan2(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);
        freeMenList.addMan(4);
        freeMenList.addMan(1);

        CPPUNIT_ASSERT(freeMenList.free_men[1] == 3);
        CPPUNIT_ASSERT(freeMenList.free_men[2] == 2);
        CPPUNIT_ASSERT(freeMenList.free_men[3] == 4);
        CPPUNIT_ASSERT(freeMenList.free_men[4] == 1);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 4);
    }

    void test_FreeMenList_addMan3(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);
        freeMenList.addMan(4);
        freeMenList.removeCurrentMan();
        freeMenList.addMan(1);

        CPPUNIT_ASSERT(freeMenList.free_men[1] == 3);
        CPPUNIT_ASSERT(freeMenList.free_men[2] == 2);
        CPPUNIT_ASSERT(freeMenList.free_men[3] == 1);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 3);
    }


    void test_FreeMenList_getNextManNumber1(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 2);
    }

    void test_FreeMenList_getNextManNumber2(){
        FreeMenList freeMenList;

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == -1);
    }

    void test_FreeMenList_getNextManNumber3(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);
        freeMenList.removeCurrentMan();

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 3);
    }


    void test_FreeMenList_replaceWith1(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);
        freeMenList.ReplaceWith(4);

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 4);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 2);
    }

    void test_FreeMenList_replaceWith2(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.ReplaceWith(4);

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 4);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 1);
    }

    void test_FreeMenList_replaceWith3(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);
        freeMenList.ReplaceWith(4);
        freeMenList.ReplaceWith(2);

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 2);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 2);
    }


    void test_FreeMenList_removeCurrentMan1(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.removeCurrentMan();

        CPPUNIT_ASSERT(freeMenList.next_man_index == 0);
    }

    void test_FreeMenList_removeCurrentMan2(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(2);
        freeMenList.removeCurrentMan();

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 3);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 1);
    }

    void test_FreeMenList_removeCurrentMan3(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(4);
        freeMenList.addMan(2);
        freeMenList.addMan(1);
        freeMenList.removeCurrentMan();
        freeMenList.removeCurrentMan();

        CPPUNIT_ASSERT(freeMenList.getNextManNumber() == 4);
        CPPUNIT_ASSERT(freeMenList.next_man_index == 2);
    }


    void test_FreeMenList_isEmpty1(){
        FreeMenList freeMenList;

        CPPUNIT_ASSERT(freeMenList.isEmpty());
    }

    void test_FreeMenList_isEmpty2(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.addMan(4);

        CPPUNIT_ASSERT(!freeMenList.isEmpty());
    }

    void test_FreeMenList_isEmpty3(){
        FreeMenList freeMenList;
        freeMenList.addMan(3);
        freeMenList.removeCurrentMan();

        CPPUNIT_ASSERT(freeMenList.isEmpty());
    }
    // =====================
    // global read single
    // =====================

    void test_read_single1 (){
    	std::istringstream r("5\n");
        int i=0;
        const bool b = smp_read_single(r, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(i == 5);
    }

    void test_read_single2 (){
    	std::istringstream r("0");
        int i;
        const bool b = smp_read_single(r, i);
        CPPUNIT_ASSERT(b == false);
    }

    void test_read_single3 (){
    	std::istringstream r("21488888888888\n");
        int i=0;
        const bool b = smp_read_single(r, i);
        CPPUNIT_ASSERT(b == false);
    }

    // =====================
    // global read multiple
    // =====================

    void test_read_multiple1(){
    	std::istringstream r("1 2 3 4 5\n");
        int i = 5;
        int line[5];
        const bool b = smp_read_multiple(r, line, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(line[0] == 1);
        CPPUNIT_ASSERT(line[1] == 2);
        CPPUNIT_ASSERT(line[2] == 3);
        CPPUNIT_ASSERT(line[3] == 4);
        CPPUNIT_ASSERT(line[4] == 5);
    }

    void test_read_multiple2(){
    	std::istringstream r("1\n");
        int i = 1;
        int line[1];
        const bool b = smp_read_multiple(r, line, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(line[0] == 1);
    }

    void test_read_multiple3(){
    	std::istringstream r("0 0 0 0 0\n");
        int i = 5;
        int line[5];
        const bool b = smp_read_multiple(r, line, i);
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(line[0] == 0);
        CPPUNIT_ASSERT(line[1] == 0);
        CPPUNIT_ASSERT(line[2] == 0);
        CPPUNIT_ASSERT(line[3] == 0);
        CPPUNIT_ASSERT(line[4] == 0);
    }


    // =====================
    // global print
    // =====================

    void test_print1 () {
        std::ostringstream w;
        smp_print(w, 1, 1);
        CPPUNIT_ASSERT(w.str() == "1 1\n");
    }

    void test_print2 () {
        std::ostringstream w;
        smp_print(w, 1, 1234567);
        CPPUNIT_ASSERT(w.str() == "1 1234567\n");
    }

    void test_print3 () {
        std::ostringstream w;
        smp_print(w, 5, 2);
        CPPUNIT_ASSERT(w.str() == "5 2\n");
    }


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_true);
    CPPUNIT_TEST(test_woman_populatePreferencesByMan);
    CPPUNIT_TEST(test_woman_engageTo);
    CPPUNIT_TEST(test_woman_foundBetterMan1);
    CPPUNIT_TEST(test_woman_foundBetterMan2);
    CPPUNIT_TEST(test_woman_foundBetterMan3);
    CPPUNIT_TEST(test_woman_isNotEngaged1);
    CPPUNIT_TEST(test_woman_isNotEngaged2);
    CPPUNIT_TEST(test_woman_isNotEngaged3);
    CPPUNIT_TEST(test_woman_reset);
    CPPUNIT_TEST(test_man_getNextPreference1);
    CPPUNIT_TEST(test_man_getNextPreference2);
    CPPUNIT_TEST(test_man_getNextPreference3);
    CPPUNIT_TEST(test_FreeMenList_addMan1);
    CPPUNIT_TEST(test_FreeMenList_addMan2);
    CPPUNIT_TEST(test_FreeMenList_addMan3);
    CPPUNIT_TEST(test_FreeMenList_getNextManNumber1);
    CPPUNIT_TEST(test_FreeMenList_getNextManNumber2);
    CPPUNIT_TEST(test_FreeMenList_getNextManNumber3);
    CPPUNIT_TEST(test_FreeMenList_replaceWith1);
    CPPUNIT_TEST(test_FreeMenList_replaceWith2);
    CPPUNIT_TEST(test_FreeMenList_replaceWith3);
    CPPUNIT_TEST(test_FreeMenList_removeCurrentMan1);
    CPPUNIT_TEST(test_FreeMenList_removeCurrentMan2);
    CPPUNIT_TEST(test_FreeMenList_removeCurrentMan3);
    CPPUNIT_TEST(test_FreeMenList_isEmpty1);
    CPPUNIT_TEST(test_FreeMenList_isEmpty2);
    CPPUNIT_TEST(test_FreeMenList_isEmpty3);
    CPPUNIT_TEST(test_read_single1);
    CPPUNIT_TEST(test_read_single2);
    CPPUNIT_TEST(test_read_single3);
    CPPUNIT_TEST(test_read_multiple1);
    CPPUNIT_TEST(test_read_multiple2);
    CPPUNIT_TEST(test_read_multiple3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
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
