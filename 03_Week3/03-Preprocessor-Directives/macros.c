#include <stdio.h>

// (1) Simple macro with replacement text
#define PI 3.14159

// (2) Macro with parameter
#define SQUARE(x) ((x) * (x))

// (5) Undefine a macro
#define TEMP 100
#undef TEMP

int main() {
    printf("PI: %f\n", PI);                     // prints 3.14159
    printf("Square of 5: %d\n", SQUARE(5));     // prints 25

    #ifdef TEMP
    printf("TEMP is defined\n");
    #else
    printf("TEMP is undefined\n");
    #endif

    return 0;
}
