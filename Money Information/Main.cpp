#include <iostream>
#include <fstream>
#include <ctime>
#include "date.h"
#include <string>
#include <vector>
using namespace std;

// TO DO:
/*
*/
//Errors
/*

*/
class Caught_Error{};
ofstream outputFile;
ifstream readFile;
float expenseInfo{}, paychechInfo{}, happinessMoney{}, Money10{};
bool invested{}, saved{}, wealthSimpleProcessedMoney{};
string path{ "E:\\Git and Github\\myGitHubRepositories\\MoneyExpenseTracker\\Money Information\\moneyInfo.txt" }, lastpayDate{};
vector<string> happinessItemsBought{}, expenseItems{};
vector<float> h_moneySpendings{}, expenceItemsCostEach{};
bool readFileWasEmpty{};

void error(string errorMessage) {
	cout << errorMessage << endl;
	throw Caught_Error{};
}

bool openReadStream() {
	readFile.open(path);
	if (!readFile.is_open()) {
		error("Error while opening read stream. File could not be opened.");
		return false;
	}
	string tempRead{};
	getline(readFile, tempRead);
	lastpayDate = tempRead;
	readFile >> tempRead;
	//check if file is empty other wise read values and assign them to feilds of the class
	if (!readFile.eof()) {
		short count{};
		if (tempRead[0] == 'e') {
			tempRead.erase(0, 1);
			expenseInfo = stof(tempRead);
			readFile >> tempRead;
			while (tempRead != "endE" && !readFile.eof()) {
				if (tempRead != "" && tempRead != " ") {
					if (count % 2 == 0) {
						expenseItems.push_back(tempRead);
					}
					else {
						expenceItemsCostEach.push_back(stof(tempRead));
					}
					count++;
				}
				getline(readFile, tempRead);

			}
		}
		getline(readFile, tempRead);
		if (tempRead == "m10") {
			getline(readFile, tempRead);
			Money10 = stof(tempRead);
			getline(readFile, tempRead);
		}

		getline(readFile, tempRead);
		if (tempRead[0] == 'h') {
			tempRead.erase(0, 1);
			happinessMoney = stof(tempRead);
			while (!readFile.eof() && tempRead != "endH") {
				getline(readFile, tempRead);
				if (tempRead == "") {
					continue;
				}
				else if (tempRead[0] == 's') {
					getline(readFile, tempRead);
					continue;
				}
				happinessItemsBought.push_back(tempRead);
				getline(readFile, tempRead);
				h_moneySpendings.push_back(stof(tempRead));
			}
		}
		readFileWasEmpty = readFile.eof();
		readFileWasEmpty = false;
	}
	else {
		cout << "Read File was empty" << endl;
		readFileWasEmpty = true;
	}
	return true;
}
bool closeReadStream() {
	readFile.close();
	if (readFile.is_open()) {
		error("Read file could not be closed.");
	}
	return true;
}
bool openOutputStream() {
	try {
		outputFile.open(path);
		if (!outputFile.is_open()) {
			error("Error in opening output stream.");
		}
		return true;
	}
	catch (Caught_Error) {
		return false;
	}

}
bool closeOutputStream() {
	if (outputFile.is_open()) {
		outputFile << lastpayDate << endl;
		outputFile << "e" << expenseInfo << endl;
		for (int i = 0; i < expenseItems.size(); i++) {
			outputFile << expenseItems[i] << endl;
			outputFile << expenceItemsCostEach[i] << endl;
		}
		outputFile << "endE" << endl;
		outputFile << "m10" << endl;
		outputFile << Money10 << endl;
		outputFile << "endm10" << endl;
		outputFile << "h" << happinessMoney << endl;
		outputFile << "size" << happinessItemsBought.size() << endl;
		for (int i = 0; i < happinessItemsBought.size(); i++) {
			outputFile << endl << happinessItemsBought[i] << "\n" << h_moneySpendings[i];
		}
		outputFile << "endH" << endl;
		outputFile << "p" << paychechInfo << endl;
	}
	else {
		cout << "Output stream is not open" << endl;
	}
	outputFile.close();
	if (!outputFile.is_open()) {
		cout << "File Closed successfully" << endl;
		return true;
	}
	else {
		cout << "File output stream not closed successfully" << endl;
		return false;
	}

	return false;
}
bool WriteToOutputStream() {
	if (!openOutputStream())
		return false;

	closeOutputStream();
	return true;
};
void printSpaceTillYouReachPos(int cursorPositionX,int tillPositionXOnConsole) {
	while (cursorPositionX < tillPositionXOnConsole) {
		cout << " ";
		cursorPositionX++;
	}
}
void printSpaceTillYouReachPos(string value, int tillPositionXOnConsole) {
	int sizeOfString = value.size();
	while (sizeOfString < tillPositionXOnConsole) {
		cout << " ";
		sizeOfString++;
	}
}
void printBudget() {
	cout << "You have the following amount available for:\n";
	cout << "expenses: "; printSpaceTillYouReachPos("expenses", 16); cout << expenseInfo << endl;
	cout << "happiness money: "; printSpaceTillYouReachPos("happiness money", 16); cout << happinessMoney << endl;
	cout << "10 % Money: "; printSpaceTillYouReachPos("10 % Money", 16); cout << Money10 << endl;
}

