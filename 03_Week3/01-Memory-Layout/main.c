#include <stdio.h>
#include "variables.h"

int main() {
    int local_var = 5;             // Stack
    printf("Local var: %d\n", local_var);

    print_static();                // Show static behavior
    print_static();

    print_volatile();              // Show volatile usage

    printf("Global initialized: %d\n", global_initialized);
    printf("Global uninitialized: %d\n", global_uninitialized);

    return 0;
}
