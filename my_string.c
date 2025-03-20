#include "my_string.h"
void printString(const char* str) {
    for (int i = 0; str[i] != '\0'; ++i)
        putchar(str[i]);
}

void getStringSize(const char *str, int* length) {
    while (str[*length] != '\0' && str[*length] != EOF) {
        (*length)++;
    }
}

void allocateMemory(char** buffer, int newSize) {
    char *temp = (char*) realloc(*buffer, sizeof(char) * (newSize + 1));
    if (temp == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    *buffer = temp;
    (*buffer)[newSize] = '\0';
}

void appendString(char** dest, int initialSize, const char* src) {
    int i = 0;
    while (src[i] != '\0' && src[i] != EOF) {
        allocateMemory(dest, initialSize + i + 1);
        (*dest)[initialSize + i] = src[i];
        i++;
    }
}

int compareStrings(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return 0;
        i++;
    }
    return str1[i] == str2[i];
}

void removeSubstring(int *size, char** buffer, int index, int length) {
    if (index < 0 || length <= 0) return;
    if (index + length > *size) length = *size - index;

    for (int i = index; i + length < *size; ++i)
        (*buffer)[i] = (*buffer)[i + length];

    *size -= length;
    allocateMemory(buffer, *size);
}

void readString(char **buffer, int *size) {
    *buffer = NULL;
    allocateMemory(buffer, 0);
    int c;
    for (int i = 0; (c = getchar()) != '\n' && c != EOF; ++i) {
        *size = i + 1;
        allocateMemory(buffer, *size);
        (*buffer)[i] = (char) c;
    }
}
