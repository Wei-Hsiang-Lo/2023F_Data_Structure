#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<cstdlib>
using namespace std;

void hSort(int data[], int n);

void heapify(int data[], int n, int i);

int main(){
	const int n1 = 40000, n2 = 100000;
	srand(time(NULL));
	cout << setw(10) << "n" <<  setw(20) << "Heap Sort" << endl;
	//the following step calculate the CPU time that each sorting methods cost
	for(int i = n1; i <= n2; i+=10000){
		double hTime = 0;
		int data[i];
  		int used[i + 10] = {0};
		int j;
		for(j = 0; j < i; j++){
			int temp = ((rand() << 15) + rand()) % i + 1;
            if(used[temp] == 0){
                data[j] = temp;
                used[temp] = 1;
            }
            else{
                j--;
            }
		}
		clock_t clicks5 = clock();
		hSort(data, i);
		clicks5 = clock() - clicks5;
		hTime += (double)clicks5 / CLOCKS_PER_SEC;
		cout << setw(10) << i << setw(20) << hTime << endl;
		for(int j = 0; j < i; j++){
			cout << data[j] << " ";
		}
	}
	
	system("PAUSE");
	return 0;
}

void hSort(int data[], int n){
	for(int i = n / 2 - 1; i >= 0; i--)
		heapify(data, n, i);
	for(int i = n - 1; i > 0; i--){
		int temp = data[0];
		data[0] = data[i];
		data[i] = temp;
		heapify(data, i, 0);
	}
}

void heapify(int data[], int n, int i){
	//initialize largest as root
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	
	if(l < n && data[l] > data[largest])
		largest = l;	
	if(r < n && data[r] > data[largest])
		largest = r;
	if(largest != i){
		int temp = data[i];
		data[i] = data[largest];
		data[largest] = temp;
		heapify(data, n, largest);
	}
}