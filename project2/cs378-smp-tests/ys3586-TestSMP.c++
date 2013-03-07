/*
g++ -ansi -pedantic -lcppunit -ldl -Wall -w TestSMP.c++ -o TestSMP.c++.app
valgrind TestSMP.c++.app >& TestSMP.out
 */

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "SMP.h"

using namespace std;
typedef vector< vector<int> > twoD_vector;

//THESE GLOBAL VARIABLES ARE MADE CORRECT BY INDIVIDUAL TESTS.
//THYE ARE INTERDEPENDENT. IN OTHER WORDS, RUN ALL TESTS!
twoD_vector m_arrays1;
twoD_vector w_arrays1;
twoD_vector m_arrays2;
twoD_vector w_arrays2;
twoD_vector m_arrays3;
twoD_vector w_arrays3;
twoD_vector output1;
twoD_vector output2;
twoD_vector output3;

// -----------
// TestSMP
// -----------

struct TestSMP : CppUnit::TestFixture {
    // ----
    // read		Note: arrays for women are different from input! content/index are switched
    // ----

    void test_read1 () {
        std::istringstream r(
        		"1 4 3 1 2\n"
        		"2 2 1 3 4\n"
        		"3 1 3 4 2\n"
        		"4 4 3 1 2\n"

        		"1 3 2 4 1\n"
        		"2 2 3 1 4\n"
        		"3 3 1 2 4\n"
        		"4 3 2 4 1\n");

		int n = 4;

		m_arrays1.resize(n);
		w_arrays1.resize(n);
		for (int j=0; j<n; j++){
			m_arrays1[j].resize(n+1);
			w_arrays1[j].resize(n+1);
		}
		SMP_read(r, n, m_arrays1, w_arrays1);
		CPPUNIT_ASSERT(m_arrays1.size() == n && w_arrays1.size() == n);

		std::ostringstream w;
		for (int i=0; i<n; ++i){
			for (int j=0; j<n; ++j){
				w << w_arrays1[i][j] << " ";
			}
			w << w_arrays1[i][n] << endl;
		}
//		cout << w.str();
		CPPUNIT_ASSERT(w.str() == "1 3 4 2 1\n2 2 1 3 4\n3 1 4 2 3\n4 3 4 2 1\n");

		std::ostringstream m;
		for (int i=0; i<n; ++i){
			for (int j=0; j<n; j++){
				m << m_arrays1[i][j] << " ";
			}
			m << m_arrays1[i][n] << endl;
		}
		CPPUNIT_ASSERT(m.str() == "1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1\n");
    }

    void test_read2 () {
        std::istringstream r(
        		"1 3 4 2 1 6 7 5\n"
        		"2 6 4 2 3 5 1 7\n"
        		"3 6 3 5 7 2 4 1\n"
        		"4 1 6 3 2 4 7 5\n"
        		"5 1 6 5 3 4 7 2\n"
        		"6 1 7 3 4 5 6 2\n"
        		"7 5 6 2 4 3 7 1\n"

        		"1 4 5 3 7 2 6 1\n"
        		"2 5 6 4 7 3 2 1\n"
        		"3 1 6 5 4 3 7 2\n"
        		"4 3 5 6 7 2 4 1\n"
        		"5 1 7 6 4 3 5 2\n"
        		"6 6 3 7 5 2 4 1\n"
        		"7 1 7 4 2 6 5 3\n");

		int n = 7;

		m_arrays2.resize(n);
		w_arrays2.resize(n);
		for (int j=0; j<n; j++){
			m_arrays2[j].resize(n+1);
			w_arrays2[j].resize(n+1);
		}
		SMP_read(r, n, m_arrays2, w_arrays2);
		CPPUNIT_ASSERT(m_arrays2.size() == n && w_arrays2.size() == n);

		std::ostringstream w;
		for (int i=0; i<n; ++i){
			for (int j=0; j<n; j++){
				w << w_arrays2[i][j] << " ";
			}
			w << w_arrays2[i][n] << endl;
		}
//		cout << w.str();
		CPPUNIT_ASSERT(w.str() ==
				string("1 4 3 1 2 7 5 6\n")+
				string("2 6 3 4 2 5 1 7\n")+
				string("3 7 5 2 6 3 1 4\n")+
				string("4 1 4 3 5 7 2 6\n")+
				string("5 1 7 4 5 3 2 6\n")+
				string("6 1 7 3 4 5 6 2\n")+
				string("7 7 3 5 4 1 2 6\n"));

		std::ostringstream m;
		for (int i=0; i<n; ++i){
			for (int j=0; j<n; j++){
				m << m_arrays2[i][j] << " ";
			}
			m << m_arrays2[i][n] << endl;
		}
		CPPUNIT_ASSERT(m.str() ==
				string("1 4 5 3 7 2 6 1\n")+
				string("2 5 6 4 7 3 2 1\n")+
				string("3 1 6 5 4 3 7 2\n")+
				string("4 3 5 6 7 2 4 1\n")+
				string("5 1 7 6 4 3 5 2\n")+
				string("6 6 3 7 5 2 4 1\n")+
				string("7 1 7 4 2 6 5 3\n"));
    }

