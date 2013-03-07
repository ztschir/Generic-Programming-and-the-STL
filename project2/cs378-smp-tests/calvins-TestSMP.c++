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

#include <algorithm>// equal
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>   // vector

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "SMP.h"

using namespace std;

// -----------
// TestSMP
// -----------

struct TestSMP : CppUnit::TestFixture {
	// --------------
	// read_single_num
	// --------------

	void test_read_single_num_1() {
		istringstream r("5\n");
		int num;
		const bool b = SMP_read_single_num(r, num);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(num ==    5);}

	void test_read_single_num_2() {
		istringstream r("100\n");
		int num;
		const bool b = SMP_read_single_num(r, num);
		CPPUNIT_ASSERT(b == true);
		CPPUNIT_ASSERT(num==    100);}
        
	void test_read_single_num_3() {
		istringstream r("");
		int num;
		const bool b = SMP_read_single_num(r, num);
		CPPUNIT_ASSERT(b == false);}

	// ----
	// read
	// ----

	void test_read_1() {
		istringstream r("1 4 3 1 2\n");
        vector< vector<int> > menList(4, vector<int>(4)); 
		const bool b = SMP_read_men(r, 4, menList);
		CPPUNIT_ASSERT(b == true);
        int test[] = {4,3,1,2};
        vector<int> testVector;
        testVector.assign(test,test+4);
		CPPUNIT_ASSERT(equal(menList[0].begin(),menList[0].end(),testVector.begin()));}

	void test_read_2() {
		istringstream r("4 3 2 4 1\n");
        vector< vector<int> > womenList(4,vector<int>(4)); 
		const bool b = SMP_read_men(r, 4, womenList);
		CPPUNIT_ASSERT(b == true);
        int test[] = {3,2,4,1};
        vector<int> testVector;
        testVector.assign(test,test+4);
		CPPUNIT_ASSERT(equal(womenList[3].begin(),womenList[3].end(),testVector.begin()));}
        
	void test_read_3() {
		istringstream r("2 2 3 1 4\n");
        vector< vector<int> > womenList(4,vector<int>(4)); 
		const bool b = SMP_read_men(r, 4, womenList);
		CPPUNIT_ASSERT(b == true);
        int test[] = {2,3,1,4};
        vector<int> testVector;
        testVector.assign(test,test+4);
		CPPUNIT_ASSERT(equal(womenList[1].begin(),womenList[1].end(),testVector.begin()));}

	// ----
	// eval
	// ----

	void test_eval_1 () {
        vector< vector<int> > menList(4,vector<int>(4));
        vector< vector<int> > womenList(4,vector<int>(4));
        vector< map<int,int> > indexList(4);
		istringstream r("1 4 3 1 2\n2 2 1 3 4\n3 1 3 4 2\n4 4 3 1 2");
        istringstream r2("1 3 2 4 1\n2 2 3 1 4\n3 3 1 2 4\n4 3 2 4 1");
        for (int i=0; i<4; ++i) {
            SMP_read_women(r, 4, womenList, indexList); 
            SMP_read_men(r2, 4, menList); }
        vector<int> menPointers=SMP_eval(4,menList,womenList,indexList); 
        int int_points[] = {0,0,1,2};
        vector<int> vec_points(4);
        vec_points.assign(int_points,int_points+4);
        CPPUNIT_ASSERT(equal(menPointers.begin(),menPointers.end(),vec_points.begin())); }

