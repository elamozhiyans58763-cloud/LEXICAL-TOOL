#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char var[10];
    int offset;
} StackItem;

typedef struct {
    StackItem stack[MAX];
    int top;
    int offset;
} StackAllocator;

void init(StackAllocator *allocator) {
    allocator->top = -1;
    allocator->offset = 0;
}

void allocate(StackAllocator *allocator, char var[], int size) {
    if (allocator->top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }

    allocator->top++;
    strcpy(allocator->stack[allocator->top].var, var);
    allocator->stack[allocator->top].offset = allocator->offset;

    printf("Allocated %s at offset %d\n", var, allocator->offset);

    allocator->offset += size;
}

void deallocate(StackAllocator *allocator) {
    if (allocator->top == -1) {
        printf("Stack Empty\n");
        return;
    }

    printf("Deallocated %s from offset %d\n",
           allocator->stack[allocator->top].var,
           allocator->stack[allocator->top].offset);

    allocator->top--;
}

int main() {
    StackAllocator allocator;
    init(&allocator);

    allocate(&allocator, "a", 4);
    allocate(&allocator, "b", 4);
    allocate(&allocator, "c", 4);

    deallocate(&allocator);
    deallocate(&allocator);
    deallocate(&allocator);

    return 0;
}
