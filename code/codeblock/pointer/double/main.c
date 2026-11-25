#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

int main()
{
    int a = 10;
    int *ptr = &a;  // Single pointer storing the address of 'a'

    printf("Address stored in ptr: %p\n", (void*)ptr);  // Print the address stored in 'ptr'

    int **qtr = &ptr;  // Double pointer storing the address of 'ptr'

    // Print the address of 'ptr' using *qtr
    printf("Address stored in qtr (which is the address of ptr): %p\n", (void*)*qtr);

    // Print the value of 'a' using **qtr
    printf("Value of a using **qtr: %d\n", **qtr);

    return 0;
}
