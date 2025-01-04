//Find the maximum area of an island in a grid using stacks for Depth First Search (DFS).

#include <stdio.h>
#include <stdlib.h>

int rows, cols;

int isSafe(int **grid, int visited[][rows], int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1 && !visited[x][y]);
}

int dfs(int **grid, int visited[][rows], int x, int y) {
    visited[x][y] = 1;
    int area = 1;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isSafe(grid, visited, newX, newY)) {
            area += dfs(grid, visited, newX, newY);
        }
    }
    return area;
}

int maxAreaOfIsland(int **grid) {
    int maxArea = 0;
    int visited[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                int area = dfs(grid, visited, i, j);
                maxArea = (area > maxArea) ? area : maxArea;
            }
        }
    }
    return maxArea;
}

int main() {
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int **grid = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Enter the grid values (0 for water, 1 for land):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int result = maxAreaOfIsland(grid);
    printf("Maximum area of an island: %d\n", result);
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
