#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string create_first_file();

string create_second_file(string first_file_name);

void insertion_sort(string words[], int n);

void sort_words(string second_file_name);

void print_file(string file_name);

void print_array(string array[], int n);