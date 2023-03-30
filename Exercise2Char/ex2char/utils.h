#ifndef UTILS_H
#define UTILS_H

int getLength(char *array);
void concatenate(char *destination, const char *source);
void characterToBinary(char c, char *binary);
void bytesToBinaryString(const unsigned char *bytes, int byteCount,
                         char *binaryString);

#endif // UTILS_H
