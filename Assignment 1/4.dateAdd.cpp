#include<iostream>
#include<cstring>
#include<sstream>
#include<cstdlib>
using namespace std;

bool isLeapYear(int year);

bool isLegal(int year, int month, int day);

int main()
{
	string date_str[3];
	string date_cin;
	string Day;
	int daysAdd, sum = 0;
	int date_int[3];
	int ind = 0;
	int leapY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int notLeapY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	cout << "Enter the date (e.g: yyyy/mm/dd) : ";
	cin >> date_cin;
	stringstream ss;
	ss << date_cin;
	while (ind <= 2){
		getline(ss, date_str[ind], '/');
		date_int[ind] = stoi(date_str[ind]);
		ind++;
	}
	cout << "Enter an integer n to get n days after " << date_str[1] << " " << date_str[2] << ", " << date_str[0] << " : ";
	cin >> daysAdd;
	//check if the user enters the right value
	if(!(isLegal(date_int[0], date_int[1], date_int[2])))
		cout << "WRONG FORMAT!!" << endl;
	//use this formula to calculate the day of the week
	
	if(date_int[0] > 1){
		for(int i = 1; i < date_int[0]; i++){
			if(isLeapYear(i))
				sum += 366;
			else
				sum += 365;
		}
	}
	if(date_int[1] > 1){
		for(int i = 0; i < date_int[1] - 1; i++){
			if(isLeapYear(date_int[0]))
				sum += leapY[i];
			else
				sum += notLeapY[i];
		}
	}
	sum += date_int[2];
	sum += daysAdd;

	//count how many year need to be added to the year
	int countYear = 1;
	while((sum >= 366 && isLeapYear(countYear)) || (sum >= 365 && !isLeapYear(countYear))){
		if(isLeapYear(countYear))
			sum -= 366;
		else
			sum -= 365;
		countYear++;
	}
	date_int[0] = countYear;
	
	//cout how many month need to be added to the month
	int countMonth = 0;
	if(isLeapYear(date_int[0])){
		while(sum >= leapY[countMonth]){
			sum -= leapY[countMonth];
			countMonth++;
		}
		date_int[1] = countMonth + 1;
	}
	else{
		while(sum >= notLeapY[countMonth]){
			sum -= notLeapY[countMonth];
			countMonth++;
		}
		date_int[1] = countMonth + 1;
	}
	date_int[2] = sum;
	
	cout << "Date after " << daysAdd << " days is " << date_int[1] << " " << date_int[2] << " ," << date_int[0] << endl;
	
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