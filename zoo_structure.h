#ifndef UNTITLED5_ZOO_STRUCTURE_H
#define UNTITLED5_ZOO_STRUCTURE_H
} BitField;
typedef struct {
    char date_str[11];
} Date;


typedef struct {
    int quantity;
    char* name;
    Date arrival_date;
    float lifespan;
} Animal;


typedef struct {
    unsigned int value : 32;
} Number;
#endif
