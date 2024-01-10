#ifndef SINGULAR_H // If SINGULAR_H is not defined
#define SINGULAR_H // Define it

extern int prec;
// Enum to represent filter types
typedef enum {EQ, NEQ, GEQ, LEQ, LESS, GREATER} filter_type;

// Function prototypes for print, shift, and filter
void print(double a[], int size);
void shift(double a[], int size, double by);
int filter(double a[], int size, filter_type t, double threshold);
filter_type parse_filter_type(const char* str);


#endif // End of SINGULAR_H
