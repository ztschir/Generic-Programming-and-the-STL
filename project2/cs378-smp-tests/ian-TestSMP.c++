#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"
#include <string>

#define private public
#define class struct
#include "SMP.h"
#undef private
#undef class

struct TestSMP : CppUnit::TestFixture {

    void test_man_constructor_starts_unengaged() {
        std::istringstream in("0 5 4 3 2 1\n");
        Man man(in, 5);
        CPPUNIT_ASSERT_EQUAL(NO_ENGAGEMENT, man.engaged_to);
    }
    void test_man_constructor_populates_choices_decremented() {
        std::istringstream in("0 5 4 3 2 1\n");
        Man man(in, 5);
        CPPUNIT_ASSERT_EQUAL(4, man.choices.front());
        man.choices.pop();
        CPPUNIT_ASSERT_EQUAL(3, man.choices.front());
    }
    void test_man_constructor_respects_input_size() {
        std::istringstream in("0 5 4 3 2 1\n");
        Man man(in, 2);
        CPPUNIT_ASSERT_EQUAL(2, (int)man.choices.size());
    }

    void test_man_pop_choice_return_value() {
        std::istringstream in("0 5 4 3 2 1\n");
        Man man(in, 5);
        CPPUNIT_ASSERT_EQUAL(4, man.pop_choice());
    }
    void test_man_pop_choice_mutates_choices() {
        std::istringstream in("0 5 4 3 2 1\n");
        Man man(in, 5);
        CPPUNIT_ASSERT_EQUAL(4, man.pop_choice());
        CPPUNIT_ASSERT_EQUAL(3, man.pop_choice());
        CPPUNIT_ASSERT_EQUAL(2, man.choices.front());
    }
    void test_man_pop_choice_changes_size() {
        std::istringstream in("0 5 4 3 2 1\n");
        Man man(in, 5);
        CPPUNIT_ASSERT_EQUAL(5, (int)man.choices.size());
        man.pop_choice();
        man.pop_choice();
        man.pop_choice();
        CPPUNIT_ASSERT_EQUAL(2, (int)man.choices.size());
        man.pop_choice();
        man.pop_choice();
        CPPUNIT_ASSERT_EQUAL(0, (int)man.choices.size());
    }

    void test_woman_constructor_starts_unengaged() {
        std::istringstream in("0 5 4 3 2 1\n");
        Woman woman(in, 5);
        CPPUNIT_ASSERT_EQUAL(NO_ENGAGEMENT, woman.engaged_to);
    }
    void test_woman_constructor_populates_choices_decremented() {
        std::istringstream in("0 5 4 3 2 1\n");
        Woman woman(in, 5);
        CPPUNIT_ASSERT_EQUAL(4, woman.choices[0]);
        CPPUNIT_ASSERT_EQUAL(3, woman.choices[1]);
    }
    void test_woman_constructor_populates_reverse_choices() {
        std::istringstream in("0 5 4 3 2 1\n");
        Woman woman(in, 5);

        CPPUNIT_ASSERT_EQUAL(0, woman.reverse_choices[4]);
        CPPUNIT_ASSERT_EQUAL(1, woman.reverse_choices[3]);
    }

    void test_woman_prefers_unengaged() {
        std::istringstream in("0 5 4 3 2 1\n");
        Woman woman(in, 5);
        CPPUNIT_ASSERT(woman.prefers(10));
    }
    void test_woman_prefers_positive() {
        std::istringstream in("0 5 4 3 2 1\n");
        Woman woman(in, 5);
        woman.engaged_to = 2;
        CPPUNIT_ASSERT(woman.prefers(4));
    }
    void test_woman_prefers_negative() {
        std::istringstream in("0 5 4 3 2 1\n");
        Woman woman(in, 5);
        woman.engaged_to = 4;
        CPPUNIT_ASSERT(!woman.prefers(2));
    }