	void test_eval_2 () {
        vector< vector<int> > menList(7,vector<int>(7));
        vector< vector<int> > womenList(7,vector<int>(7));
        vector< map<int,int> > indexList(7);
        istringstream r("1 3 4 2 1 6 7 5\n2 6 4 2 3 5 1 7\n3 6 3 5 7 2 4 1\n4 1 6 3 2 4 7 5\n5 1 6 5 3 4 7 2\n6 1 7 3 4 5 6 2\n7 5 6 2 4 3 7 1");
        istringstream r2("1 4 5 3 7 2 6 1\n2 5 6 4 7 3 2 1\n3 1 6 5 4 3 7 2\n4 3 5 6 7 2 4 1\n5 1 7 6 4 3 5 2\n6 6 3 7 5 2 4 1\n7 1 7 4 2 6 5 3");
        for (int i=0; i<7; ++i) {
            SMP_read_women(r,7, womenList, indexList); 
            SMP_read_men(r2, 7,menList); }
        vector<int> menPointers=SMP_eval(7,menList,womenList,indexList); 
        int int_points[] = {0,0,0,0,1,0,3};
        vector<int> vec_points(7);
        vec_points.assign(int_points,int_points+7);
        CPPUNIT_ASSERT(equal(menPointers.begin(),menPointers.end(),vec_points.begin())); }
        
	void test_eval_3 () {
        vector< vector<int> > menList(2,vector<int>(2));
        vector< vector<int> > womenList(2,vector<int>(2));
        vector< map<int,int> > indexList(2);
        istringstream r("1 1 2\n2 1 2");
        istringstream r2("1 1 2\n2 1 2");
        for (int i=0; i<2; ++i) {
            SMP_read_women(r,2, womenList, indexList); 
            SMP_read_men(r2,2, menList); }
        vector<int> menPointers=SMP_eval(2,menList,womenList,indexList); 
        int int_points[] = {0,1};
        vector<int> vec_points(2);
        vec_points.assign(int_points,int_points+2);
        CPPUNIT_ASSERT(equal(menPointers.begin(),menPointers.end(),vec_points.begin())); }

	// -----
	// print
	// -----

	void test_print_1 () {
		ostringstream w;
        vector< vector<int> > menList(4);
        int men[][4] = {{3,2,4,1},{2,3,1,4},{3,1,2,4},{3,2,4,1}};
        for (int i=0; i<4; ++i) {
            menList[i].assign(men[i],men[i]+4); }
        int int_points[] = {0,0,1,2};
        vector<int> vec_points(4);
        vec_points.assign(int_points,int_points+4);
		SMP_print(w,menList,vec_points);
		CPPUNIT_ASSERT(w.str() == "1 3\n2 2\n3 1\n4 4\n");}
        
	void test_print_2 () {
		ostringstream w;
        vector< vector<int> > menList(7);
        int men[][7] = {{4,5,3,7,2,6,1},{5,6,4,7,3,2,1},{1,6,5,4,3,7,2},{3,5,6,7,2,4,1},{1,7,6,4,3,5,2},{6,3,7,5,2,4,1},{1,7,4,2,6,5,3}};
        for (int i=0; i<7; ++i) {
            menList[i].assign(men[i],men[i]+7); }
        vector<int> vec_points(7);
        int int_points[] = {0,0,0,0,1,0,3};
        vec_points.assign(int_points,int_points+7);
		SMP_print(w,menList,vec_points);
		CPPUNIT_ASSERT(w.str() == "1 4\n2 5\n3 1\n4 3\n5 7\n6 6\n7 2\n");}

	void test_print_3 () {
		ostringstream w;
        vector< vector<int> > menList(2);
        int men[][2] = {{1,2},{1,2}};
        for (int i=0; i<2; ++i) {
            menList[i].assign(men[i],men[i]+2); }
        int int_points[] = {0,1};
        vector<int> vec_points(2);
        vec_points.assign(int_points,int_points+2);
		SMP_print(w,menList,vec_points);
		CPPUNIT_ASSERT(w.str() == "1 1\n2 2\n");}

	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestSMP);
	CPPUNIT_TEST(test_read_single_num_1);
	CPPUNIT_TEST(test_read_single_num_2);
	CPPUNIT_TEST(test_read_single_num_3);
	CPPUNIT_TEST(test_read_1);
	CPPUNIT_TEST(test_read_2);
	CPPUNIT_TEST(test_read_3);
	CPPUNIT_TEST(test_eval_1);
	CPPUNIT_TEST(test_eval_2);
	CPPUNIT_TEST(test_eval_3);
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);
	CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestSMP.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestSMP::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;}
