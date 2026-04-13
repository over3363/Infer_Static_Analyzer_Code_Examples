#include <stdlib.h>
#include <stdio.h>

void create_leak() {
    // Allocating 1000 bytes on the heap
    char *ptr = (char *)malloc(1000 * sizeof(char)); 
    
    if (ptr == NULL) return;

    // --- LEAK ---
    // The memory is not freed here, and 'ptr' goes out 
    // of scope when the function ends, losing the address.
    printf("Memory allocated but not freed.\n");
}

int main() {
    for (int i = 0; i < 1000000; i++) {
        create_leak(); // Repeatedly leaks memory
    }
    return 0;
}