#include <iostream>
#include <ctime>
using namespace std;

int main(){
    int data1[100], data2[100], data3[100], data4[100], data5[100];
    srand(time(NULL));
    int used[110] = {0};
	for(int i = 0; i < 100; i++){
		//since the random number(the compiler offered) is range from 0 ~ 32767 so I do the methods below to deal with it.
		int temp = (rand()) % 100 + 1;
		//the used array record the numbers which had been generated.
        if(used[temp] == 0){
            data1[i] = temp;
            data2[i] = temp;
            data3[i] = temp;
            data4[i] = temp;
            data5[i] = temp;
            used[temp] = 1;
        }
        else{
            i--;
        }
    }

    return 0;
}