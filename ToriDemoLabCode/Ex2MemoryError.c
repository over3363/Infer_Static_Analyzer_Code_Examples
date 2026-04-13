#include <stdio.h>

int* escape_example() {
    int local_var = 42; // Allocated on the stack
    return &local_var;  // BAD: Address of local variable escapes the function
}

int main() {
    int *p = escape_example();
    // 'p' now points to an invalid/reclaimed stack memory location
    printf("%d\n", *p); // Undefined behavior: may crash or print garbage
    return 0;
}
