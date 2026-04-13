#include <stdlib.h>

// Sink: Where the actual illegal access occurs
void deref(int* p) {
    *p = 42; // Pulse reports a Null dereference here
}

// Intermediate: The transitive link
void pass_through(int* p) {
    deref(p);
}

// Source: Where the bad value originates
int main() {
    int* ptr = NULL;
    pass_through(ptr); // The error is "transitive" from here to deref()
    return 0;
}
