#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<cstdlib>
using namespace std;

void mSort(int data[], int l, int r);

void merge(int data[], int l, int m, int r);

int main(){
	const int n1 = 50000, n2 = 100000;
	srand(time(NULL));
	cout << setw(10) << "n" <<  setw(20) << "Merge Sort" << endl;
	//the following step calculate the CPU time that each sorting methods cost
	for(int i = n1; i <= n2; i++){
		double mTime = 0;
		int data[i] = {0};
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
		clock_t clicks4 = clock();
		mSort(data, 0, i - 1);
		clicks4 = clock() - clicks4;
		mTime += (double)clicks4 / CLOCKS_PER_SEC;
		cout << setw(10) << i << setw(20) << mTime << endl;
		for(int j = 0; j < i; j++){
			cout << data[j] << " ";
		}
	}
	
	system("PAUSE");
	return 0;
}

void merge(int data[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (i = 0; i < n1; i++)
		L[i] = data[l + i];
	for (j = 0; j < n2; j++)
		R[j] = data[m + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			data[k] = L[i];
			i++;
		}
		else {
			data[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		data[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		data[k] = R[j];
		j++;
		k++;
	}
}

void mSort(int data[], int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;
		mSort(data, l, m);
		mSort(data, m + 1, r);

		merge(data, l, m, r);
	}
}