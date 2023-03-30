#ifndef UTILS_H
#define UTILS_H
#include <string>

using namespace std;

void writeFile(const string &filename, const string &content);
string readFile(const string &filename);
string textToBinary(const string &text);
string binaryToText(const string &binary);

#endif // UTILS_H
