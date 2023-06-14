#pragma once
#include <iostream>
#include <stdlib.h>

char* create_first_file_pointer();

char* create_second_file_pointer(const char* first_file_name);

void sort_words_pointer(const char* second_file_name);

void print_file_pointer(const char* filename);

void print_array(char** array, int n);