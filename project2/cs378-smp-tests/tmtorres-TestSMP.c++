// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "SMP.h"

using namespace std;

// -----------
// TestCollatz
// -----------

struct TestSMP : CppUnit :: TestFixture {
    // ----
    // read
    // ----
    
    void test_man1 () 
	{
        man m;
        
        m.setName(11);
        m.addPref(54);
        m.addPref(21);
        
        CPPUNIT_ASSERT(m.getName()    == 11);
        CPPUNIT_ASSERT(m.getHighest() == 54);
        CPPUNIT_ASSERT(m.getHighest() == 21);
	}
    
    void test_man2 () 
	{
        man m;
        
        m.setName(241);
        m.addPref(99);
        m.addPref(2);
        
        CPPUNIT_ASSERT(m.getName()    == 241);
        CPPUNIT_ASSERT(m.getHighest() == 99);
        CPPUNIT_ASSERT(m.getHighest() == 2);
        
	}
    
    void test_man3 () 
	{
        man m;
        
        m.setName(45);
        m.addPref(87);
        m.addPref(219);
        
        CPPUNIT_ASSERT(m.getName()    == 45);
        CPPUNIT_ASSERT(m.getHighest() == 87);
        CPPUNIT_ASSERT(m.getHighest() == 219);
	}
    
    void test_woman1 () 
	{
        woman w;
        man x;
        man y;
        
        x.setName(56);
        y.setName(43);
        
        CPPUNIT_ASSERT(w.isPartnered() == false);
        
        w.addPref(21, 56);
        w.addPref(32, 43);
        
        w.setPartner(x);
        
        CPPUNIT_ASSERT(w.isPartnered() == true);
        CPPUNIT_ASSERT(w.compare(y) == 56);
        CPPUNIT_ASSERT(w.getPartner().getName() == 56);
	}
    
    
    void test_woman2 () 
	{
        woman w;
        man x;
        man y;
        
        x.setName(122);
        y.setName(84);
        
        CPPUNIT_ASSERT(w.isPartnered() == false);
        
        w.addPref(98, 122);
        w.addPref(75, 84);
        
        w.setPartner(x);
        
        CPPUNIT_ASSERT(w.isPartnered() == true);
        CPPUNIT_ASSERT(w.compare(y) == 84);
        CPPUNIT_ASSERT(w.getPartner().getName() == 122);
        
	}
    
    
    void test_woman3 () 
	{
        woman w;
        man x;
        man y;
        
        x.setName(279);
        y.setName(23);
        
        CPPUNIT_ASSERT(w.isPartnered() == false);
        
        w.addPref(1, 279);
        w.addPref(5, 23);
        
        w.setPartner(y);
        
        CPPUNIT_ASSERT(w.isPartnered() == true);
        CPPUNIT_ASSERT(w.compare(x) == 279);
        CPPUNIT_ASSERT(w.getPartner().getName() == 23);
	}
    
    void test_read1 () 
	{
        int n = 3;
        std::istringstream r("1 3 2 1\n2 2 1 3\n3 1 2 3\n1 1 2 3\n2 3 2 1\n3 2 1 3\n");
        
        queue<man> m;
        vector<woman> w (n + 1);
        
        const bool b = smp_read(r, n, m, w);
        
        man x = m.front();
        man y = m.back();
        
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(x.getName() == 1);
        CPPUNIT_ASSERT(y.getName() == 3);
        CPPUNIT_ASSERT(x.getHighest() == 1);
        CPPUNIT_ASSERT(y.getHighest() == 2);
	}
    
    void test_read2 () 
	{
        int n = 3;
        std::istringstream r("1 1 2 3\n2 3 2 1\n3 3 2 1\n1 2 1 3\n2 1 3 2\n3 3 1 2\n");
        
        queue<man> m;
        vector<woman> w (n + 1);
        
        const bool b = smp_read(r, n, m, w);
        
        man x = m.front();
        man y = m.back();
        
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(x.getName() == 1);
        CPPUNIT_ASSERT(y.getName() == 3);
        CPPUNIT_ASSERT(x.getHighest() == 2);
        CPPUNIT_ASSERT(y.getHighest() == 3);
	}
    
    void test_read3 () 
	{
        int n = 3;
        std::istringstream r("1 2 1 3\n2 3 1 2\n3 2 1 3\n1 2 1 3\n2 1 2 3\n3 3 2 1\n");
        
        queue<man> m;
        vector<woman> w (n + 1);
        
        const bool b = smp_read(r, n, m, w);
        
        man x = m.front();
        man y = m.back();
        
        CPPUNIT_ASSERT(b == true);
        CPPUNIT_ASSERT(x.getName() == 1);
        CPPUNIT_ASSERT(y.getName() == 3);
        CPPUNIT_ASSERT(x.getHighest() == 2);
        CPPUNIT_ASSERT(y.getHighest() == 3);
	}
    
    // ----
    // arrange
    // ----
    
