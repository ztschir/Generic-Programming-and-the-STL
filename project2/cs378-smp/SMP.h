#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

// ---------------
// Women structure
// ---------------

/**
 * Stores a pref array where idx = index of the man in woman's preference list, 
 * value = position of the man in woman's preference list.
 * Stores the idx of the man the woman is engaged to, or 0 if she is not engaged. 
 * @param pref[] an array of ints, size 501
 * @param manEngagedWith an int 
 */
struct Women {
  int pref[501];
  int manEngagedWith; 
};

// -------------
// Men structure
// -------------

/**
 * Stores a pref array where idx = position of the woman in man's preference list, 
 * value = index of the woman in man's preference list.
 * Stores a pointer to the position of the last women in pref that has been processed + 1, innitially 1. 
 * @param pref[] an array of ints, size 501
 * @param position an int 
 */
struct Men {
  int pref[501];
  int position; 
};

// ------------------
// Men[] global array
// ------------------

/**
 * Stores an array of all men 
 */
Men men[501];

// --------------------
// Women[] global array
// --------------------

/**
 * Stores an array of all women 
 */
Women women[501];

// ---------------
// readTestCaseSMP
// ---------------

/**
 * reads the number of test cases
 * @param r a std::istream
 * @return the number of test cases
 */
int readTestCaseSMP(std::istream& r){
  int t;	
  r >> t;
  assert(t > 0); 
  return t;
}

// -------
// readSMP
// -------

/**
 * reads the number of pairs, the men and the women
 * @param r a std::istream
 * @param men[] an array of men (global)
 * @param women[] an array of women (global)
 * @param unengagedMen[] an array of ints, stores the idx of all unengaged men
 * @return number of pairs
 */
int readSMP(std::istream& r, Men men[], Women women[], int unengagedMen[]) {
  int t, garbage_collector, k;
  r >> t;
  assert(t > 0);
 	
  for (int i = 1; i <= t; ++i) {
    r >> garbage_collector;
    for (int j = 1; j <= t; ++j) {
      r >> k;
	  assert(k > 0);
      women[i].pref[k] = j;
    }
    women[i].pref[0] = t+1;
    women[i].manEngagedWith = 0;
  } 
    
  for (int i = 1; i <= t; ++i) {
    r >> garbage_collector;
    unengagedMen[i] = i;
    men[i].position = 1;
    for (int j = 1; j <= t; ++j) {
      r >> men[i].pref[j];
	  assert(men[i].pref[j] > 0);
    }
  }
  
  assert(t > 0);
  return t;
}

// --------
// writeSMP
// --------

/**
 * writes the correct answer of the program
 * @param w a std::ostream
 * @param men[] an array of men (global)
 * @param women[] an array of women (global)
 * @param numberOfPairs an int passed by value
 */
void writeSMP(std::ostream& w, Women women[], int numberOfPairs){
   int pairs[501];
   for(int i = 1; i <= numberOfPairs; ++i){
      pairs[women[i].manEngagedWith] = i;
   }

   for(int i = 1; i <= numberOfPairs; ++i){
      assert(pairs[i] > 0);
      w << i << " " << pairs[i] << std::endl;
   }
}

// -------
// evalSMP
// -------

/**
 * Assigns a man for each woman
 * @param men[] an array of men (global)
 * @param women[] an array of women (global)
 * @param unengagedMen[] an array of ints, stores the idx of all unengaged men
 * @param numberOfPairs an int passed by value 
 */
void evalSMP(Men men[], Women women[], int* unengagedMen, int numberOfPairs) {
   int* ptr = unengagedMen + numberOfPairs;
   while(ptr != unengagedMen) {

     Men& m = men[*ptr];     // choosing an unengaged man
	 assert(m == men[*ptr]);
	 
     Women& currentWoman = women[m.pref[m.position]]; 
	 assert(currentWoman == women[m.pref[m.position]]);
	 
     m.position++; // move ptr to next women in pref list

     // if the woman is currently engaged, identify her current partner, 
     //  compare and replace if needed

     if(currentWoman.pref[currentWoman.manEngagedWith] > currentWoman.pref[*ptr]){
	 
        int temp = currentWoman.manEngagedWith; // pass by value
        currentWoman.manEngagedWith = *ptr;
        if(temp != 0){
           *ptr = temp;
        }
        else --ptr;
     }
	 assert(*ptr >= 0);
   }
}

// --------
// solveSMP
// --------

/**
 * Solves the problem
 * @param r a std::istream
 * @param w a std::ostream 
 */
void solveSMP(std::istream& r, std::ostream& w){
    // 501 to get rid of the 0 index reference
    int unengagedMen[501];
    int numOfTestCases = readTestCaseSMP(r);
    assert(numOfTestCases > 0);

    for(int currentTestCase = 0; currentTestCase < numOfTestCases; ++currentTestCase){
        int numberOfEngagements = readSMP(r, men, women, unengagedMen);
        evalSMP(men, women, unengagedMen, numberOfEngagements);
        writeSMP(w, women, numberOfEngagements);
    }
}
