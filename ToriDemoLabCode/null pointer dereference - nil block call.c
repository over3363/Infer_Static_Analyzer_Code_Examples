#include <stdio.h>

int main() {
    // 1. Declare a block variable (syntax: return_type (^name)(arguments))
    void (^myBlock)(void);

    // 2. Explicitly set it to NULL
    myBlock = NULL;

    // 3. Attempting to call it will cause a crash (Segmentation Fault)
    printf("Calling the block now...\n");
    myBlock(); 

    return 0;
}
