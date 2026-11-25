#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, c, i, j;
    printf("Enter number of rows (r): ");
    scanf("%d", &r);
    printf("Enter number of columns (c): ");
    scanf("%d", &c);
    char a[r][c];
    printf("Enter the characters in the matrix:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf(" %c", &a[i][j]);
        }
    }
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
