#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <string>

using namespace std;

string stringToBinary(const string &input);
string xorEncrypyDecrypt(const string &input, char key);

#endif // ENCRYPTION_H
