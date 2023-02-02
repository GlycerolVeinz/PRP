#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int size = 10;
    // printf("%d\n", size/3);
    int **arr = malloc(sizeof(int*) * size);

    int a = 1;
    int b = 1;
    int *eight = &a;
    int *nine = &b;

    arr[8] = eight;
    arr[9] = nine;

    size /= 3;
    arr = realloc(arr, sizeof(int*) * size);
    printf("%p\n", arr);
    
    for (int i = 0; i < size; i++)
    {
        printf("%p\n", arr[i]);
    }

    free(arr);
    return 0;
}
