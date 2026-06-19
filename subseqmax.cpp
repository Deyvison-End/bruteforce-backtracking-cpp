#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <vector>

unsigned long long count_ssm = 0;

using namespace std;



// start e finish: início e final sendo testado agora;
// ini e end: onde são retornados o início e final da melhor sequência
// retorno é a soma da maior sequência
int subseqMaxBF(const vector<int> &array, int & ini, int & end) {
	
	int maior;
	int soma;
	int TAM = array.size();
	for(int i = 0; i < TAM; i++)
	{
	    soma = 0;
	    if(i == 0){maior = array[i];}
	    for(int j = i; j < TAM; j++)
	    {
	       soma += array[j]; 
	       if(soma > maior)
	       {
	           ini = i; 
	           end = j;
	           maior = soma;
	       }
	    }
	    
	}
	return maior;
}


void runSubseqMax(const char * name, int subseqmax(const vector<int> &, int&, int&), const vector<int> & array, bool printSeq) {
	using namespace std::chrono;

	count_ssm = 0;

	int ini = 0, end = 0;

	auto start = high_resolution_clock::now();

	int max = subseqmax(array, ini, end);

	auto finish = high_resolution_clock::now();
	long elapsed = duration_cast<nanoseconds>(finish-start).count() / 1000;

	cout << name << ": " << max << " ";


	cout << "[time: "<< setw(6) << setfill(' ') << elapsed << "us] ";
	cout << "[count: " << setw(6) << setfill(' ') << count_ssm << "] ";

	if (printSeq) {
		cout << "[ ";
		for (int i = ini; i <= end; i++) cout << array[i] << " ";
		cout << "] ";
	}

	cout << endl;
}


int subseqmax() {
	bool printSeq = true;
	int size = 30;

	srand(12345);

	vector<int> array(size);

	cout << endl << "******* SUBSEQMAX *******" << endl << endl;

	for (int i = 0; i < 10; i++) {

		for (int j = 0; j < size; j++) {
			array[j] = (rand() % (3 * size)) - (rand() % (4 * size));
		}

		cout <<"Test " << i << ": ";
		if (printSeq) {
			for (auto v : array) cout << v << " ";
		}
		cout << endl;

		runSubseqMax("Bruteforce     ", subseqMaxBF, array, printSeq);
			}

	return 0;
}






