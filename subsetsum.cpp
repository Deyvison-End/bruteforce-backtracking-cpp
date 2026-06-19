#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long count_ssk = 0;


bool subsetSumBF(const vector<int> &array, int K, vector<bool> &subset) {
    
     int n = array.size();
    int total = 1 << n; 

    for (int mask = 0; mask < total; mask++) {
        int soma = 0;

        
        for (int i = 0; i < n; i++)
            subset[i] = false;

       
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                soma += array[i];
                subset[i] = true;
            }
        }

        if (soma == K)
            return true;
    }

    return false;
}

bool subsetSumBTRec(const vector<int> &array, int n, int k, vector<bool> &subset) {

    if(k == 0){return true;}
	
	if(k < 0 || n < 0){return false;}
	
	
	subset[n] = false;
    if (subsetSumBTRec(array,n - 1, k, subset))
        return true;
        
    subset[n] = true;
    if (subsetSumBTRec(array, n - 1, k - array[n], subset))
        return true;
        
	subset[n] = false;
    return false;
}

bool subsetSumBT(const vector<int> &array, int k, vector<bool> &subset) {
	return subsetSumBTRec(array, (int)array.size(), k, subset);
}


bool check_sum(const vector<int> &array, int sum, const vector<bool> &subset) {
	int cur_sum = 0;

	for (int i = 0; i < (int)array.size(); i++) {
		if (subset[i]) cur_sum += array[i];
	}

	return (cur_sum == sum);
}

void runSubsetSum(const char *name, bool subsetSum(const vector<int> &, int, vector<bool> &), const vector<int> &array, int sum) {
	using namespace std::chrono;

    count_ssk = 0;

	vector<bool> subset(array.size(), false);

	auto start = high_resolution_clock::now();

	bool found = subsetSum(array, sum, subset);

	auto finish = high_resolution_clock::now();
	long elapsed = duration_cast<nanoseconds>(finish - start).count() / 1000;

	bool valid = found && check_sum(array, sum, subset);

	cout << name << ": " << (found ? ( valid ? "YES " : "ERR " ): " NO ");

	cout << "[time: " << elapsed << "us] ";
	cout << "[count: " << count_ssk << "] ";
	if (found) {
		cout << "[ ";
		for (unsigned i = 0; i < array.size(); i++) {
			if (subset[i])
				cout << array[i] << " ";
		}
		cout << "] ";
	}
	cout << endl;

}


int subsetsum() {
	int size = 20;

	vector<int> array(size);

	srand(333);
//	srand(12345);

	for (int i = 0; i < size; i++) {
		cout << (array[i] = 1 + rand() % (size * 5)) << " ";
	}
	cout << endl;

	cout << endl << "******* SUBSETSUM *******" << endl << endl;

	int value = 0;
	for (int i = 0; i < 20; i++) {
		value += (rand() % (size * 6));
		cout << i << ": Trying " << value << " ..." << endl;

		runSubsetSum("Bruteforce   ", subsetSumBF, array, value);
		runSubsetSum("Backtracking ", subsetSumBT, array, value);
	}


	return 0;
}

