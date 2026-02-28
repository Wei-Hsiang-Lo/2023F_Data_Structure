#include<iostream>
using namespace std;

bool isLeapYear(int year);

int main(){
	int year, month, date, day, sum = 0;
	int leapY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int notLeapY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	cout << "Enter a date : ";
	cin >> year >> month >> date;
	cout << "Enter n days : ";
	cin >> day;
	
	if(year > 1){
		for(int i = 1; i < year; i++){
			if(isLeapYear(i))
				sum += 366;
			else
				sum += 365;
		}
	}
	if(month > 1){
		for(int i = 0; i < month - 1; i++){
			if(isLeapYear(year))
				sum += leapY[i];
			else
				sum += notLeapY[i];
		}
	}
	sum += date;
	sum += day;
	cout << sum << endl;

	//count how many year need to be added to the year
	int countYear = 1;
	while((sum >= 366 && isLeapYear(countYear)) || (sum >= 365 && !isLeapYear(countYear))){
		if(isLeapYear(countYear))
			sum -= 366;
		else
			sum -= 365;
		countYear++;
	}
	year = countYear;
	
	//cout how many month need to be added to the month
	int countMonth = 0;
	if(isLeapYear(year)){
		while(sum >= leapY[countMonth]){
			sum -= leapY[countMonth];
			countMonth++;
		}
		month = countMonth + 1;
	}
	else{
		while(sum >= notLeapY[countMonth]){
			sum -= notLeapY[countMonth];
			countMonth++;
		}
		month = countMonth + 1;
	}
	
	date = sum;
	cout << "Date after " << day << " days is " << month << " " << date << " ," << year << endl;
	
	return 0;
}

bool isLeapYear(int year){
	if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	return false;
}