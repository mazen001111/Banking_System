#include "../include/Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <time.h>
using namespace std;

int Utils::nextID = 1001;

int Utils::generateID()
{
    return nextID++;
}

void Utils::setNextID(int id)
{
    nextID = id;
}

int Utils::peekNextID()
{
    return nextID;
}

string Utils::getCurrentTime() {
    std::time_t now      = std::time(nullptr);
    std::tm*    timeInfo = std::localtime(&now);

    stringstream ss;
    ss << (1900 + timeInfo->tm_year) << "-"
       << setw(2) << setfill('0') << (1 + timeInfo->tm_mon) << "-"
       << setw(2) << setfill('0') << timeInfo->tm_mday << " "
       << setw(2) << setfill('0') << timeInfo->tm_hour << ":"
       << setw(2) << setfill('0') << timeInfo->tm_min << ":"
       << setw(2) << setfill('0') << timeInfo->tm_sec;

    return ss.str();
}

int Utils::getValidInt(string prompt)
{
    int value;
    while (true)
    {
        cout << prompt;

        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a whole number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double Utils::getValidDouble(string prompt)
{
    double value;
    while (true)
    {
        cout << prompt;

        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a valid number (e.g. 100 or 99.50)." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string Utils::getValidString(string prompt)
{
    string value;
    while (true)
    {
        cout << prompt;
        getline(cin, value);

        if (!value.empty())
        {
            return value;
        }
        cout << "Input cannot be empty. Please try again." << endl;
    }
}