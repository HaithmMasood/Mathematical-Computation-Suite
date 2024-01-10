#include "aggregate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static double count(double* array, int size){
    return size;
}


static double min(double* array, int size){
    double min = array[0];
    for(int i = 1; i < size; i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    return min;
}

static double max(double* array, int size){
    double max = array[0];
    for(int i = 1; i < size; i++){
        if(array[i] > max){
            max = array[i];
        }
    }
    return max;
}


static double sum(double* array, int size){
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum+=array[i];
    }
    return sum;
}


static double avg(double* array, int size){
    return (sum(array, size) / count(array, size));
}


static double pavg(double* array, int size){
    return ((min(array, size) + max(array, size))/2);
}


typedef double (*functions)(double*, int);
static functions functionList[] = {count, min, max, sum, avg, pavg};
static const char* functionNames[]= {"COUNT", "MIN","MAX","SUM","AVG","PAVG"};

double aggregate(const char* func, double* array, int size){
    char func_upper[strlen(func) + 1];
    for(int i = 0; func[i]; i++){
        func_upper[i] = toupper(func[i]);
    }
    func_upper[strlen(func)] = '\0'; // don't forget to terminate the string

    for (int i = 0; i < 6; ++i) {
        if(strcmp(func_upper, functionNames[i]) == 0) {
            return functionList[i](array, size);
        }
    }
    fprintf(stderr, "FATAL ERROR: Invalid function name.\n");
    exit(1);
}
