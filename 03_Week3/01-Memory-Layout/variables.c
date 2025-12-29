#include <stdio.h>
#include "variables.h"

int global_initialized = 100;      // .data
int global_uninitialized;          // .bss

void print_static() {
    static int static_var = 1;     // .data
    static_var++;
    printf("Static var: %d\n", static_var);
}

volatile int sensor_input = 55;    // volatile global variable

void print_volatile() {
    printf("Volatile sensor input: %d\n", sensor_input);
}
