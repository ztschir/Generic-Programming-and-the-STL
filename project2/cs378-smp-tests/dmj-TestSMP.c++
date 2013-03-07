/*
 * File: TestSMP.c++
 * Author: Daniel Jordan
 * Copyright (C) 2012
 */

/* 
 * To test the functions under cppunit, this source file
 * must be compiled with the flags -lcppunit and -ldl.
 *
 * Don't forget to use valgrind and redirect to stderr.
 */

#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

// ----------------
// cppunit includes
// ----------------

/* CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END */
#include "cppunit/extensions/HelperMacros.h"
/* TestFixture */
#include "cppunit/TestFixture.h"
/* TextTestRunner */
#include "cppunit/TextTestRunner.h"

#include "SMP.h"

using namespace std;

// -------
// TestSMP
// -------

struct TestSMP : CppUnit::TestFixture {

	void read_women_prefs_1() {
		/* Tests a preference read for women. */
		std::istringstream r("1 4 3 1 2\n2 2 3 4 1\n3 4 1 3 2\n4 1 2 3 4\n");
		
		TestCase tc;
		tc.num_marriages = 4;

		read_women_prefs(r, tc.women, tc.num_marriages);

		CPPUNIT_ASSERT(tc.women.size() == tc.num_marriages);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man.size() == tc.num_marriages + 1);

		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[1] == 3);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[2] == 4);

		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[2] == 1);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[4] == 3);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[1] == 4);

		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[1] == 2);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[2] == 4);

		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[2] == 2);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[4] == 4);
	}


	void read_women_prefs_2() {
		/* Tests a preference read for women. */
		std::istringstream r("1 1 2 3 4\n2 1 2 3 4\n3 1 2 3 4\n4 1 2 3 4\n");
		
		TestCase tc;
		tc.num_marriages = 4;

		read_women_prefs(r, tc.women, tc.num_marriages);

		CPPUNIT_ASSERT(tc.women.size() == tc.num_marriages);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man.size() == tc.num_marriages + 1);

		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[2] == 2);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[4] == 4);

		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[2] == 2);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[4] == 4);

		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[2] == 2);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[4] == 4);

		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[2] == 2);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[4] == 4);
	}


	void read_women_prefs_3() {
		/* Tests a preference read for women. */
		std::istringstream r("1 1\n");
		
		TestCase tc;
		tc.num_marriages = 1;

		read_women_prefs(r, tc.women, tc.num_marriages);

		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women.size() == 1);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man.size() == tc.num_marriages + 1);
	}


	void read_men_prefs_1() {
		/* Tests a preference read for men. */
		std::istringstream r("1 3 4 2 1\n2 1 4 2 3\n3 2 1 3 4\n4 4 3 2 1\n");
		
		TestCase tc;
		tc.num_marriages = 4;

		read_men_prefs(r, tc.free_men, tc.num_marriages);

		CPPUNIT_ASSERT(tc.free_men.size() == tc.num_marriages);

		int correct_input[][4] = {{3, 4, 2, 1},
								 {1, 4, 2, 3},
								 {2, 1, 3, 4},
								 {4, 3, 2, 1}};

		list<Man>::const_iterator men_iter = tc.free_men.begin();
		list<Man>::const_iterator men_end = tc.free_men.end();
		int i = 0;
		while (men_iter != men_end) {
			list<int>::const_iterator rank_iter = men_iter->prefs_by_rank.begin();
			list<int>::const_iterator rank_end = men_iter->prefs_by_rank.end();
			int j = 0;
			while (rank_iter != rank_end) {
				CPPUNIT_ASSERT(*rank_iter == correct_input[i][j]);
				++j;
				++rank_iter;
			}
			++i;
			++men_iter;
		}
	}

	
	void read_men_prefs_2() {
		/* Tests a preference read for men. */
		std::istringstream r("1 4 3 2 1\n2 4 3 2 1\n3 4 3 2 1\n4 4 3 2 1\n");
		
		TestCase tc;
		tc.num_marriages = 4;

		read_men_prefs(r, tc.free_men, tc.num_marriages);

		CPPUNIT_ASSERT(tc.free_men.size() == tc.num_marriages);

		int correct_input[][4] = {{4, 3, 2, 1},
								  {4, 3, 2, 1},
								  {4, 3, 2, 1},
								  {4, 3, 2, 1}};

		list<Man>::const_iterator men_iter = tc.free_men.begin();
		list<Man>::const_iterator men_end = tc.free_men.end();
		int i = 0;
		while (men_iter != men_end) {
			list<int>::const_iterator rank_iter = men_iter->prefs_by_rank.begin();
			list<int>::const_iterator rank_end = men_iter->prefs_by_rank.end();
			int j = 0;
			while (rank_iter != rank_end) {
				CPPUNIT_ASSERT(*rank_iter == correct_input[i][j]);
				++j;
				++rank_iter;
			}
			++i;
			++men_iter;
		}
	}


	void read_men_prefs_3() {
		/* Tests a preference read for men. */
		std::istringstream r("1 1\n");
		
		TestCase tc;
		tc.num_marriages = 1;

		read_men_prefs(r, tc.free_men, tc.num_marriages);

		CPPUNIT_ASSERT(tc.free_men.size() == tc.num_marriages);

		list<Man>::const_iterator men_iter = tc.free_men.begin();
		list<int>::const_iterator rank_iter = men_iter->prefs_by_rank.begin();
		CPPUNIT_ASSERT(*rank_iter == 1);
	}


	void read_test_case_1() {
		std::istringstream r("4\n1 4 3 1 2\n2 2 3 4 1\n3 4 1 3 2\n4 1 2 3 4\n1 3 4 2 1\n2 1 4 2 3\n3 2 1 3 4\n4 4 3 2 1\n");

		TestCase tc;
		read_test_case(r, tc);

		CPPUNIT_ASSERT(tc.num_marriages == 4);
		CPPUNIT_ASSERT(tc.women.size() == tc.num_marriages);
		CPPUNIT_ASSERT(tc.free_men.size() == tc.num_marriages);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man.size() == tc.num_marriages + 1);
		CPPUNIT_ASSERT(tc.free_men.begin()->prefs_by_rank.size() == tc.num_marriages);
	
		// Women's prefs	
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[1] == 3);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[2] == 4);

		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[2] == 1);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[4] == 3);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[1] == 4);

		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[1] == 2);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[2] == 4);

		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[1] == 1);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[2] == 2);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[3] == 3);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[4] == 4);

		int correct_input[][4] = {{3, 4, 2, 1},
								 {1, 4, 2, 3},
								 {2, 1, 3, 4},
								 {4, 3, 2, 1}};

		// Men's prefs
		list<Man>::const_iterator men_iter = tc.free_men.begin();
		list<Man>::const_iterator men_end = tc.free_men.end();
		int i = 0;
		while (men_iter != men_end) {
			list<int>::const_iterator rank_iter = men_iter->prefs_by_rank.begin();
			list<int>::const_iterator rank_end = men_iter->prefs_by_rank.end();
			int j = 0;
			while (rank_iter != rank_end) {
				CPPUNIT_ASSERT(*rank_iter == correct_input[i][j]);
				++j;
				++rank_iter;
			}
			++i;
			++men_iter;
		}
	}


	void read_test_case_2() {
		std::istringstream r("4\n1 4 3 2 1\n2 4 3 2 1\n3 4 3 2 1\n4 4 3 2 1\n1 1 2 3 4\n2 1 2 3 4\n3 1 2 3 4\n4 1 2 3 4\n");

		TestCase tc;
		read_test_case(r, tc);

		CPPUNIT_ASSERT(tc.num_marriages == 4);
		CPPUNIT_ASSERT(tc.women.size() == tc.num_marriages);
		CPPUNIT_ASSERT(tc.free_men.size() == tc.num_marriages);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man.size() == tc.num_marriages + 1);
		CPPUNIT_ASSERT(tc.free_men.begin()->prefs_by_rank.size() == tc.num_marriages);
	
		// Women's prefs	
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[2] == 3);
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[1] == 4);

		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[2] == 3);
		CPPUNIT_ASSERT(tc.women[1].prefs_by_man[1] == 4);

		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[2] == 3);
		CPPUNIT_ASSERT(tc.women[2].prefs_by_man[1] == 4);

		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[4] == 1);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[3] == 2);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[2] == 3);
		CPPUNIT_ASSERT(tc.women[3].prefs_by_man[1] == 4);

		int correct_input[][4] = {{1, 2, 3, 4},
								  {1, 2, 3, 4},
								  {1, 2, 3, 4},
								  {1, 2, 3, 4}};

		// Men's prefs
		list<Man>::const_iterator men_iter = tc.free_men.begin();
		list<Man>::const_iterator men_end = tc.free_men.end();
		int i = 0;
		while (men_iter != men_end) {
			list<int>::const_iterator rank_iter = men_iter->prefs_by_rank.begin();
			list<int>::const_iterator rank_end = men_iter->prefs_by_rank.end();
			int j = 0;
			while (rank_iter != rank_end) {
				CPPUNIT_ASSERT(*rank_iter == correct_input[i][j]);
				++j;
				++rank_iter;
			}
			++i;
			++men_iter;
		}
	}


	void read_test_case_3() {
		std::istringstream r("1\n1 1\n1 1\n");

		TestCase tc;
		read_test_case(r, tc);

		CPPUNIT_ASSERT(tc.num_marriages == 1);

		// Woman's pref
		CPPUNIT_ASSERT(tc.women[0].prefs_by_man[1] == 1);

		// Man's pref
		list<Man>::const_iterator men_iter = tc.free_men.begin();
		list<int>::const_iterator rank_iter = men_iter->prefs_by_rank.begin();
		CPPUNIT_ASSERT(*rank_iter == 1);
	}


	void is_more_preferred_1() {
		Man m1;
		m1.id = 1;
		Man m2;
		m2.id = 2;
		Woman w;
		// This Woman prefers m2 over m1 because her preferences are stored
		// in order of id, not rank.
		w.prefs_by_man.push_back(0);  // Padding to align the indices with the ids.
		w.prefs_by_man.push_back(2);
		w.prefs_by_man.push_back(1);
		list<Man> l;
		l.push_front(m1);
		list<Man>::iterator m1_iter = l.begin();
		l.push_front(m2);
		list<Man>::iterator m2_iter = l.begin();

		const bool b1 = is_more_preferred(m1_iter, m2_iter, &w);
		CPPUNIT_ASSERT(b1 == false);

		const bool b2 = is_more_preferred(m2_iter, m1_iter, &w);
		CPPUNIT_ASSERT(b2 == true);
	}


	void is_more_preferred_2() {
		Man m1;
		m1.id = 1;
		Man m2;
		m2.id = 2;
		Man m3;
		m3.id = 3;
		Woman w;
		// This Woman prefers Men, from most to least, in this order: 3, 1, 2
		w.prefs_by_man.push_back(0);  // Padding to align the indices with the ids.
		w.prefs_by_man.push_back(2);
		w.prefs_by_man.push_back(3);
		w.prefs_by_man.push_back(1);
		list<Man> l;
		l.push_front(m1);
		list<Man>::iterator m1_iter = l.begin();
		l.push_front(m2);
		list<Man>::iterator m2_iter = l.begin();
		l.push_front(m3);
		list<Man>::iterator m3_iter = l.begin();

		const bool b1 = is_more_preferred(m3_iter, m1_iter, &w);
		CPPUNIT_ASSERT(b1 == true);

		const bool b2 = is_more_preferred(m3_iter, m2_iter, &w);
		CPPUNIT_ASSERT(b2 == true);

		const bool b3 = is_more_preferred(m1_iter, m2_iter, &w);
		CPPUNIT_ASSERT(b3 == true);

		const bool b4 = is_more_preferred(m1_iter, m3_iter, &w);
		CPPUNIT_ASSERT(b4 == false);

		const bool b5 = is_more_preferred(m2_iter, m3_iter, &w);
		CPPUNIT_ASSERT(b5 == false);

		const bool b6 = is_more_preferred(m2_iter, m1_iter, &w);
		CPPUNIT_ASSERT(b6 == false);
	}

	
	void is_more_preferred_3() {
		Man m1;
		m1.id = 1;
		Woman w;
		// This Woman shouldn't prefer m1 over m1--because that's impossible!
		w.prefs_by_man.push_back(0);  // Padding to align the indices with the ids.
		w.prefs_by_man.push_back(1);
		list<Man> l;
		l.push_front(m1);
		list<Man>::iterator m1_iter = l.begin();

		const bool b1 = is_more_preferred(m1_iter, m1_iter, &w);
		CPPUNIT_ASSERT(b1 == false);
	}


	void engage_1() {
		/* Engage a Man and a Woman, each of whom is the only one in the list. */
		TestCase tc;
		Man m;
		m.engaged_to = NOT_ENGAGED;
		tc.free_men.push_back(m);
		Woman w;
		w.is_engaged = false;
		tc.women.push_back(w);
		Woman * w_ptr = &(tc.women[0]);

		list<Man>::iterator m_iter = tc.free_men.begin();
		engage(m_iter, w_ptr, tc);

		CPPUNIT_ASSERT(tc.free_men.size() == 0);
		CPPUNIT_ASSERT(tc.engaged_men.size() == 1);
		CPPUNIT_ASSERT(tc.engaged_men.begin()->engaged_to == w_ptr);
		CPPUNIT_ASSERT(tc.women[0].is_engaged == true);
		CPPUNIT_ASSERT(tc.women[0].engaged_to == tc.engaged_men.begin());
	}


	void engage_2() {
		/* 
		 * Engage a Man and a Woman, each of whom is the third in a list of five
		 * people.
		 */
		TestCase tc;
		Man spacer;
		tc.free_men.push_back(spacer);
		tc.free_men.push_back(spacer);

		Man m;
		m.engaged_to = NOT_ENGAGED;
		tc.free_men.push_back(m);

		tc.free_men.push_back(spacer);
		tc.free_men.push_back(spacer);

		Woman w_spacer;
		tc.women.push_back(w_spacer);
		tc.women.push_back(w_spacer);

		Woman w;
		w.is_engaged = false;
		tc.women.push_back(w);

		tc.women.push_back(w_spacer);
		tc.women.push_back(w_spacer);
		Woman * w_ptr = &(tc.women[2]);

		list<Man>::iterator m_iter = tc.free_men.begin();
		++m_iter;
		++m_iter;
		engage(m_iter, w_ptr, tc);

		CPPUNIT_ASSERT(tc.free_men.size() == 4);
		CPPUNIT_ASSERT(tc.engaged_men.size() == 1);
		CPPUNIT_ASSERT(tc.engaged_men.begin()->engaged_to == w_ptr);
		CPPUNIT_ASSERT(tc.women[2].is_engaged == true);
		CPPUNIT_ASSERT(tc.women[2].engaged_to == tc.engaged_men.begin());
	}


	void engage_3() {
		/* 
		 * Engage a Man and a Woman, each of whom is the last in a list of five
		 * people.
		 */
		TestCase tc;
		Man spacer;
		tc.free_men.push_back(spacer);
		tc.free_men.push_back(spacer);
		tc.free_men.push_back(spacer);
		tc.free_men.push_back(spacer);

		Man m;
		m.engaged_to = NOT_ENGAGED;
		tc.free_men.push_back(m);

		Woman w_spacer;
		tc.women.push_back(w_spacer);
		tc.women.push_back(w_spacer);
		tc.women.push_back(w_spacer);
		tc.women.push_back(w_spacer);

		Woman w;
		w.is_engaged = false;
		tc.women.push_back(w);

		Woman * w_ptr = &(tc.women[4]);

		list<Man>::iterator m_iter = tc.free_men.end();
		--m_iter;
		engage(m_iter, w_ptr, tc);

		CPPUNIT_ASSERT(tc.free_men.size() == 4);
		CPPUNIT_ASSERT(tc.engaged_men.size() == 1);
		CPPUNIT_ASSERT(tc.engaged_men.begin()->engaged_to == w_ptr);
		CPPUNIT_ASSERT(tc.women[4].is_engaged == true);
		CPPUNIT_ASSERT(tc.women[4].engaged_to == tc.engaged_men.begin());
	}


	void cmp_engaged_men_1() {
		Man m1;
		m1.id = 1;

		Man m2;
		m2.id = 2;

		const bool b1 = cmp_engaged_men(m1, m2);
		CPPUNIT_ASSERT(b1 == true);
		
		const bool b2 = cmp_engaged_men(m2, m1);
		CPPUNIT_ASSERT(b2 == false);
	}


	void cmp_engaged_men_2() {
		Man m1;
		m1.id = 1;

		Man m2;
		m2.id = 1;

		const bool b1 = cmp_engaged_men(m1, m2);
		CPPUNIT_ASSERT(b1 == false);
		
		const bool b2 = cmp_engaged_men(m2, m1);
		CPPUNIT_ASSERT(b2 == false);
	}


	void cmp_engaged_men_3() {
		Man m1;
		m1.id = 500;

		Man m2;
		m2.id = 499;

		const bool b1 = cmp_engaged_men(m1, m2);
		CPPUNIT_ASSERT(b1 == false);
		
		const bool b2 = cmp_engaged_men(m2, m1);
		CPPUNIT_ASSERT(b2 == true);
	}


	void solve_test_case_1() {
		std::istringstream r("4\n1 4 3 1 2\n2 2 3 4 1\n3 4 1 3 2\n4 1 2 3 4\n1 3 4 2 1\n2 1 4 2 3\n3 2 1 3 4\n4 4 3 2 1\n");
		TestCase tc;
		read_test_case(r, tc);
		solve_test_case(tc);

		int correct_marriages[] = {3, 1, 2, 4};
		list<Man>::iterator b = tc.engaged_men.begin();
		list<Man>::iterator e = tc.engaged_men.end();
		int i = 0;
		while (b != e) {
			CPPUNIT_ASSERT(b->engaged_to->id == correct_marriages[i]);
			++i;
			++b;
		}
	}


	void solve_test_case_2() {
		std::istringstream r("4\n1 4 3 2 1\n2 4 3 2 1\n3 4 3 2 1\n4 4 3 2 1\n1 1 2 3 4\n2 1 2 3 4\n3 1 2 3 4\n4 1 2 3 4\n");
		TestCase tc;
		read_test_case(r, tc);
		solve_test_case(tc);

		int correct_marriages[] = {4, 3, 2, 1};
		list<Man>::iterator b = tc.engaged_men.begin();
		list<Man>::iterator e = tc.engaged_men.end();
		int i = 0;
		while (b != e) {
			CPPUNIT_ASSERT(b->engaged_to->id == correct_marriages[i]);
			++i;
			++b;
		}
	}


	void solve_test_case_3() {
		std::istringstream r("1\n1 1\n1 1\n");
		TestCase tc;
		read_test_case(r, tc);
		solve_test_case(tc);

		int correct_marriages[] = {1};
		list<Man>::iterator b = tc.engaged_men.begin();
		list<Man>::iterator e = tc.engaged_men.end();
		int i = 0;
		while (b != e) {
			CPPUNIT_ASSERT(b->engaged_to->id == correct_marriages[i]);
			++i;
			++b;
		}

	}


	void write_test_case_solution_1() {
		std::istringstream r("4\n1 4 3 1 2\n2 2 3 4 1\n3 4 1 3 2\n4 1 2 3 4\n1 3 4 2 1\n2 1 4 2 3\n3 2 1 3 4\n4 4 3 2 1\n");
		TestCase tc;
		read_test_case(r, tc);

		solve_test_case(tc);
		std::ostringstream w;
		write_test_case_solution(w, tc);

		std::ostringstream correct_output;
		correct_output << "1 3\n2 1\n3 2\n4 4\n";
		CPPUNIT_ASSERT(w.str() == correct_output.str());
	}


	void write_test_case_solution_2() {
		std::istringstream r("4\n1 4 3 2 1\n2 4 3 2 1\n3 4 3 2 1\n4 4 3 2 1\n1 1 2 3 4\n2 1 2 3 4\n3 1 2 3 4\n4 1 2 3 4\n");
		TestCase tc;
		read_test_case(r, tc);

		solve_test_case(tc);
		std::ostringstream w;
		write_test_case_solution(w, tc);

		std::ostringstream correct_output;
		correct_output << "1 4\n2 3\n3 2\n4 1\n";
		CPPUNIT_ASSERT(w.str() == correct_output.str());
	}


	void write_test_case_solution_3() {
		std::istringstream r("1\n1 1\n1 1\n");
		TestCase tc;
		read_test_case(r, tc);

		solve_test_case(tc);
		std::ostringstream w;
		write_test_case_solution(w, tc);

		std::ostringstream correct_output;
		correct_output << "1 1\n";
		CPPUNIT_ASSERT(w.str() == correct_output.str());
	}


	void solve_smp_1() {
		std::istringstream r("1\n4\n1 4 3 1 2\n2 2 3 4 1\n3 4 1 3 2\n4 1 2 3 4\n\
1 3 4 2 1\n2 1 4 2 3\n3 2 1 3 4\n4 4 3 2 1\n");
		
		std::ostringstream test_output;
		solve_smp(r, test_output);

		std::ostringstream correct_output;
		correct_output << "1 3\n2 1\n3 2\n4 4\n";
		CPPUNIT_ASSERT(correct_output.str() == test_output.str());
	}


	void solve_smp_2() {
		std::istringstream r("3\n4\n1 4 3 1 2\n2 2 3 4 1\n3 4 1 3 2\n4 1 2 3 4\n\
1 3 4 2 1\n2 1 4 2 3\n3 2 1 3 4\n4 4 3 2 1\n\
4\n1 4 3 2 1\n2 4 3 2 1\n3 4 3 2 1\n4 4 3 2 1\n\
1 1 2 3 4\n2 1 2 3 4\n3 1 2 3 4\n4 1 2 3 4\n\
1\n1 1\n1 1\n");
		
		std::ostringstream test_output;
		solve_smp(r, test_output);

		std::ostringstream correct_output;
		correct_output << "1 3\n2 1\n3 2\n4 4\n1 4\n2 3\n3 2\n4 1\n1 1\n";
		CPPUNIT_ASSERT(correct_output.str() == test_output.str());
	}


	void solve_smp_3() {
		std::istringstream r("1\n1 1\n1 1\n");
		
		std::ostringstream test_output;
		solve_smp(r, test_output);

		std::ostringstream correct_output;
		correct_output << "1 1\n";
		CPPUNIT_ASSERT(correct_output.str() == test_output.str());
	}


	// Test Suite
	CPPUNIT_TEST_SUITE(TestSMP);
	CPPUNIT_TEST(read_women_prefs_1);
	CPPUNIT_TEST(read_women_prefs_2);
	CPPUNIT_TEST(read_women_prefs_3);
	CPPUNIT_TEST(read_men_prefs_1);
	CPPUNIT_TEST(read_men_prefs_2);
	CPPUNIT_TEST(read_men_prefs_3);
	CPPUNIT_TEST(read_test_case_1);
	CPPUNIT_TEST(read_test_case_2);
	CPPUNIT_TEST(read_test_case_3);
	CPPUNIT_TEST(is_more_preferred_1);
	CPPUNIT_TEST(is_more_preferred_2);
	CPPUNIT_TEST(is_more_preferred_3);
	CPPUNIT_TEST(engage_1);
	CPPUNIT_TEST(engage_2);
	CPPUNIT_TEST(engage_3);
	CPPUNIT_TEST(cmp_engaged_men_1);
	CPPUNIT_TEST(cmp_engaged_men_2);
	CPPUNIT_TEST(cmp_engaged_men_3);
	CPPUNIT_TEST(solve_test_case_1);
	CPPUNIT_TEST(solve_test_case_2);
	CPPUNIT_TEST(solve_test_case_3);
	CPPUNIT_TEST(write_test_case_solution_1);
	CPPUNIT_TEST(write_test_case_solution_2);
	CPPUNIT_TEST(write_test_case_solution_3);
	CPPUNIT_TEST(solve_smp_1);
	CPPUNIT_TEST(solve_smp_2);
	CPPUNIT_TEST(solve_smp_3);
	CPPUNIT_TEST_SUITE_END();
};


int main() {
	ios_base::sync_with_stdio(false);

	cout << "TestSMP.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestSMP::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
