#include<iostream>
#include<cstring>
#include<sstream>
#include<cstdlib>
#include<cmath>
using namespace std;

bool isLeapYear(int year);

bool isLegal(int year, int month, int day);

int dateSub(int year_1, int year_2, int month_1, int month_2, int day_1, int day_2);

int main()
{
	string date_str1[3], date_str2[3];
	string date_cin1, date_cin2;
	
	int date_int1[3], date_int2[3];
	int i = 0;
	cout << "Enter the 1st date (e.g: yyyy/mm/dd) : ";
	cin >> date_cin1;
	stringstream ss1;
	ss1 << date_cin1;
	cout << "Enter the 2nd date (e.g: yyyy/mm/dd) : ";
	cin >> date_cin2;
	stringstream ss2;
	ss2 << date_cin2;
	
	while (i <= 2){
		getline(ss1, date_str1[i], '/');
		date_int1[i] = stoi(date_str1[i]);
		getline(ss2, date_str2[i], '/');
		date_int2[i] = stoi(date_str2[i]);
		i++;
	}
	
	//check if the user enters the right value
	if(!(isLegal(date_int1[0], date_int1[1], date_int1[2])))
		cout << "WRONG FORMAT!!" << endl;
	if(!(isLegal(date_int2[0], date_int2[1], date_int2[2])))
		cout << "WRONG FORMAT!!" << endl;
	//use this formula to calculate the day of the week
	cout << dateSub(date_int1[0], date_int2[0], date_int1[1], date_int2[1], date_int1[2], date_int2[2]) << endl;
	
	system("pause");
	return 0;
}

bool isLeapYear(int year){
	if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	return false;
}

bool isLegal(int year, int month, int day){
	int day_leapY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int day_notLeap[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(year <= 0 || month <= 0 || month >= 12 || day <= 0)
		return false;
	if(isLeapYear(year)){
		if(day_leapY[month - 1] >= day)
			return true;
	}
	else{
		if(day_notLeap[month - 1] >= day)
			return true;
	}
	return false;
}

int dateSub(int year_1, int year_2, int month_1, int month_2, int day_1, int day_2){
	int sum_1 = 0, sum_2 = 0;
	int leapY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int notLeapY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if(year_1 > 1){
		for(int i = 1; i < year_1; i++){
			if(isLeapYear(i))
				sum_1 += 366;
			else
				sum_1 += 365;
		}
	}
	if(month_1 > 1){
		for(int i = 0; i < month_1 - 1; i++){
			if(isLeapYear(year_1))
				sum_1 += leapY[i];
			else
				sum_1 += notLeapY[i];
		}
	}
	sum_1 += day_1;
	
	if(year_2 > 1){
		for(int i = 1; i < year_2; i++){
			if(isLeapYear(i))
				sum_2 += 366;
			else
				sum_2 += 365;
		}
	}
	
	if(month_2 > 1){
		for(int i = 0; i < month_2 - 1; i++){
			if(isLeapYear(year_2))
				sum_2 += leapY[i];
			else
				sum_2 += notLeapY[i];
		}
	}
	sum_2 += day_2;
	
	return abs(sum_1 - sum_2);
}