    void test_arrange1 () 
    {
        std::istringstream r("1 3 2 1\n2 2 1 3\n3 1 2 3\n1 1 2 3\n2 3 2 1\n3 2 1 3\n");
        
        int n = 3;
        queue<man> m;
        vector<woman> w (n + 1);
        vector<int> p (n + 1);
        
        smp_read(r, n, m, w);
        smp_arrange(m, w, p);
        
        CPPUNIT_ASSERT(p[1] == 1);
        CPPUNIT_ASSERT(p[2] == 3);
        CPPUNIT_ASSERT(p[3] == 2);
    }
    
    void test_arrange2 () 
    {
        std::istringstream r("1 1 2 3\n2 3 2 1\n3 3 2 1\n1 2 1 3\n2 1 3 2\n3 3 1 2\n");
        
        int n = 3;
        queue<man> m;
        vector<woman> w (n + 1);
        vector<int> p (n + 1);
        
        smp_read(r, n, m, w);
        smp_arrange(m, w, p);
        
        CPPUNIT_ASSERT(p[1] == 2);
        CPPUNIT_ASSERT(p[2] == 1);
        CPPUNIT_ASSERT(p[3] == 3);
    }
    
    void test_arrange3 ()  
    {
        std::istringstream r("1 2 1 3\n2 3 1 2\n3 2 1 3\n1 2 1 3\n2 1 2 3\n3 3 2 1\n");
        
        int n = 3;
        queue<man> m;
        vector<woman> w (n + 1);
        vector<int> p (n + 1);
        
        smp_read(r, n, m, w);
        smp_arrange(m, w, p);
        
        CPPUNIT_ASSERT(p[1] == 2);
        CPPUNIT_ASSERT(p[2] == 1);
        CPPUNIT_ASSERT(p[3] == 3);
    }
    
    
    // -----
    // print
    // -----
    
    void test_print1 () 
    {
        std::ostringstream w;
        int myints[] = {0, 4, 2, 3, 1};
        vector<int> p (myints, myints + sizeof(myints) / sizeof(int));
        
        smp_print(w, p);
        
        CPPUNIT_ASSERT(w.str() == "1 4\n2 2\n3 3\n4 1\n");
    }
    
    
    void test_print2 () 
    {
        std::ostringstream w;
        int myints[] = {0, 2, 4, 1, 3};
        vector<int> p (myints, myints + sizeof(myints) / sizeof(int));
        
        smp_print(w, p);
        
        CPPUNIT_ASSERT(w.str() == "1 2\n2 4\n3 1\n4 3\n");
    }
    
    void test_print3 () 
    {
        std::ostringstream w;
        int myints[] = {0, 1, 4, 2, 3};
        vector<int> p (myints, myints + sizeof(myints) / sizeof(int));
        
        smp_print(w, p);
        
        CPPUNIT_ASSERT(w.str() == "1 1\n2 4\n3 2\n4 3\n");
    }
    
    // -----
    // solve
    // -----
    
    void test_solve1 () 
	{
        std::istringstream r("1\n3\n1 3 2 1\n2 2 1 3\n3 1 2 3\n1 1 2 3\n2 3 2 1\n3 2 1 3\n");
        ostringstream w;
        smp_solve(r, w);
        
        CPPUNIT_ASSERT(w.str() == "1 1\n2 3\n3 2\n");
	}
    
    void test_solve2 () 
	{
        std::istringstream r("1\n3\n1 1 2 3\n2 3 2 1\n3 3 2 1\n1 2 1 3\n2 1 3 2\n3 3 1 2\n");
        ostringstream w;
        smp_solve(r, w);
        
        CPPUNIT_ASSERT(w.str() == "1 2\n2 1\n3 3\n");
	}
    
    void test_solve3 () 
	{
        std::istringstream r("1\n3\n1 2 1 3\n2 3 1 2\n3 2 1 3\n1 2 1 3\n2 1 2 3\n3 3 2 1\n");
        ostringstream w;
        smp_solve(r, w);
        
        CPPUNIT_ASSERT(w.str() == "1 2\n2 1\n3 3\n");
	}
    
    // -----
    // suite
    // -----
    
    CPPUNIT_TEST_SUITE(TestSMP);
    CPPUNIT_TEST(test_man1);
	CPPUNIT_TEST(test_man2);
	CPPUNIT_TEST(test_man3);
	CPPUNIT_TEST(test_woman1);
	CPPUNIT_TEST(test_woman2);
	CPPUNIT_TEST(test_woman3);
	CPPUNIT_TEST(test_read1);
	CPPUNIT_TEST(test_read2);
    CPPUNIT_TEST(test_read3);
    CPPUNIT_TEST(test_arrange1);
    CPPUNIT_TEST(test_arrange2);
    CPPUNIT_TEST(test_arrange3);
    CPPUNIT_TEST(test_print1);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_solve1);
    CPPUNIT_TEST(test_solve2);
    CPPUNIT_TEST(test_solve3);
    
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