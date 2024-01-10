#include "singular.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int prec;
void print(double a[], int size){
    for(int i = 0; i < size; i++){
        printf("%.*f ", prec, a[i]);
    }
    printf("\n");
}


void shift(double a[], int size, double by){
    for (int i = 0; i < size; ++i) {
        a[i] += by;
    }
}


int filter(double a[], int size, filter_type t, double threshold){
    int count = 0;
    for (int i = 0; i < size; i++){
        switch(t){
            case EQ : if(a[i] == threshold) a[count++] = a[i];
                break;
            case NEQ : if(a[i] != threshold) a[count++] = a[i];
                break;
            case GEQ : if(a[i] >= threshold) a[count++] = a[i];
                break;
            case LEQ : if(a[i] <= threshold) a[count++] = a[i];
                break;
            case LESS : if(a[i] < threshold) a[count++] = a[i];
                break;
            case GREATER : if(a[i] > threshold) a[count++] = a[i];
                break;
        }
    }
    return count;
}

filter_type parse_filter_type(const char* str) {
    if (strcmp(str, "EQ") == 0) {
        return EQ;
    } else if (strcmp(str, "NEQ") == 0) {
        return NEQ;
    } else if (strcmp(str, "GEQ") == 0) {
        return GEQ;
    } else if (strcmp(str, "LEQ") == 0) {
        return LEQ;
    } else if (strcmp(str, "LESS") == 0) {
        return LESS;
    } else if (strcmp(str, "GREATER") == 0) {
        return GREATER;
    } else {
        fprintf(stderr, "Invalid filter type: %s\n", str);
        exit(1);
    }
}


