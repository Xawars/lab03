#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

bool checkAdminAccess(const string &inputKey, const string &encryptedKey);
void registerUser();
bool userAccess(string &userID);
void checkBalance(const string &userID);
void withdrawMoney(const string &userID);
void userOperations(const string &userID);
void applyOperationsCost(const string &userID);
bool isUserRegistered(const string &userID);
bool isUserIDValid(const string &userID);

#endif // USER_H
