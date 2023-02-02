#include <stdio.h>

int print_triangle(char symbol, int size)
{
    scanf("%d", &size);
    
    if (&size <= 0)
    {
        fprintf(stderr, "Error: out of range\n");
        return 1;
    }  
    else
    {
        for (int i = size; i > 0; i--)
            {
                for (int j = size; j > 0; j--)
                    {
                        printf("%c",symbol);
                    }
                size -= 1;
                printf("\n");    
            }   
        printf("\n");
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int n;
    print_triangle('X', n);

    return 0;
}
