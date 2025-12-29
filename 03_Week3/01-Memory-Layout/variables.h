#ifndef VARIABLES_H
#define VARIABLES_H

extern int global_initialized;     // in .data
extern int global_uninitialized;   // in .bss

void print_static();
void print_volatile();

#endif
