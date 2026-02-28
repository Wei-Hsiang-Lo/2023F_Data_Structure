#include <iostream>
#include <ctime>//this library is used to calculate the CPU time
#include <iomanip>//this library is used to set the precision of the CPU time
using namespace std;

void straight(int* ele, pair<int, int>& query);//the function uses the straight method to find the maximum

int segmentQuery(int* arr, int l, int r, int L, int R);//this function uses the segment tree method to find the maximum

int main(){
    int eleNum = 0, qNum = 0;
    clock_t start_1, end_1, start_2, end_2;
    double time_1, time_2;

    cout << "Enter the number of the element : ";
    cin >> eleNum;
    int* ele = new int[eleNum];//reallocate memory for the array (save the input element as X0, x1, ..., Xi) which has unknown size
    int used[eleNum + 10] = {0};
	int j;
	for(j = 0; j < eleNum; j++){
		//since the random number(the compiler offered) is range from 0 ~ 32767 so I do the methods below to deal with it.
		int temp = ((rand() << 15) + rand()) % eleNum + 1;
		//the used array record the numbers which had been generated.
        if(used[temp] == 0){
            ele[j] = temp;
            }
            else{
                j--;
            }
		}
    
    cout << "Enter the number of the queries : ";
    cin >> qNum;

    pair<int, int>* query = new pair<int, int>[qNum];//reallocate memory for the array (save the query of an interval) which has unknown size
    for(int i = 0; i < qNum; i++){
        cin >> query[i].first >> query[i].second;
    }
    cout << "The result of the straight method : " << endl;
    start_1 = clock();
    for(int i = 0; i < qNum; i++){
        //if the input index is valid, find the maximum between the interval through the straight method
        if(query[i].first >= 0 && query[i].second < eleNum && query[i].first <= query[i].second)
            straight(ele, query[i]);
        //if the input index is invalid, print the error message
        else
            cout << "The " << i + 1 << " query has the wrong index value." << endl;
    }
    end_1 = clock();

    cout << "\nThe result of the segment tree method : " << endl;
    start_2 = clock();
    for(int i = 0; i < qNum; i++){
        //if the input index is valid, find the maximum between the interval through the segment tree method
        if(query[i].first >= 0 && query[i].second < eleNum && query[i].first <= query[i].second)
            cout << "The maximum element between index "<< query[i].first << " and " << query[i].second << " is " << segmentQuery(ele, query[i].first, query[i].second, 0, eleNum - 1) << endl;
        //if the input index is invalid, print the error message
        else
            cout << "The " << i + 1 << " query has the wrong index value." << endl;
    }
    end_2 = clock();

    time_1 = (double)(end_1 - start_1) / CLOCKS_PER_SEC;
    time_2 = (double)(end_2 - start_2) / CLOCKS_PER_SEC;
    //print the CPU time of two methods to compare the efficiency
    cout << "\nThe CPU time of the straight method used is : " << fixed << setprecision(10) << time_1 << endl;
    cout << "The CPU time of the segment tree method used is : " << fixed << setprecision(10) << time_2 << endl;
    delete[] ele;
    delete[] query;

    return 0;
}

void straight(int* ele, pair<int, int>& query){
    int ind = query.first;
    for(int i = query.first; i <= query.second; i++){
        if(ele[ind] < ele[i])
            ind = i;
    }
    cout << "The maximum element between index "<< query.first << " and " << query.second << " is " << ele[ind] << "." << endl;
}

int segmentQuery(int* arr, int l, int r, int L, int R){
    if(L == R)
        return arr[L];
    int m = (L + R) / 2;
    if(r <= m)
        return segmentQuery(arr, l, r, L, m);//find the part of the left subtree
    else if(l > m)
        return segmentQuery(arr, l, r, m + 1, R);//find the part of the right subtree
    else{
        //compare the maximum of the left subtree and the maximum of the right subtree, then return the bigger one
        if(segmentQuery(arr, l, r, L, m) > segmentQuery(arr, l, r, m + 1, R))
            return segmentQuery(arr, l, r, L, m);
        else
            return segmentQuery(arr, l, r, m + 1, R);
    }
}