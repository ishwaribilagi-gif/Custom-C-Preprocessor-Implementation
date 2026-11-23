#include <stdio.h>
#include "myheader.h"

// Object-like macros
#define PI 3.14
#define MAX 100

// Function-like macro
#define SQUARE(x) ((x) * (x))

int main()
{
    /* Variable declarations */

    float radius = 5;
    float area = PI * radius * radius;

    int value = MAX;
    int result = SQUARE(5);

    printf("Area = %f\n", area);
    printf("Maximum = %d\n", value);
    printf("Square = %d\n", result);

    return 0;
}
