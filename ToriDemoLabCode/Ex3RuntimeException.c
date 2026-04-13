#include <stdio.h>
#include <string.h>

// Function that expects a valid string but does not check for NULL
void printLength(char *str) {
    // BAD ARGUMENT: Dereferencing a NULL pointer causes a segmentation fault
    printf("Length: %lu\n", strlen(str)); 
}

int main() {
    char *myString = NULL; // Initializing with a bad value
    
    printf("Attempting to check length of NULL string...\n");
    
    // Passing the bad argument
    printLength(myString); 
    
    return 0;
}
