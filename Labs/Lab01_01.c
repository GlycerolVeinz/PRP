#include <stdio.h>

int main(int argc, char const *argv[])
{
    int r = getchar();
    r = r - '0';
    printf ("r = %d\n", r);
    printf ("argv = %d\n", **argv);
    
    for (int i = 0; i < **argv; ++i)
    {
 
        if (i == 1)
        {
            printf("i=1");
        }

        printf("I like argc!\n");
    }

    for (int i = 0; i < r; ++i)
    {
 
        if (i == 1)
        {
            printf("i=1");
        }

        printf("I like R!\n");
    }

    return 0;
}
