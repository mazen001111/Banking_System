#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
private:
    static int nextID;

public:
    static int generateID();
    static void setNextID(int id);
    static int peekNextID();
    static std::string getCurrentTime();
    static int getValidInt(std::string prompt);
    static double getValidDouble(std::string prompt);
    static std::string getValidString(std::string prompt);
};

#endif