//Use a stack to find the largest rectangle in a binary matrix.

#include <stdio.h>
#include <stdlib.h>

int* createStack(int capacity) {
    return (int*)malloc(capacity * sizeof(int));
}

void push(int* stack, int* top, int value) {
    stack[++(*top)] = value;
}

int pop(int* stack, int* top) {
    if (*top == -1) return -1;
    return stack[(*top)--];
}

int peek(int* stack, int top) {
    return stack[top];
}

int largestRectangleInHistogram(int* heights, int n) {
    int* stack = createStack(n);  
    int top = -1;                
    int maxArea = 0;             
    int i = 0;

    while (i < n) {
        if (top == -1 || heights[peek(stack, top)] <= heights[i]) {
            push(stack, &top, i++);
        } else {
            int height = heights[pop(stack, &top)];
            int width = top == -1 ? i : i - peek(stack, top) - 1;
            maxArea = (height * width > maxArea) ? height * width : maxArea;
        }
    }

    while (top != -1) {
        int height = heights[pop(stack, &top)];
        int width = top == -1 ? i : i - peek(stack, top) - 1;
        maxArea = (height * width > maxArea) ? height * width : maxArea;
    }

    free(stack);
    return maxArea;
}

int largestRectangleInBinaryMatrix(int** matrix, int rows, int cols) {
    int* heights = (int*)calloc(cols, sizeof(int));  
    int maxArea = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            heights[j] = (matrix[i][j] == 0) ? 0 : heights[j] + 1;
        }
       
        int currentArea = largestRectangleInHistogram(heights, cols);
        if (currentArea > maxArea) {
            maxArea = currentArea;
        }
    }

    free(heights);
    return maxArea;
}

int main() {
    int rows, cols;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &cols);
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    printf("Enter the binary matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int maxRectangle = largestRectangleInBinaryMatrix(matrix, rows, cols);
    printf("The largest rectangle area is: %d\n", maxRectangle);
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
