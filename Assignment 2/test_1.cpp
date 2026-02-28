#include <iostream>
#include <ctime>
using namespace std;

int main(){
    int data1[100], data2[100];
    srand(time(NULL));
    int used[110] = {0};
	for(int i = 0; i < 100; i++){
		//since the random number(the compiler offered) is range from 0 ~ 32767 so I do the methods below to deal with it.
		int temp = (rand()) % 100 + 1;
		//the used array record the numbers which had been generated.
        if(used[temp] == 0){
            data1[i] = temp;
            used[temp] = 1;
        }
        else{
            i--;
        }
    }
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 100; i++){
            data2[i] = data1[i];
        }
    }

    return 0;
}