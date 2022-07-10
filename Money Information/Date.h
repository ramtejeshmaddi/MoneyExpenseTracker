#pragma once
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
class Date
{
public:
	tm dateTime;
	bool dateWasGiven = false;
	struct date {
		int year{}, day{}, month{};
	};
	date givenDate{};

	//empty constructor will set time to current time

	Date() {
		//get system time
		time_t presentSystemTime{ time(NULL) };

		//convert system time to local time and store it in dateTime variable
		localtime_s(&dateTime, &presentSystemTime);
	}
	// or dateTime feild will hold any local time
	Date(string givenDate) {
		this->dateWasGiven = true;
		string partOfGivenDate{};
		for (int i = 0, j = 0; i < givenDate.size(); i++) {
			if (givenDate[i] == '/') {
				int num{ stoi(partOfGivenDate) };
				partOfGivenDate.clear();
				/*if we are reading the first part of the given date then assign the value
				to month property of tm structure*/
				if (j == 0) {
					this->givenDate.month = num - 1;
				}
				else if (j == 1) {
					this->givenDate.day = num;
				}
				else if (j == 2) {
					this->givenDate.year = num;
				}
				j++;
				continue;
			}
			partOfGivenDate.push_back(givenDate[i]); 
		}
	}
	
	void addDaysToDate(int numOfDays) {
		dateTime.tm_mday += numOfDays;
		mktime(&dateTime);
	}

	void subtractDaysToDate(int numOfDays) {
		dateTime.tm_mday -= numOfDays;
		mktime(&dateTime);
	}

	tm getDateTm() {
		return dateTime;
	}
	string getDate() {
		if (!dateWasGiven) {
			return to_string(dateTime.tm_mday) + " " + intToMonth(dateTime.tm_mon) + " " + to_string(dateTime.tm_year + 1900);
		}
		return to_string(givenDate.day) + " " + intToMonth(givenDate.month) + " " + to_string(givenDate.year);
	}

	string intToMonth(int num) {
		switch (num) {
		case 0:
			return "Jan";
		case 1:
			return "Feb";
		case 2:
			return "Mar";
		case 3:
			return "April";
		case 4:
			return "May";
		case 5:
			return "Jun";
		case 6: 
			return "Jul";
		case 7:
			return "Aug";
		case 8:
			return "sept";
		case 9:
			return "oct";
		case 10:
			return "Nov";
		case 11:
			return "Dec";
		default:
			return "Error in Month";
		}
	}
};

