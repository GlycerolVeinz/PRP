#include <stdio.h>

int main(void)
    {
        int x = 1;
        int repetitions = 10;

        for (int i = 0; i < repetitions; ++i)
            {
                printf("%d\n", x);
                x += 1;
            }
        
        x = 1;

        while (x != repetitions + 1)
        {
            printf("%d\n", x);
            x += 1;
        }

        x = 1;

        do 
            {
                printf("%d\n", x);
                x += 1;
            }
            while (x != repetitions + 1);
        
        return 0; 
    }