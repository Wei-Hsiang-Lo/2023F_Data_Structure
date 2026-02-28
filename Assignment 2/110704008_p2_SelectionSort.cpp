#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<cstdlib>
using namespace std;

void sSort(int data[], int n);

int main(){
	const int n1 = 10000, n2 = 100000;
	srand(time(NULL));
	cout << setw(10) << "n" <<  setw(20) << "Selection Sort" << endl;
	//the following step calculate the CPU time that each sorting methods cost
	for(int i = n1; i <= n2; i++){
		double sTime = 0;
		int data[i];
		int used[i + 10] = {0};
		int j, k;
		for(j = 0; j < i; j++){
			int temp = rand() % i + 1;
            if(used[temp] == 0)
            {
                data[j] = temp;
                used[temp] = 1;
            }
            else
            {
                j--;
            }
		}
		clock_t clicks2 = clock();
		sSort(data, i);
		clicks2 = clock() - clicks2;
		sTime += (double)clicks2 / CLOCKS_PER_SEC;
		cout << setw(10) << i << setw(20) << sTime << endl;
		for(int j = 0; j < i; j++){
			cout << data[j] << " ";
		}
	}
	
	system("PAUSE");
	return 0;
}

void sSort(int data[], int n){
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(data[i] > data[j])
			{
				int tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}
}