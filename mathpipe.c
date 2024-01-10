#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "aggregate.h"
#include "singular.h"  // Include the header file for singular.c

int prec = 5;
#define MAX_SIZE 256
// Define the global variable

typedef enum {
    SHIFT,
    FILTER,
    PRINT,
    AGGREGATE
} operation_type;

typedef struct {
    operation_type type;
    union {
        double shift_amount;
        struct {
            filter_type filter_t;
            double filter_threshold;
        };
        char* aggregate_function;
    };
} operation;

int main(int argc , char* argv[]) {

    int size = MAX_SIZE;  // default values
    operation operations[MAX_SIZE];  // default operations
    int operation_count = 0;
    bool firstLine = true;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (sscanf(argv[i], "-size=%d", &size) == 1) {
            continue;
        }
        if (sscanf(argv[i], "-prec=%d", &prec) == 1) {
            continue;
        }
        if (strcmp(argv[i], "SHIFT") == 0) {
            operations[operation_count].type = SHIFT;
            operations[operation_count].shift_amount = strtod(argv[++i], NULL);
            operation_count++;
            continue;
        }
        if (strcmp(argv[i], "FILTER") == 0) {
            operations[operation_count].type = FILTER;
            operations[operation_count].filter_t = parse_filter_type(argv[++i]);
            operations[operation_count].filter_threshold = strtod(argv[++i], NULL);
            operation_count++;
            continue;
        }
        if (strcmp(argv[i], "PRINT") == 0) {
            operations[operation_count].type = PRINT;
            operation_count++;
            continue;
        }
        operations[operation_count].type = AGGREGATE;
        operations[operation_count].aggregate_function = argv[i];
        operation_count++;
    }

    if (operation_count == 0) {
        fprintf(stderr, "No operation specified\n");
        return 1;
    }

    double arrayOfNumbers[MAX_SIZE];
    char line[MAX_SIZE];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        int count = 0;

        char *token = strtok(line, " ");
        while (token != NULL && count < MAX_SIZE) {
            arrayOfNumbers[count] = strtod(token, NULL);
            count++;
            token = strtok(NULL, " ");
        }

        int numberOfElements = count;

        for (int i = 0; i < operation_count; i++) {
            if(operations[i].type == SHIFT) {
                shift(arrayOfNumbers, numberOfElements, operations[i].shift_amount);
                print(arrayOfNumbers, numberOfElements);
                continue;
            }

            if(operations[i].type == FILTER) {
                numberOfElements = filter(arrayOfNumbers, numberOfElements, operations[i].filter_t, operations[i].filter_threshold);
                print(arrayOfNumbers, numberOfElements);
                continue;
            }

            if(operations[i].type == PRINT) {
                for (int j = 0; j < numberOfElements; j++) {
                    printf("%.*f ", prec , arrayOfNumbers[j]);
                    if ((j + 1) % size == 0) {
                        printf("\n");
                    }
                }
                printf("\n");  // Print a newline after printing all elements
                continue;
            }

            if(operations[i].type == AGGREGATE) {
                for (int j = 0; j < numberOfElements; j += size) {
                    double result = aggregate(operations[i].aggregate_function, arrayOfNumbers + j, size <= numberOfElements - j ? size : numberOfElements - j);
                    if (!firstLine) {
                        printf(" ");
                    }
                    printf("%.*f", prec , result);
                    firstLine = false;
                }
            }
        }
    }
    printf("\n");
    return 0;
}
