#include<iostream>
#include<cstring>
#include<sstream>
#include<cstdlib>
using namespace std;

bool isLeapYear(int year);

bool isLegal(int year, int month, int day);

string weekDay(int w);

int main()
{
	string date_str[3];
	string date_cin;
	string Day;
	int w;
	int date_int[3];
	int i = 0;
	cout << "Enter the date (e.g: yyyy/mm/dd) : ";
	cin >> date_cin;
	stringstream ss;
	ss << date_cin;
	while (i <= 2){
		getline(ss, date_str[i], '/');
		date_int[i] = stoi(date_str[i]);
		i++;
	}
	//check if the user enters the right value
	if(!(isLegal(date_int[0], date_int[1], date_int[2])))
		cout << "WRONG FORMAT!!" << endl;
	//use this formula to calculate the day of the week
	w = (date_int[2] + 2 * date_int[1] + 3 * (date_int[1] + 1) / 5 + date_int[0] + date_int[0] / 4 - date_int[0] / 100 + date_int[0] / 400) % 7;
	Day = weekDay(w);
	cout << "It is " << Day << ".\n";
	
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
	if(year < 0 || month <= 0 || month >= 12 || day <= 0)
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

string weekDay(int w){
	string tmp[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	return tmp[w];
}
