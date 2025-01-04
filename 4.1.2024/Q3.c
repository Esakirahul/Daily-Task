//Solve the Celebrity Problem using stacks.

#include <stdio.h>
#include <stdlib.h>

int knows(int a, int b, int n, int** M) {
    return M[a][b];
}

int findCelebrity(int n, int** M) {
    int left = 0;
    int right = n - 1;

    while (left < right) {
        if (knows(left, right, n, M)) {
            left++;
        } else {
            right--;
        }
    }

    int candidate = left;

    for (int i = 0; i < n; i++) {
        if (i != candidate && (knows(candidate, i, n, M) || !knows(i, candidate, n, M))) {
            return -1;
        }
    }

    return candidate;
}

int main() {
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    int** M = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        M[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &M[i][j]);
        }
    }

    int celebrity = findCelebrity(n, M);
    
    if (celebrity == -1) {
        printf("No celebrity found\n");
    } else {
        printf("The celebrity is person %d\n", celebrity);
    }

    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);

    return 0;
}
