#include "filePointer.h"
#pragma warning(disable : 4996)

char* create_first_file_pointer()
{
    FILE* fp, *not_new_file;
    int i = 0, running = 1;
    char* file_name = new char[50];
    char str[100];
    printf("Enter first file name: "); scanf("%s", file_name); getchar();
    char flag;

    fopen_s(&not_new_file, file_name, "r");
    if (not_new_file != 0)
    {
        printf("Do you want to append to file? (y/n) "); scanf("%c", &flag); getchar();
        if (flag != 'y' && flag != 'Y')
        {
            fclose(not_new_file);
            remove(file_name);
            flag = 'y';
        }
    }
    else fclose(not_new_file);

    fopen_s(&fp, file_name, "a");
    printf("Enter text to a file:\n");
    printf("Enter \"stop\" to stop entering\n");
    do
    {
        printf("%d. ", i + 1);
        fgets(str, sizeof(str), stdin);
        if (strcmp(str, "stop\n") != 0) fputs(str, fp);
        else running = 0;
        i++;

    } while (running);
    printf("=========================================\n");

    fclose(fp);
    return file_name;
}

char* create_second_file_pointer(const char* first_file_name)
{
    FILE* file1_pointer;
    FILE* file2_pointer;
    char* second_file_name = new char[50];
    printf("Enter second file name: "); scanf("%s", second_file_name); 
    char c;
    int i = 0, line_length = 0, dot_position = -1, dot_number = 0;
    bool many_dots, odd_line, ends_with_period, f1_not_opened, f2_not_opened;

    f1_not_opened = fopen_s(&file1_pointer, first_file_name, "r") != 0;
    f2_not_opened = fopen_s(&file2_pointer, second_file_name, "w") != 0;

    if (f1_not_opened || f2_not_opened)
    {
        printf("Error: could not open file.\n");
    }

    char* line = new char[100];
    if (line == NULL)
    {
        printf("Error: could not allocate memory for line buffer.\n");
    }

    else
    {
        while ((c = getc(file1_pointer)) != EOF)
        {
            line[i] = c;

            if (c == '\n')
            {
                odd_line = (line_length % 2 == 1);
                many_dots = (dot_number > 1);
                ends_with_period = (dot_position + 1 == line_length);
                if (!many_dots && odd_line && ends_with_period)
                {
                    line[line_length] = '\n';
                    line[line_length + 1] = '\0';
                    fputs(line, file2_pointer);
                }
                line = new char[100];
                i = 0; line_length = 0; dot_number = 0;
            }

            else
            {
                if (c == '.')
                {
                    dot_position = i; dot_number++;
                }
                i++; line_length++;

            }
        }
        fclose(file1_pointer); fclose(file2_pointer);
    }
    return second_file_name;
}


void insertionSort(char** arr, int n) {
    int i, j;
    char* key = new char[20];
    for (i = 1; i < n; i++) {
        strcpy(key, arr[i]);
        j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            strcpy(arr[j + 1], arr[j]);
            j = j - 1;
        }
        strcpy(arr[j + 1], key);
    }
    delete[] key;
}


void sort_words_pointer(const char* second_file_name)
{
    FILE* File2_ptr; FILE* File2_copy_ptr;
    char* nextToken = NULL; char ch;
    char* line;
    char** word;
    int i = 0, j = 0;
    bool f2_not_opened, f2_copy_not_opened;
    f2_not_opened = fopen_s(&File2_ptr, second_file_name, "r") != 0;
    f2_copy_not_opened = fopen_s(&File2_copy_ptr, "new_file_copy.txt", "w") != 0;


    if (f2_not_opened || f2_copy_not_opened)
    {
        printf("Error: could not open file.\n");
    }
    else
    {
        word = new char* [20];
        line = new char [400];
        for (int i = 0; i < 20; i++)
        {
            word[i] = new char[20];
        }
        while (fgets(line, 100, File2_ptr))
        {
            char *ptr = strtok(line, " ");
            int i = 0;
            while (ptr != NULL)
            {
                strcpy(word[i], ptr);
                ptr = strtok(NULL, " ");
                i++;
            }
            int len1 = strlen(word[i - 1]);
            word[i - 1][len1 - 2] = '\0';
            insertionSort(word, i);
            for (int j = 0; j < i; j++)
            {
                fputs(word[j], File2_copy_ptr);
                if (j != i - 1) fputs(" ", File2_copy_ptr);
            }
            fputs(".\n", File2_copy_ptr);
        }

        for (int i = 0; i < 20; i++) 
        {
            delete[] word[i];
        }

        delete[] word;
        delete[] line;

        if (fclose(File2_ptr) != 0) printf("Couldn't close %s file", second_file_name);

        if (fclose(File2_copy_ptr) != 0) printf("Couldn't close new_file_copy.txt file");

        int removed = remove(second_file_name);
        if (removed != 0) printf("Couldn't remove file\n");

        try
        {
            int rename_not_completed = rename("new_file_copy.txt", second_file_name);

            if (rename_not_completed != 0) 
                throw "Error. Couldn't rename the file\n";
        }
        catch (const char* err)
        {
            printf(err);
        }
    }
}

void print_file_pointer(const char* filename)
{
    FILE *file_ptr;
    char* str = new char[100];
    file_ptr = fopen(filename, "r");
    printf("file: %s\n", filename);
    if (file_ptr != NULL) {

        while (fgets(str, 100, file_ptr)) 
        {
            printf("%s", str);
        }
        printf("=========================================\n");
        fclose(file_ptr);
    }
    else {
        printf("Not able to open the file.");
    }
    
}

void print_array(char** array, int n)
{
    for (int j = 0; j < n; j++)
    {
        printf("%d. %s\n", (j + 1), array[j]);
    }
}

