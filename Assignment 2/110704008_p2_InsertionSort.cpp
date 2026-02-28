#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<cstdlib>
using namespace std;

void iSort(int data[], int n);

int main(){
	const int n1 = 10000, n2 = 100000;
	srand(time(NULL));
	cout << setw(10) << "n" <<  setw(20) << "Insertion Sort" << endl;
	//the following step calculate the CPU time that each sorting methods cost
	for(int i = n1; i <= n2; i++){
		double iTime = 0;
		int data[i];
		int used[i + 10] = {0};
		int j, k;
		for(j = 0; j < i; j++){
			int temp = rand() % i + 1;
            if(used[temp] == 0){
                data[j] = temp;
                used[temp] = 1;
            }
            else{
                j--;
            }
		}
		clock_t clicks1 = clock();
		iSort(data, i);
		clicks1 = clock() - clicks1;
		iTime += (double)clicks1 / CLOCKS_PER_SEC;
		cout << setw(10) << i << setw(20) << iTime << endl;
		for(int j = 0; j < i; j++){
			cout << data[j] << " ";
		}
	}
	
	system("PAUSE");
	return 0;
}

void iSort(int data[], int n){
	for(int i = 1; i < n; i++){
		int y = data[i];
		int j = i - 1;
		while(y < data[j] && j >= 0){
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = y;
	}
}
