#include "fileStream.h"
#include "filePointer.h"

/* 7. Створити текстовий файл. Слова у тексті відділені пробілами та крапками.
Кожен непарний рядок вхідного файлу, що є окремим реченням, переписати в новий текстовий файл.
Впорядкувати лексикографічно слова кожного рядка(речення) нового файлу.
Вивести вміст вхідного і створеного файлів.*/

int main(int argc, char* argv[]) 
{
    if (argc == 3 && strcmp(argv[1], "-mode") == 0)
    {
        cout << "Arguments are correct" << endl;

        if (strcmp(argv[2], "FilePointer") == 0)
            
        {
            cout << "FilePointer mode" << endl;
            const char* first_filename = create_first_file_pointer();
            const char* second_filename = create_second_file_pointer(first_filename);

            print_file_pointer(first_filename);
            print_file_pointer(second_filename);

            sort_words_pointer(second_filename);
            printf("After sorting:\n");
            print_file_pointer(second_filename);
        }
        else if (strcmp(argv[2], "FileStream") == 0)
        {
            cout << "FileStream mode" << endl;

            string first_filename = create_first_file();

            string second_filename = create_second_file(first_filename);

            sort_words(second_filename);

            cout << "First File:" << endl;
            print_file(first_filename);
            cout << "Second File:" << endl;
            print_file(second_filename);
        }
    }
 
}