    void test_read3 () {
            std::istringstream r(
            		"1 2 5 4 1 3\n"
            		"2 1 3 5 2 4\n"
            		"3 2 1 3 4 5\n"
            		"4 1 4 3 5 2\n"
            		"5 4 1 5 3 2\n"

            		"1 2 5 3 1 4\n"
            		"2 3 2 1 4 5\n"
            		"3 2 3 5 4 1\n"
            		"4 2 5 4 3 1\n"
            		"5 5 2 3 1 4\n");

    		int n = 5;

    		m_arrays3.resize(n);
    		w_arrays3.resize(n);
    		for (int j=0; j<n; j++){
    			m_arrays3[j].resize(n+1);
    			w_arrays3[j].resize(n+1);
    		}
    		SMP_read(r, n, m_arrays3, w_arrays3);
    		CPPUNIT_ASSERT(m_arrays3.size() == n && w_arrays3.size() == n);

    		std::ostringstream w;
    		for (int i=0; i<n; ++i){
    			for (int j=0; j<n; j++){
    				w << w_arrays3[i][j] << " ";
    			}
    			w << w_arrays3[i][n] << endl;
    		}
    //		cout << w.str();
    		CPPUNIT_ASSERT(w.str() ==
    				string("1 4 1 5 3 2\n")+
    				string("2 1 4 2 5 3\n")+
    				string("3 2 1 3 4 5\n")+
    				string("4 1 5 3 2 4\n")+
    				string("5 2 5 4 1 3\n"));

    		std::ostringstream m;
    		for (int i=0; i<n; ++i){
    			for (int j=0; j<n; j++){
    				m << m_arrays3[i][j] << " ";
    			}
    			m << m_arrays3[i][n] << endl;
    		}
    		CPPUNIT_ASSERT(m.str() ==
    				string("1 2 5 3 1 4\n")+
    				string("2 3 2 1 4 5\n")+
    				string("3 2 3 5 4 1\n")+
    				string("4 2 5 4 3 1\n")+
    				string("5 5 2 3 1 4\n"));
        }

    // ----
	// continue
	// ----
    void test_continue_1(){
    	list<int> m_free;
    	m_free.push_back(2);
    	m_free.pop_front();
    	CPPUNIT_ASSERT(m_free.size() == 0);

    	int steps = -1;
    	CPPUNIT_ASSERT(!SMP_continue(m_free, steps));
    	CPPUNIT_ASSERT(steps == 0);
    }

    void test_continue_2(){
    	list<int> m_free;
    	m_free.push_back(2);
    	m_free.push_back(3);
    	m_free.push_back(4);
    	m_free.pop_front();
    	CPPUNIT_ASSERT(m_free.size() == 2);

    	int steps = -1;
    	CPPUNIT_ASSERT(SMP_continue(m_free, steps));
    	CPPUNIT_ASSERT(steps == 2);
    }

    void test_continue_3(){
    	list<int> m_free;
    	m_free.push_back(2);
    	m_free.push_back(3);
    	m_free.push_back(4);

    	int steps;
    	CPPUNIT_ASSERT(SMP_continue(m_free, steps));
    	CPPUNIT_ASSERT(m_free.size() == 3);
    }

    // ----
	// entertain
	// ----
    void test_entertain_1(){
    	int n = 4;
    	vector<int> bestSuitors = vector<int>(n);
		for (int i=0; i<n; ++i){
			bestSuitors[i] = 0;
		}

		twoD_vector w_arrays;
		int man = 1, woman = 3;
		CPPUNIT_ASSERT(SMP_entertain(man, woman, bestSuitors, w_arrays));
		CPPUNIT_ASSERT(bestSuitors[2] == 1);
    }

    void test_entertain_2(){
    	int n = 4;
    	vector<int> bestSuitors = vector<int>(n);
		for (int i=0; i<n; ++i){
			bestSuitors[i] = 0;
		}

		int man = 3, woman = 3;
		bestSuitors[2] = 1;
		CPPUNIT_ASSERT(!SMP_entertain(man, woman, bestSuitors, w_arrays1));
		CPPUNIT_ASSERT(bestSuitors[2] == 1);
		bestSuitors[2] = 4;
		CPPUNIT_ASSERT(SMP_entertain(man, woman, bestSuitors, w_arrays1));
		CPPUNIT_ASSERT(bestSuitors[2] == 3);
    }

