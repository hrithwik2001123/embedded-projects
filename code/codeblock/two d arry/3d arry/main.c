#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, c, i, j,k,d;
    printf("Enter number of rows (r): ");
    scanf("%d", &r);
    printf("Enter number of columns (c): ");
    scanf("%d", &c);
     printf("Enter number of depth (d): ");
    scanf("%d", &d);
    int a[r][c][d];

    printf("3 d arry\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            for(k=0; k < d; k++){
            scanf(" %d", &a[i][j][k]);
                }
        }
    }
     for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            for(k=0; k < d; k++){
            printf(" %d", a[i][j][k]);
                }
        }
        printf("\n");
    }

}