int main() {
start:
	expenseInfo = {}, paychechInfo = {}, happinessMoney = {};
	happinessItemsBought = {}, h_moneySpendings = {};
	expenseItems = {}; expenceItemsCostEach = {};
	try {
		openReadStream();
		closeReadStream();
	}
	catch (Caught_Error) {
		cout << "Do you want to create a new file?" << endl;
		cout << "1.yes\n2.no" << endl;
		int temp{};
		cin >> temp;
		if (cin) {
			if (temp == 1) {
				WriteToOutputStream();
			}
		}
	}
	cout << "Hi Ram. Do you want to read your Money Information or Update it? Enter option number:" << endl;
	cout << "1.Read\n" << "2.Update" << endl;
	int selectedOption{0};
	cin >> selectedOption;
	if (!cin.good()) {
		cout << "Enter a number" << endl;
		cin.clear();
		goto start;
	}

	//Read money data
	if (selectedOption == 1) {
	Read:
		if (readFileWasEmpty) {
			cout << "Read file data was empty" << endl;
		}
		else {
			cout << "\nWhat do you wish to read?\n1.Happiness spendings\n2.Overall money info" << endl;
			cin >> selectedOption;
			if (cin) {
				if (selectedOption == 1) {
					float totalSpent{};
					if (happinessItemsBought.size() == 0) {
						cout << "There is no available data on this one." << endl;
					}
					else {
						cout << "For your happiness, you spent your money on these items:" << endl;
						for (int i = 0; i < happinessItemsBought.size(); i++) {
							cout << i + 1 << "." << happinessItemsBought[i];
							printSpaceTillYouReachPos(happinessItemsBought[i], 30);
							cout << "cost " << h_moneySpendings[i] << endl;
							totalSpent += h_moneySpendings[i];
						}
						printSpaceTillYouReachPos(0, 37);
						cout << totalSpent << endl;
						cout << endl;
					}
				}
				else {
					cout << "Your expense paycheck for the month is " << paychechInfo << ", received on " << lastpayDate << "." << endl;
					printBudget();
					cout << "Do you want to read the expense items?" << endl;
					cout << "1.Yes\n2.No" << endl;
					cin >> selectedOption;
					if (cin) {
						if (selectedOption == 1) {
							for (int i = 0; i < expenseItems.size(); i++) {
								cout << i + 1 << "." << expenseItems[i];
								printSpaceTillYouReachPos(expenseItems[i], 30);
								cout << expenceItemsCostEach[i] << endl;
							}
						}
					}
					else {
						cin.clear();
					}
				}
			}
			else {
				cout << "Please enter a number" << endl;
				goto Read;
			}
		}
	}
	//Update the money data
	else if (selectedOption == 2) {
		try {
			cout << "Do you want to update your Happiness money or Expense Info or Pay check info?" << endl;
			cout << "1.Happiness Money\n" << "2.Expense Info\n" << "3.Paycheck info" << endl;
			cin >> selectedOption;
			//Happiness Money
			if (selectedOption == 1) {
				string temp{}, temp2{}, temp3{};
				bool num{};
				int count{1};
				//getline(cin, temp);
				getline(cin, temp);
				cout << "Keep entering the things you bought and and their costs in this format -> product: cost. When you are done enter \"*\"" << endl;
				float totalCost{};
				while (temp[0] != '*') {
					temp.clear();
					temp2.clear();
					temp3.clear();
					num = false;
					cout << count << ".";
					getline(cin, temp);
					if (temp[0] == '*') {
						break;
					}
					for (int i = 0; i < temp.size(); i++) {
						if (num) {
							temp3 += temp[i];
						}
						else if(temp[i] != ':') {
							temp2 += temp[i];
						}
						else if (temp[i] = ':') {
							num = true;
						}	
					}
					if (!num) {
						cout << "You didn't enter a colon differentiator." << endl;
						continue;
					}
					happinessItemsBought.push_back(temp2);
					h_moneySpendings.push_back(stof(temp3));
					totalCost += stof(temp3);
					count++;
				}
				int numberOfItems = happinessItemsBought.size();
				float happinessTotalCost{};
				//print the given list with their cost
				cout << "You have bought these " << to_string(numberOfItems) << " items." << endl;
				for (int i = 0, j; i < numberOfItems; i++) {
					j = happinessItemsBought[i].size();
					cout << to_string(i + 1) + "." << happinessItemsBought[i];
					printSpaceTillYouReachPos(j, 30);
					cout << "cost " << h_moneySpendings[i] << endl;
					happinessTotalCost += h_moneySpendings[i];
				}
				printSpaceTillYouReachPos(0 , 37);
				cout << happinessTotalCost << endl;
				if (count != 1) {
					happinessMoney -= totalCost;
					WriteToOutputStream();
				}
			}

			//expense Info
			else if (selectedOption == 2) {
				cout << "Keep entering the \"item name : cost\" for each item, and when you are done enter any *." << endl;
				float expense{};
				string input{}, item{};
				bool hasSeperator = false;
				int count{1};
				cout << count << ".";
				//catch the \n left out by the cin by selecting option before and then read the user input
				getline(cin, input);
				getline(cin, input);
				// read each item and its cost
				while (input != "*") {
					hasSeperator = false;
					short eraseCount{1};
					//read string from the input and when u reach number break;
					for (int i = 0; i < input.size() && input[i] != ':'; i++) {
						if (i < input.size() - 1) {
							if (input[i + 1] == ':') {
								hasSeperator = true;
							}
						}
						item += input[i];
						eraseCount++;
					}
					if (!hasSeperator) {
						cout << "Please enter in the given format -> \"item : cost \"" << endl;
						cout << count << ".";
						continue;
					}
					expenseItems.push_back(item);
					input.erase(0, eraseCount);
					expense += stof(input);
					expenceItemsCostEach.push_back(stof(input));
					count++;
					cout << count << ".";
					//read the next input
					getline(cin, input);
				}
				if (cin.fail()) {
					cin.clear();
				}
				cout << "The total cost was: " << expense << endl;
				expenseInfo -= expense;
				cout << "You still have a total of " << expenseInfo << "$ budget for this month's expenses." << endl;
				WriteToOutputStream();
			}

			//Update paycheck info
			else if(selectedOption == 3) {
				updatePay:
				cout << "Did you get your pay check today?\n" << "1.Yes\n" << "2.No" << endl;
				cin >> selectedOption;

				//if else statements below will check if option is correctly entered
				if (!cin) {
					if (cin.fail()) {
						cout << "Error! You didn't enter a number" << endl;
						cin.clear(); 
						goto updatePay;
					}
					else if (cin.bad()) {
						cout << "Bad error!";
						return 0;
					}
				}
				else if (selectedOption < 1 || selectedOption > 2) {
					cout << "Error! You have to enter 1 or 2" << endl;
					goto updatePay;
				}

				//Set paycheck date
				Date payCheckDate;
				if (selectedOption == 1) {
					//initialze paycheck date to today's date
					payCheckDate = Date();

				}
				else {
					cout << "Enter paycheck date as month/day/year format: ";
					string enteredDate;
					cin >> enteredDate;
					enteredDate += "/";
					payCheckDate = Date(enteredDate);
					cout << "Your last paycheck was on " << payCheckDate.getDate() << endl;
				}
				lastpayDate = payCheckDate.getDate();
				cout << "Enter paycheck amount: ";
				float payCheckAmount{};
				cin >> payCheckAmount;
				cout << "\nYour paycheck amount was: " << payCheckAmount << endl;
				paychechInfo = payCheckAmount;
				Money10 += payCheckAmount * 0.01 * 10;
				happinessMoney += Money10;
				expenseInfo += payCheckAmount * 0.01 * 70;

				cout << "Do you want to delete happiness Items info?\n1.Yes\n2.No" << endl;
				cin >> selectedOption;
				if (cin) {
					if (selectedOption == 1) {
						happinessItemsBought = {};
						h_moneySpendings = {};
						if (happinessItemsBought.size() == h_moneySpendings.size() == 0) {
							cout << "Items successfully deleted" << endl;
						}
						else {
							cout << "Couldn't delete the items. Debugging required." << endl;
						}
					}
				}
				printBudget();
				WriteToOutputStream();
			}
		}
		catch (Caught_Error) {
			return 0;
		}
	}
	else {
		cout << "Have to input either 1 to Read or 2 to update!" << endl;
		goto start;
	}
	cout << "Do you want to do anything else?\n1.Yes\n2.No" << endl;
	cin >> selectedOption;
	if (cin.good()) {
		if (selectedOption == 1) {
			cout << endl;
			goto start;
		}
	}
	return 0;
}