    void test_solve_case_trivial() {
        std::istringstream in(
            "3"                 "\n"
            "1 1 2 3"           "\n"
            "2 1 2 3"           "\n"
            "3 1 2 3"           "\n"
            "1 1 2 3"           "\n"
            "2 1 2 3"           "\n"
            "3 1 2 3"           "\n"
        );
        std::ostringstream out;
        smp_solve_case(in, out);

        CPPUNIT_ASSERT(out.str() ==
            "1 1"      "\n"
            "2 2"      "\n"
            "3 3"      "\n"
        );
    }
    void test_solve_case_one_pair() {
        std::istringstream in(
            "1"             "\n"
            "1 1"           "\n"
            "1 1"           "\n"
        );
        std::ostringstream out;
        smp_solve_case(in, out);

        CPPUNIT_ASSERT(out.str() ==
            "1 1"      "\n"
        );
    }
    void test_solve_case_with_ousting() {
        std::istringstream in(
            "3"                 "\n"
            "1 1 2 3"           "\n"
            "2 1 2 3"           "\n"
            "3 1 2 3"           "\n"
            "1 3 2 1"           "\n"
            "2 3 2 1"           "\n"
            "3 3 2 1"           "\n"
        );
        std::ostringstream out;
        smp_solve_case(in, out);

        CPPUNIT_ASSERT(out.str() ==
            "1 3"      "\n"
            "2 2"      "\n"
            "3 1"      "\n"
        );
    }

    void test_solve_one_case() {
        std::istringstream in(
            "1"             "\n"
            "1"             "\n"
            "1 1"           "\n"
            "1 1"           "\n"
        );
        std::ostringstream out;
        smp_solve(in, out);

        CPPUNIT_ASSERT(out.str() ==
            "1 1"      "\n"
        );
    }

    void test_solve_multiple_cases() {
        std::istringstream in(
            "2"             "\n"
            "1"             "\n"
            "1 1"           "\n"
            "1 1"           "\n"
            "3"             "\n"
            "1 1 2 3"       "\n"
            "2 1 2 3"       "\n"
            "3 1 2 3"       "\n"
            "1 1 2 3"       "\n"
            "2 1 2 3"       "\n"
            "3 1 2 3"       "\n"
        );
        std::ostringstream out;
        smp_solve(in, out);

        CPPUNIT_ASSERT(out.str() ==
            "1 1"      "\n"
            "1 1"      "\n"
            "2 2"      "\n"
            "3 3"      "\n"
        );
    }

    void test_solve_respects_case_count() {
        std::istringstream in(
            "1"             "\n"
            "1"             "\n"
            "1 1"           "\n"
            "1 1"           "\n"
            "3"             "\n"
            "1 1 2 3"       "\n"
            "2 1 2 3"       "\n"
            "3 1 2 3"       "\n"
            "1 3 2 1"       "\n"
            "2 3 2 1"       "\n"
            "3 3 2 1"       "\n"
        );
        std::ostringstream out;
        smp_solve(in, out);

        CPPUNIT_ASSERT(out.str() ==
            "1 1"      "\n"
        );
    }

    CPPUNIT_TEST_SUITE(TestSMP);

    CPPUNIT_TEST(test_man_constructor_starts_unengaged);
    CPPUNIT_TEST(test_man_constructor_populates_choices_decremented);
    CPPUNIT_TEST(test_man_constructor_respects_input_size);
    CPPUNIT_TEST(test_man_pop_choice_return_value);
    CPPUNIT_TEST(test_man_pop_choice_mutates_choices);
    CPPUNIT_TEST(test_man_pop_choice_changes_size);
    CPPUNIT_TEST(test_woman_constructor_starts_unengaged);
    CPPUNIT_TEST(test_woman_constructor_populates_choices_decremented);
    CPPUNIT_TEST(test_woman_constructor_populates_reverse_choices);
    CPPUNIT_TEST(test_woman_prefers_unengaged);
    CPPUNIT_TEST(test_woman_prefers_positive);
    CPPUNIT_TEST(test_woman_prefers_negative);
    CPPUNIT_TEST(test_solve_case_trivial);
    CPPUNIT_TEST(test_solve_case_one_pair);
    CPPUNIT_TEST(test_solve_case_with_ousting);
    CPPUNIT_TEST(test_solve_one_case);
    CPPUNIT_TEST(test_solve_multiple_cases);
    CPPUNIT_TEST(test_solve_respects_case_count);

    CPPUNIT_TEST_SUITE_END();
};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);
    cout << "TestSMP.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestSMP::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
