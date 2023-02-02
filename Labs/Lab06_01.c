#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_NUM
    #define MAX_NUM 10
#endif


void permute(unsigned int n, unsigned int a[n])
{
    for (int i = n; i > 0; i--)
    {
        srand(42);
        int di = rand() % i;
        int tmp = a[di];
        a[di] = a[i-1];
        a[i-1] = tmp;
    }
}


int main(int argc, char const *argv[])
{
    unsigned int n = MAX_NUM;
    unsigned int a[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
    permute(n, a);
    
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
