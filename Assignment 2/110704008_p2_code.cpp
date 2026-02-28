#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;

int data1[100000], data2[100000], data3[100000], data4[100000], data5[100000];

void iSort(int data[], int n);

void sSort(int data[], int n);

void qSort(int data[], int left, int right);

void mSort(int data[], int l, int r);

void merge(int data[], int l, int m, int r);

void hSort(int data[], int n);

void heapify(int data[], int n, int i);

int main(){
	ifstream inFile;
	ofstream outFile;
	//cout the result in result.txt file. It can help me easily and clearly compare the result of each algorithms
	outFile.open("result1.txt");
	const int n1 = 10000, n2 = 100000;
	srand(time(NULL));
	outFile << setw(10) << "n" <<  setw(20) << "Insertion Sort" << setw(20) << "Selction Sort" << setw(15)
		<< "Quick Sort"<< setw(15) << "Merge Sort" << setw(15) << "Heap Sort" << endl;
	
	//the following step calculate the CPU time that each sorting methods cost
	for(int i = n1; i <= n2; i += 1000){
		double iTime = 0, sTime = 0, qTime = 0, mTime = 0, hTime = 0;
		int used[i + 10] = {0};
		int j;
		for(j = 0; j < i; j++){
			//since the random number(the compiler offered) is range from 0 ~ 32767 so I do the methods below to deal with it.
			int temp = ((rand() << 15) + rand()) % i + 1;
			//the used array record the numbers which had been generated.
            if(used[temp] == 0){
                data1[j] = temp;
                data2[j] = temp;
                data3[j] = temp;
                data4[j] = temp;
                data5[j] = temp;
                used[temp] = 1;
            }
            else{
                j--;
            }
		}
		//this part only calculate the time used in sorting
		clock_t clicks1 = clock();
		iSort(data1, i);
		clicks1 = clock() - clicks1;
		iTime += (double)clicks1 / CLOCKS_PER_SEC;
		
		clock_t clicks2 = clock();
		sSort(data2, i);
		clicks2 = clock() - clicks2;
		sTime += (double)clicks2 / CLOCKS_PER_SEC;
		
		clock_t clicks3 = clock();
		qSort(data3, 0, i - 1);
		clicks3 = clock() - clicks3;
		qTime += (double)clicks3 / CLOCKS_PER_SEC;
		
		clock_t clicks4 = clock();
		mSort(data4, 0, i - 1);
		clicks4 = clock() - clicks4;
		mTime += (double)clicks4 / CLOCKS_PER_SEC;
		
		clock_t clicks5 = clock();
		hSort(data5, i);
		clicks5 = clock() - clicks5;
		hTime += (double)clicks5 / CLOCKS_PER_SEC;
		outFile << setw(10) << i << setw(20) << iTime << setw(20) << sTime << setw(15)
			<< qTime << setw(15) << mTime << setw(15) << hTime << endl;
		//debug mode.
		for(int j = 0; j < i; j++){
			cout << setw(10) << data1[j] << setw(10) << data2[j] << setw(10) << data3[j] << setw(10)
				<< data4[j] << setw(10) << data5[j] << endl;
		}
	}
	outFile.close();
			
	system("PAUSE");
	return 0;
}

void iSort(int data1[], int n){
	for(int i = 1; i < n; i++){
		int y = data1[i];
		int j = i - 1;
		while(y < data1[j] && j >= 0){
			data1[j + 1] = data1[j];
			j--;
		}
		data1[j + 1] = y;
	}
}

void sSort(int data2[], int n){
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(data2[i] > data2[j])
			{
				int tmp = data2[i];
				data2[i] = data2[j];
				data2[j] = tmp;
			}
		}
	}
}

void qSort(int data3[], int left, int right){
	int i = left, j = right + 1, tmp;
	if(left < right){
		while(i < j){
			while(data3[++i] < data3[left]);
    		while(data3[--j] > data3[left]);
    		if(i >= j)
				break;
    		tmp = data3[i];
    		data3[i] = data3[j];
    		data3[j] = tmp;
    	}
    	tmp = data3[j];
    	data3[j] = data3[left];
    	data3[left] = tmp;
    	qSort(data3, left, j - 1);
    	qSort(data3, j + 1, right);
  	}
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
		//the devide part
		mSort(data, l, m);
		mSort(data, m + 1, r);
		//the conquer part
		merge(data, l, m, r);
	}
}

void hSort(int data5[], int n){
	for(int i = n / 2 - 1; i >= 0; i--)
		heapify(data5, n, i);
	for(int i = n - 1; i > 0; i--){
		int temp = data5[0];
		data5[0] = data5[i];
		data5[i] = temp;
		heapify(data5, i, 0);
	}
}

void heapify(int data5[], int n, int i){
	//initialize largest as root
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if(l < n && data5[l] > data5[largest])
		largest = l;
	if(r < n && data5[r] > data5[largest])
		largest = r;
	if(largest != i){
		int temp = data5[i];
		data5[i] = data5[largest];
		data5[largest] = temp;
		heapify(data5, n, largest);
	}
}