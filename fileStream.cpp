#include "fileStream.h"

string create_first_file()
{
    string str, file_name;
    char flag;
    cout << "Enter first file name: "; getline(cin, file_name);

    ifstream not_new_file(file_name);
    if (not_new_file)
    {
        cout << "Do you want to append to file? (y/n) "; cin >> flag; cin.ignore();
        if (flag != 'y' && flag != 'Y')
        {
            not_new_file.close();
            remove(file_name.c_str());
            flag = 'y';
        }
    }
    ofstream outFile(file_name, ios::app);
    int i = 1, running = 1;
    cout << "Enter text to a file:" << endl;
    cout << "Enter \"stop\" to stop entering\n";
    do
    {
        cout << i << ". "; getline(cin, str);
        if (str != "stop") outFile << str << endl;
        else running = 0;
        i++;
    } while (running);
    cout << "=========================================" << endl;
    outFile.close();
    return file_name;
}

string create_second_file(string first_file_name)
{
    string line, second_file_name;
    size_t line_length, dot_position;
    bool many_dots, odd_line, ends_with_period;
    ifstream firstFile(first_file_name);
    
    cout << "Enter second file name: "; getline(cin, second_file_name);
    ofstream secondFile(second_file_name);

    while (!firstFile.eof())
    {
        getline(firstFile, line);
        line_length = line.length();
        dot_position = line.rfind('.');
        if (dot_position == string::npos)
        {
            many_dots = false;
        }
        else many_dots = (dot_position != line.find('.'));
        ends_with_period = (dot_position + 1 == line_length);
        odd_line = (line_length % 2 == 1);


        if (!many_dots && odd_line && ends_with_period)
        {
            secondFile << line << endl;
        }
    }
    firstFile.close(); secondFile.close();

    return second_file_name;
}

void insertion_sort(string words[], int n)
{
    int i, j;
    string key;
    for (i = 1; i < n; i++)
    {
        key = words[i];
        j = i - 1;
        while (j >= 0 && words[j] > key)
        {
            words[j + 1] = words[j];
            j = j - 1;
        }
        words[j + 1] = key;
    }
}

void sort_words(string second_file_name)
{
    string line; string word[100];
    int i, words_number;
    ifstream File2(second_file_name);
    ofstream File2_copy("new_file_copy.txt");
    while (!File2.eof())
    {
        getline(File2, line, '.');
        words_number = 0;
        istringstream s1(line);
        i = 0;
        while (s1 >> word[i])
        { 
            i++;
        }

        for (int j = 0; word[j] != ""; j++) words_number++;

        insertion_sort(word, words_number);

        for (int j = 0; j < words_number; j++)
        {
            if (j + 1 == words_number) File2_copy << word[j] << "." << endl;
            else File2_copy << word[j] << " ";
        }

        for (int j = 0; j < words_number; j++) word[j] = "";
    }
    const char* file2_char_name = second_file_name.c_str();
    File2.close(); remove(file2_char_name);
    File2_copy.close();
    if (rename("new_file_copy.txt", file2_char_name) != 0)
    {
        cout << "Error. Could not rename " << second_file_name << endl;
    }

}

void print_file(string file_name)
{
    string line;
    ifstream output_File(file_name);
    if (!output_File) cout << "Cannot open file" << endl;
    else
    {
        while (!output_File.eof())
        {
            getline(output_File, line);
            if (!output_File.eof()) cout << line << endl;
            else cout << line;
        }
        cout << "=========================================" << endl;
    }
    output_File.close();
}

void print_array(string array[], int n)
{
    for (int j = 0; j < n; j++)
    {
        cout << (j + 1) << ". " << array[j] << endl;
    }
}