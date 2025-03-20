#include <stdio.h>
#include <stdlib.h>
#ifndef UNTITLED5_MY_STRING_H
#define UNTITLED5_MY_STRING_H
void printString(const char* str);
void getStringSize(const char *str, int* length);
void allocateMemory(char** buffer, int newSize);
void appendString(char** dest, int initialSize, const char* src);
int compareStrings(const char* str1, const char* str2);
void removeSubstring(int *size, char** buffer, int index, int length);
void readString(char **buffer, int *size);
#endif
