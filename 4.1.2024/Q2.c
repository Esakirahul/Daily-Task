//Use a stack to implement Tower of Hanoi for n disks.
#include <stdio.h>
#include <stdlib.h>

int* createStack(int capacity) {
    return (int*)malloc(capacity * sizeof(int));
}

int isEmpty(int top) {
    return top == -1;
}

void push(int* stack, int* top, int value) {
    stack[++(*top)] = value;
}


int pop(int* stack, int* top) {
    if (isEmpty(*top)) return 0;  
    return stack[(*top)--];
}

void printMove(int disk, char fromRod, char toRod) {
    printf("disk %d rod %c to rod %c\n", disk, fromRod, toRod);
}

void moveBetweenRods(int* src, int* srcTop, int* dest, int* destTop, char srcRod, char destRod) {
    int srcDisk = pop(src, srcTop);
    int destDisk = pop(dest, destTop);

    if (srcDisk == 0) {  
        push(src, srcTop, destDisk);
        printMove(destDisk, destRod, srcRod);
    } else if (destDisk == 0) { 
        push(dest, destTop, srcDisk);
        printMove(srcDisk, srcRod, destRod);
    } else if (srcDisk > destDisk) { 
        push(src, srcTop, srcDisk);
        push(src, srcTop, destDisk);
        printMove(destDisk, destRod, srcRod);
    } else { 
        push(dest, destTop, destDisk);
        push(dest, destTop, srcDisk);
        printMove(srcDisk, srcRod, destRod);
    }
}

void towerOfHanoi(int n) {
    int totalMoves = (1 << n) - 1;  
    int* src = createStack(n);
    int* aux = createStack(n);
    int* dest = createStack(n);

    int srcTop = -1, auxTop = -1, destTop = -1;

    for (int i = n; i >= 1; i--) {
        push(src, &srcTop, i);
    }

    char a = 'A', b = 'B', c = 'C';
    if (n % 2 == 0) {
        char temp = b;
        b = c;
        c = temp;
    }

    for (int i = 1; i <= totalMoves; i++) {
        if (i % 3 == 1) {
            moveBetweenRods(src, &srcTop, dest, &destTop, a, c);
        } else if (i % 3 == 2) {
            moveBetweenRods(src, &srcTop, aux, &auxTop, a, b);
        } else if (i % 3 == 0) {
            moveBetweenRods(aux, &auxTop, dest, &destTop, b, c);
        }
    }
    free(src);
    free(aux);
    free(dest);
}

int main() {
    int n;

    printf("Enter the number of disks: ");
    scanf("%d", &n);

    towerOfHanoi(n);

}