    void test_entertain_3(){
    	int n = 4;
    	vector<int> bestSuitors = vector<int>(n);
    	for (int i=0; i<n; ++i){
    		bestSuitors[i] = 0;
    	}

    	int man = 3, woman = 3;
    	bestSuitors[2] = 2;
    	CPPUNIT_ASSERT(SMP_entertain(man, woman, bestSuitors, w_arrays1));
    	CPPUNIT_ASSERT(bestSuitors[2] == 3);
    	man = 1;
    	CPPUNIT_ASSERT(SMP_entertain(man, woman, bestSuitors, w_arrays1));
    	CPPUNIT_ASSERT(bestSuitors[2] == 1);
    }

    // ----
    // eval
    // ----

    void test_eval_1(){
		int n = 4;
		ostringstream result, expected;

    	twoD_vector output;
		output.resize(n);
		SMP_eval(n, m_arrays1, w_arrays1, output);

		//assuming SMP_print() is working

		SMP_print(result, output);
		SMP_print(expected, output1);
//		cout << result.str() << endl;
//		cout << expected.str();

		CPPUNIT_ASSERT(result.str() == expected.str());
    }

    void test_eval_2(){
		int n = 7;
		ostringstream result, expected;

    	twoD_vector output;
		output.resize(n);
		SMP_eval(n, m_arrays2, w_arrays2, output);

		//assuming SMP_print() is working

		SMP_print(result, output);
		SMP_print(expected, output2);
//		cout << "+++ Result +++" << endl;
//		cout << result.str() << endl;
//		cout << "+++ Expected +++" << endl;
//		cout << expected.str();

		CPPUNIT_ASSERT(result.str() == expected.str());
    }

    void test_eval_3(){
    	int n = 5;
    	ostringstream result, expected;

    	twoD_vector output;
    	output.resize(n);
    	SMP_eval(n, m_arrays3, w_arrays3, output);

    	//assuming SMP_print() is working

    	SMP_print(result, output);
    	SMP_print(expected, output3);
//    	cout << "+++ Result +++" << endl;
//    	cout << result.str() << endl;
//    	cout << "+++ Expected +++" << endl;
//    	cout << expected.str();

    	CPPUNIT_ASSERT(result.str() == expected.str());
    }

    // -----
    // print
    // -----

    void test_print1 () {
        std::ostringstream w;

		int n = 4;
		output1.resize(n);
		for (int j=0; j<n; j++){
			output1[j].resize(2);
		}

		int myints[] = {1,3};
		int s1 = sizeof(myints);
		int s2 = sizeof(int);
		int i = 0;
		vector<int> line = vector<int>(myints, myints + s1/ s2 );
		output1[i++] = line;

		myints = {2,2};
		line = vector<int>(myints, myints + s1/ s2 );
		output1[i++] = line;
		myints = {3,1};
		line = vector<int>(myints, myints + s1/ s2 );
		output1[i++] = line;
		myints = {4,4};
		line = vector<int>(myints, myints + s1/ s2 );
		output1[i++] = line;

		SMP_print(w, output1);

		CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n4 4\n");
    }

    void test_print2 () {
        std::ostringstream w;

		int n = 7;
		output2.resize(n);
		for (int j=0; j<n; j++){
			output2[j].resize(2);
		}

		int myints[] = {1,4};
		int s1 = sizeof(myints);
		int s2 = sizeof(int);
		int i = 0;
		vector<int> line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;

		myints = {2,5};
		line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;
		myints = {3,1};
		line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;
		myints = {4,3};
		line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;
		myints = {5,7};
		line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;
		myints = {6,6};
		line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;
		myints = {7,2};
		line = vector<int>(myints, myints + s1/ s2 );
		output2[i++] = line;

		SMP_print(w, output2);

		CPPUNIT_ASSERT(w.str() == "1 4\n2 5\n3 1\n4 3\n5 7\n6 6\n7 2\n");
    }

    void test_print3 () {
            std::ostringstream o;

    		int n = 5;
    		output3.resize(n);
    		for (int j=0; j<n; j++){
    			output3[j].resize(2);
    		}

    		output3[0][0] = (1);	output3[0][1] = (2);
    		output3[1][0] = (2);	output3[1][1] = (3);
    		output3[2][0] = (3);	output3[2][1] = (4);
    		output3[3][0] = (4);	output3[3][1] = (5);
    		output3[4][0] = (5);	output3[4][1] = (1);

    		SMP_print(o, output3);
//    		cout << o.str();

    		CPPUNIT_ASSERT(o.str() == "1 2\n2 3\n3 4\n4 5\n5 1\n");
        }

    // -----
    // solve
    // -----

    //Covered in acceptance tests.

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_read1);
    CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_continue_1);
    CPPUNIT_TEST(test_continue_2);
    CPPUNIT_TEST(test_continue_3);
    CPPUNIT_TEST(test_entertain_1);
    CPPUNIT_TEST(test_entertain_2);
    CPPUNIT_TEST(test_entertain_3);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
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
