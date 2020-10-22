#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ARRAY_SIZE 100

void buble_sort(long long input_array[], int copy_size);

int analyse_to(char* to_string) {
    int length_to_string = strlen(to_string);
    int to = 0;
    int is_correct = 1;
    for (int i = 5; i < length_to_string; ++i) {
        if (!isdigit(to_string[i])) {
            is_correct = 0;
            break;
        }
    }
    if (is_correct) {
        to = strtol(to_string + 5, NULL, 10);
    }
    return to;
}

int analyse_from(char* from_string) {
    int length_from_string = strlen(from_string);
    int from = 0;
    int is_correct = 1;
    for (int i = 7; i < length_from_string; ++i) {
        if (!isdigit(from_string[i])) {
            is_correct = 0;
            break;
        }
    }
    if (is_correct) {
        from = strtol(from_string + 7, NULL, 10);
    }
    return from;
}

int analyse_parameters(int argc, char **argv, int *to, int *from) {
    if (argc < 2)
        return -1;
    if (argc > 3)
        return -2;
    for (int i = 1; i < argc; i++) {
        if (strncmp("--to=", argv[i], 5) == 0)
            *to = analyse_to(argv[i]);
        else if (strncmp("--from=", argv[i], 7) == 0)
            *from = analyse_from(argv[i]);
    }
    return 0;
}


int read_array(long long input_array[]) {

    int array_size = 0;
    char last_element;
    long long element;

    do {
        if (scanf("%lli%c", &element, &last_element) != 2)
            exit(-1);
        input_array[array_size] = element;
        array_size++;
    } while (last_element != '\n');
    return array_size;
}

int copy_array(long long input_array[], long long array_copy[], int array_size, int to, int from) {
    int copy_size = 0;
    for (int i = 0; i < array_size; i++) {
        if (to != 0 && input_array[i] > to)
            fprintf(stderr, "%lli ", input_array[i]);
        else if (from != 0 && input_array[i] < from)
            fprintf(stdout, "%lli ", input_array[i]);
        else if ((input_array[i] > from) && (input_array[i] < to)) {
            array_copy[copy_size] = input_array[i];
            copy_size++;
        }

    }
    return copy_size;
}

    for (int i = 0; i < copy_size - 1; i++) {
        for (int j = 0; j < copy_size - i - 1; j++) {
            if (array_copy[j] > array_copy[j + 1]) {
                long long tmp = array_copy[j];
                array_copy[j] = array_copy[j + 1];
                array_copy[j + 1] = tmp;
            }
        }
    }
int find_difference(int copy_size, long long input_array[], long long array_copy[]) {
        int difference = 0;
        for (int i = 0; i < copy_size; i++) {
            if (array_copy[i] !=input_array[i])
                difference++;
        }
    return difference;
    }




int main(int argc, char **argv) {
    int to = 0, from = 0;
    int array_size = 0;
    int copy_size = 0;
    long long input_array[MAX_ARRAY_SIZE], array_copy[MAX_ARRAY_SIZE];



    int analyse_return_code = analyse_parameters(argc, argv, &to, &from);
    if (analyse_return_code != 0)
        return analyse_return_code;

    int array_length = read_array(input_array);
    array_length = copy_array(input_array, array_copy, array_size, to, from);

    int result = find_difference(copy_size, input_array, array_copy);

    return result;
}

