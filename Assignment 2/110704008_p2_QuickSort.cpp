#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstring>
#include<cstdlib>
using namespace std;

void qSort(int data[], int left, int right);

int main(){
	const int n1 = 10000, n2 = 100000;
	srand(time(NULL));
	cout << setw(10) << "n" <<  setw(20) << "Quick Sort" << endl;
	//the following step calculate the CPU time that each sorting methods cost
	for(int i = n1; i <= n2; i++){
		double qTime = 0;
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
		clock_t clicks3 = clock();
		qSort(data, 0, i - 1);
		clicks3 = clock() - clicks3;
		qTime += (double)clicks3 / CLOCKS_PER_SEC;
		cout << setw(10) << i << setw(20) << qTime << endl;
		for(int j = 0; j < i; j++){
			cout << data[j] << " ";
		}
	}
	
	system("PAUSE");
	return 0;
}

void qSort(int data[], int left, int right){
	int i = left, j = right + 1, tmp;
	if(left < right){
		while(i<j){
			while(data[++i] < data[left]);
    		while(data[--j] > data[left]);
    		if(i >= j)
				break;
    		tmp = data[i];
    		data[i] = data[j];
    		data[j] = tmp;
    	}
    	tmp = data[j];
    	data[j] = data[left];
    	data[left] = tmp;
    	qSort(data, left, j - 1);
    	qSort(data, j + 1, right);
  	}
}