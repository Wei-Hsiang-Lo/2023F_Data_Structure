#include<iostream>
#include<cstring>
#include<sstream>
#include<cmath>
#include<cstdlib>
using namespace std;

const int LEAPY[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int NOTLEAPY[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class TheDate{
public:
	TheDate();
	TheDate(int, int, int);
	int getYear();
	int getMonth();
	int getDay();
	void setYear(int newYear);
	void setMonth(int newMonth);
	void setDay(int newDay);
	bool isLeapYear(int year);
	void isLegal();
	string weekDay();
	string monthItoS(int month);
	int sumOfdays();
private:
	int year;
	int month;
	int day;
	int w;
};

int main(){
	TheDate date_1, date_2;
	string date_str1[3], date_str2[3];
	string date_cin1, date_cin2;
	char sub;
	int date_int1[3], date_int2[3];
	int i = 0;
	cout << "Enter the date 1 and date 2 to substract (e.g: yyyy/mm/dd - YYYY/MM/DD) : ";
	cin >> date_cin1 >> sub >> date_cin2;
	stringstream ss1, ss2;
	ss1 << date_cin1;
	ss2 << date_cin2;
	while (i <= 2){
		getline(ss1, date_str1[i], '/');
		date_int1[i] = stoi(date_str1[i]);
		getline(ss2, date_str2[i], '/');
		date_int2[i] = stoi(date_str2[i]);
		i++;
	}
	
	date_1.setYear(date_int1[0]);
	date_1.setMonth(date_int1[1]);
	date_1.setDay(date_int1[2]);
	date_1.isLegal();
	date_2.setYear(date_int2[0]);
	date_2.setMonth(date_int2[1]);
	date_2.setDay(date_int2[2]);
	date_2.isLegal();
	cout << abs(date_1.sumOfdays() - date_2.sumOfdays()) << " days from " << date_1.monthItoS(date_1.getMonth()) << " " << date_1.getDay() << ", " << date_1.getYear()
		<< " is " << date_2.monthItoS(date_2.getMonth()) << " " << date_2.getDay() << ", " << date_2.getYear() << ".\n";
	
	system("PAUSE");
	return 0;
}

TheDate::TheDate():year(1), month(1), day(1)
{}

TheDate::TheDate(int theYear, int theMonth, int theDay):year(theYear), month(theMonth), day(theDay)
{}

int TheDate::getYear()
{
	return year;
}

int TheDate::getMonth()
{
	return month;
}

int TheDate::getDay()
{
	return day;
}

void TheDate::setYear(int newYear)
{
	year = newYear;
}

void TheDate::setMonth(int newMonth)
{
	month = newMonth;
}

void TheDate::setDay(int newDay)
{
	day = newDay;
}

bool TheDate::isLeapYear(int year)
{
	if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	return false;
}

void TheDate::isLegal()
{
	if(year <= 0 || month <= 0 || month >= 12 || day <= 0){
		cout << "WRONG FORMAT!" << endl;
		exit(1);
	}
	if(isLeapYear(year)){
		if(LEAPY[month - 1] >= day)
			return;
	}
	else{
		if(NOTLEAPY[month - 1] >= day)
			return;
	}
	cout << "WRONG FORMAT!" << endl;
	exit(1);
}

string TheDate::weekDay(){
	int w = 0;
	w = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	string tmp[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	return tmp[w];
}

string TheDate::monthItoS(int month){
	string tmp[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "Octobor", "November", "December"};
	return tmp[month - 1];
}

int TheDate::sumOfdays(){
	int sum = 0;
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
				sum += LEAPY[i];
			else
				sum += NOTLEAPY[i];
		}
	}
	sum += day;
	
	return sum;
}
