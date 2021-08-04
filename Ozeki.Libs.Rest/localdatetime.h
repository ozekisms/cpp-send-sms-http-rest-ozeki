#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class localdatetime
{
public:

	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	localdatetime(void) {
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		this->year = (1900 + newtime.tm_year);
		this->month = (1 + newtime.tm_mon);
		this->day = newtime.tm_mday;
		this->hour = newtime.tm_hour;
		this->minute = newtime.tm_min;
		this->second = newtime.tm_sec;
	}

	localdatetime(int year, int month, int day, int hour, int minute, int second) {
		this->year = year;
		this->month = month;
		this->day = day;
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}

	string toString(void) {
		string result = "";
		result += to_string(this->year) + "-";
		if (to_string(this->month).length() == 1) {
			result += "0" + to_string(this->month) + "-";
		}
		else {
			result += to_string(this->month) + "-";
		}
		if (to_string(this->day).length() == 1) {
			result += "0" + to_string(this->day) + "T";
		}
		else {
			result += to_string(this->day) + "T";
		}
		if (to_string(this->hour).length() == 1) {
			result += "0" + to_string(this->hour) + ":";
		}
		else {
			result += to_string(this->hour) + ":";
		}
		if (to_string(this->minute).length() == 1) {
			result += "0" + to_string(this->minute) + ":";
		}
		else {
			result += to_string(this->minute) + ":";
		}
		if (to_string(this->second).length() == 1) {
			result += "0" + to_string(this->second);
		}
		else {
			result += to_string(this->second);
		}
		return result;
	}

	void addWeek(void) {
		vector<int> numOfDaysNotLeapYear = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		vector<int> numOfDaysLeapYear = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (year % 4 == 0 || (year % 100 == 0 && year % 400 == 0)) {
			if ((day + 7) > numOfDaysLeapYear[month - 1]) {
				int diff = numOfDaysLeapYear[month - 1] - day;
				day = 7 - diff;
				month += 1;
			}
			else {
				day += 7;
			}
			if (month == 13) {
				month = 1;
				year += 1;
			}
		}
		else {
			if ((day + 7) > numOfDaysNotLeapYear[month - 1]) {
				int diff = numOfDaysNotLeapYear[month - 1] - day;
				day = 7 - diff;
				month += 1;
			}
			else {
				day += 7;
			}
			if (month == 13) {
				month = 1;
				year += 1;
			}
		}
	}
	localdatetime(string datetime) {
		vector<string> datetimeVector = getDateComponents(datetime);
		vector<string> dateVector = getDate(datetimeVector[0]);
		vector<string> timeVector = getTime(datetimeVector[1]);
		this->year = stoi(dateVector[0]);
		this->month = stoi(dateVector[1]);
		this->day = stoi(dateVector[2]);
		this->hour = stoi(timeVector[0]);
		this->minute = stoi(timeVector[1]);
		this->second = stoi(timeVector[2]);
	}
private:
	vector<string> getDateComponents(string datetime) {
		vector<string> datetimeVector;
		size_t prev = 0, pos = 0;
		string delimeter = " ";
		do
		{
			pos = datetime.find(delimeter, prev);
			if (pos == std::string::npos)
				pos = datetime.length();
			std::string token = datetime.substr(prev, pos - prev);
			if (!token.empty())
				datetimeVector.push_back(token);
			prev = pos + delimeter.length();
		} while (pos < datetime.length() && prev < datetime.length());
		return datetimeVector;
	}

	vector<string> getDate(string date) {
		vector<string> dateVector;
		size_t prev = 0, pos = 0;
		string delimeter = "-";
		do
		{
			pos = date.find(delimeter, prev);
			if (pos == std::string::npos)
				pos = date.length();
			std::string token = date.substr(prev, pos - prev);
			if (!token.empty())
				dateVector.push_back(token);
			prev = pos + delimeter.length();
		} while (pos < date.length() && prev < date.length());
		return dateVector;
	}

	vector<string> getTime(string time) {
		vector<string> timeVector;
		size_t prev = 0, pos = 0;
		string delimeter = ":";
		do
		{
			pos = time.find(delimeter, prev);
			if (pos == std::string::npos)
				pos = time.length();
			std::string token = time.substr(prev, pos - prev);
			if (!token.empty())
				timeVector.push_back(token);
			prev = pos + delimeter.length();
		} while (pos < time.length() && prev < time.length());
		return timeVector;
	}
};

