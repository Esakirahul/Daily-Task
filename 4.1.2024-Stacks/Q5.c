//Implement a stack to support increment operation (e.g., increment the bottom k elements by a given value).
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int *arr;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity * sizeof(int));
    return stack;
}

void resizeStack(struct Stack *stack) {
    stack->capacity *= 2;  
    stack->arr = (int*)realloc(stack->arr, stack->capacity * sizeof(int));
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void push(struct Stack *stack, int value) {
    if (stack->top == stack->capacity - 1) {
        resizeStack(stack);  
    }
    stack->arr[++stack->top] = value;
}

int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;  
    }
    return stack->arr[stack->top--];
}

void increment(struct Stack *stack, int k, int value) {
    int limit = (k > stack->top + 1) ? stack->top + 1 : k;  
    for (int i = 0; i < limit; i++) {
        stack->arr[i] += value;
    }
}

void printStack(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    int n, k, incrementValue;
    printf("Enter the number of elements in the stack: ");
    scanf("%d", &n);

    struct Stack *stack = createStack(n);  
    printf("Enter %d elements for the stack:\n", n);
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        push(stack, value);
    }
    printf("Stack before increment: ");
    printStack(stack);
    printf("Enter the number of bottom elements to increment (k): ");
    scanf("%d", &k);
    printf("Enter the increment value: ");
    scanf("%d", &incrementValue);
    increment(stack, k, incrementValue);
    printf("Stack after incrementing bottom %d elements by %d: ", k, incrementValue);
    printStack(stack);
    free(stack->arr);
    free(stack);
}
