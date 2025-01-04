#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct StackElement {
    char* str;
    int repeat;
};

struct Stack {
    struct StackElement* elements;
    int top;
    int capacity;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->elements = (struct StackElement*)malloc(capacity * sizeof(struct StackElement));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(struct Stack* stack, const char* str, int repeat) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->elements = (struct StackElement*)realloc(stack->elements, stack->capacity * sizeof(struct StackElement));
    }
    stack->top++;
    stack->elements[stack->top].str = strdup(str);
    stack->elements[stack->top].repeat = repeat;
}

struct StackElement pop(struct Stack* stack) {
    if (stack->top == -1) {
        exit(EXIT_FAILURE);
    }
    return stack->elements[stack->top--];
}

char* decodeString(const char* s) {
    struct Stack* stack = createStack(100);
    char* currentStr = strdup("");
    int num = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        } else if (s[i] == '[') {
            push(stack, currentStr, num);
            free(currentStr);
            currentStr = strdup("");
            num = 0;
        } else if (s[i] == ']') {
            struct StackElement top = pop(stack);
            int repeat = top.repeat;
            char* temp = (char*)malloc(strlen(currentStr) * repeat + 1);
            temp[0] = '\0';
            for (int j = 0; j < repeat; j++) {
                strcat(temp, currentStr);
            }
            char* newStr = (char*)malloc(strlen(top.str) + strlen(temp) + 1);
            strcpy(newStr, top.str);
            strcat(newStr, temp);
            free(currentStr);
            free(top.str);
            free(temp);
            currentStr = newStr;
        } else {
            size_t len = strlen(currentStr);
            currentStr = (char*)realloc(currentStr, len + 2);
            currentStr[len] = s[i];
            currentStr[len + 1] = '\0';
        }
    }

    free(stack->elements);
    free(stack);
    return currentStr;
}

int main() {
    char input[100];

    printf("Enter the encoded string: ");
    scanf("%s", input);

    char* decodedString = decodeString(input);
    printf("Decoded string: %s\n", decodedString);

    free(decodedString);
    return 0;
}
