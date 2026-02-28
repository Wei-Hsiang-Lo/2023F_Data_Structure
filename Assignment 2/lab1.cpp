#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

int main(){
    long numSt;
    cin >> numSt;
    long *interval = (long *)malloc(sizeof(long) * 2 * numSt + 5);//save the interval of each student
    long *index = (long *)malloc(sizeof(long) * numSt + 5);

    for(int i = 0; i < 2 * numSt; i++){
        cin >> interval[i];
    }//input the beginning and the end of each student
    for(int i = 0; i < numSt; i++){
        char *compare = (char *)malloc(sizeof(char ) * 1000000000);
        memset(compare + interval[2 * i] , '+', interval[2 * i + 1] - interval[2 * i] + 1);
        for(int j = 0; j < numSt; j++){
            if(j != i && compare[interval[ 2 * j]] == '+' && compare[interval[ 2 * j + 1]] == '+'){
                res1[i] = 1;
                break;
            }
            else
                res1[i] = 0;
        }
        free(compare);
    }
    for(int i = 0; i < numSt; i++){
        char *compare = (char *)malloc(sizeof(char ) * 1000000000);
        memset(compare + interval[2 * i] , '+', interval[2 * i + 1] - interval[2 * i] + 1);
        for(int j = 0; j < numSt; j++){
            if(j != i && compare[interval[ 2 * j] - 1] != '+' && compare[interval[ 2 * j + 1] + 1] != '+'){
                res2[i] = 1;
                break;
            }
            else
                res2[i] = 0;
        }
        free(compare);
    }
    
    for(int i = 0; i < numSt; i++){
        cout << res1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < numSt; i++){
        cout << res2[i] << " ";
    }
    cout << endl;
    cout << time;
    
    return 0;
}