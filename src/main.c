#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_ARRAY_SIZE 100

void bubble_sort(int array[], int length);

int analyse_to(char *to_string) {
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

int analyse_from(char *from_string) {
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

int read_array(int array[]) {

    int array_size = 0;
    char last_element;
    int element;
    do {
        if (scanf("%d%c", &element, &last_element) != 2)
            exit(-1);
        array[array_size] = element;
        array_size++;
    } while (last_element != '\n');
    return array_size;
}

int filter_array(int array[], int filtered_array[], int length, int to, int from) {
    int filtered_size = 0;

    for (int i = 0; i < length; i++) {
        if (array[i] > to)
            fprintf(stderr, "%d ", array[i]);
        if (array[i] < from)
            fprintf(stdout, "%d ", array[i]);
        if ((array[i] >= from) && (array[i] <= to)) {
            filtered_array[filtered_size] = array[i];
            filtered_size++;
        }

    }
    return filtered_size;
}

void copy_array(int to[], int from[], int length) {
    for (int i = 0; i < length; i++) {
        to[i] = from[i];
    }
}

int find_difference(int size, int first_array[], int second_array[]) {
    int difference = 0;
    for (int i = 0; i < size; i++) {
        if (second_array[i] != first_array[i])
            difference++;
    }
    return difference;
}

int main(int argc, char **argv) {
    int to = INT_MAX, from = INT_MIN;
    int input_array[MAX_ARRAY_SIZE];

    int analyse_return_code = analyse_parameters(argc, argv, &to, &from);
    if (analyse_return_code != 0)
        return analyse_return_code;

    int input_array_length = read_array(input_array);

    int filtered_array[MAX_ARRAY_SIZE];
    int filtered_array_length = filter_array(input_array, filtered_array, input_array_length, to, from);
    int array_copy[MAX_ARRAY_SIZE];
    copy_array(array_copy, filtered_array, filtered_array_length);

    bubble_sort(array_copy, filtered_array_length);
    int result = find_difference(filtered_array_length, filtered_array, array_copy);

    return result;
}
