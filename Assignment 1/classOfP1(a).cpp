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
	//constructor
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
private:
	int year;
	int month;
	int day;
	int w;
};

int main(){
	TheDate date_1;
	string date_str[3];
	string date_cin;
	
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
	
	date_1.setYear(date_int[0]);
	date_1.setMonth(date_int[1]);
	date_1.setDay(date_int[2]);
	date_1.isLegal();
	cout << date_1.monthItoS(date_int[1]) << " " << date_str[2] << ", " << date_str[0] << " is " << date_1.weekDay() <<"." << endl;
	
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