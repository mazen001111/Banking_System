#ifndef UTILS_H
#define UTILS_H

#include <string>
using namespace std;

class Utils {
private:
    //the id assigned the next new member
    static int nextID;

public:
 //generate and id for the new customer and increments nextID
    static int generateID();

    static void setNextID(int id);

    // Useful for testing or display purposes.
    static int peekNextID();

    static string getCurrentTime();

    static int getValidInt(string prompt);

    static double getValidDouble(string prompt);

    static string getValidString(string prompt);
// just validation
};

#endif
