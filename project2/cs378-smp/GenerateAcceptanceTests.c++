#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// ----
// main
// ----

/**
 * Generates acceptance tests
 */
int main(int argc, char *argv[]) {
	
	int numberOfTestCases = 200;
	vector< vector<int> > engagementsArray;
	
	srand ( time(NULL) );
	
	for(int i = 0; i < numberOfTestCases; ++i){
		vector<int> initalNumbers;
		int numberOfEngagements = rand() % 20;
		for(int j = 1; j < numberOfEngagements; ++j){
			initalNumbers.push_back(j);
		}
		engagementsArray.push_back(initalNumbers);
	}
	
	
	cout << numberOfTestCases << endl;
	
    
    
	for(vector<int> permutations : engagementsArray){
        vector<int> tempPermutations (permutations);
        
		int permutationsLength = permutations.size();
		cout << permutationsLength << endl;

		for(int k = 0; k < 2; ++k){
			int counter = 1;
            
			while(next_permutation(permutations.begin(), permutations.end()), counter <= permutationsLength){
				
				for(int permutationNumber: permutations){
					cout << permutationNumber << " ";
				}
				++counter;
				cout << endl;
			}
            permutations = tempPermutations;
		}
		
	}
	return 0;
}