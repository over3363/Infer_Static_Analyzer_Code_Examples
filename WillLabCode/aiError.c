#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int  id;
} Item;

void init_item(Item *it, const char *name, int id);
void reset_item(Item *it);
void print_item(const Item *it);
char *get_item_name(Item *it);

int main() {
    Item a;
    init_item(&a, "example", 42);

    char *cached_name = get_item_name(&a);

    if (a.id % 2 == 0) {
        reset_item(&a);
    }

    printf("Cached name length: %zu\n", strlen(cached_name)); // <-- use-after-free
    print_item(&a);

    return 0;
}

void init_item(Item *it, const char *name, int id) {
    it->name = malloc(strlen(name) + 1);
    if (!it->name) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(it->name, name);
    it->id = id;
}

void reset_item(Item *it) {
    if (it->name) {
        free(it->name);
        it->name = NULL;
    }
    it->id = -1;
}

void print_item(const Item *it) {
    if (it->name)
        printf("Item: %s (id=%d)\n", it->name, it->id);
    else
        printf("Item: <no name> (id=%d)\n", it->id);
}

char *get_item_name(Item *it) {
    return it->name;
}