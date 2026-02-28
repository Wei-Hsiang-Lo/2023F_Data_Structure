#include<iostream>
#include<cmath>
using namespace std;

bool isLeapYear(int year);

int main(){
	int year_1, year_2, month_1, month_2, day_1, day_2;
	int sum_1 = 0, sum_2 = 0;
	int leapY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int notLeapY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	cout << "Enter the first date : ";
	cin >> year_1 >> month_1 >> day_1;
	cout << "Enter the second date : ";
	cin >> year_2 >> month_2 >> day_2;
	
	for(int i = 0; i < year_1; i++){
		if(isLeapYear(year_1))
			sum_1 = sum_1 + 366;
		else
			sum_1 = sum_1 + 365;
	}
	if(month_1 > 1){
		for(int i = 1; i < month_1 - 1; i++){
			if(isLeapYear(year_1))
				sum_1 = sum_1 + leapY[i];
			else
				sum_1 = sum_1 + notLeapY[i];
		}
	}
	sum_1 = sum_1 + day_1;
	
	for(int i = 0; i < year_2; i++){
		if(isLeapYear(year_2))
			sum_2 = sum_2 + 366;
		else
			sum_2 = sum_2 + 365;
	}
	if(month_2 > 1){
		for(int i = 1; i < month_2 - 1; i++){
			if(isLeapYear(year_2))
				sum_2 = sum_2 + leapY[i];
			else
				sum_2 = sum_2 + notLeapY[i];
		}
	}
	sum_2 = sum_2 + day_2;
	cout << abs(sum_1-sum_2) << endl;
	
	return 0;
}

bool isLeapYear(int year){
	if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	return false;
}