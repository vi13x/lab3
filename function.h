#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "windows.h"
#include "zoo_structure.h"
#include "my_string.h"

#ifndef UNTITLED5_FUNCTION_H
#define UNTITLED5_FUNCTION_H
void input_animal(Animal *a);
void print_animal(Animal *a);
Animal* find_animals(Animal *arr, int size, const char *name);
int remove_animals(Animal **arr, int *size, const char *name, int quantity);
void flush_input_buffer();
void clear_screen();
void task1();
void task2();
int validate_birth_date(const char *date);
int load_animals_from_file(Animal **zoo, int *zoo_size, const char *filename);
int save_animals_to_file(Animal *zoo, int zoo_size, const char *filename);
#endif
