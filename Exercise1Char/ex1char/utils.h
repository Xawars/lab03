#ifndef UTILS_H
#define UTILS_H
#pragma once

int getLength(char *array);
void concatenate(char *destination, const char *source);
void characterToBinary(char c, char *binary);
void binaryStringtoBytes(const char *binaryString, unsigned char
                                                       *bytes, int &byteCount);

#endif // UTILS_H
